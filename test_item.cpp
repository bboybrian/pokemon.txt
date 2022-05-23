#include "Item.h"

int main()
{
    Pokeball pkball;
    Potion pot;
    TM tm;

    pkball.set_amount(5);
    pot.set_amount(10);
    tm.set_amount(3);

    if (pkball.name == "Pokeball" && pot.name == "Potion" && tm.name == "TM") {
        cout << "Construction successful\n";
    }

    pkball.upgrade_item();
    pot.upgrade_item();
    pkball.upgrade_item();
    pot.upgrade_item();

    if (pkball.name == "Ultra Ball" && pkball.potency == 20 && pot.name == "Hyper Potion" && pot.potency == 200) {
        cout << "upgrade_item() successful\n";
    }

    int money = 2000;
    int cost = pkball.buy_item(2,money);
    money = money - cost;
    cost = pot.buy_item(1,money);
    money = money - cost;
    cost = tm.buy_item(2,money);
    money = money - cost;

    if (money == 300 && pkball.amount == 7 && pot.amount == 11 && tm.amount == 5) {
        cout << "buy_item(int amount, int money) successful\n";
    }

    cost = tm.buy_item(1,money);

    if (cost == 0) {
        cout <<"Not enough money successful\n";
    }

    pkball.use_item();
    pot.use_item();
    tm.use_item();

    if (pkball.amount == 6 && pot.amount == 10 && tm.amount == 4) {
        cout << "use_item() successful\n";
    }

    cout << "Testing print_item():\n";
    pkball.print_item();
    pot.print_item();
    tm.print_item();
}