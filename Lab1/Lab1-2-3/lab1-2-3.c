// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "chain.h"

#define ADDCOL 1
#define ADDROW 2
#define INCREMENT 3
#define SCALARMULTIPLY 4
#define SCALARDIVIDE 5
#define SCALARPOWER 6
#define DELETE 7
#define PRINT 8
#define QUIT 9


// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);
matrix* copy_matrix(matrix* mat);


int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    // print_chain(chn);
    // free(chn);
	return 0;
}

// parse the input
void run(chain *chn) 
{
    matrix* mat = create_matrix(2, 2);
	insert_node_before(chn, 0, copy_matrix(mat));
    add_col(mat, (int[]){1, 2});
    insert_node_before(chn, 0, copy_matrix(mat));
}

//Print the chain
void print_chain(chain * chn)
{
   
}

matrix* copy_matrix(matrix* mat) {
    matrix* new_mat = create_matrix(mat->num_rows, mat->num_cols);
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_cols; j++) {
            new_mat->data[i][j] = mat->data[i][j];
        }
    }
    return new_mat;
}

