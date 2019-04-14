#include "types.h"
#include "user.h"
#include "stat.h"

char buf[512];

char lastNew[1024];
char cLine[1024];

void unicat(int fd)
{
	int n;
	int curLineOffset = 0;

	int isNew = 1;
	int firstLine = 1;

	while ((n = read(fd, buf, 1)) > 0) {
		if ((strcmp(buf, "\n")) == 0) {
			if (isNew) {
				if (firstLine == 0) {
					lastNew[curLineOffset] = '\0';
					printf(1, "%s", lastNew);
				}
				strcpy(lastNew, cLine);
				strcpy(cLine, "");
			}
			curLineOffset = 0;
			isNew = 0;
			firstLine = 0;
		}
		
		if ((strcmp(buf, "\r")) == 0) {
			cLine[curLineOffset] = '\n';
		} else {
			cLine[curLineOffset] = buf[0];
		}

		if (cLine[curLineOffset] != lastNew[curLineOffset]) {
			isNew = 1;
		}
		else if (firstLine == 1) {
			isNew = 1;
		}
		curLineOffset += 1;
	}
		

	if (n < 0) {
		printf(1, "unicat: read error \n");
		exit();
	}
	printf(1, "%s\n", cLine);
}

void ccat(int fd)
{
	int n;
	int curLineOffset = 0;

	int isNew = 1;
	int firstLine = 1;
	int count = 0;

	while ((n = read(fd, buf, 1)) > 0) {
		if ((strcmp(buf, "\n")) == 0) {
			cLine[curLineOffset] = '\n';
			if (isNew) {
				if (firstLine == 0) {
					printf(1, "%d %s", count, lastNew);
				}
				strcpy(lastNew, cLine);
				strcpy(cLine, "");
				count = 0;
			}
			count += 1;
			curLineOffset = 0;
			isNew = 0;
			firstLine = 0;
			n = read(fd, buf, 1);
		}

		cLine[curLineOffset] = buf[0];
		if (cLine[curLineOffset] != lastNew[curLineOffset]) {
			isNew = 1;
		}
		else if (firstLine == 1) {
			isNew = 1;
		}
		curLineOffset += 1;
	}


	if (n < 0) {
		printf(1, "unicat: read error \n");
		exit();
	}

//	cLine[curLineOffset] = '\n';
	if (isNew) {
		printf(1, "%d %s", count, lastNew);
	}
}

void dcat(int fd)
{
	int n;
	int curLineOffset = 0;

	int isNew = 1;
	int firstLine = 1;
	int count = 0;

	while ((n = read(fd, buf, 1)) > 0) {
		if ((strcmp(buf, "\n")) == 0) {
			cLine[curLineOffset] = '\n';
			if (isNew) {
				if ((firstLine == 0) && (count > 1)) {
					printf(1, "%d %s", count, lastNew);
				}
				strcpy(lastNew, cLine);
				strcpy(cLine, "");
				count = 0;
			}
			count += 1;
			curLineOffset = 0;
			isNew = 0;
			firstLine = 0;
			n = read(fd, buf, 1);
		}

		cLine[curLineOffset] = buf[0];
		if (cLine[curLineOffset] != lastNew[curLineOffset]) {
			isNew = 1;
		}
		else if (firstLine == 1) {
			isNew = 1;
		}
		curLineOffset += 1;
	}


	if (n < 0) {
		printf(1, "unicat: read error \n");
		exit();
	}

//	cLine[curLineOffset] = '\n';
	if (count > 1) {
		printf(1, "%d %s", count, lastNew);
	}
}

void icat(int fd)
{
	int n;
	int curLineOffset = 0;

	int isNew = 1;
	int firstLine = 1;
	int count = 0;

	while ((n = read(fd, buf, 1)) > 0) {
		if ((strcmp(buf, "\n")) == 0) {
			cLine[curLineOffset] = '\n';
			if (isNew) {
				if (firstLine == 0) {
					printf(1, "%s", lastNew);
				}
				strcpy(lastNew, cLine);
				strcpy(cLine, "");
				count = 0;
			}
			count += 1;
			curLineOffset = 0;
			isNew = 0;
			firstLine = 0;
			n = read(fd, buf, 1);
		}

		cLine[curLineOffset] = buf[0];
		int ascii = (int)(cLine[curLineOffset]);
		if (ascii > 96){
			cLine[curLineOffset] = (char)(ascii - 32);
		}
		if (cLine[curLineOffset] != lastNew[curLineOffset]) {
			isNew = 1;
		}
		else if (firstLine == 1) {
			isNew = 1;
		}
		curLineOffset += 1;
	}


	if (n < 0) {
		printf(1, "unicat: read error \n");
		exit();
	}

//	cLine[curLineOffset] = '\n';
	if (isNew) {
		printf(1, "%s", lastNew);
	}
}

void cicat(int fd)
{
	int n;
	int curLineOffset = 0;

	int isNew = 1;
	int firstLine = 1;
	int count = 0;

	while ((n = read(fd, buf, 1)) > 0) {
		if ((strcmp(buf, "\n")) == 0) {
			cLine[curLineOffset] = '\n';
			if (isNew) {
				if (firstLine == 0) {
					printf(1, "%d %s", count, lastNew);
				}
				strcpy(lastNew, cLine);
				strcpy(cLine, "");
				count = 0;
			}
			count += 1;
			curLineOffset = 0;
			isNew = 0;
			firstLine = 0;
			n = read(fd, buf, 1);
		}

		cLine[curLineOffset] = buf[0];
		int ascii = (int)(cLine[curLineOffset]);
		if (ascii > 96){
			cLine[curLineOffset] = (char)(ascii - 32);
		}
		if (cLine[curLineOffset] != lastNew[curLineOffset]) {
			isNew = 1;
		}
		else if (firstLine == 1) {
			isNew = 1;
		}
		curLineOffset += 1;
	}


	if (n < 0) {
		printf(1, "unicat: read error \n");
		exit();
	}

//	cLine[curLineOffset] = '\n';
	if (isNew) {
		printf(1, "%d %s", count, lastNew);
	}
}

int main(int argc, char * argv[]) {

	int fd, i;
	if (argc <= 1) {
		unicat(0);
		exit();
	}

	if (argc == 2) {
		for (i = 1; i < argc; i++) {
			if ((fd = open(argv[i], 0)) < 0) {
				printf(1, "cat: cannot open %s\n", argv[i]);
				exit();
			}
			unicat(fd);
			close(fd);
		}
		exit();
	}
	else if (argc == 3) {
		if (strcmp(argv[1], "-c") == 0) {
			if ((fd = open(argv[2], 0)) < 0) {
				printf(1, "cat: cannot open %s\n", argv[2]);
				exit();
			}
			ccat(fd);
			close(fd);
		}
		else if(strcmp(argv[1], "-d") == 0){
			if ((fd = open(argv[2], 0)) < 0) {
				printf(1, "cat: cannot open %s\n", argv[2]);
				exit();
			}
			dcat(fd);
			close(fd);
		}
		else if(strcmp(argv[1], "-i") == 0){
			if ((fd = open(argv[2], 0)) < 0) {
				printf(1, "cat: cannot open %s\n", argv[2]);
				exit();
			}
			icat(fd);
			close(fd);
		}
	}
	else if(argc == 4){
		if ((strcmp(argv[1], "-c") == 0) && (strcmp(argv[2], "-i") == 0)){
			if ((fd = open(argv[3], 0)) < 0) {
				printf(1, "cat: cannot open %s\n", argv[2]);
				exit();
			}
			cicat(fd);
			close(fd);
		}
	}


	exit();
//Part2 ends here



}