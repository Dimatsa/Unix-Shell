#include "Utils.c"

// get_argv returns an array of null-terminated arguments from a single line
// effects: allocates memory, caller must free array
char **get_argv(void);

// prints the error and exits the program
void produce_error(char *error_str);
