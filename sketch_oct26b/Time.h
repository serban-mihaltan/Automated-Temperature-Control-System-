#ifndef TIME_H
#define TIME_H

#include <LiquidCrystal.h>

class Time {
public:
    int seconds, minutes, hours;

    // Constructor
    Time(int seconds = 0, int minutes = 0, int hours = 0);

    // Metode
    int time_is_null();
    void display_time(int x, int y);
    void update_time();
    int total_seconds();

    // Operator de asignare
    Time operator=(const Time &t);

    // Operatori de incrementare
    Time &operator++();
    Time operator++(int);
    
    // Operatori de decrementare
    Time &operator--();
    Time operator--(int);
};

#endif // TIME_H
