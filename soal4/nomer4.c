#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <syslog.h> 
#include <unistd.h> 
#include <time.h> 

int main() { 
  pid_t pid, sid; 

  pid = fork(); 

  if (pid < 0) { 
	exit(EXIT_FAILURE); 
  } 

  if (pid > 0) { 
	exit(EXIT_SUCCESS); 
  } 

  umask(0); 

  sid = setsid(); 

  if (sid < 0) { 
	exit(EXIT_FAILURE); 
  } 

  if ((chdir(".")) < 0) { 
	exit(EXIT_FAILURE); 
  } 

close(STDIN_FILENO); 
close(STDOUT_FILENO); 
close(STDERR_FILENO); 

int i=1;

while(1) { 
	struct stat cek; 
	time_t timer; 
	stat("/home/zaky/Documents/makanan/makan_enak.txt", &cek); 

	if(difftime(time(&timer), cek.st_atime) <= 30){  
		char makan[100]; 
		sprintf(makan, "%d", i); 
		char directory[200] = "/home/zaky/Documents/makanan/makan_sehat"; 
		strcat(directory, makan); 
		strcat(directory,".txt"); 

		FILE *new = fopen(directory, "w");
		fclose(new);
		i++;
	}
	sleep(5);
    }

    exit(EXIT_SUCCESS); 
}
