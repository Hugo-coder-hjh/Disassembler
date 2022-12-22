/************************************************************************/
/* File Name : lc4.c 													*/
/* Purpose   : This file contains the main() for this project			*/
/*             main() will call the loader and disassembler functions	*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"
#include <string.h>

/* program to mimic pennsim loader and disassemble object files */

int main (int argc, char** argv) {

	/**
	 * main() holds the linked list &
	 * only calls functions in other files
	 */
	char* input_file = NULL;
	/* step 1: create head pointer to linked list: memory 	*/
	row_of_memory* memory = NULL ;
	char* suffix = ".obj";


	/* step 2: determine filename, then open it		*/
	/*   TODO: extract filename from argv, pass it to open_file() */
	// check the argc
	if (argc != 2) {
		fprintf (stderr, "error1: usage: ./lc4 <object_file.obj>\n") ;
		return 1;
	}else {
		input_file = argv[1];
	}

	char* truncate = strchr(input_file, '.');
	// check file type: .obj
	if (strcmp(truncate, suffix) != 0){
		fprintf (stderr, "error1: usage: ./lc4 <object_file.obj>\n") ;
		return 1;
	}
	// check whether the filename is legal
	if (strlen(input_file) < 5) {
		fprintf (stderr, "error1: usage: ./lc4 <object_file.obj>\n") ;
		return 1;
	}

	FILE* file = open_file(input_file);
	/* step 3: call function: parse_file() in lc4_loader.c 	*/
	/*   TODO: call function & check for errors		*/
	if (file == NULL) {
		fprintf (stderr, "error1: usage: ./lc4 <object_file.obj>\n") ;
		return 1;
	}else {
		// even if the function failed, we should still free the memory;
		if(parse_file(file, &memory) != 0) {
			fprintf (stderr, "parse_file() failed\n") ;
			return 2;
		}
	}

	/* step 4: call function: reverse_assemble() in lc4_disassembler.c */
	/*   TODO: call function & check for errors		*/

	if(reverse_assemble(memory) != 0)
    {
        fprintf (stderr, "reverse_assemble() failed\n") ;
        delete_list(&memory);
        return 2;
    }

	/* step 5: call function: print_list() in lc4_memory.c 	*/
	/*   TODO: call function 				*/
	print_list(memory);

	/* step 6: call function: delete_list() in lc4_memory.c */
	/*   TODO: call function & check for errors		*/
	if (delete_list(&memory) != 0) {
		fprintf (stderr, "encouter an error in deleting the list!\n") ;
		return 2;
	}

	/* only return 0 if everything works properly */
	return 0 ;
}
