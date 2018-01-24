#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

#define MAX_STRING_LENGTH 40

typedef struct line LINE, *LINE_POINTER;

struct line {
	int number;
	char german[MAX_STRING_LENGTH];
	char english[MAX_STRING_LENGTH];
}; // struct line

void initializeLine(LINE_POINTER lp, int number, char* german, char* english) {
	lp->number = number;
	strcpy(lp->german, german);
	strcpy(lp->english, english);
} // initializeLine(LINE_POINTER, int, char*, char*)

void printLine(LINE line) {
	//printf("%s\n","printline1");
	char padding[41];
	//printf("%s\n","printline2");
	// initialize strings with MAX_STRING_LENGTH spaces
	//printf("%d\n", strlen("                                        "));
	strcpy(padding,"                                        ");
	//printf("%s\n","printline3");
	padding[MAX_STRING_LENGTH - strlen(line.german) + 1] = 0;
	//printf("%s\n","printline4");
	printf("%02d: %s%s(%s)\n",line.number,line.german,padding,line.english);
	//printf("%s\n","printline5");
} // printLine(LINE)

int main(int argc, char** argv) {
	LINE stanza[5];
	LINE verse[5];
	struct iovec iov[3];

	initializeLine(&stanza[0],0,"Du schaust mir in die Augen","You look in my eyes");
	initializeLine(&stanza[1],1,"Du musst mir garnichts sagen","You need not say anything");
	initializeLine(&stanza[2],2,"Ich weiss es sowieso","I know it anyway");
	initializeLine(&stanza[3],3,"Dein herz","Your heart");
	initializeLine(&stanza[4],4,"Sagt es mir","Speaks to me");

	printf("%s\n","Print what is to be written.");
	printLine(stanza[0]);
	printLine(stanza[1]);
	printLine(stanza[2]);
	printLine(stanza[3]);
	printLine(stanza[4]);

	// open file for writing
	int fd = open("schlager.txt", O_WRONLY | O_CREAT | O_TRUNC);

	if(fd == -1) {
		perror("open");
		return 1;
	} // if

	for(int i = 0; i < 5; i++) {
		iov[0].iov_base = &stanza[i].number;
		iov[0].iov_len = sizeof(int);

		iov[1].iov_base = stanza[i].german;
		iov[1].iov_len = MAX_STRING_LENGTH;

		iov[2].iov_base = stanza[i].english;
		iov[2].iov_len = MAX_STRING_LENGTH;

		ssize_t nr = writev(fd,iov,3);
		if(nr == -1){
			perror("writev");
			return 1;
		} // if
	} // for

	// close file after writing
	if(close(fd)) {
		perror("close");
		return 1;
	}
	fd = open("schlager.txt", O_RDONLY);
	if(fd == -1) {
		perror("open");
		return 1;
	} // if

	for(int i = 0; i < 5; i++) {
		iov[0].iov_base = &verse[i].number;
		iov[0].iov_len = sizeof(int);

		iov[1].iov_base = &verse[i].german;
		iov[1].iov_len = MAX_STRING_LENGTH;

		iov[2].iov_base = &verse[i].english;
		iov[2].iov_len = MAX_STRING_LENGTH;

		ssize_t nr = readv(fd,iov,3);
		if(nr == -1) {
			perror("readv");
			return 1;
		} // if
	} // for

	// close file after reading
	if(close(fd)) {
		perror("close");
		return 1;
	} // if

	printf("\n\n%s\n","Print what was read.");
	printLine(verse[0]);
	printLine(verse[1]);
	printLine(verse[2]);
	printLine(verse[3]);
	printLine(verse[4]);

	return 0; // success!
} // main(int argc, char** argv)








