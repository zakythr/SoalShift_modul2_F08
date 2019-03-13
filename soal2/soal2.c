#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) 
  {
	chmod ("/home/zaky/hatiku/elen.ku",  S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);
	struct stat stb;
	char folderelen[30]="/home/zaky/hatiku/elen.ku";
	stat(folderelen, &stb);

	struct passwd *pw = getpwuid(stb.st_uid);
	struct group *gr = getgrgid(stb.st_gid);
	char mydata[10]="www-data";
	int usr=strcmp(pw->pw_name, mydata);
	int grup=strcmp(gr->gr_name, mydata);

	if(usr==0 && grup==0){
		remove(folderelen);
	}

	sleep(3);

	}
	exit(EXIT_SUCCESS);
  }
