#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    
     srand(time(NULL));
    
    int jeu = (float)rand()/RAND_MAX *2+1;
    printf("%d\n",jeu);



    return 0;
}