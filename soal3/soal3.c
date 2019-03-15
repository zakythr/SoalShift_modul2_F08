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

    if (pipe(fd) < 0)
        exit(1);

    childid = fork();

    if (childid == 0)
    {
        char* argv[3] = { "unzip", "/home/zaky/Downloads/campur2.zip", NULL };
        execv("/usr/bin/unzip", argv);
    }

    childid = fork();
    if (childid == 0)
    {
        execlp("touch", "touch", "daftar.txt", NULL);
    }

    while (wait(&stat) > 0)
        ;
    childid = fork();
    if (childid == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
        execlp("ls", "ls", "/home/zaky/campur2", NULL);
    }
    else
    {
        while (wait(&stat) > 0)
            ;
	//close(STDOUT_FILENO);
        dup2(fd[0], STDIN_FILENO);
        int fileopen = open("home/zaky/daftar.txt", O_WRONLY | O_CREAT);
	//dup2(fileopen, STDOUT_FILENO);        
	close(fd[0]);
	close(fd[1]);
        dup2(fileopen, STDOUT_FILENO);
        char* argv[3] = { "grep", ".txt$", NULL };
        execv("/bin/grep", argv);
    }
}

