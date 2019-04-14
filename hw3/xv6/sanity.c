#include "types.h"
#include "user.h"


int
main()
{
	int i, j, k;
	int pid;
	int wtime, rtime, iotime, status;
	int sums[3];
	int proc[20];

	for (i = 0; i < 20; i++) {
		proc[i] = fork();
		if (proc[i] == -1) {//child
			printf(1, "forked failed:( exiting...\n");
			exit(); // children exit here
		}
		if (proc[i] > 0) continue;
		if (i >= 10) k = 20000000;
    else k = 10000000;
    for(j = 0; j < k; j++){}
    exit();
		//continue; // father continues to spawn the next child
	}

	while((pid = wait_stat(&wtime, &rtime, &iotime, &status)) != -1){
		for (i = 1; i < 20; ++i) {

		//pid = wait_stat(&wtime, &rtime, &iotime, &status);
			//printf(1, "status: %d, proc[i]: %d\n", status, proc[i]);
			if(status == proc[i]){
			printf(1, "pid: %d, waiting time: %d, running: %d, turnaround: %d\n", pid, wtime, rtime, wtime + rtime + iotime);

			break;
			}
		}

	sums[0] += wtime;
	sums[1] += rtime;
	sums[2] += wtime + rtime + iotime;
	}


	printf(1, "Average waiting time: %d\nAverage running time: %d\nAverage turnaround time: %d\n\n\n", sums[0]/20, sums[1]/20, sums[2]/20);
	exit();
}
