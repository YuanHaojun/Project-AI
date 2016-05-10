/*2016.05.10
Group AI Project
Group memebers  :
 Taouk, Kamile                 
 Vincent, Jack Alexander       
 Wen, Winson                        
 Yao, Zhiyuan                       
 Yuan, Haojun                        	
*/




#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Game.h"

#define MAX_TURNS 10000
#define TERRA_NULLIS -1
#define NUM_UNIS 3

#define UNI_A_PATH1 ""
#define UNI_A_PATH2 "LRLRLRRLRLRRLRL"
#define UNI_B_PATH1 "LRLRLRRLRL"
#define UNI_B_PATH2 "RRLRL"
#define UNI_C_PATH1 "LRLRL"
#define UNI_C_PATH2 "RRLRLLRLRL"



#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

typedef struct _game {
    int currentTurn;
    int Students[NUM_UNIS][6];
} game;

void testDisposeGame (void);
void testMakeAction (void);
void testThrowDice (void);
void testGetDiscipline (void);
void testGetDiceValue (void);
void testGetMostARCs (void);
void testGetMostPublications (void);
void testGetWhoseTurn (void);
void testGetCampus(void);
void testGetARC(void);
void testIsLegalAction (void);
void testGetKPIpoints (void);
void testGetARCs (void);
void testGetGO8s (void);
void testGetCampuses (void);
void testGetIPs (void);
void testGetPublications (void);
void testGetStudents (void);
void testGetExchangeRate (void);

void testGame(void);


int main (int argc, char * argv[]) {
   testGame();
   printf("All tests passed, you are Awesome!\n");
   return EXIT_SUCCESS;
}
  

void testDisposeGame (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
    assert(g != NULL);
    disposeGame(g);
 
    printf("testDisposeGame passed!\n");
}

void testMakeAction (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
 
    action a;
    assert (g->currentTurn == TERRA_NULLIS);
    a.actionCode = PASS;
    makeAction(g, a);
    assert (g->currentTurn == 0 );
    disposeGame(g);
 
    printf("testMakeAction passed!\n");
}
 
void testThrowDice (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines, testDice);
      int turnNumbers=-1;
      while (turnNumbers < 10000) {
      int diceScore = 5;
      throwDice(g, diceScore);
      turnNumbers ++;
      assert(getTurnNumber(g) == turnNumbers);
      assert(getWhoseTurn(g) == (turnNumbers % NUM_UNIS) + 1);
   }
    printf("testThrowDice passed!\n");
}	

void testGetDiscipline (void) {   
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines, testDice);
 
    int regionID = 3;
    assert(getDiceValue(g,regionID) == 12);
    assert(getDiscipline(g,regionID) == STUDENT_MMONEY);
    regionID = 6;
    assert(getDiceValue(g,regionID) == 3);
    assert(getDiscipline(g,regionID) == STUDENT_MTV);
    regionID = 20;
    assert(getDiceValue(g,regionID) != 2);
    assert(getDiscipline(g,regionID) != STUDENT_THD);
    disposeGame(g);
 
    printf("testGetDiscipline passed!\n");
}
 
void testGetDiceValue (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
    int regionID = 0;

   while (regionID < NUM_REGIONS) {
      assert(getDiceValue(g, testDice[regionID]) == testDice[regionID]);
      regionID ++;
   }
    printf("testGetDiceValue passed!\n");
}
 
void testGetMostARCs (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    action a;
    Game g1 = newGame(testDisciplines,testDice);
    Game g2 = newGame(testDisciplines,testDice);
    
 
    assert(getMostARCs(g1) == NO_ONE);
    a.actionCode = PASS;
    makeAction(g1, a);
    a.actionCode = OBTAIN_ARC;
    makeAction(g1, a);
    assert(getMostARCs(g1) == UNI_A);
    a.actionCode = PASS;
    makeAction(g1, a); 
    a.actionCode = OBTAIN_ARC;
    makeAction(g1, a);
    a.actionCode = OBTAIN_ARC;
    makeAction(g1, a);
    assert(getMostARCs(g1) == UNI_B);
    disposeGame(g1);

    assert(getMostARCs(g2) == NO_ONE);
    a.actionCode = PASS;
    makeAction(g2, a);
    a.actionCode = OBTAIN_ARC;
    makeAction(g2, a);
    a.actionCode = PASS;
    makeAction(g2, a); 
    a.actionCode = OBTAIN_ARC;
    makeAction(g2, a);
    a.actionCode = PASS;
    makeAction(g2, a); 
    a.actionCode = OBTAIN_ARC;
    makeAction(g2, a);
    assert (getMostARCs(g2) == NO_ONE);
    disposeGame(g2);

    printf("testGetMostARCs passed!\n");
}
 
