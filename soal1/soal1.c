#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

int main()
{
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);


    while(1)
    {
	sleep(3);
	chdir("/");
        DIR *dp;
        struct dirent *ep;
        //buka folder direktori
        dp = opendir ("/home/zaky/Documents");
        while ((ep = readdir (dp)) != NULL){
	  char *filename = ep->d_name;
          char *dupli = strdup(filename);
          char *titik = strrchr(dupli, '.');
          if (!titik)
                continue;
          char *extensi = strdup(titik + 1);
          if (strcmp (extensi, "png") == 0){
             *titik = '\0';
	     char asal[300], tempat[300];
             strcpy(tempat, "/home/zaky/modul2/gambar/");
             strcpy(asal, "/home/zaky/Documents/");
             strcat(asal, filename);
             strcat(dupli, "_grey.");
             strcat(tempat, dupli);
             strcat(tempat, extensi);
             /*pindahkan file .png ke folder lain  dengan fungsi rename*/
		puts(asal); puts(tempat);
             if (rename(asal, tempat) == -1)
		printf("%s\n", strerror(errno));
             }
          }
       closedir (dp);
     }
    exit(EXIT_SUCCESS);
}

