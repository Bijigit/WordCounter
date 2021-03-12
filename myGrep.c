#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myGrep.h"

int main(int argc, char *argv[]){
    FILE *inputFile = NULL;
    char linebuffer[150];
    char longestLine[150];
    int longestLength;
    int numLines = 0;
    int numOccurrences = 0;
    OccurrenceNode *head = NULL;
    OccurrenceNode *temp = NULL;
    OccurrenceNode *tail = NULL;
    char *wordPtr = NULL;
    int wordPos;
    char tempStr[150];

   if(argc != 3){
        printf("myGrep: improper number of arguments\nUsage: ./a.out <filename> <word>");
        return 0;
    }
    
    inputFile = fopen(argv[1], "r");
    while(!feof(inputFile)){//while not at the end of the file
        numLines++;
        fgets(linebuffer, 150, inputFile);//get first line
        longestLength = updateLongestLine(longestLength, longestLine, linebuffer);//this method returns the length of the longer string as an int
        strcpy(tempStr, linebuffer); //strtok corrupts original string, so the current string is coppied to a temp string to be preserved
        wordPtr = (char *)strtok(tempStr, " .,?/\'\"-:;");//gets next token in current string
        wordPos = 0;
        while(wordPtr){
            if(strcmp(wordPtr, argv[2]) == 0){  
                if(head == NULL){   //if this is the first occurrence
                    //creates first node
                    head = (OccurrenceNode *)malloc(sizeof(OccurrenceNode));
                    tail = head;
                    temp = head;
                    head->lineNumber = numLines;
                    strcpy(head->lineText, linebuffer);
                    head->wordPosition = wordPos;
                    head->next = NULL;
                    numOccurrences++;
                }else{  //using a tail pointer to allow adding to the end of the linked list.
                        //this allows the list to be read front to back with O(n) time complexity instead of
                        //O(n^2) by iterating to the end for every node we want to print
                    //creates subsequent nodes
                    tail->next = (OccurrenceNode *)malloc(sizeof(OccurrenceNode));
                    tail = tail->next;
                    tail->lineNumber = numLines;
                    strcpy(tail->lineText, linebuffer);
                    tail->wordPosition = wordPos;
                    tail->next = NULL;
                    numOccurrences++;
                }
            }
            wordPtr = (char *)strtok(NULL, " .,?/\'\"-:;"); //get next token
            wordPos++;
        }
    }

    printf("%s %s %s\n", argv[0], argv[1], argv[2]);
    fclose(inputFile);
    printf("longest line: %snum chars: %d\nnum lines: %d\n", longestLine, longestLength, numLines);
    printf("total occurrences of word: %d\n", numOccurrences);
    printLinkedList(head, temp);
    return 0;
}

int updateLongestLine(int currentLongestLength, char * longestLine, char * currentLine){
    int currentLength = strlen(currentLine);
    if(currentLength > currentLongestLength){
        strcpy(longestLine, currentLine);
        return currentLength;
    }
    return currentLongestLength;
}

void printLinkedList(OccurrenceNode * head, OccurrenceNode * temp){
    while(head){
        printf("line %d; word %d; %s", head->lineNumber, head->wordPosition, head->lineText);
        head = head->next;
        free(temp);
        temp = head;
    }
}
