#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main(){
    int s_socket, s_server;
    char buf[1000]="Connected to the Server!";
    s_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, other;
    memset(&server, 0, sizeof(server));
    memset(&other, 0, sizeof(other));

    server.sin_family = AF_INET;
    server.sin_port=htons(9009);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s_socket, (struct shockaddr*)&server, sizeof(server));
    listen(s_socket,5);
    socklen_t add;
    add = sizeof(other);
    s_server = accept(s_socket, (struct sockadddr*)&other, &add);
    int checker = 1;
    send(s_server, buf, sizeof(buf), 0);
    
    FILE *fp;
    fp = fopen("newLogo.bmp", "wb");
    // text = fopen("logo.txt", "rb");
    int c;
    int che = 0;
    while(che==0){
        recv(s_server, &c, sizeof(c), 0);
        fputc(c,fp);
        recv(s_server, &che, sizeof(che), 0);
    }
    printf("\n\n");

    printf("Successfully recieved the data.\n");
    fclose(fp);
    // fclose(text);


    close(s_server);
    return 0;
}
