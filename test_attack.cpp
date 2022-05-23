#include "Attack.h"

int main()
{
    Attack blank;
    Attack water = Attack("Aqua Jet", "Water", 40, 100,	20);

    if (blank.name == "MissingNo." && water.name == "Aqua Jet") {
        cout << "Construction successful\n";
    }

    blank.set_name("Aqua Tail");
    blank.set_type("Water");
    blank.set_stats(90,90,10);

    cout << "Testing print_attk():\n";
    blank.print_attk();

    cout << "Testing print_small():\n";
    water.print_small();

    blank.PP = 0;
    water.PP = 0;
    blank.restore_PP();
    water.restore_PP();

    if (blank.PP == 10 && water.PP == 20) {
        cout <<"restore_PP() successful\n";
    }
}