#include "gameIO.h"
#include <stdarg.h>

/*
    printInstruction() function:
        --> Custom printing function which prints an instruction in a different colour.
*/
void printInstruction(char* format,...)
{
      char *parse; // Pointer to a character used to parse the string inputted
      unsigned int i; // Integer for storing 
      char *string;
      
      printf(PRINT_MAGENTA); // Sets print colour to Magenta (the colour used for instructions)

      va_list argList; // Initialises a variable list of arguments
      va_start(argList, format); // Gives va_start the number of arguments

      for(parse = format; *parse != '\0'; parse++)
      {
        while(*parse != '%' && *parse != '\0') // While we haven't gotten a format specifier or the null character
        {
            putchar(*parse); // Output the current letter
            parse++; // Increment our pointer to the next character
        }
        
        if(*parse != '\0')
        {
            switch(*++parse)
            {
                case 'c' : // If the format is a character
                    i = va_arg(argList, int); // Assigns the character argument to i
                    putchar(i); // Outputs the character
                    break; // Ends this case

                case 'd' : // If the format is an integer
                    i = va_arg(argList, int); // Assigns the integer argument to i
                    printf("%d", i);
                    break; // Ends this case

                case 's' :
                    string = va_arg(argList, char *); // Assigns the string argument to 'string'
                    puts(string); // Outputs the string
                    break; // Ends this case

                default:
                    puts(PRINT_RED "\nError, invalid format specifier.\n" PRINT_MAGENTA);
                    break;
            }
        }
      }
      va_end(argList); // Ends memory allocation to the argument list
      printf(PRINT_RESET); // Resets the print colour to white
      fflush(stdout);
}