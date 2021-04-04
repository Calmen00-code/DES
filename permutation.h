#ifndef PERMUTATION
#define PERMUTATION

#define ROW_IP 8
#define COL_IP 8

/* PC-1 */
#define PC1_ROW 7
#define PC1_COL 8
#define PC1_BITS 56

/* PC-2 */
#define PC2_ROW 6
#define PC2_COL 8
#define PC2_BITS 48


int* getInitialPermutation();
int** getInverseInitialPermutation();
int** getExpansionPermutation();
int** getPermutationFunction();
void initialPermutation( int * );
void finalPermutation( int * );
int* pc1_process( int* );
int* pc2_process( int* );

#endif
