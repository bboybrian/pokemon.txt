#ifndef POKEMON_H
#define POKEMON_H

#include "Attack.h"
#include <cmath>
using namespace std;

class Pokemon
{
public:
    Pokemon();
    Pokemon(string aSpecies, int numberOfTypes, string aType1, string aType2, int aHP, int aAtk, int aDef, int aSpd);
    void Initialize();
    void set_level(int aLevel);
    void use_attk(Attack attk, Pokemon& defender);
    int change_hp(float ahp, float modifier);
    void print_small();
    virtual void print_pkm();
    ~Pokemon();

    string species,name;
    string typing[2] = {"?","?"};
    Attack attacks[4] = {Attack(),Attack(),Attack(),Attack()};
    int types,level,maxHP,currentHP,atk,def,spd,xp,xpToLevel;
    static Attack **all_attacks;
};

class tamePokemon: public Pokemon
{
public:
    tamePokemon();
    tamePokemon(Pokemon aPokemon);
    ~tamePokemon();
    void new_attk(int choice, string aType);
    void add_xp(int axp);
    void set_name(string aName);
    virtual void print_pkm();
};
#endif