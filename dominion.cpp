#include "dominion.h"
#include <algorithm>


using namespace std;

namespace Dominion {

/* Game  */
Game::Game() 
{
  cout << "Game created." << endl;
}

void Game::add_player(Player* player)
{
  players.push_back(player);
}

void Game::start() 
{
  cout << "Game starting with players:" << endl;
  for(Player* player : players)
  {
    cout << player->name << endl;
  }
  cout << endl;

  supply.setup(players);

  cout << "Supply contents:" << endl;
  for(auto pile : supply.card_piles)
  {
    cout << pile.first->title << " " << pile.second << endl;
  }
  cout << endl;

  int player_count = players.size();
  int turn_counter = 0;
  while(!supply.game_over())
  {
    Player* player = players[turn_counter % player_count];
    player->take_turn();

    if(++turn_counter >= 150)
    {
      cout << "Stopping Game: Too many turns (" << turn_counter << ")" << endl;
      break;
    }
  }

  cout << "Game Over!" << endl << endl;

  for(Player* player : players)
  {
    int victory_points = 0;

    for(auto cards: {player->deck, player->hand, player->discard_pile})
    {
      for(auto card : cards)
      {
        victory_points += card->victory_points;
      }
    }

    cout << player->name << ": " << victory_points << "points" << endl;
  }
}


/* Supply */
void Supply::setup(vector<Player*> players) 
{
  for(Player* player : players)
  {
    player->supply = this;
  }

  int player_count = players.size();

  //default values are for a 4 player game
  int kingdom_card_count = 10;
  int victory_card_count = 12;
  int curse_count = 30;
  int copper_count = 60 - 4 * 7;
  int silver_count = 40;
  int gold_count = 30;
  
  switch(player_count)
  {
    case 3:
      curse_count = 20;
      copper_count = 60 - 3 * 7;
      break;
    case 2:
      victory_card_count = 8;
      curse_count = 10;
      copper_count = 60 - 2 * 7;
      break;
    case 1: //no one player rules, but it works fine
      victory_card_count = 6;
      curse_count = 10;
      copper_count = 60 - 7;
      break;
  }

  // empty the supply card piles in case we want to play using old supply object
  card_piles.clear();
  
  // treasure cards
  card_piles[get_card("Copper")] = copper_count;
  card_piles[get_card("Silver")] = silver_count;
  card_piles[get_card("Gold")] = gold_count;
  
  // victory cards
  for(string title : {"Estate", "Duchy", "Province"})
  {
    card_piles[get_card(title)] = victory_card_count;
  }

  // curse cards
  card_piles[get_card("Curse")] = curse_count;

  // kingdom cards
  // todo: allow randomize or selection of specific Kingdom cards
  for(string title : {"Village", "Market", "Smithy"})
  {
    card_piles[get_card(title)] = kingdom_card_count;
  }
}

void Supply::pop_card(const Card* card)
{
  if(card_piles[card] > 0)
  {
    card_piles[card]--;
    if(card_piles[card] == 0)
    {
      piles_empty++;
    }
  }
}

bool Supply::game_over()
{
  if(piles_empty >= 3)
  {
    cout << "Three supply piles empty!" << endl;
    return true;
  }

  if(card_piles[get_card("Province")] == 0)
  {
    cout << "Last Province purchased!" << endl;
    return true;
  }

  return false;
}


/* Player */
Player::Player() {
  /* give player a starting deck of 7 Coppers and 3 Estates
   * then shuffle it and draw starting hand (5 cards) */

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

int Player::get_purse()
{
  return purse;
}

int Player::get_buys()
{
  return buys;
}

int Player::count_treasure()
{
  int sum = 0;
  for(auto card : hand)
  {
    sum += card->treasure_value;
  }
  return sum;
}

void Player::play_action_card(string )
{
  if(buy_phase) return;
  //todo: implement this
  // check that card is in hand
  // move card to play area
  // do card stuff
}

void Player::start_buy_phase()
{
  if(!buy_phase)
  {
    buy_phase = true;
    purse += count_treasure();
  }
}

void Player::buy_card(string title)
{
  if(!buy_phase) return;

  const Card* card = get_card(title);

  if(supply->card_piles[card] > 0 && card->cost <= purse)
  {
    cout << "Buying card: " << title << endl;
    supply->pop_card(card);
    purse -= card->cost;
    discard_pile.push_back(card);
  }
}


/* Player private */
void Player::draw_card()
{
  /* draw a card
   * if draw deck is empty and discard pile is not
   * recycle the discard pile into the deck
   */
  if(!deck.empty())
  {
    hand.push_back(deck.back());
    deck.pop_back();
  }
  else if(!discard_pile.empty())
  {
    shuffle_cards(discard_pile);
    deck.swap(discard_pile);
    draw_card();
  }
}

void Player::draw_cards(int num_cards)
{
  while(num_cards-- > 0) draw_card();
}

void Player::take_turn()
{
  // initialize turn state parameters
  actions = 1;
  card_draws = 0;
  buys = 1;
  purse = 0;
  buy_phase = false;

  cout << ">> " << name << "'s turn" << endl;
  cout << "hand: ";
  for(auto card : hand)
  {
    cout << card->title <<" ";
  }
  cout << endl;

  take_turn_impl();

  /* Clean-up phase: move cards into discard_pile and draw new hand */
  discard_pile.insert(discard_pile.end(), play_area.begin(), play_area.end());
  play_area.clear();

  discard_pile.insert(discard_pile.end(), hand.begin(), hand.end());
  hand.clear();

  draw_cards();

  cout << endl;
}


/* AutoPlayer implementation */
AutoPlayer::AutoPlayer() {}
AutoPlayer::AutoPlayer(string name) : Player(name) {}

void AutoPlayer::take_turn_impl()
{
  start_buy_phase();
  int purse = get_purse();
  cout << "purse value: " << purse << endl;

  while(get_buys() > 0 && get_purse() >= 3)
  {
    int purse = get_purse();
    if(purse >= 8)
    {
      buy_card("Province");
    }
    else if(purse >= 6)
    {
      buy_card("Gold");
    }

    buy_card("Silver");
  }
}


/* HumanPlayer */
HumanPlayer::HumanPlayer() {}

HumanPlayer::HumanPlayer(string name) : Player(name) {}

void HumanPlayer::take_turn_impl()
{
  //todo: implement command line interface for human player
}


/* Function definitions */

void shuffle_cards(vector<const Card*>& cards)
{
  /* Initialize default_random engine and seed with random_device 
   * for always random shuffling (uncomment #define for repeatable shuffling). 
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


