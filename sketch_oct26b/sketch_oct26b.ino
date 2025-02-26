#include <EEPROM.h>
#include <LiquidCrystal.h>
#include "Time.h"
#include "PID.h"
#include "Menu.h"
#include "Phase.h"
#define TP35_SENSOR_CHANNEL 0 // Setare pin senzor de temp A0
#define ADC_REF_VOLTAGE 5.0   // Setare tensiune de referinta 5V

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Salvarea parametrilor dupa fiecare modificare(clasa Menu) fct x1
// TEMP,TI,TM,TR,KP,KI,KD

LiquidCrystal lcd_1(12, 9, 5, 4, 3, 2);

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Declararea variabilelor globale
Time TI, TM, TR, TRAMAS;
float TEMP = 0, TEMPACT;
int perturb = 0;
float KI = 0, KP = 0, KD = 0, lasterror;
Phase phase;
Menu menu;


void init_adc()
{
    ADMUX |= (1 << REFS0);                                 // Setare tensiune de alimentare ca tensiune de referinta ADC   
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Setare prescaler clock ADC la 128
    ADCSRA |= (1 << ADEN);                               // Enable ADC
}

float read_temperature() // Functie de citire a datelor din ADC
{
    ADMUX &= 0xF0;                  // Setarea pinilor din ADMUX pentru citire
    ADMUX |= TP35_SENSOR_CHANNEL;  // Setarea pinului la care este legat senzorul de temperatura (A0)
    ADCSRA |= (1 << ADSC);        // Start conversie ADC
    while (ADCSRA & (1 << ADSC)) // Asteptare finalizat conversie ADC
    {}

    uint16_t adc_value = ADC;                                     // Calculul temperaturii folosind rezultatul de la ADC
    
    //Serial.println(adc_value);
    float voltage = (float)adc_value * ADC_REF_VOLTAGE / 1024.0; // Transformare valoare analogica in tensiune
    float temperature = voltage * 100.0;                         // Transformare tensiune in grade celsius (fara offset)
    return temperature;
}

void setup()
{
    lcd_1.begin(16, 2); // Configurare numar linii si coloane pe LCD
    init_adc();
    // aici ar tb citite din memoria NEVOLATILA parameti
    // TEMP,TI,TM,TR,KP,KI,KD
    Time t(1, 0, 0);

    int adress = 0;

    EEPROM.get(adress, TEMP);
    adress += sizeof(TEMP);

    EEPROM.get(adress, TI);
    adress += sizeof(TI);
    EEPROM.get(adress, TM);
    adress += sizeof(TM);
    EEPROM.get(adress, TR);
    adress += sizeof(TR);

    EEPROM.get(adress, KP);
    adress += sizeof(KP);
    EEPROM.get(adress, KI);
    adress += sizeof(KI);
    EEPROM.get(adress, KD);
    adress += sizeof(KD);

    //TRAMAS = TI = TM = TR = t;  // Variabile folosite pentru simulare
    //TEMP = 50;
    //KP=2.0;
    //KI=5.0;
    //KD=1.0;
    //menu.select();
    phase.setphase(0);
    randomSeed(analogRead(0)); // folosim random nu rand(nu mai schimb tot codul)

    DDRB |= (1 << DDB3); // Setare pin 9 (PB1) drept output

    // Setare Timer 2 in modul de functionare Fast PWM mode pe pinul 9 (PB1) fara prescaler
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (1 << CS20) | (1 << CS20);                          

     // Setare Timer in modul de functionare normal
    // TCCR1A pentru Timer 1
    TCCR1A = 0;

     // Timer-ul are un prescaler de 1024 care se seteaza folosind bitii de tip CS
    // TCCR1B pentru Timer 1
    TCCR1B = (1 << CS12) | (1 << CS10);
    Serial.begin(9600);
}

void loop()
{
    if (TCNT1 > 15625) // Valoarea incrementata de timer TCNT(0,1,2) si numarul de evenimente intr-o secunda
    {
        lcd_1.clear();
        TRAMAS--;
        TEMPACT = read_temperature();
        if (PINC & 1 << 5)
        {
            perturb = perturb ^ 1; // adaugare perturbatii
        }
        TEMPACT += (float)random(-10, 10) / 5 * perturb;
        Serial.println(TEMPACT);
        phase.select();
        menu.select();
        TCNT1 = 0; // Resetare variabila timer
       // delay(1000);
    }
}