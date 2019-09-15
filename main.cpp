#include <iostream>
#include <sys/inotify.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

using namespace std;

#define BUF_LEN (10 * (sizeof (struct inotify_event) + NAME_MAX +1))


static volatile int event_fd;

void handler(int sig, siginfo_t *si, void *data)
{
  event_fd = si->si_fd;
}

int main()
{

int inotifyFD = inotify_init();
int inotifyFileWD;
char buff[BUF_LEN];
ssize_t numRead;
char *p;
struct inotify_event *event;

struct sigaction sa;

if(inotifyFD == -1) {cout <<"inotify fault" << endl;}
inotifyFileWD=inotify_add_watch(inotifyFD,"./plik.log",IN_CLOSE_WRITE);
if(inotifyFileWD == -1) {cout <<"inotify fault" << endl; return 0;}

sa.sa_sigaction = handler;
sigemptyset(&sa.sa_mask);
sa.sa_flags = SA_SIGINFO;
sigaction(SIGRTMIN + 1, &sa, NULL);

while(1)
{

/*
numRead = read(inotifyFD, buff, BUF_LEN);
if(numRead == 0){
  cout << "Read from inotify returned 0!" << endl;
  return 0;
}
if(numRead == -1) {
  cout << "Read error" << endl;
  return 0;
}

for(p = buff; p < buff + numRead;)
{
 event = (struct inotify_event *) p;
 cout << "Event on file" << endl;
 p+= sizeof(struct inotify_event) + event->len;
}
*/

}


}
