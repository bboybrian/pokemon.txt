#include "Trainer.h"

int main()
{
    srand(time(NULL));
    Pokemon pkm;
    Trainer trn;
    pkm.Initialize();
    trn.Initialize();

    // Setup Phase
    player player;
    string name;
    int input;
    cout << "\nEnter a name:\n";
    getline(cin,name);
    if (name == "") {
        name = "Kiddo";
    }
    player.set_name(name);

    Pokemon starters[3] = {trn.pokedex[577],trn.pokedex[65],trn.pokedex[84]};
    cout << "\nChoose a Starter:\n";
    for (int i = 0; i < 3; i++) {
        starters[i].set_level(5);
        starters[i].print_pkm();
    }
    do {
        cout << "[ 1 / 2 / 3 ]\n";
        cin >> input;
        if (!cin) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(256,'\n');
        }
        cout << endl;
    } while (input != 1 && input != 2 && input != 3);
    player.set_team(starters[input - 1]);
    cout << "Name your " << player.team[0].species << ":\n";
    cin.get();
    getline(cin,name);
    if (name == "") {
        name = player.team[0].species;
    }
    cout << endl;
    player.team[0].set_name(name);
    player.print_team();
    player.print_inv();
    // End of setup phase


    int cycle = 1;
    while (cycle < 11) {
        cout << "🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲         CYCLE " << cycle << "         🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲\n\n";
        player.change_money(2000);



        // Prep phase
        bool next = 0;
        cout << "⏩        Prep Phase        ⏩\n";
        while (next == 0) {
            do {
                cout << "1: Use Items\n2: Visit Poke Mart\n3: Release Pokemon\n4: Next Phase\n";
                cin >> input;
                if (!cin) {
                    cout << "Invalid input!\n";
                    cin.clear();
                    cin.ignore(256,'\n');
                }
                cout << endl;
            } while (input != 1 && input != 2 && input != 3 && input != 4);
            switch (input) {
                case 1:
                    do {
                        cout << "1: Use " << player.pots.name << endl;
                        cout << "2: Use TM\n";
                        cin >> input;
                        if (!cin) {
                            cout << "Invalid input!\n";
                            cin.clear();
                            cin.ignore(256,'\n');
                        }
                        cout << endl;
                    } while (input != 1 && input != 2);
                    switch(input) {
                        case 1:
                            player.use_pot();
                            break;
                        case 2:
                            player.use_TM();
                            break;
                    }
                    player.print_inv();
                    break;
                case 2:
                    player.pokemart();
                    player.print_inv();
                    break;
                case 3:
                    if (player.currentSN <= 1) {
                        cout << "You cannot release your only Pokemon!\n";
                    } else
                    {
                        input = player.which_pkm();
                        player.release(input);
                    }
                    break;
                case 4:
                    next = 1;
                    break;
            }
            cout << "Proceed to Upgrade phase? [1/0]\n";
            cin >> next;
            if (!cin) {
                next = 0;
                cout << "Invalid input!\n";
                cin.clear();
                cin.ignore(256,'\n');
            }
            cout << endl;
        }
        next = 0;
        // End of prep phase

        // Upgrade Phase
        cout << "⏩       Perk Selction Phase        ⏩\n\n";
        do {
            cout << "💎        Perks        💎\n";
            do {
                cout << "1: Upgrade Pokeballs\n2: Upgrade Potions \n3: Level up a Pokemon\n";
                cin >> input;
                if (!cin) {
                    cout << "Invalid input!\n";
                    cin.clear();
                    cin.ignore(256,'\n');
                }
                cout << endl;
            } while (input != 1 && input != 2 && input != 3);
            switch (input) {
                case 1:
                    cout << "You have chosen: Upgrade Pokeballs\n";
                    if (player.balls.level == 4) {
                        cout << "Pokeballs cannot be upgraded further!\n";
                        break;
                    } else {
                        player.balls.upgrade_item();
                        next = 1;
                    }
                    break;
                case 2:
                    cout << "You have chosen: Upgrade Potions\n";
                    if (player.pots.level == 4) {
                        cout << "Potions cannot be upgraded further!\n";
                        break;
                    } else {
                        player.pots.upgrade_item();
                        next = 1;
                    }
                    break;
                case 3:
                    cout << "You have chosen: Level up a Pokemon\n";
                    input = player.which_pkm();
                    if (player.team[input].level == 100) {
                        cout << player.team[input].level << " cannot be levelled further!\n";
                        break;
                    } else {
                        player.team[input].add_xp(player.team[input].xpToLevel - player.team[input].xp);
                        next = 1;
                    }
            }
        } while (next == 0);
        // End of Upgrade phase



        cycle++;
        cout << "NAME\tCOST\tPOTENCY\tLEVEL\n";
        cout << player.pots.name << "\t" << player.pots.cost << "\t" << player.pots.potency << "\t" << player.pots.level << endl;
        cout << player.balls.name << "\t" << player.balls.cost << "\t" << player.balls.potency << "\t" << player.balls.level << endl;
    } // <- Close bracket for while(cycle < 11)
}