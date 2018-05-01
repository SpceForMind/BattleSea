play: sea_battle.o find_scale_of_ship.o
		gcc -o play sea_battle.o find_scale_of_ship.o && ./play
sea_battle.o: sea_battle.c game_matrix.h ships_flags.h settings_ships.h coordinate_enemy_ships.h struct_ships.h
	gcc -c sea_battle.c 

find_scale_of_ship.o: find_scale_of_ship.c find_scale_of_ship.h ships_flags.h
	gcc -c find_scale_of_ship.c
clean:
	rm -rf *.o play
