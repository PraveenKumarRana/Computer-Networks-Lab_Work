#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int calculator(int a, int b, int option){
    switch(option){
        case 1:{
            // addition will be done here.
            return a+b;
        }
        case 2:{
            // substraction will be done here.
            return a-b;
        }
        case 3:{
            // multiplication will be done here.
            return a*b;
        }
        case 4:{
            // Division takes place here.
            return a/b;
        }
    }
    return 0;
}

int main(){
    int s_socket, s_server;
    char buf[1000]="Hi Server Started : ";
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
    while(checker){
        printf("Inside while Loop\n");
        // memset(buf, 0, sizeof buf);
        strcpy(buf,"What operations you want to perform ?\n");
        send(s_server, buf, sizeof(buf), 0);
        strcpy(buf,"Select any options\n1. Addition\n2. Substraction\n3. Multiplication\n4. Division\n");
        send(s_server, buf, sizeof(buf), 0);
        int option;
        recv(s_server,&option, sizeof(option),0);
        printf("Client : Option : %d\n", option);
        strcpy(buf,"Enter First Number : ");
        send(s_server, buf, sizeof(buf), 0);
        int a;
        recv(s_server,&a,sizeof(a),0);
        printf("Client : First Number : %d\n", a);
        strcpy(buf,"Enter Second Number : ");
        send(s_server, buf, sizeof(buf), 0);
        int b;
        recv(s_server,&b,sizeof(b),0);
        printf("Client : Second Number : %d\n", b);
        int result = calculator(a,b,option);
        strcpy(buf,"Result of your Selected computation : ");
        printf("Result of your Computation : %d\n", result);
        send(s_server, buf, sizeof(buf), 0);
        send(s_server, &result, sizeof(result), 0);
        recv(s_server,&checker, sizeof(checker), 0);
    }
    close(s_server);
    return 0;
}
