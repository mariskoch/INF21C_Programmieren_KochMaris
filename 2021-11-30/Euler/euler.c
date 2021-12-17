#include <stdio.h>

int main() {
    int numberOfSummands;
    double result = 0;
    double iFactorial = 1;
    printf("How many summands do you want to work with: ");
    scanf("%d", &numberOfSummands);
    if(numberOfSummands < 0) {
        printf("Please enter a valid number");
    }

    for(int i = 0; i <= numberOfSummands; i++){
        iFactorial = 1;
        for(int j = i; j > 0; j--){
            iFactorial = iFactorial * j;
        }
        printf("%lf\n", iFactorial);
        result += (1/iFactorial);
    }

    //Format: k = 0 | fac =          16184321 | e = 2.71828...

    printf("Result: %lf", result);
    return 0;
}