void testGetMostPublications (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g1 = newGame (testDisciplines,testDice);
    action a;
 
    assert(getMostPublications(g1) == NO_ONE);
    a.actionCode = PASS;
    makeAction(g1, a);
    a.actionCode = OBTAIN_PUBLICATION;
    makeAction(g1, a);
    
    assert(getMostPublications(g1) == UNI_A);
    a.actionCode = PASS;
    makeAction(g1, a); 
    a.actionCode = OBTAIN_PUBLICATION;
    makeAction(g1, a);
    a.actionCode = OBTAIN_PUBLICATION;
    makeAction(g1, a);
    assert(getMostPublications(g1) == UNI_B);
    a.actionCode = PASS;
    makeAction(g1, a);
    a.actionCode = OBTAIN_PUBLICATION;
    makeAction(g1, a);
    makeAction(g1, a);
    assert(getMostPublications(g1) == NO_ONE);
    disposeGame(g1);
 
    printf("testGetMostPublications passed!\n");
}

void testGetTurnNumber (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g1 = newGame(testDisciplines,testDice);
    Game g2 = newGame(testDisciplines,testDice);
    action a;
 
    assert(getTurnNumber(g1) != -2);
    assert(getTurnNumber(g1) >= -1);
    assert(getTurnNumber(g1) < MAX_TURNS);
    disposeGame(g1);
    
    assert(getTurnNumber(g2) == -1);
    a.actionCode = PASS;
    makeAction(g2, a);
    assert(getTurnNumber(g2) == 0);
    a.actionCode = PASS;
    makeAction(g2, a);
    makeAction(g2, a);
    makeAction(g2, a);
    assert(getTurnNumber(g2) == 3);
    disposeGame(g2);
 
    printf("testGetTurnNumber passed!\n");
}

void testGetWhoseTurn (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
    action a;
 
    assert((getWhoseTurn(g)) == NO_ONE);
    a.actionCode = PASS;
    makeAction(g,a);
    assert((getWhoseTurn(g)) == UNI_A);
    makeAction(g,a);
    assert((getWhoseTurn(g)) == UNI_B);
    makeAction(g,a);
    assert((getWhoseTurn(g)) == UNI_C);
    makeAction(g,a);
    assert((getWhoseTurn(g)) == UNI_A);
    makeAction(g,a);
    assert((getWhoseTurn(g)) == UNI_B);
    makeAction(g,a);
    assert((getWhoseTurn(g)) == UNI_C);
    makeAction(g,a);
    assert((getWhoseTurn(g)) == UNI_A);
    a.actionCode = OBTAIN_ARC;
    makeAction(g,a);
    assert((getWhoseTurn(g)) == UNI_A);
 
 
    disposeGame(g);
    printf("testGetWhoseTurn passed!\n");
}

void testGetCampus(void){
 
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
 
    assert(getCampus(g, UNI_A_PATH1) == CAMPUS_A);
    assert(getCampus(g, UNI_A_PATH2) == CAMPUS_A);
    assert(getCampus(g, UNI_B_PATH1) == CAMPUS_B);
    assert(getCampus(g, UNI_B_PATH2) == CAMPUS_B);
    assert(getCampus(g, UNI_C_PATH1) == CAMPUS_C);
    assert(getCampus(g, UNI_C_PATH2) == CAMPUS_C);
 
    disposeGame(g);
    printf("testGetCampus passed!\n");
 
}
 
 
void testGetARC(void){
 
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
 
    Game g = newGame(disciplines, dice);
    action testAction = {0};

    throwDice(g, 9);

    assert(getTurnNumber(g) == 0);

    assert(getWhoseTurn(g) == UNI_A);

    testAction.actionCode = PASS;

    throwDice(g, 5);
    assert(getTurnNumber(g) == 1);
    assert(getWhoseTurn(g) == UNI_B);
 
    testAction.actionCode = OBTAIN_ARC;
    strcpy(testAction.destination, "LRLRLRLRLRLR");

    assert(isLegalAction(g, testAction) == FALSE);
    strcpy(testAction.destination, "LRLRLRRLRLB");

    assert(isLegalAction(g, testAction) == TRUE);
 
    throwDice(g, 6);
    assert(getTurnNumber(g) == 2);
    assert(getWhoseTurn(g) == UNI_C);
    testAction.actionCode = PASS;
 
    assert(getARC(g, "LR") == VACANT_ARC);
    assert(getARC(g, "RL") == VACANT_ARC);
    assert(getARC(g, "LRLR") == VACANT_ARC);
    assert(getARC(g, "RLRL") == VACANT_ARC);
    assert(getARC(g, "RLRLRL") == VACANT_ARC);
    assert(getARC(g, "RLLRRRL") == VACANT_ARC);

    testAction.actionCode = OBTAIN_ARC;
    strcpy(testAction.destination, "RLLRRRL");
    makeAction(g, testAction);
    assert (getARC(g, "RLLRRRL") == ARC_C);
 
    disposeGame(g);
    printf("testGetARC passed!\n");
 
 
}
 
