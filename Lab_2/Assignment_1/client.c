#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main(){
    int c_socket;
    char buf[1000] = "hello server";
    c_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr = INADDR_ANY;
    if(connect(c_socket,(struct sockaddr*)&client,sizeof(client))==-1){
        printf("Connect issue");
        return 0;
    }
    int checker = 1;
    recv(c_socket,buf,sizeof(buf),0);
    printf("%s\n", buf);
    while(checker){
        recv(c_socket,buf,sizeof(buf),0);
        printf("Server : %s\n", buf);
        recv(c_socket,buf,sizeof(buf),0);
        printf("Server : %s\n", buf);
        int option;
        scanf("%d", &option);
        send(c_socket, &option, sizeof(option), 0);
        recv(c_socket,buf,sizeof(buf),0);
        printf("Server : %s\n", buf);
        int a;
        scanf("%d",&a);
        send(c_socket, &a, sizeof(a), 0);
        recv(c_socket,buf,sizeof(buf),0);
        printf("Server : %s\n", buf);
        int b;
        scanf("%d", &b);
        send(c_socket, &b, sizeof(b), 0);
        recv(c_socket,buf,sizeof(buf),0);
        printf("Server : %s\n", buf);
        int result;
        recv(c_socket,&result,sizeof(result), 0);
        printf("%d\n",result);
        printf("Do you want to continue (0 or 1): ");
        scanf("%d",&checker);
        send(c_socket, &checker, sizeof(checker), 0);
    }
    close(c_socket);
    return 0;
}