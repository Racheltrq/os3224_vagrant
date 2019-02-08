#include "types.h"
#include "user.h"
#include "stat.h"

char buf[64];

char lastNew[64];
char cLine[64];

void unicat(int fd)
{
	int n;
	int curLineOffset = 0;

	int isNew = 1;
	int firstLine = 1;

	while ((n = read(fd, buf, 1)) > 0) {
		//printf(1, "isNew: %d", isNew);
		if ((strcmp(buf, "\n")) == 0) {
			//printf(1, "firstLine = %d\n", firstLine);
			//Line End. Write if not new.
			//cLine[curLineOffset] = '\n';
			if (isNew) {
//				write(1, cLine, sizeof(cLine));
				if(firstLine == 0)
					printf(1, "%s", lastNew);
				strcpy(lastNew, cLine);
				strcpy(cLine, "");
			}
			curLineOffset = 0;
			isNew = 0;
			firstLine = 0;
		}

		cLine[curLineOffset] = buf[0];
		if (cLine[curLineOffset] != lastNew[curLineOffset]) {
			isNew = 1;
		}else if (firstLine == 1){
			isNew = 1;
		}
		curLineOffset += 1;

		//printf(1, "Cur Line Offset: %d\n", curLineOffset);
		//printf(1, "cLine: %s\n", cLine);
	}
		

	if (n < 0) {
		printf(1, "unicat: read error \n");
		exit();
	}
	printf(1, "%s\n", cLine);
}

int main(int argc, char * argv[]) {
	printf(1, "argc: %d\n", argc);
	printf(1, "argv: %s\n", argv[1]);


	int fd, i;
	if (argc <= 1) {
		unicat(0);
		exit();
	}

	
	for (i = 1; i < argc; i++) {
		if ((fd = open(argv[i], 0)) < 0) {
			printf(1, "%d\n", fd);
			printf(1, "cat: cannot open %s\n", argv[i]);
			exit();
		}
		unicat(fd);
		close(fd);
	}
	exit();

	if (strcmp(argv[0], "-c")) {
		printf(1, "-c\n");
		exit();
	}
	else if (strcmp(argv[0], "-d")) {
		printf(1, "-d\n");
		exit();
	}
	else if (strcmp(argv[0], "-d")) {

		exit();
	}
	return 0;
}
