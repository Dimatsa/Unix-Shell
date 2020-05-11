#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const int MAX_INPUT_LEN = 64;
const int MAX_TOKEN_COUNT = 16;

char **get_argv(void) {
    // Retrieving input from user
    char input_str[64 + 1] = {};
    printf("$shell: ");
    fgets(input_str, 64, stdin);

    // Converting input into array of args
    char **argv = malloc(sizeof(char *) * (MAX_TOKEN_COUNT + 1));
    assert(argv);
    int token_count = 0;
    int curr_token_len = 0;
    char *curr_token = strtok(input_str, " "); 
    char *curr_token_ptr = NULL;

    if (curr_token) {
        curr_token_len = strlen(curr_token);
        curr_token_ptr = malloc(sizeof(char) * (curr_token_len + 1 + 5));
        assert(curr_token_ptr);
        strcpy(curr_token_ptr, curr_token);
        char *p = strchr(curr_token_ptr, '\n');
        if (p) *p = '\0';
        argv[0] = curr_token_ptr;
        ++token_count;
    } else {
        return NULL;
    }

    while (curr_token) {
        curr_token = strtok(NULL, " ");
        if (!curr_token) {
            break;
        }
        curr_token_len = strlen(curr_token);
        curr_token_ptr = malloc(sizeof(char) * (curr_token_len + 1 + 5));
        assert(curr_token_ptr);
        strcpy(curr_token_ptr, curr_token);
        char *p = strchr(curr_token_ptr, '\n');
        if (p) *p = '\0';
        argv[token_count] = curr_token_ptr;
        ++token_count;
    }

    argv[token_count] = malloc(sizeof(char));
    *argv[token_count] = '\0';

    return argv;
}

void produce_error(char *error_str) {
    perror(error_str);
}