void testIsLegalAction (void){
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
 
    Game g = newGame(disciplines, dice);
    action testAction = {0};

    throwDice(g, 9);

    assert(getTurnNumber(g) == 0);

    assert((getWhoseTurn(g)) == UNI_A);

    testAction.actionCode = PASS;

    throwDice(g, 5);
    assert(getTurnNumber(g) == 1);
    assert(getWhoseTurn(g) == UNI_B);
 

    testAction.actionCode = OBTAIN_ARC;
    strcpy(testAction.destination, "LRLRLRLRLRLR");

    assert(isLegalAction(g, testAction) == FALSE);
    strcpy(testAction.destination, "LRLRLRRLRLB");

    assert(isLegalAction(g, testAction) == TRUE);
 
    throwDice(g, 6);
    assert(getTurnNumber(g) == 2);
    assert(getWhoseTurn(g) == UNI_C);
    testAction.actionCode = PASS;
 
    testAction.actionCode = PASS;
    assert(isLegalAction (g, testAction) == TRUE);
    testAction.actionCode = BUILD_CAMPUS;
    assert(isLegalAction (g, testAction) == FALSE);
    testAction.actionCode = BUILD_GO8;
    assert(isLegalAction (g, testAction) == FALSE);
    testAction.actionCode = OBTAIN_ARC;
    assert(isLegalAction (g, testAction) == FALSE);
    testAction.actionCode = START_SPINOFF;
    assert(isLegalAction (g, testAction) == TRUE);
    testAction.actionCode = OBTAIN_PUBLICATION;
    assert(isLegalAction (g, testAction) == FALSE);
    testAction.actionCode = OBTAIN_IP_PATENT;
    assert(isLegalAction (g, testAction) == FALSE);
 
    disposeGame(g);
    printf("testIsLegalAction passed!\n");
 
}

void testGetKPIpoints (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
    
    int activePlayer = 0;
    int numCampuses = 0;
    int numGO8 = 0;
    int numARC = 0;
    int numIP = 0;
    int hasMostARCs = 0;
    int hasMostPubs = 0;
    int expectedKPI = 0;
    
    assert(getTurnNumber(g) == -1);
    throwDice(g, BUILD_GO8);
    assert(getTurnNumber(g) == 0);
    
    while (activePlayer <= NUM_UNIS){
        numCampuses = getCampuses(g,activePlayer);
        numGO8 = getGO8s(g, activePlayer);
        numARC = getARCs(g, activePlayer);
        numIP = getIPs(g, activePlayer);
        hasMostARCs = (getMostARCs(g) == activePlayer);
        hasMostPubs = (getMostPublications(g)  == activePlayer);
        expectedKPI = 10*numCampuses + 20*numGO8 + 2*numARC
        + 10*numIP + 10*hasMostARCs + 10*hasMostPubs;
 
        assert(getKPIpoints(g, activePlayer) == expectedKPI);
        
        activePlayer++;
    }
    
    disposeGame(g);
 
    printf("testGetKPIpoints passed!\n");
}

void testGetARCs (void) {   
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
    action a;
 
    int i = 1;
    while (i <= NUM_UNIS){
        assert(getARCs(g, i) == 0);
        i++;
    }
 
    a.actionCode = PASS;
    makeAction(g, a);
    a.actionCode = OBTAIN_ARC;
    makeAction(g, a);
    assert(getARCs(g, UNI_A) == 1);
 
    disposeGame(g);
 
    printf("testGetARCs passed!\n");
}

void testGetGO8s (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
 
    int i = 1;
    while (i <= NUM_UNIS) {
        assert(getGO8s(g, i) == 0);
        i++;
    }
 
    disposeGame(g);
 
    printf("testGetGO8s passed!\n");
}

