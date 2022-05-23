#ifndef ATTACK_H
#define ATTACK_H

#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

class Attack
{
public:
    Attack();
    Attack(string aName, string aType, int aPower, int aAccuracy, int aPP);
    void set_type(string aType);
    void set_name(string aName);
    void set_stats(int aPower, int aAccuracy, int aPP);
    void restore_PP();
    void print_attk();
    void print_small();

    string name,type;
    int power,PP,maxPP,accuracy;
};
#endif