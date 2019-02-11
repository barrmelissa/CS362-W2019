/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
//lines 33 -47 taken from examples from class
int test_gainCard(){
    int count = 0;
    int seed = 1000;
    // int numPlayer = 4;
    int i;
    int result1;
    int size;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    char *message;
    srand(time(NULL));
    printf ("\n**********************\nunittest4.c -> TESTING the function gainCard():\n**********************\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(2, k, seed, &G);
    size = sizeof(k)/sizeof(int);
    printf("\n****Testing discard pile****\n\n");
    //checking discardcount after gaining each card in k
    for(i=0; i < size; i++){
        result1 = G.discardCount[1];
        gainCard(k[i], &G, 0, 1);
        message = "discard pile increases after we run gaincard";
        assertTrue(G.discardCount[1], result1+1, message, &count);
    }
    printf("\n****Testing hand count****\n\n");
    //checking handcount after gaining each card in k
    for(i=0; i < size; i++){
        result1 = G.handCount[1];
        gainCard(k[i], &G, 2, 1);
        message = "hand count increases after we run gaincard";
        assertTrue(G.handCount[1], result1+1, message, &count);
    }
    printf("\n****Testing deck count****\n\n");
    //checking deckcount after gaining each card in k
    for(i=0; i < size; i++){
        result1 = G.deckCount[1];
        gainCard(k[i], &G, 1, 1);
        message = "deck count increases after we run gaincard";
        assertTrue(G.deckCount[1], result1+1, message, &count);
    }
    printf("\n****Testing supply count****\n\n");
    //checking supplycount after gaining each card in k
    for(i=0; i < size; i++){
        result1 = G.supplyCount[k[i]];
        gainCard(k[i], &G, 1, 1);
        message = "supply count decreases after we run gaincard";
        assertTrue(G.supplyCount[k[i]], result1-1, message, &count);
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
    test_gainCard();
    return 0;
}