#include <stdio.h>
#include <math.h>
#include "functionlib.h"

double x1;
double derivationValue;
int iterations = 0;
int maxiterations = 1000;

void approximateZero(double x0, double derivationType){
    for(int counter = 0; counter < maxiterations; counter++){

        //derivation = 1 --> analytic derivation
        //derivation = 2 --> numeric derivation
        switch ((int)derivationType){
            case 1: derivationValue = analyticDerivation(x0); break;
            case 2: derivationValue = numericDerivation(x0); break;
        }

        if(fabs(valueOfFunction(x0))<pow(10,-10)){
            break;
        }
        else if(fabs((x0-(valueOfFunction(x0)/derivationValue))-x0)<pow(10,-10)){
            break;
        }
        else{
            //x1 contains new xn+1
            x1 = (x0-(valueOfFunction(x0)/derivationValue));
            //reset startvalue for next iteration; x0 contains now xn+1
            x0 = x1;
        }
        iterations++;
    }
    if(iterations == maxiterations){
        printf("WARNING: The maximum amount of iterations has been reached, the accuracy of the approximated zero can not be guaranteed\n");
    }
    //returning x0, because it contains the latest xn+1
    printf("i = %10d | x=\t%10.10lf\n", iterations, x0);
}