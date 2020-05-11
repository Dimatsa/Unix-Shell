#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "Utils.h"

int main(void) {
    int child_pid = 0;
    char ** argv = NULL;
    char *file = NULL;

    while (true) {
        argv = get_argv();
        file = argv[0];
        int stat_loc = 0;

        // Clones the call process
        child_pid = fork();

        // Executes commands for the child
        if (child_pid == 0) {
            int execvp_err = execvp(file, argv);

            if (execvp_err) {
                produce_error("Error executing process");
            } 
        } // Error creating new process 
        else if (child_pid < 0) {
            produce_error("Error creating child");
        } // Executes commands for the parent
        else {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        // Freeing allocated memory
        int del_index = 0;
        for (; argv[del_index]; ++del_index) {
            free(argv[del_index]);
        }
        free(argv[del_index]);
        free(argv);
    }
}