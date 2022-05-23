#include "Attack.h"

using namespace std;

Attack::Attack()
{
    name = "MissingNo.";
    power = 0;
    maxPP = 0;
    PP = 0;
    accuracy = 0;
    type = "-";
}

Attack::Attack(string aName, string aType, int aPower, int aAccuracy, int aPP)
{
    name = aName;
    power = aPower;
    maxPP = aPP;
    PP = maxPP;
    accuracy = aAccuracy;
    type = aType;
}

void Attack::set_type(string aType)
{
    type = aType;
}

void Attack::set_name(string aName)
{
    name = aName;
}

void Attack::set_stats(int aPower, int aAccuracy, int aPP)
{
    power = aPower;
    maxPP = aPP;
    PP = maxPP;
    accuracy = aAccuracy;
}

void Attack::restore_PP()
{
    PP = maxPP;
}

void Attack::print_attk()
{
    cout << "Attack:\t\t" << name << endl;
    cout << "Type:\t\t" << type << endl;
    cout << "Power:\t\t" << power << endl;
    cout << "Power Points:\t" << PP << "/" << maxPP << endl;
    cout << "Accuracy:\t" << accuracy << endl << endl;
}

void Attack::print_small()
{
    cout << name;
    if (name.length() < 5) {
        cout << "\t\t\t(" << type << ")";
    } else if (name.length() < 13) {
        cout << "\t\t(" << type << ")";
    } else {
        cout << "\t(" << type << ")";
    }
    if (type.length() < 6) {
        cout << "\t\t" << PP << "/" << maxPP << "\tPP\t🎯 " << accuracy << endl;
    } else {
        cout << "\t" << PP << "/" << maxPP << "\tPP\t🎯 " << accuracy << endl;
    }
}