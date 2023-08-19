// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
void insert_node_before(list *lst, int index, char *word)
{	
	// TODO
	node* new_node = (node*) malloc(sizeof(node));

	// Make a new copy of the word
	char* new_word = malloc(strlen(word)+1);
	strcpy(new_word, word);
	new_node->word = new_word;

	// Inserting the first node
	if (lst->head == NULL) {
		lst->head = new_node;
		new_node->prev = lst->head;
		new_node->next = lst->head;
	} else {
		int temp = 0;
		node* current = lst->head;

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


void insert_node_after(list *lst, int index, char *word)
{
	// TODO

	// Insert it before the next node
	insert_node_before(lst, index+1, word);
}


char *list_to_sentence(list *lst)
{
	// TODO

	// Get the length of the sentence
	int length = 0;
	length += strlen(lst->head->word);
	node* node = lst->head->next;
	while(node != lst->head) {
		length += strlen(node->word);
		node = node->next;
	}

	// Allocate memory for the sentence
	char* sentence = malloc(length+1);

	// Iterate through the list and concatenate the words
	node = lst->head;
	sentence = strcat(sentence, node->word);
	node = node->next;

	while (node != lst->head) {
		sentence = strcat(sentence, " ");
		sentence = strcat(sentence, node->word);
		node = node->next;
	}
	return sentence;
}


void delete_node(list *lst, int index)
{
	// TODO

	// Deleting the head node
	if (index == 0) {
		// Head is the only node in the list
		if (lst->head->next == lst->head) {
			node* to_delete = lst->head;
			lst->head = NULL;
			free(to_delete);
		
		// Head is not the only node in the list, update the head to next node
		} else {
			node* head = lst->head;
			head->prev->next = head->next;
			head->next->prev = head->prev;
			lst->head = head->next;
			free(head);
		}
	} else {

		int temp = 0;
		node* current = lst->head;

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


void delete_list(list *lst)
{
	// TODO
	while (lst->head != NULL) {
		delete_node(lst, 0);
	}
}


