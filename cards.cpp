#include "dominion.h"

#include <unordered_map>
#include <iostream>

namespace Dominion {

using namespace std;

/* Card constructor definitions */
Card::Card() {}
Card::Card(string title, int cost) : title(title), cost(cost) {}


/* helper function for quickly defining simple card types */
Card construct_treasure(string title, int cost, int treasure_value)
{
  Card card(title, cost);
  card.type = {"Treasure"};
  card.treasure_value = treasure_value;
  return card;
}

Card construct_victory(string title, int cost, int victory_points)
{
  Card card(title, cost);
  card.type = {"Victory"};
  card.victory_points = victory_points;
  return card;
}


/*
 * Define all the cards
 */
vector<Card> make_card_vector()
{
  vector<Card> card_vector;

  Card card; //temp location for building cards

  /* Treasure Cards */
  card = construct_treasure("Copper", 0, 1);
  card_vector.push_back(card);

  card = construct_treasure("Silver", 3, 2);
  card_vector.push_back(card);

  card = construct_treasure("Gold", 6, 3);
  card_vector.push_back(card);

  /* Victory Cards */
  card = construct_victory("Estate", 2, 1);
  card_vector.push_back(card);

  card = construct_victory("Duchy", 5, 3);
  card_vector.push_back(card);

  card = construct_victory("Province", 8, 6);
  card_vector.push_back(card);

  /* Curse Cards */
  
  /* Kingdom Cards */


  return card_vector;
}

/* Returns pointer to card definition.
 * For first run only, the card definitions are created 
 * and stored in a static variable.
 */
const Card* get_card(string title)
{
  static unordered_map<string, Card> card_map;
  static bool card_map_initialized = false;

  if(!card_map_initialized) 
  {
    card_map_initialized = true;

    vector<Card> card_vector = make_card_vector();
    for(Card card_n : card_vector) {
      card_map[card_n.title] = card_n;
    }
  }

  return &card_map[title];
}


}//namespace Dominion
