#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
using namespace std;

class Item
{
public:
    virtual void use_item();
    int buy_item(int amt, int money);
    virtual void upgrade_item();
    void set_amount(int amt);
    void print_item();

    string name,description;
    int cost,potency,amount,level;
};

class Pokeball: public Item
{
public:
    Pokeball();
    virtual void upgrade_item();
};

class Potion: public Item
{
public:
    Potion();
    virtual void upgrade_item();
};

class TM: public Item
{
public:
    TM();
};
#endif