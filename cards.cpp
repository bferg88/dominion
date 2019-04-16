#include "cards.h"

#include <unordered_map>

namespace Dominion {

using namespace std;

/* Card constructor definitions */
Card::Card() {}
Card::Card(string title, int cost) : title(title), cost(cost) {}


/* helper functions for defining simple card types concisely*/
Card construct_treasure_card(string title, int cost, int treasure_value)
{
  Card card(title, cost);
  card.type = {"Treasure"};
  card.treasure_value = treasure_value;
  return card;
}

Card construct_victory_card(string title, int cost, int victory_points)
{
  Card card(title, cost);
  card.type = {"Victory"};
  card.victory_points = victory_points;
  return card;
}

Card construct_basic_kingdom_card(string title, int cost, int card_increment, 
  int action_increment, int buy_increment, int coin_increment)
{
  Card card(title, cost);
  card.type = {"Kingdom"};
  card.card_increment = card_increment;
  card.action_increment = action_increment;
  card.buy_increment = buy_increment;
  card.coin_increment = coin_increment;
  return card;
}


/*
 * Define all the cards
 */
vector<Card> make_cards()
{
  vector<Card> cards;

  Card card; //temp location for building cards

  /* Treasure Cards */
  card = construct_treasure_card("Copper", 0, 1);
  cards.push_back(card);

  card = construct_treasure_card("Silver", 3, 2);
  cards.push_back(card);

  card = construct_treasure_card("Gold", 6, 3);
  cards.push_back(card);

  /* Victory Cards */
  card = construct_victory_card("Estate", 2, 1);
  cards.push_back(card);

  card = construct_victory_card("Duchy", 5, 3);
  cards.push_back(card);

  card = construct_victory_card("Province", 8, 6);
  cards.push_back(card);

  /* Curse Cards */
  card = Card("Curse", 0);
  card.type = {"Curse"};
  card.victory_points = -1;
  cards.push_back(card);
  
  /* Kingdom Cards */
  card = construct_basic_kingdom_card("Village", 3, 1, 2, 0, 0);
  cards.push_back(card);

  card = construct_basic_kingdom_card("Market", 5, 1, 1, 1, 1);
  cards.push_back(card);

  card = construct_basic_kingdom_card("Smithy", 4, 3, 0, 0, 0);
  cards.push_back(card);

  return cards;
}


/* Return pointer to a constant card definition.
 * For first run only, the card definitions are created 
 * and stored in a static variable map as constants 
 * to prevent accidental modification of card definitions.
 */
const Card* get_card(string title)
{
  static unordered_map<string, const Card> card_map;
  static bool card_map_initialized = false;

  if(!card_map_initialized) 
  {
    card_map_initialized = true;

    vector<Card> cards = make_cards();
    for(const Card card : cards) {
      card_map.insert({card.title, card});
    }
  }

  return &card_map[title];
}


}//namespace Dominion
