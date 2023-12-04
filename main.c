#include<stdlib.h>
#include <stdio.h>

#define handCardCombinations 32

/// @brief this array takes the card combination bitstring as an index and returns the number of one bits
///        in it's binary representation, i.e. the number of cards in the combination
int handCombToBitCount[32];

/// @brief represents a card with a rank and suit 
struct card {
  //1:1, ..., 11:J, 12:Q, 13:K
  char rank;
  //0:heart, 1:diamond, 2:spade, 3:club
  char suit;

};

//a countable cribbage hand is 5 cards, the 4th index card is the up card.
struct card *hand;

/// @brief initializes hand combination bit count lookup table
void initialize() {

  // To initially generate the 
  // table algorithmically 
  handCombToBitCount[0] = 0; 
  for (int i = 0; i < 32; i++)
  { 
      handCombToBitCount[i] = (i & 1) + handCombToBitCount[i / 2]; 
  } 

  //allocate space for hand
  hand = malloc(sizeof(struct card) * 5);

  //define hand
  hand->rank = 11;
  (hand + 1)->rank = 11;
  (hand + 2)->rank = 11;
  (hand + 3)->rank = 11;
  (hand + 4)->rank = 11;

}

/// @brief function recieves a binary string representaiton of a combination of a  hand, that is
///        using the Card array defined above, the bit in the string is 1 if the card in the array is 
///        involved else 0 if not in the combination. Should return the cribbage score on that specific
///        hand combination
/// @param hand 
/// @return 
int score(int comb) {
  int sum = 0;

  if (handCombToBitCount[comb] == 5) {

  } else if (handCombToBitCount[comb] == 4) {

  } else if (handCombToBitCount[comb] == 3) {

  } else if (handCombToBitCount[comb] == 4) {

  } else if (handCombToBitCount[comb] == 2) {

  } else if (handCombToBitCount[comb] == 1) {

  } else if (handCombToBitCount[comb] == 0) {
    sum += 0;
  } else {
    printf("%s", "Unexpected behavior in \"score\" function");
  }

  return sum;
}

/// @brief function iterates through all possible 0, 1, 2, 3, 4, 5 card combinations of a hand, sums
///        the score of each combination, and returns the sum as the hand count
/// @return 
int handCount() {
  int count = 0;

  for (int cardCombination = 0; cardCombination < handCardCombinations; ++cardCombination) {
    count += score(cardCombination);
  }

  return count;
}

/// @brief main function
/// @return 
int main() {
  initialize();


  return 0;

}

