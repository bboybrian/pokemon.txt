#include "Pokemon.h"
#include <algorithm>
#include <cmath>

using namespace std;

Attack** Pokemon::all_attacks;

Pokemon::Pokemon()
{
    species = "?";
    name = "?";
    types = 0;
    level = 0;
    maxHP = 0;
    currentHP = maxHP;
}

void Pokemon::Initialize()
{
    all_attacks = new Attack*[18];
    for (int i = 0; i < 18; i++) {
        all_attacks[i] = new Attack[10];
    }

    //18 types, 10 attacks per type
    string types[18] = {"Bug","Dark","Dragon","Electric","Fairy","Fighting","Fire","Flying","Ghost","Grass","Ground","Ice","Normal","Poison","Psychic","Rock","Steel","Water"};
    string attack_names[18][10] = {{"Bug Bite","Lunge","Megahorn","Skitter Smack","Steamroller","X-Scissor","Bug Buzz","Attack Order","Fury Cutter","Silver Wind"},
                                   {"Bite","Crunch","Dark Pulse","Darkest Lariat","Foul Play","Jaw Lock","Knock Off","Night Daze","Sucker Punch","Throat Punch"},
                                   {"Breaking Swipe","Clanging Scales","Draco Meteor","Dragon Breath","Dragon Claw","Dragon Pulse","Dragon Rush","Outrage","Spacial Rend","Twister"},
                                   {"Bolt Beak","Bolt Strike","Buzzy Buzz","Charge Beam","Discharge","Electroweb","Overdrive","Parabolic Charge","Spark","Thunder"},
                                   {"Dazzling Gleam","Draining Kiss","Fairy Wind","Fleur Cannon","Misty Explosion","Moonblast","Play Rough","Sparkly Swirl","Spirit Break","Strange Steam"},
                                   {"Body Press","Brick Break","Circle Throw","Close Combat","Cross Chop","Drain Punch","Focus Blast","Mach Punch","Rolling Kick","Submission"},
                                   {"Blaze Kick","Blue Flare","Ember","Fire Fang","Flame Burst","Flamethrower","Heat Wave","Inferno","Lava Plume","Pyro Ball"},
                                   {"Acrobatics","Aeroblast","Air Cutter","Chatter","Dragon Ascent","Drill Peck","Floaty Fall","Hurricane","Peck","Wing Attack"},
                                   {"Astonish","Hex","Lick","Moongeist Beam","Ominous Wind","Shadow Ball","Shadow Claw","Poltergeist","Shadow Sneak","Spirit Shackle"},
                                   {"Apple Acid","Branch Poke","Drum Beating","Energy Ball","Leaf Blade","Leaf Storm","Needle Arm","Petal Blizzard","Seed Bomb","Vine Whip"},
                                   {"Bone Club","Drill Run","Earth Power","Earthquake","Land's Wrath","Mud Bomb","Mud Slap","Precipice Blades","Scorching Sands","Stomping Tantrum"},
                                   {"Aurora Beam","Avalanche","Blizzard","Frost Breath","Ice Beam","Ice Fang","Ice Punch","Icicle Crash","Icy Wind","Powder Snow"},
                                   {"Body Slam","Chip Away","Covet","Crush Claw","Cut","Extreme Speed","False Swipe","Headbutt","Quick Attack","Tackle"},
                                   {"Acid","Acid Spray","Cross Poison","Gunk Shot","Poison Jab","Poison Tail","Sludge Bomb","Sludge Wave","Smog","Venoshock"},
                                   {"Confusion","Dream Eater","Expanding Force","Extrasensory","Glitzy Glow","Heart Stamp","Photon Geyser","Psybeam","Psycho Cut","Zen Headbutt"},
                                   {"Accelerock","Ancient Power","Diamond Storm","Power Gem","Rock Slide","Rock Throw","Rock Tomb","Rock Wrecker","Smack Down","Stone Edge"},
                                   {"Anchor Shot","Behemoth Bash","Bullet Punch","Flash Cannon","Iron Head","Iron Tail","Metal Claw","Meteor Mash","Mirror Shot","Sunsteel Strike"},
                                   {"Aqua Jet","Aqua Tail","Bubble","Crabhammer","Hydro Pump","Muddy Water","Scald","Surf","Water Pulse","Waterfall"}};

    int attack_stats[18][10][3] = {{{60,100,20},{80,100,15},{120,85,10},{70,90,10},{65,100,20},{80,100,15},{90,100,10},{90,100,15},{40,95,20},{60,100,5}},
                                   {{60,100,25},{80,100,15},{80,100,15},{85,100,10},{95,100,15},{80,100,10},{65,100,20},{85,95,10},{70,100,5},{80,100,15}},
                                   {{60,100,15},{110,100,5},{130,90,5},{60,100,20},{80,100,15},{85,100,10},{100,75,10},{120,100,10},{100,95,5},{40,100,20}},
                                   {{85,100,10},{130,85,5},{90,100,15},{50,90,10},{80,100,15},{55,95,15},{80,100,10},{65,100,20},{65,100,20},{110,70,10}},
                                   {{80,100,10},{50,100,10},{40,100,30},{130,90,5},{100,100,5},{95,100,15},{90,90,10},{90,100,15},{75,100,15},{90,95,10}},
                                   {{80,100,10},{75,100,15},{60,90,10},{120,100,5},{100,80,5},{75,100,10},{120,70,5},{40,100,30},{60,85,15},{80,80,20}},
                                   {{85,90,10},{130,85,5},{40,100,25},{65,95,15},{70,100,15},{90,100,15},{95,90,10},{100,50,5},{80,100,15},{120,90,5}},
                                   {{55,100,15},{100,95,5},{60,95,25},{65,100,20},{120,100,5},{80,100,20},{90,95,15},{110,70,10},{35,100,35},{60,100,35}},
                                   {{30,100,15},{65,100,10},{30,100,30},{100,100,5},{60,100,5},{80,100,15},{70,100,15},{110,90,5},{40,100,30},{80,100,10}},
                                   {{80,100,10},{40,100,40},{80,100,10},{90,100,10},{90,100,15},{130,90,5},{60,100,15},{90,100,15},{80,100,15},{45,100,25}},
                                   {{65,85,20},{80,95,10},{90,100,10},{100,100,10},{90,100,10},{65,85,10},{20,100,10},{120,85,10},{70,100,10},{75,100,10}},
                                   {{65,100,20},{60,100,10},{110,70,5},{60,90,10},{90,100,10},{65,95,15},{75,100,15},{85,90,10},{55,95,15},{40,100,25}},
                                   {{85,100,15},{70,100,20},{60,100,25},{75,95,10},{50,95,30},{80,100,5},{40,100,40},{70,100,15},{40,100,30},{40,100,35}},
                                   {{40,100,30},{40,100,20},{70,100,20},{120,80,5},{80,100,20},{50,100,25},{90,100,10},{95,100,10},{30,70,20},{65,100,10}},
                                   {{50,100,25},{100,100,15},{80,100,10},{80,100,20},{90,100,15},{60,100,25},{100,100,5},{65,100,20},{70,100,20},{80,90,15}},
                                   {{40,100,20},{60,100,5},{100,95,5},{80,100,20},{75,90,10},{50,90,15},{60,95,15},{75,90,10},{50,100,15},{100,80,5}},
                                   {{80,100,20},{100,100,5},{40,100,30},{80,100,10},{80,100,15},{100,75,15},{50,95,35},{90,90,10},{65,85,10},{100,100,5}},
                                   {{40,100,20},{90,90,10},{40,100,30},{100,90,10},{110,80,5},{90,85,10},{80,100,15},{90,100,15},{60,100,20},{80,100,15}}};
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 10; j++) {
            all_attacks[i][j].set_type(types[i]);
            all_attacks[i][j].set_name(attack_names[i][j]);
            all_attacks[i][j].set_stats(attack_stats[i][j][0],attack_stats[i][j][1],attack_stats[i][j][2]);
        }
    }
}

