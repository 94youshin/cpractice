#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<netinet/in.h>
#include <arpa/inet.h>

int startup(u_short *port);
void error_die(const char *sc);


void error_die(const char *sc)
{
	perror(sc);
    exit(1);
}

int startup(u_short *port)
{
	int httpd = 0;
    int on = 1;
    struct sockaddr_in name;
    httpd = socket(PF_INET,SOCK_STREAM,0);
	if (httpd == -1)
      error_die("socket");


    memset(&name,0,sizeof(name)); //将内存清0
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if((setsockopt(httpd,SOL_SOCKET,SO_REUSEADDR, &on,sizeof(on))) < 0)
    {
        error_die("setsockopt failed");
    }
    if(bind(httpd,(struct sockaddr *)&name,sizeof(name)) < 0)
    {
        /* data */
        error_die("bind");
    }
    if (*port == 0) 
    {
        socklen_t namelen = sizeof(name);
        if(getsockname(httpd, (struct sockaddr *)&name,&namelen)== -1)
            error_die("getsockname");
        *port = ntohs(name.sin_port);
    }
    if (listen(httpd,5) < 0)
        error_die("listen");
    return httpd;
}

int main(void)
{
    int server_sock = 1;
    u_short port = 4000;

    server_sock = startup(&port);
	//printf("%d", server_sock);
    sleep(60);
    close(server_sock);
    return 0;
}
