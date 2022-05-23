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
    cin >> name;
    player.set_name(name);

    Pokemon starters[3] = {trn.pokedex[577],trn.pokedex[65],trn.pokedex[84]};
    cout << "\nChoose a Starter:\n";
    for (int i = 0; i < 3; i++) {
        starters[i].set_level(5);
        starters[i].print_pkm();
    }
    cout << "[ 1 / 2 / 3 ]\n";
    cin >> input;
    cout << endl;
    player.set_team(starters[input - 1]);
    player.print_team();
    player.print_inv();
    // End of setup phase


    int cycle = 1;
    while (cycle > 0) {
        cout << "🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲         CYCLE " << cycle << "         🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲 🚲\n\n";



        // Prep phase
        bool next = 0;
        cout << "⏩        Prep Phase        ⏩\n";
        while (next == 0) {
            cout << "1: Use Items\n2: Visit Poke Mart\n3: Release Pokemon\n4: Next Phase\n";
            cin >> input;
            cout << endl;
            switch (input) {
                case 1:
                    cout << "1: Use " << player.pots.name << endl;
                    cout << "2: Use TM\n";
                    cin >> input;
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
                default:
                    cout << "Invalid input!\n";
            }
            cout << "Proceed to encounter phase? [1/0]\n";
            cin >> next;
            cout << endl;
        }
        next = 0;
        // End of prep phase



        // Encounter phase
        cout << "⏩       Encounter Phase        ⏩\n\n";
        int enclvl, win;
        for (int i = 0; i < 10; i++) {
            win = 0;
            player.resetPtcp();
            Pokemon encounter = trn.pokedex[rand()%693];
            enclvl = ceil(rand()%(player.avg_level()/2 + 5));
            enclvl = min(enclvl,100);
            enclvl = max(enclvl,1);
            encounter.set_level(enclvl);
            cout << "⚔️   A wild " << encounter.species << " appears!   ⚔️\n";
            cout << "Go, " << player.team[0].name << "!\n";
            player.currentOut = 0;
            player.participate();
            //1 encounter
            while (win == 0) {
                //1 round of combat
                encounter.print_pkm();
                player.team[player.currentOut].print_pkm();
                player.participate();
                if (player.team[player.currentOut].spd >= encounter.spd) {
                    do {
                        win = player.turn(encounter,0);
                    } while (win == -3);
                    cout << "(TEST) WIN1: " << win << endl;
                    if (win != 0) {
                        break;
                    }
                    encounter.use_attk(encounter.attacks[rand()%4],player.team[player.currentOut]);
                    win = player.check_faint();
                    //cout << "CURRENTHP: " << player.team[player.currentOut].currentHP << endl;
                    cout << "(TEST) WIN2: " << win << endl;
                } else {
                    encounter.use_attk(encounter.attacks[rand()%4],player.team[player.currentOut]);
                    win = player.check_faint();
                    //cout << "CURRENTHP: " << player.team[player.currentOut].currentHP << endl;
                    cout << "(TEST) WIN3: " << win << endl;
                    if (win != 0) {
                        break;
                    }
                    do {
                        win = player.turn(encounter,0);
                    } while (win == -3);
                    cout << "(TEST) WIN4: " << win << endl;
                }
            }
            switch (win) {
                case 2:
                    //cout << "TEST: PKM CAUGHT!" << endl;
                    break;
                case 1:
                    player.calc_xp(encounter);
                    break;
                case -1:
                    cout << "💨    You have run from the wild " << encounter.species << ".    💨\n\n";
                    break;
                case -2:
                    cout << "You have lost the game...\n";
                    return 0;
            }
            win = 0;
        }
        // End of encounter phase



        // Rest Phase
        cout << "⏩       Rest Phase        ⏩\n\n";
        for (int i = 0; i < player.currentSN; i++) {
            player.team[i].change_hp(cycle*20,1);
        }
        player.print_team();

        while (next == 0) {
            cout << "1: Use Items\n2: Next Phase\n";
            cin >> input;
            cout << endl;
            switch (input) {
                case 1:
                    cout << "1: Use " << player.pots.name << endl;
                    cout << "2: Use TM\n";
                    cin >> input;
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
                    next = 1;
                    break;
                default:
                    cout << "Invalid input!\n";
            }
            cout << "Proceed to challenge phase? [1/0]\n";
            cin >> next;
            cout << endl;
        }
        next = 0;
        // End of rest phase



        // Challenge Phase
        cout << "⏩       Challenge Phase        ⏩\n\n";
        string names[31] = {"Ash","Youngster Joey","Picnic Girl Elena","Jogger Craig","Idol Grace","Artist William","Hiker Kenney","Waiter Clint","Ninja Boy Zach","Collector Edwin",
                            "Ash","Principal Asuka","Gamer Hugo","Commander Jupiter","Butler Chalmers","Lady Anette","Pilot Leonard","Mysterious Sisters Rune & Rime","Harlequin Charley","Scientist Gideon",
                            "Ash","Striker Marco","Super Nerd Brian","Giovanni","Lorelei","Bruno","Agatha","Lance","Champion Ash","Professor Oak","Rival Ash"};
        opponent oppo = opponent(names[min(cycle - 1,30)]);
        oppo.size = max(3,player.currentSN);
        int aLevel = player.avg_level();
        for (int i = 0; i < oppo.size; i++) {
            int ID = rand() % 693;
            oppo.team[i] = trn.pokedex[ID];
            oppo.team[i].set_level(aLevel);
            aLevel = ceil(aLevel*1.1);
        }
        oppo.generate_inv(player.avg_level());
        cout << "⚔️    " << oppo.name << ": “Technology is incredible! The power of C++ is staggering!    ⚔️”\n";
        oppo.print_team();
        player.print_team();
        player.resetPtcp();
        while (win != -2 && (win != 1 && oppo.currentOut < oppo.size - 1)) {
            oppo.team[oppo.currentOut].print_pkm();
            player.team[player.currentOut].print_pkm();
            player.participate();
                if (player.team[player.currentOut].spd >= oppo.team[oppo.currentOut].spd) {
                    do {
                        win = player.turn(oppo.team[oppo.currentOut],1);
                    } while (win == -3);
                    cout << "(TEST) WIN1: " << win << endl;
                    if (win == -2) {
                        break;
                    } else if (win == 1) {
                        player.calc_xp(oppo.team[oppo.currentOut]);
                    }
                    oppo.turn(player.team[player.currentOut]);
                    win = player.check_faint();
                    cout << "(TEST) WIN2: " << win << endl;
                } else {
                    oppo.turn(player.team[player.currentOut]);
                    win = player.check_faint();
                    cout << "(TEST) WIN3: " << win << endl;
                    if (win == -2) {
                        break;
                    } else if (win == 1) {
                        player.calc_xp(oppo.team[oppo.currentOut]);
                    }
                    do {
                        win = player.turn(oppo.team[oppo.currentOut],1);
                    } while (win == -3);
                    cout << "(TEST) WIN4: " << win << endl;
                }
            }
            if (win == -2) {
                cout << "You have lost the game...\n";
                return 0;
            }
        // End of challenge phase


        // Perk Selection Phase
        cout << "⏩       Perk Selction Phase        ⏩\n\n";
        do {
            cout << "💎        Perks        💎\n1: Upgrade Pokeballs\n 2: Upgrade Potions \n 3: Level up a Pokemon\n";
            cin >> input;
            cout << endl;
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
        // End of perk selection phase



        cycle++;
    } // <- Close bracket for while(cycle > 0)
}