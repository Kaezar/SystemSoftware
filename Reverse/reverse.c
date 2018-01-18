#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <string.h>
#include "reverse.h"

int main(int argc, char** argv)
{

    // character buffer only needs to be a single char because of the loop
    char buffer;
    ssize_t ret;
    // return value of close
    int code;
    char fileName[50], partA[50], partB[50];

    // open the file specified in the command line argument for reading
    int fd = open(argv[1], O_RDONLY);

    // get the name of the file to be reversed from the command line arguments
    strcpy(fileName, argv[1]);

    // split the extension from the filename using a tokenizer
    char *token = strtok(fileName,".");
    strcpy(partA,token);

    // reverse the extensionless filename
    reverse_string(partA);

    // add the . back to the end of the filename
    strcat(partA,".");

    // get the extension
    token = strtok(NULL,".");
    strcpy(partB,token);

    // recombine the reversed filename and extension
    strcat(partA, partB);

    // create a new file with the reversed filename
    int rfd = creat(partA, 0700);

    // get the position of the end of file (file size)
    int fileSize = lseek(fd, 0, SEEK_END);

    // loop through each byte in the file in reverse, reading the byte, and writing its contents to the reverse file
    for(int i = fileSize - 1; i >= 0; i--) {
        ret = pread(fd, &buffer, 1, i);
        ret = write(rfd, &buffer, 1);
    } // for

    // close files
    code = close(fd);
    code = close(rfd);

    return 0;
}