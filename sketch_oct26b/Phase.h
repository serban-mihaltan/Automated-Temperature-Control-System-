#ifndef PHASE_H
#define PHASE_H

class Phase
{
private:
    int state;
    char symbol;

public:
    Phase(int state = 0, char symbol = '/');
    void select();
    void incalzire();
    void racire();
    void mentinere();
    char get_symbol();
    void setphase(int i);
};

#endif // PHASE_H
