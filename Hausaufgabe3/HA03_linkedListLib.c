#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HA03_linkedListLib.h"

void addListElem(listElement *start)
{

    listElement *new;
    new = (listElement *)malloc(sizeof(listElement));
    if (new == NULL)
    {
        printf("can't reserve storage.\n");
        return;
    }

    listElement *currElem = start;
    while (currElem->nextElem != NULL)
        currElem = currElem->nextElem; // get last elem in list
    currElem->nextElem = new;          // add new to the end of list
    new->nextElem = NULL;

    /* fill data in new element */
    printf("Please enter last name: \n");
    scanf("%s", new->lastName);
    printf("Please enter first name: \n");
    scanf("%s", new->firstName);
    printf("Please enter age: \n");
    scanf("%d", &(new->age));
    printf("end of function\n");
}

void printList(listElement *start)
{

    if (start->nextElem == NULL)
        printf("List is empty.\n");
    else
    {
        int i = 0;
        listElement *currElem = start;
        printf("\ncurrent list:\n\n");
        do
        {
            currElem = currElem->nextElem;
            printf("%d", i);
            i++;
            printf("\t last name: %s\n", currElem->lastName);
            printf("\t first name: %s\n", currElem->firstName);
            printf("\t age: %d\n", currElem->age);
        } while (currElem->nextElem != NULL);
    }
    printf("\n");
}

void delListElem(listElement *start)
{
    listElement *temp1, *temp2;
    int elementToDelete;

    if(start->nextElem == NULL){
        printf("ERROR: List is empty, there is nothing to delete\n\n");
        return;
    }

    printList(start);
    printf("What element do you want to delete: \n");
    scanf("%d", &elementToDelete);
    system("cls");   
    printList(start);

    while (elementToDelete<0 || elementToDelete>getLenOfList(start)-1){
        printf("ERROR: Inedex exceeds length of list\n");
        printf("What element do you want to delete: \n");
        scanf("%d", &elementToDelete);
        system("cls");
        printList(start);
    }

    temp2 = start;
    for(int i = 0; i < elementToDelete; i++){
        temp1 = temp2->nextElem;
        temp2 = temp1;
    }
    free(temp2->nextElem);
    temp2->nextElem = temp2->nextElem->nextElem;
    system("cls");
    printf("\nelement %d was successfully deleted\n\n", elementToDelete);
}

void delList(listElement *start)
{
    listElement *temp1, *temp2;
    temp1 = start->nextElem;

    if(start->nextElem == NULL){
        printf("ERROR: List is empty, there is nothing to delete\n\n");
        return;
    }

    while (temp1->nextElem != NULL)
    {
        temp2 = temp1->nextElem;
        temp1->nextElem = temp2->nextElem;
        free(temp2);
    }
    free(temp1);
    start->nextElem = NULL;
    printf("The entire list has successfully been deleted\n\n");
}

int getLenOfList(listElement *start)
{ // we use this for save list fcn

    int counter = 0;
    listElement *currElem = start;
    while (currElem->nextElem != NULL)
    { // get last elem in list
        currElem = currElem->nextElem;
        counter++;
    }
    return counter;
}

void saveList(listElement *start)
{
    listElement *temp;
    //225 + ".txt" is the maximum length of a filename windows supports
    int charLen = 225;
    char fileName[charLen];
    char *fileNameWithFileending = calloc(charLen+4, sizeof(char));
    FILE *fPtr;
    
    if(start->nextElem == NULL){
        printf("ERROR: List is empty, there is nothing to save\n\n");
        return;
    }
    printf("What should the textfile be named [max. length 225], do not enter a file ending: \n");
    scanf("%s", fileName);

    strcat(fileNameWithFileending, fileName);
    strcat(fileNameWithFileending, ".txt");

    fPtr = fopen(fileNameWithFileending, "w");
    
    if(fPtr == NULL){
        printf("ERROR: Could not open or create file\n");
        return;
    }

    fprintf(fPtr, "%d\n", getLenOfList(start));
    temp = start->nextElem;
    for(int i = 0; i < getLenOfList(start); i++){
        fprintf(fPtr, "%s\t", temp->lastName);
        fprintf(fPtr, "%s\t", temp->firstName);
        fprintf(fPtr, "%d\n", temp->age);
        temp = temp->nextElem;
    }

    fclose(fPtr);
    system("cls");
    printf("\nThe list was successfully saved in %s\n\n", fileNameWithFileending);
}

void loadList(listElement *start)
{
    //229 is maximum length of filename that windows supports
    char filename[229];
    FILE *fPtr;
    int length;

    if(system("dir *.txt >nul 2>nul") == 1){
        system("cls");
        printf("ERROR: There is no *.txt file in your directory\n\n");
        return;
    }

    system("dir *.txt");
    printf("Which file do you want to load: \n");
    scanf("%s", &filename);

    while ((fPtr = fopen(filename, "r"))==NULL)
    {
        system("cls");
        system("dir *.txt");
        printf("ERROR: This file does not exist or cannot be opened\n");
        printf("Which file do you want to load: \n");
        scanf("%s", &filename);
    }

    fscanf(fPtr, "%d", &length);

    for(int i = 0; i < length; i++){
        listElement *new;
        new = malloc(sizeof(listElement));
        listElement *currElem = start;
        while (currElem->nextElem != NULL){
            currElem=currElem->nextElem;
        }
        currElem->nextElem = new;
        new->nextElem = NULL;

        fscanf(fPtr, "%s %s %d\n", new->lastName, new->firstName, &(new->age));
    }
    fclose(fPtr);
    system("cls");
    printf("Loaded list successfully\n");
    printList(start);
}


void exitFcn(listElement *start)
{
    int exitValue;

    //does not ask whether to safe, when list is empty
    if(start->nextElem == NULL) {
        printf("\nList was empty, there is no need to save anything\n\n");
        return;
    } 

    printf("Do you want to save your current list? \n");
    printf("0... No\n");
    printf("1... Yes\n");
    scanf("%d", &exitValue);

    while (exitValue != 0 && exitValue != 1)
    {
        system("cls");
        printf("ERROR: Please enter a valid integer\n");
        printf("Do you want to save your current list? \n");
        printf("0... No\n");
        printf("1... Yes\n");
        scanf("%d", &exitValue);
    }
    
    switch (exitValue)
    {
    case 0:
        break;
    case 1:
        saveList(start);
        break;
    default:
        break;
    }
}

void sortList(listElement *start)
{

    printf("\n>>sortList fcn is tbd.\n\n");
}

void stringToLower(char *string)
{

    printf("\n>>stringToLower fcn is tbd.\n\n");
}