void testGetCampuses (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
    
    int i;
    for(i = 0; i < NUM_UNIS; i++){
        assert(getCampuses(g, i + UNI_A) == 2);
    }
 
    disposeGame(g);
    
    printf("testGetCampuses passed!\n");
}
 
void testGetIPs (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g0 = newGame(testDisciplines,testDice);
    action a;
 
    assert (getIPs (g0, UNI_A) == 0);
    assert (getIPs (g0, UNI_B) == 0);
    assert (getIPs (g0, UNI_C) == 0);

    disposeGame(g0);
 
    Game g1 = newGame(testDisciplines,testDice);

    a.actionCode = PASS;
    makeAction(g1, a);

    a.actionCode = OBTAIN_IP_PATENT;
    makeAction(g1, a);
    assert (getIPs (g1, UNI_A) == 1);
    assert (getIPs (g1, UNI_B) == 0);
    assert (getIPs (g1, UNI_C) == 0);

    a.actionCode = PASS;
    makeAction(g1, a);
    assert (getIPs (g1, UNI_A) == 1);
    assert (getIPs (g1, UNI_B) == 0);
    assert (getIPs (g1, UNI_C) == 0);

    a.actionCode = OBTAIN_IP_PATENT;
    makeAction(g1, a);
    makeAction(g1, a);
    assert (getIPs (g1, UNI_A) == 1);
    assert (getIPs (g1, UNI_B) == 2);
    assert (getIPs (g1, UNI_C) == 0);
    disposeGame(g1);

    printf("testGetIPs passed!\n");
}
 
void testGetPublications (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
    action a;
 

    assert (getPublications(g, UNI_A) == 0 );
    assert (getPublications(g, UNI_B) == 0 );
    assert (getPublications(g, UNI_C) == 0 );

    a.actionCode = PASS;
    makeAction(g, a);
    a.actionCode = OBTAIN_PUBLICATION;
    makeAction(g, a);
    assert (getPublications(g, UNI_A) == 1);
    assert (getPublications(g, UNI_B) == 0);
    assert (getPublications(g, UNI_C) == 0);

    disposeGame(g);
 
    printf("testGetPublications passed!\n");
}
 
void testGetStudents (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
 

    assert(getStudents(g, UNI_A, STUDENT_MTV) >= 0);
    disposeGame(g);
 
    printf("testGetStudents passed!\n");
}
 
void testGetExchangeRate (void) {
    int testDisciplines[] = DEFAULT_DISCIPLINES;
    int testDice[] = DEFAULT_DICE;
    Game g = newGame(testDisciplines,testDice);
 

    assert (getExchangeRate (g, UNI_A, STUDENT_BPS, STUDENT_BQN) == 3);
    assert (getExchangeRate (g, UNI_A, STUDENT_BPS, STUDENT_MJ) == 3);
    assert (getExchangeRate (g, UNI_A, STUDENT_BPS, STUDENT_MTV) == 3);
    assert (getExchangeRate (g, UNI_A, STUDENT_BPS, STUDENT_MMONEY) == 3);

    assert (getExchangeRate(g, UNI_B, STUDENT_BPS, STUDENT_BQN) == 3);
    assert (getExchangeRate (g, UNI_B, STUDENT_BPS, STUDENT_MJ) == 3);
    assert (getExchangeRate (g, UNI_B, STUDENT_BPS, STUDENT_MTV) == 3);
    assert (getExchangeRate(g, UNI_B, STUDENT_BPS, STUDENT_MMONEY) == 3);

    assert (getExchangeRate (g, UNI_C, STUDENT_BPS, STUDENT_BQN) == 3);
    assert (getExchangeRate (g, UNI_C, STUDENT_BPS, STUDENT_MJ) == 3);
    assert (getExchangeRate(g, UNI_C, STUDENT_BPS, STUDENT_MTV) == 3);
    assert (getExchangeRate(g, UNI_C, STUDENT_BPS, STUDENT_MMONEY) == 3);
    disposeGame(g);
 
    printf("testGetExchangeRate passed!\n");
}

void testGame(void) {
 
    testDisposeGame ();
    testMakeAction ();
    testThrowDice ();
    testGetDiscipline ();
    testGetDiceValue ();
    testGetMostARCs ();
    testGetMostPublications ();
    testGetTurnNumber ();
    testGetWhoseTurn ();
    testGetCampus();
    testGetARC();
    testIsLegalAction ();
    testGetKPIpoints ();
    testGetARCs ();
    testGetGO8s ();
    testGetCampuses ();
    testGetIPs ();
    testGetPublications ();
    testGetStudents ();
    testGetExchangeRate ();

}
