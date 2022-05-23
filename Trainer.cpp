#include "Trainer.h"
#include <fstream>
#include <sstream>

using namespace std;

int player::currentSN = 0;
int player::participant[6] = {0,0,0,0,0,0};
Pokemon* Trainer::pokedex;

Trainer::Trainer()
{
    name = "A strange man";
}

void Trainer::use_pot()
{
}

void Trainer::Initialize()
{
    pokedex = new Pokemon[693];
    string aSpecies, aType1, aType2;
    int numberOfTypes, aHP, aAtk, aDef, aSpd;
    int i = 0;
    ifstream file("Pokemon.txt");
    string str;

    while (getline(file, str)) {
        istringstream iss(str);
        getline(iss,aSpecies,'%');
        str = str.substr(str.find('%') + 1);
        istringstream iss2(str);
        iss2 >> numberOfTypes >> aType1 >> aType2 >> aHP >> aAtk >> aDef >> aSpd;
        pokedex[i] = Pokemon(aSpecies,numberOfTypes,aType1,aType2,aHP,aAtk,aDef,aSpd);
        i++;
    }
}

void Trainer::set_name(string aName)
{
    name = aName;
}

void Trainer::print_team()
{
    cout << "😀        " <<name << "'s Team        😀\n";
    for (int i = 0; i < 6; i++) {
        if (team[i].species != "?") {
            cout << i + 1 << ": ";
            team[i].print_small();
        }
    }
    cout << endl;
}

void Trainer::turn()
{
}

opponent::opponent(string aName)
{
    name = aName;
    currentOut = 0;
}

void opponent::generate_inv(int avg_level)
{
    //cout << "AVG LVL: " << avg_level << endl;
    int amt = rand() % 5;
    pots.set_amount(amt);
    int cap = ceil(avg_level/25)*25;
    float roll = pow(rand() % 100,2);
    while (roll > cap)
    {
        //cout << "CAP, ROLL: " << cap << ", " << roll << endl;
        roll = pow(rand() % 100,2);
    }
    roll = ceil(roll/2500);
    for (int i = 0; i < (roll - 1); i++) {
        pots.upgrade_item();
    }
}

void opponent::turn(Pokemon& defender)
{
    if (team[currentOut].currentHP > 0 && team[currentOut].maxHP - team[currentOut].currentHP >= pots.potency && pots.amount > 0)
    {
        use_pot();
    } else if (team[currentOut].currentHP <= 0 && currentOut < size - 1) {
        currentOut++;
        cout << name << " sends out " << team[currentOut].name << " !\n\n";
    } else if (team[currentOut].currentHP > 0) {
        team[currentOut].use_attk(team[currentOut].attacks[rand()%4],defender);
    } else {
        cout << name << " has been defeated!\n\n";
    }
}

void opponent::use_pot()
{
    cout << name << " uses a " << pots.name << "!\n";
    team[currentOut].change_hp(pots.potency,1);
    cout << team[currentOut].name << " restored " << pots.potency << " HP!\n";
    pots.amount--;
}

player::player()
{
    name = "A new challenger";
    money = 1000;
    currentOut = 0;
}

void player::set_team(Pokemon aPkm)
{
    team[currentSN] = aPkm;
    currentSN++;
}

void player::release(int aPkm)
{
    cout << team[aPkm].name << " has been released!\n";
    currentSN = aPkm;
    for (int i = currentSN + 1; i < 6; i++) {
        if (team[i].species != "?") {
            team[currentSN] = team[i];
            currentSN++;
        }
    }
    //cout << "TEST  CURRENTSN: " << currentSN << endl;
    team[currentSN] = tamePokemon();
}

int player::avg_level()
{
    int total = 0;
    for (int i = 0; i < 6; i++) {
        if (team[i].level != 0) {
            total = total + team[i].level;
        }
    }
    return (total/currentSN);
}

void player::print_inv()
{
    cout <<"🎒        Backpack        🎒\n";
    cout << "Money:\t$" << money << endl;
    cout << "Amt.\tName\t\t\tDescription\n";
    balls.print_item();
    pots.print_item();
    discs.print_item();
    cout << endl;
}

