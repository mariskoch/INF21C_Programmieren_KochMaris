#include <stdio.h>

int main() {
    //prints the sum of two doubles in console
    double first_summand = 5.5;
    double second_summand = 10.5;
    double result = first_summand + second_summand;
    //printf("Integer addition: %lf + %lf = %lf", first_summand, second_summand, result);

    //sum of numbers from 0 to 99
    int loop_sum = 0;
    for(int i = 0; i < 100; i++) {
        loop_sum += i;
    }
    //printf("The result of the "for" loop_sum is: %d", loop_sum);

    //sum of numbers from FIRST_INPUT to SECOND_INPUT
    int start = 0;
    int end = 100;
    int sum = 0;
    int counter = 0;

    printf("Sum from: ");
    scanf("%d", &start);

    printf("Sum to: ");
    scanf("%d", &end);

    while (counter <= end) {
        sum += counter;
        counter++;
    }
    printf("The sum from %d to %d = %d", start, end, sum);



    return 0;
}