#include <stdio.h>

#include "handCount.h"

/// @brief main function
/// @return 
int main() {
  initHandCount();
  loadHand(
    12, 1,
    5, 1,
    1, 1,
    7, 1, 
    8, 1
  );

  printf("%d", handCount());
  return 0;

}

