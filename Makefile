
FLAGS=-std=c++11 -Wall -Wextra -pedantic -Werror

monarch: main.cpp dominion.o cards.o
	g++ $(FLAGS) main.cpp dominion.o cards.o -o monarch

dominion.o: dominion.cpp dominion.h
	g++ $(FLAGS) -c dominion.cpp

cards.o: cards.cpp dominion.h
	g++ $(FLAGS) -c cards.cpp

clean:
	rm -f *.o monarch  
