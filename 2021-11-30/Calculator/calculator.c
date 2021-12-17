//Task:     Create calculator
//Names:    Adrian, Maris, Sophie, Nils, Ari, Anastasia
//Date:     30.11.2021

#include <stdio.h>

int main() {
    int typeOfCalculation;
    double first;
    double second;

    printf("What type of calculation do you want to execute? Addition [1], Subtraction [2], Multiplication [3], Division[4]: ");
    scanf("%d", &typeOfCalculation);

    if(typeOfCalculation > 4 || typeOfCalculation < 1) {
        printf("Please enter a number between 1 and 4.");
        return 1;
    }

    printf("First value: ");
    scanf("%lf", &first);
    printf("Second value: ");
    scanf("%lf", &second);

    if(typeOfCalculation == 4 && second == 0) {
        printf("Division by zero is not allowed.");
        return 1;
    }

    switch(typeOfCalculation) {
        case 1: printf("Result of addition: %lf + %lf = %lf", first, second, first+second); break;
        case 2: printf("Result of subtraction: %lf - %lf = %lf", first, second, first-second); break;
        case 3: printf("Result of multiplication: %lf * %lf = %lf", first, second, first*second); break;
        case 4: printf("Result of division: %lf / %lf = %lf", first, second, first/second); break;
        default: printf("An unexpected error occured."); return 1;
    }

    return 0;
}