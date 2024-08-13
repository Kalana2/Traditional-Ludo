#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>


#include "types.c"
#include "logic.c"

int main(){

    srand(time(NULL));
    printLudoHeading();
    playerSetup();
    logic();
    
    return 0;

}