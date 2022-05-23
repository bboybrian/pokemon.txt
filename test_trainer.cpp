#include "Trainer.h"

int main()
{
    srand(time(NULL));
    Trainer blank;
    Pokemon pkm;
    pkm.Initialize();
    blank.Initialize();
    opponent ash = opponent("Ash");
    player player;

    if (ash.name == "Ash" && blank.name == "A strange man" && player.name == "A new challenger") {
        cout << "1. Construction successful\n";
    }

    ash.generate_inv(1);
    int pots = ash.pots.amount;
    ash.use_pot();
    cout << "^ Here Pokemon faints because blank Pokemon object has 0 HP\n";

    if (pots != 0 && (pots - ash.pots.amount == 1)) {
        cout << "2. generate_inv() & use_pot() successful\n";
    }

    ash.size = 3;
    for (int i = 0; i < 3; i++) {
        int ID = rand() % 693;
        ash.team[i] = blank.pokedex[ID];
        ash.team[i].set_level(10);
    }

    if (ash.team[0].level == 10 && ash.team[1].level == 10 && ash.team[2].level == 10 && ash.team[3].level == 0) {
        cout << "3. Team generation successful\n";
    }

    Pokemon squirtle = Pokemon("Squirtle",1,"Water","-",44,48,65,63);
    squirtle.set_level(5);
    Pokemon bulbasaur = Pokemon("Bulbasaur",2,"Grass","Poison",45,49,49,45);
    bulbasaur.set_level(7);
    player.set_team(squirtle);
    player.set_team(bulbasaur);

    if (player.currentSN == 2 && player.team[1].name == "Bulbasaur") {
        cout << "4. Player catch pokemon successful\n";
    }

    player.release(1);
    if (player.currentSN == 1 && player.team[1].name == "?") {
        cout << "5. Player release pokemon successful\n";
    }
}