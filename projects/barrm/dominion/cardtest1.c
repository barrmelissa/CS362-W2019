/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"

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

int test_greatHall() {
	int count = 0;
    int newCards = 0;
	int newAction = 0;
    int discarded = 1;
    int shuffledCards = 0;

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

	printf("\n----------------- cardtest1.c -> Testing Card: %s ----------------\n", TESTCARD);

	printf("TEST 1: +1 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	// choice1 = 1;
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;
	message = "hand count has new card added and card discared";
	assertTrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded, message, &count);
	message = "deck count has new card subtracted and shuffles cards";
	assertTrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards, message, &count);

	printf("TEST 2: +1 action\n");

	newAction = 1;
	message = "action added to total action count";
	assertTrue(testG.numActions, G.numActions + newAction, message, &count);

	printf("TEST 3: +1 discard\n");
	message = "card discarded, played card count updated";
	assertTrue(testG.playedCardCount, G.playedCardCount + discarded, message, &count);

    if(count == 0){
        printf("\nAll tests passed!\n\n");
    }
    else{
        printf("\nERROR: %d tests failed\n\n", count);
    }

	return 0;
}

int main(){
	printf("\n*****************************\n*****************************\nSTART OF CARD TESTS\n*****************************\n*****************************\n");
	test_greatHall();
	return 0;
}
