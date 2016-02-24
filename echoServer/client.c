#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>
#include <math.h>
#include <sys/termios.h>

#define DATA "Hello Word Of Socket"
int main(int argc,char *argv[]){
int sock;
struct sockaadr_in server;
struct hostent *hp,*gethostbyname();
char buf[1024];

/*create socket*/
sock=socket(AF_INET,SOCK_STREAM,0);
if(sock<0){
	perror("Fail to Create Socket !");
	exit(1);
}

server.sin_family=AF_INET;
hp =gethostbyname (*argv[1]);

if(hp==0){
	perror("get host name by fails!");
	exit(1);
}
memcopy(&server.sin_addr,hp->h_addr,hp->h_length);
server.sin_port=htona(5000);

if(connect(sock,(struct sockaddr *)&server, sizeof(server))<0){
	perror("connecting fail !");
	exit(1);
}
if(send(sock,DATA, sizeof(DATA),0)<0){
	perror("send fail !");
	exit(1);
}
printf("Send=%s\n",DATA);
close(sock);
return 0;
}
