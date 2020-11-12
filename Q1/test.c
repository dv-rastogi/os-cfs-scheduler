/* Name: Divyansh Rastogi
   Roll_Number: 2019464 */

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SYS_divyansh 440
#define lim 1000000000
long soft_runtime = 10000;

int main()
{
	
  pid_t pid = fork();
  if (pid < 0) {
  	puts("Forking error!");
  	return 1;
  }
  if (pid > 0) {
  	wait(NULL);
  	struct timeval start, end;
  	gettimeofday(&start, NULL);
  	for(long i = 0; i < lim; ++ i);
  	gettimeofday(&end, NULL);
  	printf("time taken without soft_runtime : %lf ms\n", (double)(end.tv_usec-start.tv_usec)/1000 + (double)(end.tv_sec-start.tv_sec)*1000);
  }
  else {
  	printf("pid of process: %d\n", getpid());
  	long res = syscall(SYS_divyansh, getpid(), soft_runtime);
  	perror("System call status");
  	printf("System call returned %ld.\n", res);
  	if (res != 0) return 1;
  	struct timeval start, end;
  	gettimeofday(&start, NULL);
  	for(long i = 0; i < lim; ++ i);
  	gettimeofday(&end, NULL);
  	printf("time taken with soft_runtime : %lf ms\n", (double)(end.tv_usec-start.tv_usec)/1000 + (double)(end.tv_sec-start.tv_sec)*1000);  
  	return 0;	
  }
  
  return 0;
}