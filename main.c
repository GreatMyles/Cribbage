#include <stdio.h>
#include <string.h>

#include "handCount.h"


int defawlt() {
  initHandCount();
  loadHand(
    12, 1,
    5, 1,
    1, 1,
    7, 1, 
    8, 1
  );

  printf("%d\n", handCount());

  loadHand(
    12, 2,
    5, 0,
    13, 1,
    5, 2, 
    10, 3
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


























