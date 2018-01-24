#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <string.h>
#include "reverse.h"

/// Reverse given file
/** Reads through a file backwards and makes a new file that is the reverse of the original */
int main(int argc, char** argv)
{

    // character buffer only needs to be a single char because of the loop
    char buffer;
    ssize_t ret;
    // return value of close
    int code;
    char file_name[50], part_a[50], part_b[50], a_trap[50];
    char dot = ".";

    // open the file specified in the command line argument for reading
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        perror("open");
    }

    // get the name of the file to be reversed from the command line arguments
    strcpy(file_name, argv[1]);

/*
    char *find;

    find = strchr(file_name, ".");

    printf("%s\n", find);

    if (find != NULL) {
*/


    // split the extension from the filename using a tokenizer
    char *token = strtok(file_name,&dot);
    strcpy(part_a,token);

    // reverse the extensionless filename
    reverse_string(part_a);

    strcpy(a_trap, part_a);

    // add the . back to the end of the filename
    strcat(a_trap,&dot);

    // get the extension
    token = strtok(NULL,&dot);
    strcpy(part_b,token);

    // recombine the reversed filename and extension
    strcat(a_trap, part_b); 


/*
    } else {
        printf("%s\n","else" );
        // reverse the filename
        reverse_string(file_name);

        // copy the reversed filename to part_a
        strcpy(part_a, file_name);
    } // if else
*/

    // create a new file with the reversed filename
    int df = creat(a_trap, 0700);
    if(df == -1){
        perror("creat");
    }

    // get the position of the end of file (file size)
    int file_size = lseek(fd, 0, SEEK_END);

    // loop through each byte in the file in reverse, reading the byte, and writing its contents to the reverse file
    for(int i = file_size - 1; i >= 0; i--) {
        ret = pread(fd, &buffer, 1, i);
        if(ret == -1){
            perror("pread");
        }
        ret = write(df, &buffer, 1);
        if(ret == -1){
            perror("write");
        }
    } // for

    // close files
    code = close(fd);
    code = close(df);

    return 0;
}