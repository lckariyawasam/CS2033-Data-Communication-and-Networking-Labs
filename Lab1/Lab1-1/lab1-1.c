// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>

// user-defined header files
#include "node.h"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list * lst); 
void run(list * lst);


int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
}

// parse the input
void run(list *lst) 
{
	char buffer[MAX_WORD_LENGTH*20];
    scanf("%s", buffer);

    // Split the string on ,
    char *token = strtok(buffer, ",");

    while (token != NULL) {
        insert_node_before(lst, 0, token);
        token = strtok(NULL, ",");
    }

    // Read the next command
    int command;
    scanf("%d", &command);

    while (command != 0) {
        if (command == INSERT_BEFORE) {
            int index;
            char word[MAX_WORD_LENGTH];
            scanf("%d %s", &index, word);
            insert_node_before(lst, index, word);
        } else if (command == INSERT_AFTER) {
            int index;
            char word[MAX_WORD_LENGTH];
            scanf("%d %s", &index, word);
            insert_node_after(lst, index, word);
        } else if (command == DELETE_NODE) {
            int index;
            scanf("%d", &index);
            delete_node(lst, index);
        } else if (command == DELETE_LIST) {
            delete_list(lst);
        } else {
            printf("Invalid command\n");
        }
        scanf("%d", &command);
    }

}

//Print the list contents
void print_list(list * lst)
{
    printf("%s \n", list_to_sentence(lst));
}

