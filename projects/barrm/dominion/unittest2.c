/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

//made my own assertTrue function
int assertTrue(int result, int test, char *message, int *count){
    if(result == test){
        printf("PASS: %s\n", message);
    }else{
        printf("FAIL: %s\n", message);
        *count += 1;
    }
    return 0;
}

//testing function
//lines 33 -42 taken from examples from class
int test_numHandCards(){
    int count = 0;
    int seed = 1000;
    int numPlayer = 4;
    int p, i, n, l; 
    int result1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    char *message;
    srand(time(NULL));
    printf ("\n**********************\nunittest2.c -> TESTING the function numHandCards():\n**********************\n");

    //looping through for the # of players to play the game, max of 4
    for (l = 2; l <= numPlayer; l++){
        printf("\n****************\nTesting with %d players\n", l);
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(l, k, seed, &G);
        for (i = 1; i <= l; i++){
            printf("\nTesting player %d\n", i);
            message = "original hand is 5";
            result1 = numHandCards(&G);
            assertTrue(G.handCount[i-1], numHandCards(&G), message, &count);
            drawCard(i-1, &G);
            message = "drawing card adds 1 to total hand";
            assertTrue(G.handCount[i-1], result1+1, message, &count);
            result1 += 1;
            //randomly decide how many cards to remove, not bad becuase I'm not randomly choosing inputs
            //I'm just randomly deciding how many to take out just to give some variety          
            n = rand() % result1;
            for(p=0; p<n; p++){
                discardCard(n, i-1, &G, 0);
            }
            message = "discarded randomly decided amount of cards";
            assertTrue(G.handCount[i-1], result1-n, message, &count);
            endTurn(&G);
            if(i < l){
                message = "turn ended, hand count back to 5";
                assertTrue(G.handCount[i], 5, message, &count);
            }
        }

    }
    if(count == 0){
        printf("\nAll tests passed!\n\n");
    }
    else{
        printf("\nERROR: %d tests failed\n", count);
    }

    return 0;
}

int main(){
    test_numHandCards();
    return 0;
}