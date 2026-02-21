## Brainfck++
is an esoteric programming language based on the infamous Brainf*ck. 
Brainfck++ offers additional utilities to the original language to make it easier to form large-scale coding projects in the language, along with some shortcuts to make development easier in the langauge

## Same as Original
Layout: Starting with a mutable-length vector consisting of integers that the code operates on (starting with [0])(however, stored as a 32-bit signed int instead of an 8-bit int)
There exists a pointer that points to a value on the layout that the code operates on (starting at 0)
Operations:
* \>  MOVE_RIGHT: moves pointer to the right (if there are no more values to the right, append a 0 to the right of the vector layout)
* \<  MOVE_LEFT: moves pointer to the left (if there are no more values to the left, return with an error). I believe that this helps with future debugging, testing, and code safety in concurrency with other operations.
* \+  INCREMENT: increment the integer the pointer points to by 1
* \-  DECREMENT: decrement the integer the pointer points to by 1
* \. -> o  OUTPUT(in brainfck++ write o instead of .): output the ASCII character associated with the integer the pointer points to
* \] WHILE: jump backwards to matching [ if the integer the pointer points to is NOT 0
* \, XXXXXXXX (Original Input command was removed for different input commands seen below)

## Added Features
One Value called the SAVE is introduced in Brainfck++ to help with copying values over; it acts as another integer space always accessible by the program
* \^ SAVE: copies the value in the cell the pointer points to into the SAVE cell
* v LOAD: copies the value in the SAVE cell into the cell the pointer points to

* \( IF: jump forwards to matching ) if the integer the pointer points to is NOT 0
* \! NOT: if the integer pointer points to is 0, turn it into 1; if the integer the pointer points to is NOT 0, turn it into 0
* \# NUMBER: set the value of the cell the pointer is pointing to the integer that appears directly after the \# sign (e.g. #245 -> 245)
* \' CHARACTER: set the value of the cell the pointer is pointing at to the static cast integer of the character next to it (e.g., 'A -> 65)
* \"" STRING: starting at the cell the pointer is pointing at, add the static cast integer of the first character, move one cell to the right, and add the next character in the same way
* \p PRINT: prints the integer value of the integer the pointer points to
* _: STRING_INPUT: lets the user input a string up to the length of the saved pointer integer and enters the string into the cells just like in the "" feature
* ~: INTEGER_INPUT: lets the user input an integer and stores it in the cell the pointer points to (not putting in an integer leads to an error)

* \|name:value| DEFINE / FUNCTION: defines a definition called name to be replaced by the value by putting the name in {}
  e.g {add_3}|add_3:+++| -> +++
* \@ IMPORT: imports another file into the current file, essentially replacing the @fileName.bfpp with the contents of the file fileName.bfpp
  
