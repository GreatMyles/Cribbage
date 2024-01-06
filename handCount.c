#include <stdio.h>
#include <stdlib.h>

#include "handCount.h"

#define handCardCombinations 32

/// @brief this array takes the card combination bitstring as an index and returns the number of one bits
///        in it's binary representation, i.e. the number of cards in the combination
int handCombToBitCount[32];

/// @brief represents a card with a rank and suit 
struct card {
  //0:nullcard, 1:1, ..., 11:J, 12:Q, 13:K
  char rank;
  //0:heart, 1:diamond, 2:spade, 3:club
  char suit;
};

//a countable cribbage hand is 5 cards, the 4th index card is the up card.
struct card *hand;

/// @brief must be called after init function
void loadHand (char r1, char s1, char r2, char s2, char r3, char s3, char r4, char s4, char r5, char s5) {
  hand->rank = r1;
  hand->suit = s1;
  (hand + 1)->rank = r2;
  (hand + 1)->suit = s2;
  (hand + 2)->rank = r3;
  (hand + 2)->suit = s3;
  (hand + 3)->rank = r4;
  (hand + 3)->suit = s4;
  (hand + 4)->rank = r5;
  (hand + 4)->suit = s5;
}

/// @brief initializes hand combination bit count lookup table
void initHandCount() {
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
  loadHand(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

int rankToValue(struct card *theCard) {
  if ((theCard)->rank == 11 || (theCard)->rank == 12 || (theCard)->rank == 13)
    return 10;
  else return theCard->rank;
}

int fifteen(struct card *tempHand) {
  int sum = 0;
  for (int i = 0; i < 5; ++i) {
    printf("%d\n", (tempHand + i)->rank);
    sum += rankToValue((tempHand + i));
  }
  printf("%s%d\n", "sum: ", sum);
  if (sum == 15)
    return 2;
  else 
    return 0;
}

/// @brief function recieves a binary string representaiton of a combination of a  hand, that is
///        using the Card array defined above, the bit in the string is 1 if the card in the array is 
///        involved else 0 if not in the combination. Should return the cribbage score on that specific
///        hand combination
/// @param hand 
/// @return 
int score(int comb) {
  int sum = 0;

  int cardChoiceCounter = comb;
  
  struct card tempHand[5];
  for (int i = 0; i < 5; ++i) tempHand[0].rank = 0;


  if (cardChoiceCounter & 16) {
    tempHand[4] = *(hand + 4);
    cardChoiceCounter -= 16;
  }
  if (cardChoiceCounter & 8){
    
    tempHand[3] = *(hand + 3);
    cardChoiceCounter -= 8;
  }
  if (cardChoiceCounter & 4){
    
    tempHand[2] = *(hand + 2);
    cardChoiceCounter -= 4;
  }
  if (cardChoiceCounter & 2){
    
    tempHand[1] = *(hand + 1);
    cardChoiceCounter -= 2;
  }
  if (cardChoiceCounter & 1){
    
    tempHand[0] = *(hand);
    cardChoiceCounter -= 1;
  }
  
  if (handCombToBitCount[comb] == 5) {
    //fifteen
    sum += fifteen(tempHand);
  } else if (handCombToBitCount[comb] == 4) {
    //fifteen
    sum += fifteen(tempHand);

  } else if (handCombToBitCount[comb] == 3) {
    //fifteen
    sum += fifteen(tempHand);
  } else if (handCombToBitCount[comb] == 2) {
    //fifteen
    sum += fifteen(tempHand);
  } else if (handCombToBitCount[comb] == 1) {

  } else if (handCombToBitCount[comb] != 0) {
    printf("%s\n", "Unexpected behavior in \"score\" function");
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