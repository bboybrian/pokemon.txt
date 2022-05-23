main0: Attack.cpp Pokemon.cpp Item.cpp Trainer.cpp main.cpp
	g++ -std=c++11 -o main Attack.cpp Pokemon.cpp Item.cpp Trainer.cpp main.cpp

test_item: Item.cpp test_item.cpp
	g++ -std=c++11 -o test_item Item.cpp test_item.cpp
test_atk: Attack.cpp test_attack.cpp
	g++ -std=c++11 -o test_atk Attack.cpp test_attack.cpp
test_pkm: Attack.cpp Pokemon.cpp test_pokemon.cpp
	g++ -std=c++11 -o test_pkm Attack.cpp Pokemon.cpp test_pokemon.cpp
test_trn: Attack.cpp Pokemon.cpp Item.cpp Trainer.cpp test_trainer.cpp
	g++ -std=c++11 -o test_trn Attack.cpp Pokemon.cpp Item.cpp Trainer.cpp test_trainer.cpp
test_challenge: Attack.cpp functions.cpp Pokemon.cpp Item.cpp Trainer.cpp test_challenge.cpp
	g++ -std=c++11 -o test_challenge Attack.cpp functions.cpp Pokemon.cpp Item.cpp Trainer.cpp test_challenge.cpp
test_upgrade: Attack.cpp functions.cpp Pokemon.cpp Item.cpp Trainer.cpp test_upgrade.cpp
	g++ -std=c++11 -o test_upgrade Attack.cpp functions.cpp Pokemon.cpp Item.cpp Trainer.cpp test_upgrade.cpp

main: main0
	./main

test_I: test_item
	./test_item > output_I.txt
test_A: test_atk
	./test_atk > output_A.txt
test_P: test_pkm
	./test_pkm > output_P.txt
test_T: test_trn
	./test_trn > output_T.txt

test01: main0
	./main < input.txt > output.txt

test_c: test_challenge
	./test_challenge < input_c.txt > output_c.txt
test_u: test_upgrade
	./test_upgrade < input_u.txt > output_u.txt
