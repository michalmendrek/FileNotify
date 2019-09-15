#include <iostream>
#include <sys/inotify.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>

using namespace std;

#define BUF_LEN (10 * (sizeof (struct inotify_event) + NAME_MAX +1))

int main()
{

int inotifyFD = inotify_init();
int inotifyFileWD;
int epollFD   = epoll_create(sizeof(inotifyFD));
int cfg;
int ret;
char buff[BUF_LEN];
ssize_t numRead;
char *p;
struct inotify_event *event;
struct epoll_event ev;


if(inotifyFD == -1) {cout <<"inotify fault" << endl;}

inotifyFileWD=inotify_add_watch(inotifyFD,"./plik.log",IN_CLOSE_WRITE);

if(inotifyFileWD == -1) {cout <<"inotify fault" << endl; return 0;}

if(epollFD <0 ) {cout << "Epoll fault" << endl;}

//ev.events=EPOLLIN|EPOLLOUT|EPOLLET;
ev.events=EPOLLIN|EPOLLET;

cfg = epoll_ctl(epollFD, EPOLL_CTL_ADD, inotifyFD, &ev);

if (cfg < 0) {cout << "Epoll fault" << endl;}



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

 ret = epoll_wait(epollFD, &ev, 100, 1000);
 if(ret > 0 )
 {
  cout << "Modify done" << endl;
   numRead = read(inotifyFD, buff, BUF_LEN);
   for(p = buff; p < buff + numRead;)
 {
  event = (struct inotify_event *) p;
  cout << "Event on file" << endl;
  p+= sizeof(struct inotify_event) + event->len;
 }

 } else if(ret <0) {cout << "Error in pooling" << endl;} else 
 {
  cout << "TimeOut" << endl;
 }




}


}
