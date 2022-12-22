/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"
/* user code memory bounds for LC4 */
#define USER_CODE_LOWER 0x0000
#define USER_CODE_UPPER 0x1FFF

/*
 * adds a new node to linked list pointed to by head - MUST keep list in order by address
 */
int add_to_list (row_of_memory** head,
		 short unsigned int address,
		 short unsigned int contents)
{

	/* allocate memory for a single node */
	row_of_memory* new_isa = malloc (sizeof(row_of_memory));
	if (new_isa == NULL) return -1;
	/* populate fields in newly allocated node w/ address&contents (it's ok if CONTENTS=NULL) */
	new_isa->address = address;
	new_isa->label = NULL;
	new_isa->contents = contents;
	new_isa->assembly = NULL;
	new_isa->next = NULL;
	/* if head==NULL, node created is the new head of the list! */
	if (*head == NULL) {
		*head = new_isa;
		return 0;
	}

	/* otherwise, traverse linked list until you reach an address before the address passed in */
	row_of_memory* start = *head;    // save start of the linked_list first
	if (start->address > new_isa->address){
		new_isa->next = start;
		*head = new_isa;     // update the head
		return 0;
	} else {
		while (start->next != NULL && start->next->address < new_isa->address) {
			start = start->next;
		}
		// allocate memory for a temp node
		row_of_memory* temp = *head;
		temp = start->next;
		start->next = new_isa;
		new_isa->next = temp;     // temp == NULL or node with bigger address;
	} 
	/* insert node into the list - perform necessary "surgery" on this list */
	/* REMEMBER, .OBJ file can be out of ORDER!  Make certain to insert incoming node in order by address!! */
	/* return 0 for success, -1 if malloc fails */

	return 0 ;
}

/*
 * search linked list by address field, returns node if found
 */
row_of_memory* search_address (row_of_memory* head,
			       short unsigned int address )
{
	
	/* traverse linked list, searching each node for "address"  */
	while (head != NULL) {
		if (head->address == address) {
			/* return pointer to node in the list if item is found */
			return head;
		}
		head = head->next;
	}
	/* return NULL if list is empty or if "address" isn't found */
	return NULL ;
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode  (row_of_memory* head,
				      short unsigned int opcode  )
{
	while (head != NULL) {
		/* traverse linked list until node is found with matching opcode
		AND "assembly" field of node is empty */
		if ((head->address)>= USER_CODE_LOWER && (head->address) <= USER_CODE_UPPER) {
			if (((head->contents>>12) == opcode) && (head->assembly == NULL)) {
				/* return pointer to node in the list if item is found */
				return head ;
			}
		}
		
		head=head->next;
	}

    /* return NULL if list is empty or if no matching nodes */
	return NULL ;
}


void print_list (row_of_memory* head )
{
	/* make sure head isn't NULL */
	if (head == NULL) {return;}
	/* print out a header */
	printf("<label>\t\t<address>\t<contents>\t<assembly>\n");
	/* traverse linked list, print contents of each node */
	while (head != NULL) {
		if (head->label != NULL) {
			printf("%s", head->label);
			for(int i=0; i<(16-(strlen(head->label))); i++)
                printf(" ");
		}else {
			printf("\t\t");
		}
		printf("%.4X\t\t",head->address);
        printf("%.4X\t\t",head->contents);
		if (head->assembly != NULL) {
			printf("%s\t\n", head->assembly);
		}else {
			printf("\t\n");
		}
		head = head->next;
           
	}
	return ;

}

/*
 * delete entire linked list
 */
int delete_list    (row_of_memory** head )
{
	/* delete entire list node by node */
	while (*head != NULL) {
		// use a tmp node to remember the next node of current node
		row_of_memory* tmp = (*head)->next;
		// then free the current node
		if ((*head)->label != NULL) {
			free((*head)->label);
		}
		if ((*head)->assembly != NULL) {
			free((*head)->assembly);
		}
		free(*head);
		// update the current node to the next node and keep looping
		*head = tmp;
	}
	/* if no errors, set head = NULL upon deletion */
	*head=NULL;
	/* return 0 if no error, -1 for any errors that may arise */
	return 0 ;
}
