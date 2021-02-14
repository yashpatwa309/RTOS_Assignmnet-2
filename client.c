#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *text)
{
    perror(text);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, port_num, n;
    struct sockaddr_in server_addr;
    struct hostent *server;

    char buff[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    port_num = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"error, No such host\n");
        exit(0);
    }
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&server_addr.sin_addr.s_addr,
         server->h_length);
    server_addr.sin_port = htons(port_num);
    if (connect(sockfd,(struct sockaddr *) &server_addr,sizeof(server_addr)) < 0) 
        error("error in connecting");
    printf("client: ");
    while(1)
    {
        bzero(buff,256);
        fgets(buff,255,stdin);
        n = write(sockfd,buff,strlen(buff));
        if (n < 0) 
             error("error in writing to the socket");
        bzero(buff,256);
        n = read(sockfd,buff,255);
        if (n < 0) 
             error("error in reading from the socket");
        printf("Server : %s\n",buff);
        int i = strncmp("See You" , buff , 7);
        if(i == 0)
               break;
    }
    close(sockfd);
    return 0;
}
