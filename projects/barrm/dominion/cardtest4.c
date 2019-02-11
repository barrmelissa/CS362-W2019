/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

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

int test_adventurer() {
	int count = 0;
    int tresureCards = 0;
    int discarded = 1;
    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	char *message;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\n----------------- cardtest4.c -> Testing Card: %s ----------------\n", TESTCARD);

	printf("TEST 1: revealing only 2 treasure cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

    message = "handcount before card is played is at 5";
    assertTrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + tresureCards, message, &count);
    tresureCards = 2;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    message = "handcount after adventure card is played increases by 2 for 2 treasure cards";
    assertTrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + tresureCards, message, &count);
    
    int cardDrawn;
    int expectedCard;
    //checking that the two cards added in the new hand are now treasure cards
    for(i=1; i <= 2; i++){
        cardDrawn = testG.hand[thisPlayer][testG.handCount[thisPlayer]-i];
        expectedCard = G.hand[thisPlayer][G.handCount[thisPlayer]-i];
        message = "added cards in handcount are indeed treasure cards";
        assertTrue(cardDrawn, expectedCard, message, &count);
    }
   
   	printf("TEST 2: discard count updates\n");
   //I put a bug in the original code so this won't work but showing that it doesn't
    message = "discard count upated";
    assertTrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+discarded, message, &count);
    shuffle(thisPlayer, &testG);
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    message = "shuffled and ran again, new discard count upated";
    assertTrue(testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+discarded, message, &count);
    if(count == 0){
        printf("\nAll tests passed!\n\n");
    }
    else{
        printf("\nERROR: %d tests failed\n\n", count);
    }

	return 0;
}

int main(){
	test_adventurer();
	return 0;
}
