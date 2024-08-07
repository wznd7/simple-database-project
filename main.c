#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>

/*** data structures ***/
typedef struct {
    char * buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*) malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void die(const char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void print_prompt() {printf("db > ");}

void read_input(InputBuffer * input_buffer){
    // assuming input_buffer->buffer is NULL (freed or newly initialied), will malloc for you!
    ssize_t bytes_read = getline(&(input_buffer->buffer),  &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0){
        die("Error reading input\n");
    }

    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = '\0';

}

void close_input_buffer(InputBuffer * input_buffer){
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char* argv[]){
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if(strcmp(input_buffer->buffer, ".exit") == 0){
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s' .\n", input_buffer->buffer);
        }
    } 
}