//
//  main.c
//  dailyCodingProblem172
//
//  Created by Denny Caruso on 31/08/2020.
//  Copyright © 2020 Denny Caruso. All rights reserved.
//

/*
     Daily Coding Problem 172 - Level: Medium
     This problem was asked by Dropbox.
     
     Given a string s and a list of words words, where each word is the same length,
     find all starting indices of substrings in s that is a concatenation of every word in words exactly once.
     
     For example, given s = "dogcatcatcodecatdog" and words = ["cat", "dog"],
     return [0, 13], since "dogcat" starts at index 0 and "catdog" starts at index 13.
     
     Given s = "barfoobazbitbyte" and words = ["dog", "cat"], return [] since there are no substrings composed
     of "dog" and "cat" in s. The order of the indices does not matter.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

int findIndexes(char *, char *, int *, int);
void getErrorMemory(char *);

int main(int argc, const char * argv[]) {
    char *string = "dogcatcatcodecatdog";
    char *words[] = { "dog", "cat" };
    char *revWords[] = { "cat", "dog" };
    
    int *occurrences = (int *) malloc(strlen(string) / (strlen(words[0]) + strlen(words[1])) * sizeof(int) *  (sizeof(words) / sizeof(words[0])));
    if(!occurrences) getErrorMemory("occurrences");
    
    int size = ((int) (strlen(string) / (strlen(words[0]) + strlen(words[1])))) *  (sizeof(words) / sizeof(words[0]));
    
    int nWords = sizeof(words) / sizeof(words[0]);
    for(int i = 0; i < size; i++) occurrences[i] = -1;
    
    char *key = (char *) malloc((sizeof(char) * size) + 1), *revKey = (char *) malloc((sizeof(char) * size) + 1);
    if(!key || !revKey) getErrorMemory("key");
    
    for(int i = 0; i < nWords; i++) strcpy(key + (strlen(words[0]) * i), words[i]);
    for(int i = 0; i < nWords; i++)strcpy(revKey + (strlen(words[0]) * i), revWords[i]);
    
    int i, j, counter = 0, idx;
    for (i = 0; i < size / 2; i++) {
        if (i == 0) {
            idx = findIndexes(string + counter, key, occurrences, i);
        } else {
            idx = findIndexes(string + counter + (strlen(words[0]) * 2), key, occurrences, i);
        }
        
        
        if (idx != -1) {
            occurrences[i] = (int) (idx + ((counter * strlen(key)))) % strlen(string);
            counter = occurrences[i];
        } else {
            break;
        }
    }
    
    counter = 0;
    for (j = 0; j < size / 2; j++) {
        if (j == 0) {
            idx = findIndexes(string + counter, revKey, occurrences, j);
        } else {
            idx = findIndexes(string + counter + (strlen(words[0]) * 2), revKey, occurrences, j);
        }

        if (idx != -1) {
            occurrences[j + i] = (int) (idx + ((counter * strlen(key)))) % strlen(string);
            counter = occurrences[j + i];
        } else {
            break;
        }
    }
    
    printf("[");
    for (int i = 0; i < size; i++) if (occurrences[i] != -1) printf(" %d", occurrences[i]);
    printf(" ]\n\n");
    
    return 0;
}

int findIndexes(char *string, char *key, int *occurrences, int counter) {
    int stringLength = (int) strlen(string), keyLength = (int) strlen(key);
    
    for (int i = 0; i <= (stringLength - keyLength); i++) {
        if (strncmp(string + i, key, keyLength) == 0) {
            return i + (keyLength * counter);
        }
    }
    return -1;
}

void getErrorMemory(char *errMsg) {
    printf("\nError allocating memory for %s...\n", errMsg);
    exit(EXIT_FAILURE);
}
