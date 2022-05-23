#include "Trainer.h"

int main()
{
    //This test gives the player a team of level 100 pokemon vs a team of level 10-15 pokemon to reliably test win scenario
    //Lose scenario happens naturally when testing main.cpp
    srand(time(NULL));
    Pokemon pkm;
    Trainer trn;
    pkm.Initialize();
    trn.Initialize();

    // Setup Phase
    player player;
    int input;
    int cycle = 1;
    string name;
    cout << "\nEnter a name:\n";
    getline(cin,name);
    player.set_name(name);
    for (int i = 0; i < 6; i++) {
        player.set_team(trn.pokedex[rand()%693]);
        player.team[i].set_level(100);
        cout << "Name your " << player.team[i].species << ":\n";
        getline(cin,name);
        cout << endl;
        player.team[i].set_name(name);
    }
    player.print_team();
    player.print_inv();
    int win = 0;

    do {
        int aLevel = 10;
        cout << "⏩       Challenge Phase        ⏩\n\n";
        string names[31] = {"Ash","Youngster Joey","Picnic Girl Elena","Jogger Craig","Idol Grace","Artist William","Hiker Kenney","Waiter Clint","Ninja Boy Zach","Collector Edwin",
                            "Ash","Principal Asuka","Gamer Hugo","Commander Jupiter","Butler Chalmers","Lady Anette","Pilot Leonard","Mysterious Sisters Rune & Rime","Harlequin Charley","Scientist Gideon",
                            "Ash","Striker Marco","Super Nerd Brian","Giovanni","Lorelei","Bruno","Agatha","Lance","Champion Ash","Professor Oak","Rival Ash"};
        opponent oppo = opponent(names[min(cycle - 1,30)]);
        oppo.size = max(3,player.currentSN);
        for (int i = 0; i < oppo.size; i++) {
            int ID = rand() % 693;
            oppo.team[i] = trn.pokedex[ID];
            oppo.team[i].set_level(aLevel);
            aLevel = ceil(aLevel*1.1);
        }
        oppo.generate_inv(player.avg_level());
        cout << "⚔️    " << oppo.name << ": “Technology is incredible! The power of C++ is staggering!”    ⚔️\n";
        oppo.print_team();
        player.print_team();
        player.resetPtcp();
        while (win != -2 && oppo.team[oppo.currentOut].currentHP > 0 && win != 1 && oppo.currentOut < oppo.size - 1) {
            cout << "OPPO.CURRENTOUT: " << oppo.currentOut << endl;
            win = 0;
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
                    cout << "TEST: " << oppo.team[oppo.currentOut].species << endl;
                    win = player.turn(oppo.team[oppo.currentOut],1);
                } while (win == -3);
                cout << "(TEST) WIN4: " << win << endl;
            }
        }
        if (win == -2) {
            cout << "You have lost the game...\n";
            return 0;
        }
        cycle++;
    } while (cycle < 3);
}