/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
//lines 32 -42 taken from examples from class
int test_supplyCount(){
    int count = 0;
    int seed = 1000;
    int numPlayer = 4;
    int i, l; 
    int result1;
    int result2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    char *message;
    srand(time(NULL));
    printf ("\n**********************\nunittest3.c -> TESTING the function supplyCount():\n**********************\n");

    //looping through to test the 4 different cards in the supply initlized
    for (l = 2; l <= numPlayer; l++){
        printf("\n****************\nTesting with %d players\n", l);
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(l, k, seed, &G);
        //checking that all the initilized ones are correct
        for(i=0; i<=6; i++){
            result1 = supplyCount(i, &G);
            message = "full supply initilized correctly at start of game";
            assertTrue(G.supplyCount[i], result1, message, &count);
        }
    }
    //testing buying a card
    result2 = supplyCount(copper, &G);
    buyCard(copper, &G);
    message = "supply updated after card bought";
    assertTrue(G.supplyCount[copper], result2-1, message, &count);   

    if(count == 0){
        printf("\nAll tests passed!\n\n");
    }
    else{
        printf("\nERROR: %d tests failed\n", count);
    }

    return 0;
}

int main(){
    test_supplyCount();
    return 0;
}