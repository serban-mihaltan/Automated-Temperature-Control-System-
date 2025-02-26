#include "PID.h"
#include "Time.h"

extern float TEMP;
extern float                                                                                                               TEMPACT;
extern float KP, KI, KD;
extern float lasterror;
extern Time TI, TM, TR, TRAMAS;

void PID()
{
    Time TDelta(10, 1, 0); // Timpul de incalzire pana la TMAX
    int TEMPDelta = 20;//in 50 de secunde se incalzeste de la 28 la 53 de grade
    //!!!!!!!!!!!!!!
    // tb aflate din hard

    int output;
    float error;          // Eroare calculata ca diferenta dintre input si setpoint
    float integral;      // Termenul integrator
    float derivative;   // Termenul derivator

    error = TEMP - TEMPACT;
    if (error > 0)
    {
        float proportional = KP * error;                  // Termenul proportional
        integral += error * KI;                          // Termenul integrator
        derivative = (error - lasterror) * KD;          // Termenul derivator
        output = proportional + integral + derivative; // Output PID
        lasterror = error;
        OCR2A = ((output * TDelta.total_seconds()) / (TEMPDelta * TRAMAS.total_seconds())) * 255;
        //(output/tramas)/(TEMPDelta/TDelta)*255
        //daca in TDelta s-a incalzit cu TempDelta la 255(un factor de umplere de unu) at se va incalzi cu output in  de TRAMAS la un factor de umplere de x/255
    }
    else OCR2A = 0;
}