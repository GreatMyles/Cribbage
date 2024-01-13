#include <stdio.h>
#include <string.h>

#include "handCount.h"


int defawlt() {
  initHandCount();
  loadHand(
    2, 1,
    3, 1,
    1, 1,
    7, 1, 
    8, 9
  );

  printf("%d\n", handCount());
  //TODO: this hand is bugged
  loadHand(
    12, 3,
    5, 11,
    13, 3,
    5, 3, 
    11, 3
  );

  printf("%d\n", handCount());

  loadHand(
    5, 2,
    5, 0,
    5, 1,
    5, 2, 
    10, 3
  );

  printf("%d\n", handCount());

  return 0;
}

int input(char* arg) {
  if (strcmp(arg, "i"))
    return -1;

  return 0;

}

/// @brief main function
/// @return 
int main(int argc, char *argv[]) {
  switch (argc) {
    case 1: return defawlt();
    case 2: return input(argv[1]);
  }

  return -1;
}


