int player::turn(Pokemon& encounter, int pvp)
{
    cout << "What will you do?\n";
    int choice, valid;
    if (pvp == 1) {
        do {
            valid = 1;
            cout << "1: Fight\n2: Use Potion\n3: Swap\n";
            cin >> choice;
            if (!cin) {
                cout << "Invalid input!\n";
                cin.clear();
                cin.ignore(256,'\n');
            }
            cout << endl;
            if (choice == 3 && currentSN <= 1) {
                cout << "You have no other Pokemon to send out!\n";
                valid = 0;
            }
        } while (choice != 1 && choice != 2 && choice != 3 || valid == 0);
    } else {
        do {
            valid = 1;
            cout << "1: Fight\n2: Use Item\n3: Swap\n4: Run\n";
            cin >> choice;
            if (!cin) {
                cout << "Invalid input!\n";
                cin.clear();
                cin.ignore(256,'\n');
            }
            cout << endl;
            if (choice == 3 && currentSN <= 1) {
                cout << "You have no other Pokemon to send out!\n";
                valid = 0;
            }
        } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 || valid == 0);
    }
    switch (choice) {
        //Case 1 - Fight
        case 1:
            int valid;
            do {
                valid = 1;
                cout <<"Pick an attack\t\t⚔️\n";
                for (int i = 0; i < 4; i++) {
                    cout << i + 1 << ": ";
                    team[currentOut].attacks[i].print_small();
                }
                cin >> choice;
                if (!cin) {
                    cout << "Invalid input!\n";
                    cin.clear();
                    cin.ignore(256,'\n');
                }
                cout << endl;
                if (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
                    valid = 0;
                }
                if (valid == 1) {
                    if (team[currentOut].attacks[choice - 1].PP == 0) {
                        cout << team[currentOut].name << " has run out of Power Points for " << team[currentOut].attacks[choice - 1].name << "!\n";
                        cout <<"Choose another attack -> \n";
                        valid = 0;
                    }
                }
            } while (valid == 0);
            team[currentOut].attacks[choice - 1].PP--;
            team[currentOut].use_attk(team[currentOut].attacks[choice - 1],encounter);
            if (encounter.currentHP <= 0) {
                return 1;
            }
            return 0;
        //Case 2 - Use Item
        case 2:
            if (pvp == 1) {
                cout << "TEST AMT: " << pots.amount << endl;
                choice = 0;
                if (pots.amount == 0) {
                    choice = -3;
                }
                use_pot();
            } else {
                do {
                    cout << "1: Use " << pots.name << endl;
                    cout << "2: Use " << balls.name << endl;
                    cin >> choice;
                    if (!cin) {
                        cout << "Invalid input!\n";
                        cin.clear();
                        cin.ignore(256,'\n');
                    }
                    cout << endl;
                } while (choice != 1 && choice != 2);
                switch(choice) {
                        case 1:
                            choice = 0;
                            if (pots.amount == 0) {
                                choice = -3;
                            }
                            use_pot();
                            break;
                        case 2:
                            choice = use_pkball(encounter);
                            break;
                    }
            }
            return choice;
        //Case 3 - Swap
        case 3:
            cout << "Which Pokemon will you send?\n";
            currentOut = which_pkm();
            cout << "Go, " << team[currentOut].name << "!\n";
            return 0;
        //Case 4 - Run
        case 4:
            if (pvp == 1) {
                return 0;
            }
            return -1;
    }
}

void player::participate()
{
    participant[currentOut] = 1;
}

void player::resetPtcp()
{
    for (int i = 0; i < 6; i++) {
        participant[i] = 0;
    }
}

void player::calc_xp(Pokemon defeated)
{
    int xp = ((defeated.maxHP + defeated.atk + defeated.def + defeated.spd) * defeated.level) / 14;
    change_money(xp);
    int n = 0;
    for (int i = 0; i < 6; i++) {
        n = n + participant[i];
    }
    xp = xp / n;
    for (int i = 0; i < 6; i++) {
        if (participant[i] == 1) {
            team[i].add_xp(xp);
        }
    }
    cout << endl;
}

int player::which_pkm()
{
    int choice;
    do {
        cout << "Choose a Pokemon\n";
        print_team();
        cin >> choice;
        if (!cin) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(256,'\n');
        }
        cout << endl;
    } while (choice > currentSN || choice <= 0);
    return choice - 1;
}

