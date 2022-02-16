#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HA04_EulerLib.h"

#define NUMOFSTATES 2

void RHS_MSD(double*rhs, double*y){ // mass spring damper

    //these are the values for task 2
    //values can be changed to desire
    double m = 1.0; // mass of object
    double c = 2.0; // feder constant
    double d = 3.0; // damper constant

    double x = y[0]; // position
    double v = y[1]; // speed

    /*calc derivatives and store in rhs*/

    rhs[0] = v;
    rhs[1] = (-(((d*v)/m)+((c*x)/m)));
}

void eulerSettings_MSD(simHandle* handle){
    /*num of states*/

    handle->numOfStates = (int)NUMOFSTATES;
    
    /*right hand site*/
    
    handle->f = &RHS_MSD;
    
    /*reserve storage for init state vec*/
    handle->stateVecInit = (double*)malloc(sizeof(double) * (handle->numOfStates));

    /*get user defined Simtime*/
    printf("Simtime (in s): \n");
    scanf("%lf", &handle->simTime);
    if(handle->simTime <= 0){
        printf("ERROR: Simulationtime must be greater than 0\n");
        while (handle->simTime <= 0)
        {
            printf("Simtime (in s), Simtime must be greater than 0: \n");
            scanf("%lf", &handle->simTime);
        }
    }

    /*get user defined StepSize*/
    printf("StepSize (in s): \n");
    scanf("%lf", &handle->stepSize);
    if(handle->stepSize <= 0){
        printf("ERROR: Stepsize must be greater than 0\n");
        while (handle->stepSize <= 0)
        {
            printf("StepSize (in s), Stepsize must be greater than 0: \n");
            scanf("%lf", &handle->stepSize);
        }
    }

    

    /*get init state position*/
    printf("position(t = 0): \n");

    scanf("%lf", &(handle->stateVecInit[0]));

    /*get init state speed*/
    printf("speed(t = 0): \n");

    scanf("%lf", &(handle->stateVecInit[1]));

    /*reserve storage for states and derivatives*/
    
    //ceil necessary, because integratorSteps can only be integers
    //ceil, so last "partial" will not get lost
    handle->stateVec = malloc(sizeof(double) * (handle->numOfStates) * (int)(ceil(handle->simTime/handle->stepSize)));
    handle->derivStateVec = malloc(sizeof(double) * (handle->numOfStates) * (int)(ceil(handle->simTime/handle->stepSize)));
    
    /*init states and derivatives with zero*/
    for(int i = 2; i < (ceil(handle->simTime/handle->stepSize)); i++){
        handle->stateVec[i] = 0;
        handle->stateVec[i+1] = 0;
        handle->derivStateVec[i] = 0;
        handle->derivStateVec[i+1] = 0;
    }
}

void eulerForward(simHandle* handle){ // this is called only once
    int numOfStates = handle->numOfStates;
    int integratorSteps = (int)ceil(handle->simTime/handle->stepSize);

    double* derivTemp = malloc(sizeof(double) * (handle->numOfStates));
    double* stateTemp = malloc(sizeof(double) * (handle->numOfStates));

    /*write init states*/
    for(int i = 0; i < numOfStates; i++){
        handle->stateVec[i] = handle->stateVecInit[i];
    }
    for(int i = 0; i < integratorSteps; i++){
        /*get derivatives*/
        
        stateTemp[0] = handle->stateVec[2*i];
        stateTemp[1] = handle->stateVec[2*i+1];
        RHS_MSD(derivTemp, stateTemp);
        handle->derivStateVec[2*i] = derivTemp[0];
        handle->derivStateVec[2*i+1] = derivTemp[1];

        for(int j = 0; j < numOfStates; j++){
        /*euler step*/
        handle->stateVec[i*2+2+j] = handle->stateVec[i*2+j]+handle->stepSize*handle->derivStateVec[i*2+j];
       }
    }
}

void showResults_MSD(simHandle* handle){
    int integratorSteps = (int)ceil(handle->simTime/handle->stepSize);
    /*print data to text file*/

    FILE *fPtr;
    fPtr = fopen("simData.txt", "w");
    if(fPtr == NULL){
        printf("ERROR: Could not open or create result file\n");
        exit(-1);
    }
    for(int i = 0; i<integratorSteps; i++){
        fprintf(fPtr, "%lf %lf %lf\n", i*handle->stepSize, handle->stateVec[i*2], handle->stateVec[i*2+1]);
    }
    fclose(fPtr);

    /*call gnuplot*/
    
    char *commandsForGnuplot[] = {"set title 'Results of simulation'",

                                  "set xlabel 'time in s'",

                                  "plot 'simData.txt' using 1:2 title 'Position over Time', '' using 1:3 title 'Speed over Time'"};

    FILE *gnuPlotPipe = popen("gnuplot -persistent", "w");
    if(gnuPlotPipe == NULL) {
        printf("ERROR: Could not open GnuPlot");
        exit(-1);
    }
    for(int i = 0; i < 3; i++){
        fprintf(gnuPlotPipe, "%s\n", commandsForGnuplot[i]);
    }
    fprintf(gnuPlotPipe, "exit");
    fclose(gnuPlotPipe);
}