#ifndef TRAINER_H
#define TRAINER_H

#include "Pokemon.h"
#include "Item.h"
using namespace std;

class Trainer
{
public:
    Trainer();
    void Initialize();
    void set_name(string aName);
    void print_team();
    virtual void use_pot();
    virtual void turn();

    Potion pots;
    string name;
    static Pokemon *pokedex;
    int currentOut;
    tamePokemon team[6];
};

class opponent: public Trainer
{
public:
    opponent(string aName);
    void generate_inv(int avg_level);
    virtual void use_pot();
    virtual void turn(Pokemon& defender);

    int size;
};

class player: public Trainer
{
public:
    player();
    void set_team(Pokemon aPkm);
    void release(int aPkm);
    int avg_level();
    void print_inv();
    int use_pkball(Pokemon wildpkm);
    int which_pkm();
    void use_TM();
    virtual void use_pot();
    void change_money(int change);
    virtual int turn(Pokemon& encounter, int pvp);
    void took_part();
    void calc_xp(Pokemon defeated);
    void participate();
    void resetPtcp();
    int check_faint();
    void pokemart();

    static int participant[6];
    static int currentSN;
    Pokeball balls;
    TM discs;
    int money;
};
#endif