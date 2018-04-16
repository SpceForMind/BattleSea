play: sea_battle.o
		gcc -o play sea_battle.o && ./play
sea_battle.o: sea_battle.c game_flags_and_matrix.h  settings_ships.h coordinate_enemy_ships.h struct_ships.h
	gcc -c sea_battle.c

clean:
	rm -rf *.o play
