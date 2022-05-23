#include "Item.h"

using namespace std;

void Item::print_item()
{
    if (name.size() > 7)
    {
        cout << amount << "\t" << name << "\t\t" << description << endl;
    } else
    {
        cout << amount << "\t" << name << "\t\t\t" << description << endl;
    }
}

void Item::upgrade_item()
{
}

int Item::buy_item(int amt, int money)
{
    int tcost = cost * amt;
    if (tcost > money)
    {
        cout << "Not enough money! You have: " << money << endl << endl;
        return 0;
    } else {
        amount = amount + amt;
        return tcost;
    }
}


void Item::set_amount(int amt)
{
    amount = amt;
}

void Item::use_item()
{
    if (amount > 0)
    {
        amount--;
    }
}

Pokeball::Pokeball()
{
    name = "Pokeball";
    description = "A round device used to catch and contain Pokémon.";
    cost = 200;
    potency = 10;
    amount = 5;
    level = 1;
}

void Pokeball::upgrade_item()
{
    level++;
    string names[3] = {"Great Ball","Ultra Ball","Heal Ball"};
    string descriptions[3] = {"1.5x the catch rate of a Pokeball.","1.5x the catch rate of a Pokeball.","Fully restores HP & PP of caught Pokemon."};
    int potencies[3] = {15,20,10};
    name = names[level - 2];
    description = descriptions[level - 2];
    potency = potencies[level - 2];
}

Potion::Potion()
{
    name = "Potion";
    description = "Restores a Pokemon by 20HP.";
    cost = 300;
    potency = 20;
    amount = 0;
    level = 1;
}

void Potion::upgrade_item()
{
    level++;
    string names[3] = {"Super Potion","Hyper Potion","Max Potion"};
    string descriptions[3] = {"Restores a Pokemon by 50HP.","Restores a Pokemon by 200HP.","Restores all of a Pokemon's HP."};
    int potencies[3] = {50,200,1000};
    name = names[level - 2];
    description = descriptions[level - 2];
    potency = potencies[level - 2];
}

TM::TM()
{
    name = "TM";
    description = "Teaches a Pokemon a new move, based on its type.";
    cost = 500;
    potency = 1000;
    amount = 0;
    level = 1;
}