#include <stdio.h>
#include "approximatezerolib.h"

int main(){
    double x0;
    double derivationType;

    printf("What is your starting x: ");
    scanf("%lf", &x0);
    printf("Would you like to work with the analytic derivation [1] or numeric derivation [2]: ");
    scanf("%lf", &derivationType);
    //derivationType can only be equal to 1 or 2
    while(derivationType != 1 && derivationType != 2){
        printf("ERROR: Please enter a valid integer [1, 2]\n");
        printf("Would you like to work with the analytic derivation [1] or numeric derivation [2]: ");
        scanf("%lf", &derivationType);
    }

    approximateZero(x0, derivationType);

    return 0;
}