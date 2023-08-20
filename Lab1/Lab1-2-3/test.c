// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "chain.c"

#define ADDROW 2
#define ADDCOL 3
#define INCREMENT 4
#define SCALARMULTIPLY 5
#define SCALARDIVIDE 6
#define SCALARPOWER 7
#define DELETE 8
#define QUIT 0

// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);
matrix* copy_matrix(matrix* mat);
int* stringToArray(char* input, int cols);


int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}

// parse the input
void run(chain *chn) 
{
    int num_rows;
    scanf("%d", &num_rows);
    scanf("%*c");

    int num_cols = 0;
    char * string = (char *) malloc(sizeof(char) * 100);
    fgets(string, 100, stdin);

    char * string_copy = (char *) malloc(sizeof(char) * 100);
    strcpy(string_copy, string);
    
    char* token = strtok(string, " ");
    while (token != NULL) {
        num_cols++;
        token = strtok(NULL, " ");
    }

    matrix* mat = create_matrix(num_rows, num_cols);
    
    // Add the first row
    int* arr = stringToArray(string_copy, num_cols);
    for (int j = 0; j < num_cols; j++) {
        mat->data[0][j] = arr[j];
    }

    for (int i = 1; i < num_rows; i++) {
        char * new_row = (char *) malloc(sizeof(char) * 100);
        fgets(new_row, 100, stdin);
        int* arr = stringToArray(new_row, num_cols);
        for (int j = 0; j < num_cols; j++) {
            mat->data[i][j] = arr[j];
        }
    }

    insert_node_before(chn, 0, mat);

    // Read the next command
    int command;
    scanf("%d", &command);

    while (command != QUIT) {
        if (command == ADDCOL) {
            int new_col[num_rows];
            for (int i = 0; i < num_rows; i++) {
                scanf("%d", &new_col[i]);
            }
            add_col(mat, new_col);
            num_cols++;
            insert_node_before(chn, 0, mat);
        } else if (command == ADDROW) {
            int new_row[num_cols];
            for (int i = 0; i < num_cols; i++) {
                scanf("%d", &new_row[i]);
            }
            add_row(mat, new_row);
            num_rows++;
            insert_node_before(chn, 0, mat);
        } else if (command == INCREMENT) {
            int index;
            scanf("%d", &index);
            increment(mat, index);
            insert_node_before(chn, 0, mat);
        } else if (command == SCALARMULTIPLY) {
            int scalar;
            scanf("%d", &scalar);
            scalar_multiply(mat, scalar);
            insert_node_before(chn, 0, mat);
        } else if (command == SCALARDIVIDE) {
            int scalar;
            scanf("%d", &scalar);
            scalar_divide(mat, scalar);
            insert_node_before(chn, 0, mat);
        } else if (command == SCALARPOWER) {
            int scalar;
            scanf("%d", &scalar);
            scalar_power(mat, scalar);
            insert_node_before(chn, 0, mat);
        } else if (command == DELETE) {
            int index;
            scanf("%d", &index);
            delete_node(chn, index);
            insert_node_before(chn, 0, mat);
        } else {
            printf("Invalid command %d\n", command);
        }
        scanf("%d", &command);
    }

}



//Print the chain
void print_chain(chain * chn)
{
    node* current = chn->head;
    print_matrix(current->mat);
    printf("\n");
    current = current->next;
    while (current != chn->head) {
        print_matrix(current->mat);
        printf("\n");
        current = current->next;
    }
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

void insert_node_before(chain *chn, int index, matrix *mat) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->mat = copy_matrix(mat);
    new_node->next = NULL;
    new_node->prev = NULL;


    // Inserting the first node
	if (chn->head == NULL) {
		chn->head = new_node;
		new_node->prev = chn->head;
		new_node->next = chn->head;
    } else {
        int temp = 0;
		node* current = chn->head;

		// Traverse the linked list to reach the required index
		while (1) {

			// Inserting the node at the required index
			if (temp == index) {
				new_node->next = current;
				new_node->prev = current->prev;
				current->prev->next = new_node;
				current->prev = new_node;
				break;
			}

			// Traverse forwards if index is positive, backwards if index is negative
			if (index > 0) {
				temp++;
				current = current->next;
			} else {
				temp--;
				current = current->prev;
			}
		}
    }

}

void insert_node_after(chain *chn, int index, matrix *mat) {
    // Insert it before the next node
    insert_node_before(chn, index+1, mat);
}

void delete_node(chain *chn, int index) {
    // TODO
    if (index == 0) {
        // Head is the only node in the chain
        if (chn->head->next == chn->head) {
            node* to_delete = chn->head;
            chn->head = NULL;
            free(to_delete);
        
        // Head is not the only node in the chain, update the head to next node
        } else {
            node* head = chn->head;
            head->prev->next = head->next;
            head->next->prev = head->prev;
            chn->head = head->next;
            free(head);
        }

	} else {

		int temp = 0;
		node* current = chn->head;

		// Traverse through the linked list till the required index is found
		while (1) {
			if (temp == index) {
				current->prev->next = current->next;
				current->next->prev = current->prev;
				free(current);
				break;
			}

			// Traverse forwards if index is positive, backwards if index is negative
			if (index > 0) {
				temp++;
				current = current->next;
			} else {
				temp--;
				current = current->prev;
			}
		}
	}
}

void delete_list(chain *chn) {
    // TODO
    while (chn->head != NULL) {
        delete_node(chn, 0);
    }
}

int* stringToArray(char* input, int cols) {
    int* arr = (int*) malloc(sizeof(int) * cols);
    char* token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        arr[i] = atoi(token);
        token = strtok(NULL, " ");
        i++;
    }
    return arr;
} 