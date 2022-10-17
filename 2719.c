#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  int industria[20][12];

  // alocate memory
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 12; j++) {
      scanf(" %d", &industria[i][j]);
    }
  }

  // first break
  int firstMonth;
  int firstYear;

  scanf(" %d", &firstMonth);
  scanf(" %d", &firstYear);

  // second break
  int secondMonth;
  int secondYear;

  scanf(" %d", &secondMonth);
  scanf(" %d", &secondYear);

  // calculate
  int firstRow = firstYear - 2000;
  int firstCol = firstMonth - 1;
  int secondRow = secondYear - 2000;
  int secondCol = secondMonth - 1;

  // output
  if (firstRow == secondRow) {
    int sum = 0;
    for (int i = firstCol; i <= secondCol; i++) {
      sum += industria[firstRow][i];
    }

    printf("%d", sum);
  }

  if (firstRow < secondRow) {
    int sum = 0;
    for (int i = firstCol; i < 12; i++) {
      sum += industria[firstRow][i];
    }

    for (int i = firstRow + 1; i < secondRow; i++) {
      for (int j = 0; j < 12; j++) {
        sum += industria[i][j];
      }
    }

    for (int i = 0; i <= secondCol; i++) {
      sum += industria[secondRow][i];
    }

    printf("%d", sum);
  }

  return 0;
}