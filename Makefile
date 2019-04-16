
FLAGS=-std=c++11 -Wall -Wextra -pedantic -Werror

monarch: main.o dominion.o cards.o player_impl.o
	g++ $(FLAGS) main.o dominion.o cards.o player_impl.o -o monarch

main.o: main.cpp dominion.h player_impl.h
	g++ $(FLAGS) -c main.cpp

dominion.o: dominion.cpp dominion.h cards.h
	g++ $(FLAGS) -c dominion.cpp

cards.o: cards.cpp cards.h
	g++ $(FLAGS) -c cards.cpp

player_impl.o: player_impl.cpp player_impl.h dominion.h
	g++ $(FLAGS) -c player_impl.cpp

clean:
	rm -f *.o monarch  
