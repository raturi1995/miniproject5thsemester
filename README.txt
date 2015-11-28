				MINI PROJECT
-------------------------------------------------------------------------------------------------------------------------------------
TOPIC:		ASSEMBLER ON HYPOTHETICAL MACHINE(S.I.C)
-------------------------------------------------------------------------------------------------------------------------------------
INPUT:		Input.txt is the input file where the assembly code is written.
OUTPUT:		1) Inter.txt is the output file from pass1. It is  the intermediate file of the assembly code.
		2) Output.txt is the final output file from pass2 .It is the object file of the assembly code.
-------------------------------------------------------------------------------------------------------------------------------------
SUBMISSION:
	SUBMITTED BY:
			SHUBHAM RATURI
			BTech(CSE)-5th SEM
			C-33
			UNIV.ROLL.NO.-2007555
--------------------------------------------------------------------------------------------------------------------------------------
DESCRIPTION:
		In input file input.txt assembly code is written. In assembly code where there is no value inn the paticular block,"*"astric is used to show that there is no value.
		All the mnemonics are declaired in the program in op_tab  structure.
		No index addressing is used,the index value is by default 0.
		All the addressing is done in hexadecimal. 
HEADERFILES:
		Four Header files are created for different type of functions.
			1)conversion.h -
					For conversion of hexadecimal number to decimal and character to its hexaascii number.
			2)checking_functions.h -
					For checking the opcode and operand for validation,so that location counter can get increased accordingly.
			3)mystructures.h - 
					Structures are created for operation table and symbol table ,and all the mnemonics are defined here with there opcode.
			4)headerfiles.h- 
					In this searching functions are created as search_opcode and search_label ,and all other headerfiles are inherited here only.
 
