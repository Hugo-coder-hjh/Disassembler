/************************************************************************/
/* File Name : lc4_disassembler.c 										*/
/* Purpose   : This file implements the reverse assembler 				*/
/*             for LC4 assembly.  It will be called by main()			*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"
#define USER_CODE_LOWER 0x0000
#define USER_CODE_UPPER 0x1FFF
#define USER_DATA_LOWER 0x2000
#define USER_DATA_UPPER 0x7FFF

int reverse_assemble (row_of_memory* memory)
{
	// create the variables to use
	short unsigned int OPCODE = 0x0001;   // first version
	short unsigned int SUB_OPCODE;
	short unsigned int REGISTER;
	row_of_memory* node_searched;

	// call the helper function to find the node
	node_searched = search_opcode(memory, OPCODE);
 
	// keep searching the node until it is NULL
	while (node_searched != NULL) {
      // create the temp variables to store the instructions
      // update when every node updates
      char isa[50];
      char IMM[3]; // IMM5 the biggest is 11111
      // access and modify the SUB_OPCODE
      SUB_OPCODE = (node_searched->contents) >> 3;  // shift to the end
      SUB_OPCODE = SUB_OPCODE & 0x0007;   // BIT MASK with 0x0007 (0000000000000111)
      switch(SUB_OPCODE) 
      {
         case 000:
            strcpy(isa,"ADD");
            break; 

         case 001:
            strcpy(isa,"MUL");
            break; 

         case 010:
            strcpy(isa,"SUB");
            break; 

         case 011:
            strcpy(isa,"DIV");
            break; 

         default: 
            strcpy(isa,"ADD");
            break; 
      }
      // get Rd
      REGISTER = (node_searched->contents) >> 9;  // shift to the end
      REGISTER = REGISTER & 0x0007;   // BIT MASK with 0x0007 (0000000000000111)
      // decide the register number and add it to isa
      switch(REGISTER) 
      {
         case 0:
            strcat(isa," R0,");
            break;

         case 1:
            strcat(isa," R1,");
            break;

         case 2:
            strcat(isa," R2,");
            break;

         case 3:
            strcat(isa," R3,");
            break;
               
         case 4:
            strcat(isa," R4,");
            break;

         case 5:
            strcat(isa," R5,");
            break;

         case 6:
            strcat(isa," R6,");
            break;

         case 7:
            strcat(isa," R7,");
            break;

         default :
            return -1; 
      }

      // get Rs
      REGISTER = (node_searched->contents) >> 6;  // shift to the end
      REGISTER = REGISTER & 0x0007;   // BIT MASK with 0x0007 (0000000000000111)
      // decide the register number and add it to isa
      switch(REGISTER) 
      {
         case 0:
            strcat(isa," R0,");
            break;

         case 1:
            strcat(isa," R1,");
            break;

         case 2:
            strcat(isa," R2,");
            break;

         case 3:
            strcat(isa," R3,");
            break;
               
         case 4:
            strcat(isa," R4,");
            break;

         case 5:
            strcat(isa," R5,");
            break;

         case 6:
            strcat(isa," R6,");
            break;

         case 7:
            strcat(isa," R7,");
            break;

         default : 

            return -1; 
      }

      // get IMM
      REGISTER = (node_searched->contents) >> 5;  // shift to the end
      REGISTER = REGISTER & 0x0001;   // BIT MASK with 0x0001 (0000000000000001)
      if (REGISTER == 1) {
         REGISTER = (node_searched->contents) & 0x001f;   // BIT MASK with 0x001f (0000000000011111)
         // consider the positive and negative
         if (REGISTER > 15){
            REGISTER = 16 - (REGISTER & 0b0000000000001111);
            sprintf(IMM,"%d",REGISTER);
            IMM[2]='\0';
            strcat(isa," #-");
            strcat(isa,IMM);
         }else {
            sprintf(IMM,"%d",REGISTER);
            IMM[2]='\0';
            strcat(isa," #");
            strcat(isa,IMM);
         }
      
      }else {
         // get Rt
         REGISTER = (node_searched->contents) & 0x0007;   // BIT MASK with 0x0007 (0000000000000111)
         // decide the register number and add it to isa
         switch(REGISTER) 
         {
         case 0:
            strcat(isa," R0");
            break;

         case 1:
            strcat(isa," R1");
            break;

         case 2:
            strcat(isa," R2");
            break;

         case 3:
            strcat(isa," R3");
            break;
               
         case 4:
            strcat(isa," R4");
            break;

         case 5:
            strcat(isa," R5");
            break;

         case 6:
            strcat(isa," R6");
            break;

         case 7:
            strcat(isa," R7");
            break;

         default : 
            return -1; 
         }
      }
   // allocate memory strings before calling strcpy()!
   node_searched->assembly=malloc( sizeof(char) * ((strlen(isa))+1) );
   strcpy(node_searched->assembly, isa);
   node_searched = search_opcode(memory, OPCODE);      
	}// outside while loop

	return 0 ;
}
