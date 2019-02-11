/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

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
//lines 31 -40 taken from examples from class
int test_endTurn(){
    int count = 0;
    int seed = 1000;
    int numPlayer = 4;
    int p; 
    int i;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    char *message;
    
    printf ("\n**********************\nunittest1.c -> TESTING the function endTurn():\n**********************\n");
    //testing with max of 4 players
    //testing if player's turn updates for max amount players
    for (p = 2; p <= numPlayer; p++){
    
        printf("\nTesting with %d players.\n", p);

        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(p, k, seed, &G);
        //now loop for the number of players
        for (i = 1; i <= p; i++){
            printf("\nTesting player %d out of %d players.\n", i, p);
            message = "current player is equal to current turn";
            assertTrue(G.whoseTurn, i-1, message, &count);
            //end turn and go to next player if there is one
            endTurn(&G);
            //otherwise its going out of bounds          
            if(i < p){
                message = "ended turn, next player's turn";
                assertTrue(G.whoseTurn, i, message, &count);
            }
        }
        message = "everyone got a turn, returned back to first player";
        assertTrue(G.whoseTurn, 0, message, &count);


    }
    //testing if cards are discarded for each player after turn and new hands are drawn
    printf("***************************************");
    for (p = 2; p <= numPlayer; p++){
    
        printf("\nTesting discard for %d players.\n", p);

        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(p, k, seed, &G);
        //now loop for the number of players
        for (i = 0; i < p; i++){
            printf("\nTesting player %d out of %d players.\n", i+1, p);
            message = "player holds 5 cards at start of turn";
            assertTrue(G.handCount[i], 5, message, &count);
            //otherwise its going out of bounds
            if((i+1) != p){
                message = "next player (before their turn) holds 0 cards";
                assertTrue(G.handCount[i+1], 0, message, &count);
            }
            //end turn and go to next player if there is one
            endTurn(&G);
            message = "player ends turn, all cards discarded";
            assertTrue(G.handCount[i], 0, message, &count);
            //otherwise its going out of bounds
            if((i+1) != p){
                message = "next player (now their turn) holds full hand";
                assertTrue(G.handCount[i+1], 5, message, &count);
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
    printf("\n*****************************\n*****************************\nSTART OF UNIT TESTS\n*****************************\n*****************************\n");
    test_endTurn();
    return 0;
}