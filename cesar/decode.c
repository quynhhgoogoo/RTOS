#include "decode.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

void decode(char original_message[], char resulting_message[]){
    int a = 0;
    int b = 0;
    int len, num;

    len = strlen(original_message);
    num = sqrt(len);
    printf("Length of %s is %d\n", original_message, num);

    char matrix[8][8];
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
          matrix[i][j] = original_message[a];
          a++;
          printf("%c", matrix[i][j]);
        }
        printf("\n");
     }

    printf("============================\n");
    printf("Decoded message is :\n");

    for (int i = 0; i<num; i++){
      for(int j = 0; j<num; j ++){
        resulting_message[b]=matrix[j][i];
        b++;
      }
    }
printf("\n");
}

void print_result(char message[]){
        printf("%s",message);
	printf("\n");
}

