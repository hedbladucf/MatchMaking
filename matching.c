/*
* Oscar Hedblad
* COP3502, 0002
* Matchmaking Program
* Professor Marshall Tappen
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

/* My different prototypes */
int factorial(int n);
int matchScores(int perm[], int boysRating[][10], int girlsRatings[][10], int len);
int matchDifference(int perm[], int boysRating[][10], int girlsRatings[][10], int len);
void permute(int perm[], int len);
void copy(int x[],int y[], int numb);
void print(char boys[][20], char girls[][20], int perm[], int len);

int main() {

FILE* ifp;
ifp= fopen("matching.txt","r");

/* Makes sure that the file name entered exists */
if (ifp == NULL)
printf("Missing file, please check file name!");

/* Reads in first number at the top of .txt file */
int counter, F;
fscanf(ifp, "%d", &F);

/* For loop that determines the amount of times to be calculated */
    for (counter = 1;counter <= F;counter++) {

/* Declaration of various variables */
        int numb;
        int girlsPermute[10], topPermute[10];
        char boys[10][20], girls[10][20];
        int boysRating[10][10], girlsRatings[10][10];
        int topScore = 0, difference = 0;

/* Read in the number of pairs */
        fscanf(ifp, "%d", &numb);

/* Initialize all girls permute to ZERO */
        int i, j, verify = 0;
        for (i = 0;i < numb;i++) {
            girlsPermute[i] = i;
            topPermute[i] = i;
        }
/* Reads and scans all names and numbers (scores) */
        for (i = 0;i < numb;i++){
            fscanf(ifp, "%s", boys[i]);
        }
        for (i = 0;i < numb;i++){
            fscanf(ifp, "%s", girls[i]);
        }
        for (i = 0;i < numb;i++){
            for (j = 0;j < numb;j++){
                fscanf(ifp, "%d", &boysRating[i][j]);
            }
        }
        for (i = 0;i < numb;i++){
            for (j = 0;j < numb;j++){
                fscanf(ifp, "%d", &girlsRatings[i][j]);
            }
        }
/* For loop that checks and makes sure that the correct number of permutations is done */
        for (i = 0;i < factorial(numb);i++) {

/* Updates scores and calls functions to calculate and determine which ratings are best */
            int presentScore = matchScores(girlsPermute, boysRating, girlsRatings, numb);
            int presentDifference =  matchDifference(girlsPermute, boysRating, girlsRatings, numb);

/* If statement that correctly fixes any situation when a tie occurs */
            if (verify && presentScore == topScore && presentDifference == difference){
            }
/* If statement that updates the new current best suitable match */
            if (presentScore > topScore || (presentScore == topScore && presentDifference < difference)) {
                copy(topPermute, girlsPermute, numb);
                topScore = presentScore;
                difference = presentDifference;
            }
/* Begins next permutation */
            permute(girlsPermute, numb);
    }
/* Prints out the Matching number and their maximum (top) score */
        printf("Matching #%d: Maximum Score = %d.\n\n", counter, topScore);
        print(boys, girls, topPermute, numb);
    }
    return 0;
}

/* Takes in lower case f, it then factorize the number to find total number of factorials */
int factorial(int f) {
    if (f == 0)
        return 1;
    else
        return f*factorial(f-1);
}

/* Intakes permutation array and its length, then makes the permutation */
void permute(int perm[], int len) {

/* Correctly identifies the spot that needs to SWAP. It then decrements to move to next index */
    int i = len - 1;
    while (i > 0 && perm[i] < perm[i - 1]) i--;
    i--;

if (i == -1) return;

/*  Swap index at [i] */
    int k = len - 1;
    while (k > i && perm[k]<perm[i]) k--;

/* Changes the numbers positions */
    int temp = perm[i];
    perm[i] = perm[k];
    perm[k] = temp;

/* Swap temp variable from index [i +1] to [len - 1] in order to move correctly */
   int q, w;
   for (q = i + 1, w = len - 1;q < w;q++, w--) {
       temp = perm[q];
       perm[q] = perm[w];
       perm[w] = temp;
    }
}

/* Reads in both the boy/girl rating and the length of the boys array, then returns the score of matching boys and girls */
int matchScores(int perm[], int boysRating[][10], int girlsRatings[][10], int len) {

    int p, score = 0;
    for (p = 0;p < len;p++) {

/* If-else statement that updates the present score for the last counter and compares it to the lower of the two scores */
        if (boysRating[p][perm[p]] <= girlsRatings[perm[p]][p]){
            score += boysRating[p][perm[p]];
            }
        else
            score += girlsRatings[perm[p]][p];
    }
return score;
}

/* Final update of score to determine the "winning pair" */
int matchDifference(int perm[], int boysRating[][10], int girlsRatings[][10], int len) {

/* Subtraction that calculates the best matches */
    int m, score = 0;
    for (m = 0;m < len;m++)
        score += (boysRating[m][perm[m]]-girlsRatings[perm[m]][m]);

return score;
}

/* Copies corresponding values of array Y into X. */
void copy(int x[],int y[], int numb) {
    int i;
    for (i = 0;i < numb;i++)
        x[i] = y[i];
}

/* Takes in the length and names of the boy/girl array,
* and the permutation for the girls, then prints the most suitable boy-girl match.*/
void print(char boys[][20], char girls[][20], int perm[], int len) {

    int z;
    for (z = 0;z < len;z++)
        printf("%s %s\n", boys[z], girls[perm[z]]);
        printf("\n");
}
