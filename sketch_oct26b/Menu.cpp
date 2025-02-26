#include "Menu.h"
#include "Time.h"
#include "Phase.h"

extern LiquidCrystal lcd_1;
extern float TEMP;
extern float TEMPACT;
extern float KP, KI, KD;
extern float lasterror;
extern Time TI, TM, TR, TRAMAS;

Menu::Menu()
{
    this->state = 0;
}

void Menu::select()
{
    switch (state)
    {
        case 0: // default
            this->base_mode();
            break;
        case 1:
            this->mode1();
            break;
        case 2:
            this->mode2();
            break;
        case 3:
            this->mode3();
            break;
        case 4:
            this->mode4();
            break;
        case 5:
            this->mode5();
            break;
        case 6:
            this->mode6();
            break;
        case 7:
            this->mode7();
            break;
        case 11: // set T
            this->mode11();
            break;
        case 21: // set ti
            this->mode21();
            break;
        case 31: // set tm
            this->mode31();
            break;
        case 41: // set tr
            this->mode41();
            break;
        case 51: // set kp
            this->mode51();
            break;
        case 61: // set ki
            this->mode61();
            break;
        case 71: // set kd
            this->mode71();
            break;
        default:
            break;
    }
}

void Menu::base_mode()
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("TA: ");
    lcd_1.setCursor(3, 0);
    lcd_1.print(TEMPACT);
    lcd_1.setCursor(9, 0);
    lcd_1.print("T: ");
    lcd_1.setCursor(11, 0);
    lcd_1.print(TEMP);
    TRAMAS.display_time(0, 1);
    lcd_1.setCursor(11, 1);
    lcd_1.print(phase.get_symbol());
    if (PINC & 1 << 4) this->state = 1;
}

void Menu::mode1()
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Set temperature");
    temp = TEMP;
    if (PINC & 1 << 4)
        this->state = 11;
    else if (PINC & 1 << 3)
        this->state = 0;
    else if (PINC & 1 << 2)
        this->state = 7;
    else if (PINC & 1 << 1)
        this->state = 2;
}

void Menu::mode2()
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Set tincalzire");
    ti = TI;
    if (PINC & 1 << 4)
        this->state = 21;
    else if (PINC & 1 << 3)
        this->state = 0;
    else if (PINC & 1 << 2)
        this->state = 1;
    else if (PINC & 1 << 1)
        this->state = 3;
}

void Menu::mode3()
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Set tmentinere");
    tm = TM;
    if (PINC & 1 << 4)
        this->state = 31;
    else if (PINC & 1 << 3)
        this->state = 0;
    else if (PINC & 1 << 2)
        this->state = 2;
    else if (PINC & 1 << 1)
        this->state = 4;
}

void Menu::mode4()
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Set tracire");
    tr = TR;
    if (PINC & 1 << 4)
        this->state = 41;
    else if (PINC & 1 << 3)
        this->state = 0;
    else if (PINC & 1 << 2)
        this->state = 3;
    else if (PINC & 1 << 1)
        this->state = 5;
}

void Menu::mode5()
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Set KP");
    kp = KP;
    if (PINC & 1 << 4)
        this->state = 51;
    else if (PINC & 1 << 3)
        this->state = 0;
    else if (PINC & 1 << 2)
        this->state = 4;
    else if (PINC & 1 << 1)
        this->state = 6;
}

void Menu::mode6()
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Set KI");
    ki = KI;
    if (PINC & 1 << 4)
        this->state = 61;
    else if (PINC & 1 << 3)
        this->state = 0;
    else if (PINC & 1 << 2)
        this->state = 5;
    else if (PINC & 1 << 1)
        this->state = 7;
}

void Menu::mode7()
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Set KD");
    kd = KD;
    if (PINC & 1 << 4)
        this->state = 71;
    else if (PINC & 1 << 3)
        this->state = 0;
    else if (PINC & 1 << 2)
        this->state = 6;
    else if (PINC & 1 << 1)
        this->state = 1;
}

