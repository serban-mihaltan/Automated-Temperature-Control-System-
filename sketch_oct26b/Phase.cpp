#include "Phase.h"
#include "Time.h"  // Include necessary headers if needed, like Time.h or PID.h
#include "PID.h"

extern LiquidCrystal lcd_1;
extern float TEMP;
extern float TEMPACT;
extern float KP, KI, KD;
extern float lasterror;
extern Time TI, TM, TR, TRAMAS;

// Constructor
Phase::Phase(int state, char symbol)
{
    this->state = state;
    this->symbol = symbol;
}

// Function to determine the current state of the system
void Phase::select()
{
    switch (state)
    {
    case 0:
        this->incalzire();
        break;
    case 1:
        this->mentinere();
        break;
    case 2:
        this->racire();
        break; // Don't forget to include this 'break' statement
    default:
        break;
    }
}

// Heating function
void Phase::incalzire()
{   
    //TEMPACT*=0.82;//compensare 
    PID();  // Adjust temperature
    if (TRAMAS.time_is_null())
    {
        this->state = 1;
        this->symbol = '-';
        TRAMAS = TM; // Set TRAMAS to TM when heating is done
    }
}

// Cooling function
void Phase::racire()
{
    OCR2A = 0;  // Adjust temperature
    if (TRAMAS.time_is_null())
    {
        this->state = 0;
        this->symbol = '/';
        TRAMAS = TI; // Set TRAMAS to TI when cooling is done
    }
}

// Maintenance function
void Phase::mentinere()
{ 
    //  TEMPACT*=0.82;//compensare
    PID();  // Adjust temperature
    if (TRAMAS.time_is_null())
    {
        this->state = 2;
        this->symbol = '\\';
        TRAMAS = TR; // Set TRAMAS to TR when maintaining
    }
}

// Return the symbol representing the current state of the system
char Phase::get_symbol()
{
    return this->symbol;
}

// Set the system state based on an integer input
void Phase::setphase(int i)
{
    switch (i)
    {
    case 0:
        this->state = 0;
        this->symbol = '/';
        TRAMAS = TI; // Set TRAMAS to TI
        break;
    case 1:
        this->state = 1;
        this->symbol = '-';
        TRAMAS = TM; // Set TRAMAS to TM
        break;
    case 2:
        this->state = 2;
        this->symbol = '\\';
        TRAMAS = TR; // Set TRAMAS to TR
        break;
    default:
        break;
    }
}
