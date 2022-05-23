#include "Pokemon.h"

int main()
{
    srand(time(NULL));
    Pokemon blank;
    blank.Initialize();
    Pokemon squirtle = Pokemon("Squirtle",1,"Water","-",44,48,65,63);
    squirtle.set_level(5);
    if (blank.name == "?" && squirtle.name == "Squirtle" && squirtle.maxHP == 54) {
        cout << "Pokemon construction successful\n";
    }

    tamePokemon starter = tamePokemon(squirtle);
    if (starter.maxHP == 54) {
        cout << "tamePokemon construction successful\n";
    }

    cout << "Test use_attk and change_hp()\n";
    Pokemon bulbasaur = Pokemon("Bulbasaur",2,"Grass","Poison",45,49,49,45);
    bulbasaur.set_level(7);
    bulbasaur.use_attk(bulbasaur.attacks[0], starter);

    cout << "Test learning a new attack - when player uses TM\n";
    starter.new_attk(2,"Normal");
    if (starter.attacks[2].type == "Normal") {
        cout << "new_attk successful\n";
    }

    cout << "Test print_pkm()\n";
    bulbasaur.print_pkm();
    starter.print_pkm();

    starter.add_xp(1000);
    if (starter.xpToLevel > 1000) {
        cout << "add_xp(int aXP) successful\n";
    }

    cout << "Test print_small()\n";
    bulbasaur.print_small();
    starter.print_small();
}