void Menu::mode11() // set Temp
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Temp: ");
    lcd_1.setCursor(0, 1);
    lcd_1.print(temp);
    if (PINC & 1 << 4)
    {
        this->state = 1;
        TEMP = temp;
        EEPROM.put(0, TEMP);
        //!!!!!!!!!!!!!!!!!!!
    }
    else if (PINC & 1 << 3)
        this->state = 1;
    else if (PINC & 1 << 2)
        temp--;
    else if (PINC & 1 << 1)
        temp++;
}

void Menu::mode21()   // set timp incalzire
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Timp Incalzire: ");
    ti.display_time(0, 1);
    if (PINC & 1 << 4)
    {
        this->state = 2;
        TI = ti;
        //!!!!
        EEPROM.put(0 + sizeof(TEMP), TI);
    }
    else if (PINC & 1 << 3)
        this->state = 2;
    else if (PINC & 1 << 2)
        ti--;
    else if (PINC & 1 << 1)
        ti++;
}

void Menu::mode31() // set timp mentinere
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Timp mentinere: ");
    lcd_1.setCursor(0, 1);
    tm.display_time(0, 1);
    if (PINC & 1 << 4)
    {
        this->state = 3;
        TM = tm;
        //!!!!
        EEPROM.put(0 + sizeof(TEMP) + sizeof(TI), TM);
    }
    else if (PINC & 1 << 3)
        this->state = 3;
    else if (PINC & 1 << 2)
        tm--;
    else if (PINC & 1 << 1)
        tm++;
}

void Menu::mode41()  // set timp racire
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("Timp racire: ");
    lcd_1.setCursor(0, 1);
    tr.display_time(0, 1);
    if (PINC & 1 << 4)
    {
        this->state = 4;
        TR = tr;
        //!!!!
        EEPROM.put(0 + sizeof(TEMP) + sizeof(TI) + sizeof(TM), TR);
    }
    else if (PINC & 1 << 3)
        this->state = 4;
    else if (PINC & 1 << 2)
        tr--;
    else if (PINC & 1 << 1)
        tr++;
}

void Menu::mode51()   // set KP
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("KP: ");
    lcd_1.setCursor(0, 1);
    lcd_1.print(kp);
    if (PINC & 1 << 4)
    {
        this->state = 5;
        KP = kp;
        //!!!!
        EEPROM.put(0 + sizeof(TEMP) + sizeof(TI) + sizeof(TM) + sizeof(TR), KP);
    }
    else if (PINC & 1 << 3)
        this->state = 5;
    else if (PINC & 1 << 2)
        kp -= 0.1;
    else if (PINC & 1 << 1)
        kp += 0.1;
}

void Menu::mode61() // set KI
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("KI: ");
    lcd_1.setCursor(0, 1);
    lcd_1.print(ki);
    if (PINC & 1 << 4)
    {
        this->state = 6;
        KI = ki;
        //!!!!
        EEPROM.put(0 + sizeof(TEMP) + sizeof(TI) + sizeof(TM) + sizeof(TR) + sizeof(KP), KI);
    }
    else if (PINC & 1 << 3)
        this->state = 6;
    else if (PINC & 1 << 2)
        ki -= 0.1;
    else if (PINC & 1 << 1)
        ki += 0.1;
}

void Menu::mode71() // set KD
{
    lcd_1.setCursor(0, 0);
    lcd_1.print("KD: ");
    lcd_1.setCursor(0, 1);
    lcd_1.print(kd);
    if (PINC & 1 << 4)
    {
        this->state = 7;
        KD = kd;
        //!!!!
        EEPROM.put(0 + sizeof(TEMP) + sizeof(TI) + sizeof(TM) + sizeof(TR) + sizeof(KP) + sizeof(KI), KD);
    }
    else if (PINC & 1 << 3)
        this->state = 7;
    else if (PINC & 1 << 2)
        kd -= 0.1;
    else if (PINC & 1 << 1)
        kd += 0.1;
}
