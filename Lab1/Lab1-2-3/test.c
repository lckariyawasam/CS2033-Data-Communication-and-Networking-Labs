// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
// #include "chain.h"
#include "chain.c"

#define N 5

// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);


int main()
{
    matrix* mat = create_matrix(N, N);
    int* row = (int *) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        row[i] = i;
    }
    add_col(mat, row);
    scalar_multiply(mat, 2);
    print_matrix(mat);
    printf("\n");
    scalar_power(mat, 2);
    print_matrix(mat);

}

// parse the input
void run(chain *chn) 
{
	
}

//Print the chain
void print_chain(chain * chn)
{
   
}
