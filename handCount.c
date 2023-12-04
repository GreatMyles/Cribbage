#include <stdio.h>

#define possibleHands 32


int score(int hand) {
  return 1;
}

int handCount() {

  int count = 0;

  for (int hand = 0; hand < possibleHands; ++hand) {
    count += score(hand);
  }

  return count;

}