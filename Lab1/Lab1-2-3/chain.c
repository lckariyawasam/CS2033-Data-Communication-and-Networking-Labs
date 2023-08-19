#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:
int power(int base, int exponent);

// implementation
matrix *create_matrix(int num_rows, int num_cols)
{   
    // TODO
    
    matrix* mat = (matrix*) malloc(sizeof(matrix));
    mat->num_rows = num_rows;
    mat->num_cols = num_cols;

    // Allocate memory for matrix data
    mat->data = (int **) malloc(sizeof(int *) * num_rows);

    for (int i=0; i < num_rows; i++) {
        // Allocate memory for each row
        mat->data[i] = malloc(sizeof(int) * num_cols);
        for (int j = 0; j < num_cols; j++) {
            // Set each value to 0
            mat->data[i][j] = 0;
        }
    }

    return mat;

}

void add_row(matrix *mat, int *row)
{
    // TODO
    mat->num_rows++;

    mat->data = realloc(mat->data, sizeof(int *) * mat->num_rows);
    mat->data[mat->num_rows - 1] = (int*) malloc(sizeof(int) * mat->num_cols);

    for (int i = 0; i < mat->num_cols; i++) {
        mat->data[mat->num_rows-1][i] = row[i];
    }

}

void add_col(matrix *mat, int *col)
{
    // TODO

    mat->num_cols++;

    for (int i = 0; i < mat->num_rows; i++) {
        mat->data[i] = realloc(mat->data[i], sizeof(int) * mat->num_cols);
        mat->data[i][mat->num_cols-1] = col[i];
    }
}

void increment(matrix *mat, int num)
{
    // TODO
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] += num;
        }
    }
}

void scalar_multiply(matrix *mat, int num)
{
    // TODO
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] *= num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    // TODO
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] /= num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    // TODO
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] = power(mat->data[i][j], num);
        }
    }
}

void delete_matrix(matrix *mat)
{
    // TODO
    for (int i = 0; i < mat->num_rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);

}

int power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}


/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat) 
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

//Add the rest of the functions needed for the chain below
