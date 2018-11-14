#include <stdio.h>
#include <math.h>
#include <string.h>
#include "decode.h"
#include <stdlib.h>

int main(void){
    char mess[70];
    char newmess[70];

    printf("Enter your message \n");
    gets(mess);

    decode(mess, newmess);
    print_result(newmess);

return(0);
}

