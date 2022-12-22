/************************************************************************/
/* File Name : lc4_loader.c		 										*/
/* Purpose   : This file implements the loader (ld) from PennSim		*/
/*             It will be called by main()								*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"

/* declarations of functions that must defined in lc4_loader.c */

FILE* open_file(char* file_name)
{
	FILE *src_file;
	// should check what is the file_name passed in
	src_file = fopen(file_name, "rb");
	if (src_file != NULL) {return src_file;}	
	return NULL ;
}

int parse_file (FILE* my_obj_file, row_of_memory** memory)
{
	/*
	format of the obj file:
	header (CODE/DATA), <address> , <n=#words> (2bytes each) (1 word == each instruction == 1 node);
	head (SYMBOL), <address>, <n=#bytes> (actually is n+1 cuz we should hold the NULL);
	*/
	// short unsigned int can determine that every fread() only read 2bytes
	short unsigned int header;
	short unsigned int address;
	short unsigned int n;
	short unsigned int word;
	row_of_memory* label_address;
	char* SYMBOL;

	// read the header first
	while (fread (&header, sizeof(short unsigned int), 1, my_obj_file)) {
		header = (header << 8) | (header >> 8);

		if (header == 0xCADE || header == 0xDADA) {
			fread (&address, sizeof(short unsigned int), 1, my_obj_file);
			fread (&n, sizeof(short unsigned int), 1, my_obj_file);
			address = (address << 8) | (address >> 8);
		    n = (n << 8) | (n >> 8);
			// put each word into the linked_list
			while (n > 0) {
				fread (&word, sizeof(short unsigned int), 1, my_obj_file);
				word = (word << 8) | (word >> 8);
				// printf("contents: %.4X\n", word);
				// create the node
				// add the node to linked_list
				add_to_list(memory, address, word);
				// every time add a node, we should update its according address
				address++;
				n--;
			}
		}else if (header == 0xC3B7) {
			fread (&address, sizeof(short unsigned int), 1, my_obj_file);
			fread (&n, sizeof(short unsigned int), 1, my_obj_file);
			address = (address << 8) | (address >> 8);
		    n = (n << 8) | (n >> 8);
			// allocate the memory for a SYMBOL (add an additional byte to hold the NULL)
			SYMBOL = malloc(sizeof(char)*(n+1));
			// check the malloc
			if (SYMBOL == NULL) return 2;
			// mark the index of the NULL
			int index = 0;

			while (n > 0) {
				// fread() return a pointer (address)
				fread (&SYMBOL[index], sizeof(char), 1, my_obj_file);
				// printf("contents: %.4X\n", SYMBOL[index]);
				index++;
				n--;
			}
			// populate the end of the SYMBOL as a NULL
			SYMBOL[index] = '\0';
			// search the address and put the SYMBOL into this node
			label_address = search_address(*memory, address);
				   
			if (label_address != NULL) {
				label_address->label = SYMBOL;
			}else {
				// create the node first, then assign the SYMBOL to this node
				add_to_list(memory, address, 0);     // contents type is short unsigned int
				// get the label_address again
				label_address = search_address(*memory, address);
				label_address->label = SYMBOL;
			}
			
		}else {
			fprintf (stderr, "the header is illegal\n") ;
			return 2;  // the header is illegal
		}
	};

	// close the file
	if (fclose(my_obj_file)!=0) {
		fprintf (stderr, "encouter an error in closing the file!\n") ;
		return 2 ;
	}

	return 0 ;
}
