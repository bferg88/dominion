#include "dominion.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

namespace Dominion {

/* Game implementation */
Game::Game() {}

void Game::add_player(Player* player)
{
  players.push_back(player);
}

void Game::start() 
{
  cout << "Game starting with players:" << endl;
  for(auto player : players)
  {
    cout << player->name << endl;
  }
  cout << endl;

  int player_count = players.size();
  for(int i = 0; i < 8; i++) //limit turns in case of bad players
  {
    players[i % player_count]->take_turn();
  }
}


/* base Player class implementation */
Player::Player() {
  /* give player a starting deck of 7 Coppers and 3 Estates
   * then shuffle it and draw starting hand (5 cards) */

  cout << "building deck" << endl;
  
  vector<const Card*> coppers(7, get_card("Copper"));
  deck.insert(deck.end(), coppers.begin(), coppers.end());

  vector<const Card*> estates(3, get_card("Estate"));
  deck.insert(deck.end(), estates.begin(), estates.end());

  shuffle_cards(deck);
  draw_cards();
}

Player::Player(string name_) : Player() 
{
  name=name_;
}


void Player::replace_deck_from_discard()
{
  shuffle_cards(discard);
  deck = discard;
  discard = vector<const Card*>();
}

void Player::draw_card()
{
  if(!deck.empty())
  {
    hand.push_back(deck.back());
    deck.pop_back();
  }
  else if(!discard.empty())
  {
    replace_deck_from_discard();
    draw_card();
  }
}

void Player::draw_cards(int num_cards)
{
  while(num_cards-- > 0)
  {
    draw_card();
  }
}


/* HumanPlayer implementation */
HumanPlayer::HumanPlayer() {}

HumanPlayer::HumanPlayer(string name) : Player(name) {}

void HumanPlayer::take_turn()
{
  cout << name <<"'s turn:" << endl;
  //todo: implement console interface
  while(true)
  {
    cout << "Choose an option: " << endl;
    cout << "\t1: list cards" << endl;
    cout << "\t2: use action card" << endl;
    cout << "\t3: make purchase" << endl;
    cout << "\t(press any other key to end turn)" << endl;
    string input;
    cin >> input;
  }
}


/* AutoPlayer implementation */
AutoPlayer::AutoPlayer() {}

AutoPlayer::AutoPlayer(string name) : Player(name) {}

void AutoPlayer::take_turn()
{
  cout << name << "'s turn: " << endl;
  
  hand
  
  gain_card(
}


/* Function definitions */

void shuffle_cards(vector<const Card*>& cards)
{
  /* Initialize default_random engine and seed with random_device 
   * for always random shuffling (uncomment #define for repeatable shuffling. 
   *
   * Using default_random_engine instead of random_device directly because 
   * it's considered better practice as random_device potentially throws
   * exception under high loads.
   */

//  #define REPEATABLE_SHUFFLE

  #ifdef REPEATABLE_SHUFFLE
  static auto rng = default_random_engine();
  #else
  static auto rng = default_random_engine(random_device()());
  #endif

  shuffle(cards.begin(), cards.end(), rng);
}

}//namespace Dominion