int player::use_pkball(Pokemon wildpkm)
{
    if (balls.amount > 0 && currentSN < 6)
    {
        balls.amount--;
        cout << name << " throws a " << balls.name <<"!\n";
        int chance = (wildpkm.maxHP * 4 * balls.potency)/ (wildpkm.currentHP * 10);
        int roll = (rand() % 12) + 1;
        cout << "ROLL: " << roll << "CHANCE: " << chance << endl;
        if (roll < chance) {
            cout << wildpkm.species << " was caught!\n";
            team[currentSN] = tamePokemon(wildpkm);
            cout << "Name your " << team[currentSN].species << ":\n";
            getline(cin,name);
            if (name == "") {
                name = team[currentSN].species;
            }
            cout << endl;
            team[currentSN].set_name(name);
            currentSN++;
            return 2;
        }
        else {
            cout << wildpkm.species << " escaped!\n";
            return 0;
        }
    }
    else if (currentSN == 6) {
        cout << "Your team is full!" << endl << endl;
        return -3;
    }
    else {
        cout << "You have no Pokeballs!" << endl << endl;
        return -3;
    }
}

void player::use_TM()
{
    if (discs.amount > 0)
    {
        int choice = which_pkm();
        int atkchoice, i;

        do {
            cout << "Replace which of " << team[choice].name <<"'s moves?\n";
            for (i = 0; i < 4; i++) {
                cout << i + 1<< ": " << team[choice].attacks[i].name << " (" << team[choice].attacks[i].type << ")\n";
            }
            cin >> atkchoice;
            if (!cin) {
                cout << "Invalid input!\n";
                cin.clear();
                cin.ignore(256,'\n');
            }
            cout << endl;
        } while (atkchoice != 1 && atkchoice != 2 && atkchoice != 3 && atkchoice != 4);
        atkchoice--;
        cout << "Replace " << team[choice].attacks[atkchoice].name << " with move of which type?\n";
        for (i = 0; i < team[choice].types; i++) {
            cout << team[choice].typing[i] << endl;
        }
        if (team[choice].typing[0] != "Normal" && team[choice].typing[0] != "Normal") {
            cout << "Normal\n";
        }
        cout << "(Type anything else to cancel)\n";
        string typechoice;
        cin >> typechoice;

        if (typechoice != team[choice].typing[0] && typechoice != team[choice].typing[1] && typechoice != "Normal") {
            typechoice = "";
            cout << "Cancelling...\n";
        } else {
            team[choice].new_attk(atkchoice, typechoice);
            discs.amount--;
        }
    }
    else {
        cout << "You have no TMs!" << endl << endl;
    }
}

void player::use_pot()
{
    if (pots.amount > 0)
    {
        int choice = which_pkm();
        team[choice].change_hp(pots.potency,1);
        pots.amount--;
    }
    else {
        cout << "You have no potions!" << endl << endl;
    }
}

void player::pokemart()
{
    int tcost, amt, input;
    cout <<"🏬        Poke Mart        🏬\n";
    cout << "Money:\t$" << money << endl;
    cout << "What would you like to buy?\n";
    cout << "S/N\tPrice\t\tName\n";
    do {
        cout << "1:\t$" << balls.cost << "\t\t" << balls.name << endl;
        cout << "2:\t$" << pots.cost << "\t\t" << pots.name << endl;
        cout << "3:\t$" << discs.cost << "\t\t" << "TM\n";
        cin >> input;
        if (!cin) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(256,'\n');
        }
        cout << endl;
    } while (input != 1 && input != 2 && input != 3);
    do {
        cout << "\nHow many would you like?\n";
        cin >> amt;
        if (!cin) {
            amt = -1;
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(256,'\n');
        }
        cout << endl;
    } while (amt < 0);
    switch(input) {
        case 1:
            tcost = balls.buy_item(amt, money);
            break;
        case 2:
            tcost = pots.buy_item(amt, money);
            break;
        case 3:
            tcost = discs.buy_item(amt, money);
            break;
    }
    change_money(- tcost);
}

void player::change_money(int change)
{
    if (change < 0)
    {
        cout << "You have spent $" << -change << "." << endl << endl;
    } else if (change > 0)
    {
        cout << "You have earned $" << change << "!" << endl << endl;
    }
    money = money + change;
}

int player::check_faint()
{
    if (team[currentOut].currentHP <= 0) {
        release(currentOut);
        participant[currentOut] = 0;
        if (currentSN != 0) {
            cout << "Which Pokemon will you send?\n";
            currentOut = which_pkm();
            cout << "Go, " << team[currentOut].name << "!\n";
            return 0;
        } else {
            return -2;
        }
    }
    return 0;
}