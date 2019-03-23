#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int fd[2];
    pipe(fd);
    int stat;
    pid_t childid;
    pid_t childid2;

    if (pipe(fd) < 0)
        exit(1);

    childid = fork();

    if (childid == 0)
    {
        char* argv[5] = { "unzip", "/home/zaky/Downloads/campur2.zip", "-d", "/home/zaky/SoalShift_modul2_F08/soal3", NULL };
        execv("/usr/bin/unzip", argv);
    }
    else
    {
    while (wait(&stat) > 0);
    childid2 = fork();
    if (childid2 == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        char* argv[3] = {"ls", "/home/zaky/SoalShift_modul2_F08/soal3/campur2", NULL};
	execv("/bin/ls", argv);
        //execlp("ls", "ls", "/home/zaky/SoalShift_modul2_F08/soal3/campur2", NULL);
    }
    else
    {
		while((wait(&stat))>0);
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		int fileopen = open("/home/zaky/SoalShift_modul2_F08/soal3/daftar.txt", O_WRONLY);
		close(fd[0]);
		dup2(fileopen, STDOUT_FILENO);
		char *argv[3] = {"grep",".txt$", NULL};
		execv("/bin/grep", argv);
    }
  }
}