Pokemon::Pokemon(string aSpecies, int numberOfTypes, string aType1, string aType2, int aHP, int aAtk, int aDef, int aSpd)
{
    species = aSpecies;
    name = species;
    types = numberOfTypes;
    typing[0] = aType1;
    typing[1] = aType2;
    level = 0;
    maxHP = aHP;
    currentHP = maxHP;
    atk = aAtk;
    def = aDef;
    spd = aSpd;

    //Generate a set of 4 attacks w/o repeat based on Pokemon's typing
    int type1;
    int type2 = 12;
    string all_types[18] = {"Bug","Dark","Dragon","Electric","Fairy","Fighting","Fire","Flying","Ghost","Grass","Ground","Ice","Normal","Poison","Psychic","Rock","Steel","Water"};
    for (int i = 0; i < 18; i++) {
        if (aType1 == all_types[i]) {
            type1 = i;
        }
        if (aType2 == all_types[i]) {
            type2 = i;
        }
    }
    int randomizer[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    random_shuffle(randomizer, randomizer + 10);
    attacks[0] = all_attacks[type1][randomizer[0]];
    attacks[1] = all_attacks[type1][randomizer[1]];
    if (aType2 == "-")
    {
        attacks[2] = all_attacks[type1][randomizer[2]];
        attacks[3] = all_attacks[type2][randomizer[3]];
    }
    else
    {
        attacks[2] = all_attacks[type2][randomizer[2]];
        attacks[3] = all_attacks[type2][randomizer[3]];
    }
}

void Pokemon::set_level(int aLevel)
{
    level = aLevel;
    maxHP = maxHP + (level * 2);
    currentHP = maxHP;
    atk = atk + level - 1;
    def = def + level - 1;
    spd = spd + level - 1;
    xp = pow((level - 1),3);
    xpToLevel = pow((level),3);
}

void Pokemon::use_attk(Attack attk, Pokemon& defender)
{
    string all_types[18] = {"Bug","Dark","Dragon","Electric","Fairy","Fighting","Fire","Flying","Ghost","Grass","Ground","Ice","Normal","Poison","Psychic","Rock","Steel","Water"};
    string type_symb[18] = {"🐞","🕶","🐲","⚡","🧚","👊","🔥","🎈","👻","🌿","🐘","❄️","⚪","☢️","🔮","🗿","⚙️","🌊"};
    int atkType, defType;
    for (int i = 0; i < 18; i++) {
        if (attk.type == all_types[i]) {
            atkType = i;
        }
    }
    cout << type_symb[atkType] << "  " << name << " uses " << attk.name << "!\n";

    float modifier = 1;
    float effect = 1;
    float fltatk = atk;
    float fltdef = defender.def;
    int roll = rand() % 100 + 1;
    if (roll > attk.accuracy)
    {
        cout << "💤  The attack missed!\n\n";
        modifier = 0;
    } else
    {
        float dmg = ((((2 * level)/5 + 2)*attk.power*(fltatk/fltdef))/50 + 2);
        //cout << "DAMAGE= " << (2 * level)/5 + 2 << "*" << attk.power << "*" << atk << "/" << defender.def << "/50 + 2 = " << dmg << endl;
        roll = rand() % 100 + 1;
            if (roll < (spd/5.12))
            {
                cout << "💯  Critical hit!\n";
                modifier = modifier * 2;
            }
        //"Bug","Dark","Dragon","Electric","Fairy","Fighting","Fire","Flying","Ghost","Grass","Ground","Ice","Normal","Poison","Psychic","Rock","Steel","Water"
        float typeChart[18][18] = {{1,2,1,1,0.5,0.5,0.5,0.5,0.5,2,1,1,1,0.5,2,1,0.5,1},
                                    {1,0.5,1,1,0.5,0.5,1,1,2,1,1,1,1,1,2,1,1,1},
                                    {1,1,2,1,0,1,1,1,1,1,1,1,1,1,1,1,0.5,1},
                                    {1,1,0.5,0.5,1,1,1,2,1,0.5,0,1,1,1,1,1,1,2},
                                    {1,2,2,1,1,2,0.5,1,1,1,1,1,1,0.5,1,1,0.5,1},
                                    {0.5,2,1,1,0.5,1,1,0.5,0,1,1,2,2,0.5,0.5,2,2,1},
                                    {2,1,0.5,1,1,1,0.5,1,1,2,1,2,1,1,1,0.5,2,0.5},
                                    {2,1,1,0.5,1,2,1,1,1,2,1,1,1,1,1,0.5,0.5,1},
                                    {1,0.5,1,1,1,1,1,1,2,1,1,1,0,1,2,1,1,1},
                                    {0.5,1,0.5,1,1,1,0.5,0.5,1,0.5,2,1,1,0.5,1,2,0.5,2},
                                    {0.5,1,1,2,1,1,2,0,1,0.5,1,1,1,2,1,2,2,1},
                                    {1,1,2,1,1,1,0.5,2,1,2,2,0.5,1,1,1,1,0.5,0.5},
                                    {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0.5,0.5,1},
                                    {1,1,1,1,2,1,1,1,0.5,2,0.5,1,1,0.5,1,0.5,0,1},
                                    {1,0,1,1,1,2,1,1,1,1,1,1,1,2,0.5,1,0.5,1},
                                    {2,1,1,1,1,0.5,2,2,1,1,0.5,2,1,1,1,1,0.5,1},
                                    {1,1,1,0.5,2,1,0.5,1,1,1,1,2,1,1,1,2,0.5,0.5},
                                    {1,1,0.5,1,1,1,2,1,1,0.5,2,1,1,1,1,2,1,0.5}};
        for (int i = 0; i < defender.types; i++) {
            for (int j = 0; j < 18; j++) {
                if (defender.typing[i] == all_types[j]) {
                    defType = j;
                }
            }
            effect = effect * typeChart[atkType][defType];
        }

        if (effect == 4) {
            cout << "💥  It's extremely effective!!\n";
        }else if (effect == 2) {
            cout << "💪  It's super effective!\n";
        } else if (effect == 0) {
            cout << "💩  It's completely ineffective...\n";
        } else if (effect < 1) {
            cout << "🤔  It's not very effective...\n";
        }
        float random = rand() % 16 + 85;
        modifier = modifier * effect * random * 0.01;
        //cout << "MOD: " << modifier << endl;
        defender.change_hp(- dmg, modifier);
    }
}

int Pokemon::change_hp(float ahp, float modifier)
{
    int change = ceil(ahp * modifier);
    change = min(change,maxHP - currentHP);
    if (change < 0)
    {
        cout << "💢  " << name << " takes " << -change << " damage!\n\n";
    } else if (change > 0)
    {
        cout << "⛑️  " << name << " restores " << change << " health!\n\n";
    } else if (change == 0)
    {
        cout << name << "'s HP remains unchanged.\n\n";
    }
    currentHP = currentHP + change;
    if (currentHP <= 0)
    {
        cout << name << " has fainted!\n\n";
    }
}

void Pokemon::print_pkm()
{

    cout << "Name:\t\t" << species << endl;;
    cout << "Level:\t\t" << level << endl;
    cout << "Type:\t\t";
    for (int i = 0; i < types; i++) {
        cout << typing[i] << " ";
    }
    cout << endl;
    cout << "HP:\t\t" << currentHP << "/" << maxHP << endl << endl;
    //cout << "Attacks:\t" << attacks[0].name << ", " << attacks[1].name << ", " << attacks[2].name << ", " << attacks[3].name << endl << endl;
}

void Pokemon::print_small()
{
    if (name != species && name != "")
    {
        cout << name << "   (" << species << ")";
    } else
    {
        cout << name;
    }
    cout << " LVL " << level;
    for (int i = 0; i < types; i++) {
        cout << " " << typing[i];
    }
    cout << endl;
}

Pokemon::~Pokemon()
{
}

tamePokemon::tamePokemon()
{
    species = "?";
    name = "?";
    types = 0;
    level = 0;
    maxHP = 0;
    currentHP = 0;
    atk = 0;
    def = 0;
    spd = 0;
    xp = 0;
    xpToLevel = 0;
    for (int i = 0; i < 4; i++) {
        attacks[i] = Attack();
    }
}

tamePokemon::tamePokemon(Pokemon pkm)
{
    name = pkm.name;
    species = pkm.species;
    level = pkm.level;
    types = pkm.types;
    maxHP = pkm.maxHP;
    currentHP = pkm.currentHP;
    atk = pkm.atk;
    def = pkm.def;
    spd = pkm.spd;
    for (int i = 0; i < 4; i++) {
        attacks[i] = pkm.attacks[i];
    }
    typing[0] = pkm.typing[0];
    typing[1] = pkm.typing[1];
    xp = pow((level - 1),3);
    xpToLevel = pow((level),3);
}

void tamePokemon::new_attk(int choice, string aType)
{
    int type1;
    string all_types[18] = {"Bug","Dark","Dragon","Electric","Fairy","Fighting","Fire","Flying","Ghost","Grass","Ground","Ice","Normal","Poison","Psychic","Rock","Steel","Water"};
    for (int i = 0; i < 18; i++) {
        if (aType == all_types[i]) {
            type1 = i;
        }
    }
    Attack replacement = all_attacks[type1][rand()%10];
    while (replacement.name == attacks[0].name || replacement.name == attacks[1].name || replacement.name == attacks[2].name || replacement.name == attacks[3].name) {
        Attack replacement = all_attacks[type1][rand()%10];
        // if (replacement.name == attacks[0].name || replacement.name == attacks[1].name || replacement.name == attacks[2].name || replacement.name == attacks[3].name) {
        //     cout << "TRUE\n";
        //     cout << replacement.name << endl;
        // }
    }
    cout << name << " has forgotten " << attacks[choice].name << "!\n";
    attacks[choice] = replacement;
    cout << name << " has learned " << attacks[choice].name << "!\n\n";

}

void tamePokemon::add_xp(int axp)
{
    if (level < 100)
    {
        cout << name << " has gained " << axp << " EXP!\n";
        xp = xp + axp;
        //'while' in case of multiple level ups
        while (xp >= xpToLevel)
        {
            cout << "✨    " << name << " has leveled up!    ✨\n";
            level++;
            xpToLevel = pow(level + 1,3);
            maxHP = maxHP + 2;
            currentHP = maxHP;
            for (int i = 0; i < 4; i++) {
                attacks[i].restore_PP();
            }
        }
    }
}

void tamePokemon::set_name(string aName)
{
    name = aName;
}

void tamePokemon::print_pkm()
{

    cout << "Name:\t\t";
    if (name != species)
    {
        cout << name << "\t(" << species << ")" << endl;
    } else
    {
        cout << name << endl;
    }
    cout << "Level:\t\t" << level << endl;
    cout << "Type:\t\t";
    for (int i = 0; i < types; i++) {
        cout << typing[i] << " ";
    }
    cout << endl;
    cout << "HP:\t\t" << currentHP << "/" << maxHP << endl;
    cout << "EXP:\t\t" << xp << "/" << xpToLevel << endl;
    cout << "Attacks:\t" << attacks[0].name << ", " << attacks[1].name << ", " << attacks[2].name << ", " << attacks[3].name << endl << endl;
}

tamePokemon::~tamePokemon()
{
}