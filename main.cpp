#include "dominion.h"
#include "player_impl.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {
  cout << "Hello Dominion!" << endl << endl;

  // make instance of game
  Dominion::Game game;

  // make players
  Dominion::AutoPlayer player1("Adam");
  Dominion::AutoPlayer player2("Eve");

  // add players to game
  game.add_player(&player1);
  game.add_player(&player2);

  game.start();
}

