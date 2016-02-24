#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include <arpa/inet.h>
#include <sys/un.h>
int main(int argc,char *argv[]){
int sock,mysock,rval;
struct sockaadr_un server;
char buf[1024];

/*create socket*/
sock=socket(AF_INET,SOCK_STREAM,0);
if(sock<0){
	perror("Fail to Create Socket !");
	exit(1);
}

server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=5000;

//bind socket
if(bind(sock,(struct sockaddr *)&server,sizeof(server))<0){
	perror("socket binding fail !");
	exit(1);
}

//listen 
listen(sock,5);

//accept
while(1){
	mysock=accept(sock,(struct sockaddr *) 0,0);
	if(mysock==-1){
		perror("process accept fail !");
	}else{
		memset(buf,0,sizeof(buf));
		if((rval=recv(mysock,buf,sizeof(buf),0))<0){
			perror("reading stream message error !");
		}else if(rval==0){
			perror("ending connection...");
		}else{
			printf("MSG :\n%s",buf);
		}
		printf("got the MSG(rval=%d) \n",rval);
	}
}
return 0;
}
