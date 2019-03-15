#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

char *fname(int simbol)
{
  time_t waktu=time(NULL);
  struct tm time = *localtime(&waktu);
  static char namafd[500];
  static char nampung[500];
  memset(&namafd, 0, sizeof(namafd));
  memset(&nampung, 0, sizeof(nampung));
  if (simbol==1)
  {
    sprintf(nampung, "%d", time.tm_mday);
    strcat(namafd, nampung);
    strcat(namafd, ":");
    sprintf(nampung, "%d", time.tm_mon+1);
    strcat(namafd, nampung);
    strcat(namafd, ":");
    sprintf(nampung, "%d", time.tm_year+1900);
    strcat(namafd, nampung);
    strcat(namafd, "-");
    sprintf(nampung, "%d", time.tm_hour);
    strcat(namafd, nampung);
    strcat(namafd, ":");
    sprintf(nampung, "%d", time.tm_min);
    strcat(namafd, nampung);
  }
  else
  {
    time.tm_min+=30;
    mktime(&time);
    sprintf(nampung, "%d", time.tm_mday);
    strcat(namafd, nampung);
    strcat(namafd, ":");
    sprintf(nampung,  "%d", time.tm_mon+1);
    strcat(namafd, nampung);
    strcat(namafd, ":");
    sprintf(nampung, "%d", time.tm_year+1900);
    strcat(namafd, nampung);
    strcat(namafd, "-");
    sprintf(nampung, "%d", time.tm_hour);
    strcat(namafd, nampung);
    strcat(namafd, ":");
    sprintf(nampung, "%d", time.tm_min);
    strcat(namafd, nampung);
    }
    return namafd;
}


    int main()
    {
    pid_t pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);
    umask(0);
    pid_t sid = setsid();
    if (sid < 0)
        exit(EXIT_FAILURE);
    if ((chdir("/")) < 0)
        exit(EXIT_FAILURE);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

	//main program
	char namapath[250];
	memset(&namapath, 0, sizeof(namapath));
	strcat(namapath, "/home/zaky/log/");

	//fork-kan daemon/orphan child
	pid=fork();

	if(pid==0){
	  while(1){
		char folder[200];
		memset(&folder, 0, sizeof(folder));
		strcat(folder, fname(1));

		strcat(namapath, folder);
		mkdir(namapath, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);

		memset(&namapath, 0, sizeof(namapath));
		strcat(namapath, "/home/zaky/log/");
		sleep(1800);
	  }
	}
	else if (pid>0){
	  int tanda=0;
	  int diff=1;
	  char alterFolder[250];
	  memset(&alterFolder, 0, sizeof(alterFolder));
	  while(1){
	    char sebelum[500];
	    char now[500];
	    memset(&sebelum, 0, sizeof(sebelum));
	    memset(&now, 0, sizeof(now));

	    strcat(now, fname(1));

	    char temp[250];
	    memset(&temp, 0, sizeof(temp));
	    strcat(temp, namapath);
	    strcat(temp, alterFolder);

	    struct stat stb;

	    //printf("p %s\n", sebelum);
	    //printf("s %s\n", alterFolder);
	    //printf("c %s\n", now);

	    if (diff==1)
	    {
		memset(&sebelum, 0, sizeof(sebelum));
		strcat(sebelum, fname(1));
		memset(&alterFolder, 0, sizeof(alterFolder));		//untuk nama folder sebelum ditambah 30 menit
		strcat(alterFolder, fname(0));
	    }
	    else if (diff<1 && strcmp(now,alterFolder)==0 && stat(temp, &stb)==0)
	    {
		memset(&sebelum, 0, sizeof(sebelum));
		strcat(sebelum, alterFolder);
		memset(&alterFolder, 0, sizeof(alterFolder));		//untuk nama folder sesudah ditambah 30 menit 
		strcat(alterFolder, fname(0));
	    }

	    memset(&temp, 0, sizeof(temp));
	    strcat(temp,namapath);
	    strcat(temp, sebelum);

	    if ((stat(temp,&stb)==0) && (strcmp(sebelum,"")!=0))
	    {
		while(1){
		  diff--;
		  char *pathsyslog="/var/log/syslog";		//proses untuk membuat log#.log dan memindah isi syslog ke file log#.log

		  char artlog[250];
		  memset(&artlog, 0, sizeof(artlog));		//ada juga proses penamaan file sesuai format
		  strcat (artlog, namapath);
		  strcat (artlog, sebelum);
		  strcat (artlog, "/log");

		  char flagchar[200];
		  memset(&flagchar, 0, sizeof(flagchar));
		  sprintf(flagchar, "%d", tanda+1);
		  strcat (artlog, flagchar);
		  strcat (artlog, ".log");

		  FILE *baca = fopen ((char*)pathsyslog, "r");
		  FILE *pindah = fopen ((char*)artlog, "w");

		  char konten;
		  while ((konten = fgetc(baca))!=EOF){
			fputc(konten,pindah);
		  }
			fclose(baca);
			fclose(pindah);

		  tanda++;
		  if(tanda%30==0)			//proses pemberhentian penambahan file log#.log di folder lama
			break;				//dan dilanjutkan lg penambahan file di folder baru
		  sleep(60);
		}
	      }
	    }
	  }
    	  exit(EXIT_SUCCESS);
}
