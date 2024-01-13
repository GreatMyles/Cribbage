#include <stdio.h>
#include <stdlib.h>

#include "handCount.h"

#define handCardCombinations 32

/// @brief this array takes the card combination bitstring as an index and returns the number of one bits
///        in it's binary representation, i.e. the number of cards in the combination
int handCombToBitCount[handCardCombinations];

/// @brief represents a card with a rank and suit 
struct card {
  //0:nullcard, 1:1, ..., 11:J, 12:Q, 13:K
  char rank;
  //0:heart, 1:diamond, 2:spade, 3:club, rank value + 8 -> is top card 
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

/// @brief implementation of insertion sort sorts a hand passed in by a pointer to its first card in 
/// non-increasing order
int sortHand (struct card *hand, int n) {
  int i, swpRank, swpSuit, j;
  for (i = 1; i < n; ++i) {
    j = i;
    while (j > 0 && (hand + j - 1)->rank < (hand + j)->rank) {
      swpRank = (hand + j - 1)->rank;
      swpSuit = (hand + j - 1)->suit;
      
      (hand + j - 1)->rank = (hand + j)->rank;
      (hand + j - 1)->suit = (hand + j)->suit;

      (hand + j)->rank = swpRank;
      (hand + j)->suit = swpSuit;

      j = j - 1;
    }	
  }
  return 0;
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


/// @brief this function is mainly used for the purpose of mapping the rank of a face card to the value 10
int rankToValue(struct card *theCard) {
  if ((theCard)->rank == 11 || (theCard)->rank == 12 || (theCard)->rank == 13)
    return 10;
  else return theCard->rank;
}

/// @brief this function takes a pointer to a subset of a hand as input and returns 2 if the set of cards is summed to fifteen
int fifteen(struct card *tempHand) {
  int sum = 0;
  for (int i = 0; i < 5; ++i) {
    sum += rankToValue((tempHand + i));
  }
  if (sum == 15)
    return 2;
  else 
    return 0;
}

/// @brief counts the points due to pairs in a hand subset (assumes the hand is sorted with all null cards at the end)) 
int pair(struct card *tempHand) {
  //switch (size) {
    return 2 * (tempHand->rank == (tempHand+1)->rank);
	//case 3: return 6 * (tempHand->rank == (tempHand+1)->rank && tempHand->rank == (tempHand+2)->rank);
    //case 4: return 12 * (tempHand->rank == (tempHand+1)->rank && tempHand->rank == (tempHand+2)->rank && tempHand->rank == (tempHand+3)->rank);
    //default: printf("pair evaluated incorrectly\n"); return -1;	
  //}

}


/// @brief counts the points due to runs in a hand, a 5 card hand should always be passed into this function
/// @param tempHand 
/// @return 
int runs(struct card *tempHand) {
  int score = -1;
  //create hand with no dupes to find longest run
  struct card *tempHandNoDupes = malloc(sizeof(struct card) * 5);
  tempHandNoDupes->rank = tempHand->rank;
  tempHandNoDupes->suit = tempHand->suit;

  int j = 1;
  for (int i = 1; i < 5 ; ++i) {
    if ((tempHand+i)->rank != (tempHandNoDupes+j-1)->rank){
      (tempHandNoDupes+j)->rank = (tempHand+i)->rank;
      (tempHandNoDupes+j)->suit = (tempHand+i)->suit;
      j += 1;
    }
  }

  while (j < 5) {
    (tempHandNoDupes+j)->rank = 0;
    (tempHandNoDupes+j)->suit = 0;
    j++;
  }

  //scan tempHand to identify type of run (single, double, triple, quad) and return correct amount of points
  int maxRunSize = 1;
	int runSize = 1;
  for (int i = 1; i < 5; ++i) {
    if ((tempHandNoDupes+i)->rank != 0 && (tempHandNoDupes+i)->rank == (tempHandNoDupes+i-1)->rank - 1) {
      runSize++;
      if (runSize > maxRunSize)
        {maxRunSize = runSize;}
    }
    else
      {runSize = 1;}
  }

  switch (maxRunSize) {
    case 5:
      score = 5;
      break;
    case 4:
      score = 4;
      for (int i = 1; i < 5; ++i) {
        if ((tempHand+i)->rank == (tempHand+i-1)->rank)
          {score = 8;break;}
      }
      break;
    case 3:{
      //iterate through hand, checking for pairs
      int i = 1;
			int pairs = 0;
      while (i < 5) {
				if ((tempHand+i)->rank == (tempHand+i-1)->rank) {
					pairs++;
					if (i < 4 && (tempHand+i+1)->rank == (tempHand+i-1)->rank) {
						score = 9;
						break;
					} else {
						i++;
					}
				}
				i++;
      }
			switch (pairs){
				case 0:
					score = 3;
					break;
				case 1:
					score = 6;
					break;
				case 2:
				  score = 12;
					break;
				case 3:
					score = 9;
					break;
			}
			break;
		}
    default:
      score = 0;
      break;
  }
  
  free(tempHandNoDupes);
  return score;
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
  for (int i = 0; i < 5; ++i) tempHand[i].rank = 0;

  // This chunk checks the bits in the comb string and compiles a temporary hand  
  if (cardChoiceCounter >> 4) {
    tempHand[4] = *(hand + 4);
    cardChoiceCounter -= 16;
  }
  if (cardChoiceCounter >> 3){
    
    tempHand[3] = *(hand + 3);
    cardChoiceCounter -= 8;
  }
  if (cardChoiceCounter >> 2){
    
    tempHand[2] = *(hand + 2);
    cardChoiceCounter -= 4;
  }
  if (cardChoiceCounter >> 1){
    
    tempHand[1] = *(hand + 1);
    cardChoiceCounter -= 2;
  }
  if (cardChoiceCounter){
    tempHand[0] = *(hand);
    cardChoiceCounter -= 1;
  }

  sortHand(tempHand, 5);

  if (handCombToBitCount[comb] == 5) {
    //fifteen
    sum = sum + fifteen(tempHand) + runs(tempHand);
  } else if (handCombToBitCount[comb] == 4) {
    //fifteen
	sum = sum + fifteen(tempHand);

  } else if (handCombToBitCount[comb] == 3) {
    //fifteen
  	sum = sum + fifteen(tempHand);

  } else if (handCombToBitCount[comb] == 2) {
    //fifteen
  	sum = sum + fifteen(tempHand) + pair(tempHand);

  } else if (handCombToBitCount[comb] == 1) {
	sum = sum + fifteen(tempHand);

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
