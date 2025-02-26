#ifndef MENU_H
#define MENU_H

#include <EEPROM.h>
#include <LiquidCrystal.h> // Assuming you are using a LiquidCrystal library
#include "Time.h"         // Include the Time class if necessary
#include "Phase.h"

extern Phase phase;

class Menu // Meniul de selectie si modificare a parametriilor
{
private:
    int temp;
    float ki, kd, kp;
    Time ti, tm, tr;

public:
    int state;
    Menu();
    void select();

private:
    void base_mode();
    void mode1();
    void mode2();
    void mode3();
    void mode4();
    void mode5();
    void mode6();
    void mode7();
    void mode11(); // set Temp
    void mode21(); // set timp incalzire
    void mode31(); // set timp mentinere
    void mode41(); // set timp racire
    void mode51(); // set KP
    void mode61(); // set KI
    void mode71(); // set KD
};

#endif // MENU_H
