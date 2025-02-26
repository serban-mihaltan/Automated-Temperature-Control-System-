#include "Time.h"
#include <LiquidCrystal.h>
extern LiquidCrystal lcd_1;

// Constructor
Time::Time(int seconds, int minutes, int hours)
    : seconds(seconds), minutes(minutes), hours(hours) {}

int Time::time_is_null() {
    return (this->seconds == 0 && this->minutes == 0 && this->hours == 0) ? 1 : 0;
}

void Time::display_time(int x, int y) {
    lcd_1.setCursor(x, y);
    if (this->hours < 10) lcd_1.print('0');
    lcd_1.print(this->hours);
    lcd_1.print(":");

    if (this->minutes < 10) lcd_1.print('0');
    lcd_1.print(this->minutes);
    lcd_1.print(":");

    if (this->seconds < 10) lcd_1.print('0');
    lcd_1.print(this->seconds);
}

void Time::update_time() {
    if (!this->time_is_null()) {
        if (this->seconds >= 60) {
            this->seconds = 0;
            this->minutes++;
            if (this->minutes >= 60) {
                this->minutes = 0;
                this->hours++;
            }
        }

        if (this->seconds < 0) {
            this->seconds = 59;
            this->minutes--;
            if (this->minutes < 0) {
                this->minutes = 59;
                this->hours--;
            }
        }
    }
}

Time Time::operator=(const Time &t) {
    this->seconds = t.seconds;
    this->minutes = t.minutes;
    this->hours = t.hours;
    this->update_time();
    return *this;
}

Time &Time::operator++() {
    this->seconds++;
    this->update_time();
    return *this;
}

Time Time::operator++(int) {
    Time t = *this; // Salvează starea curentă
    this->seconds++;
    this->update_time();
    return t; // Returnează starea salvată
}

Time &Time::operator--() {
    if (!this->time_is_null()) this->seconds--;
    this->update_time();
    return *this;
}

Time Time::operator--(int) {
    Time t = *this; // Salvează starea curentă
    if (!this->time_is_null()) this->seconds--;
    this->update_time();
    return t; // Returnează starea salvată
}

int Time::total_seconds() {
    return hours * 3600 + minutes * 60 + seconds;
}
