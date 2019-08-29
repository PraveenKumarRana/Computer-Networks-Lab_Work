#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main(){
    int c_socket;
    char buf[1000] = "Client Connected!";
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
    recv(c_socket,buf,sizeof(buf),0);
    printf("Msg from server: %s\n",buf);
    
    FILE *fp, *text;
    // printf("Error generated before while.\n");
    fp = fopen("logo.bmp", "rb");
    // text = fopen("logo.txt", "wb");
    // Reading the data out.
    int c;
    int che = 0;
    while(EOF != (c = fgetc(fp))){
        // fputc(c,text);
        send(c_socket, &c, sizeof(c), 0);
        send(c_socket, &che, sizeof(che), 0);

    }
    printf("\n\n");

    if(feof(fp)){
        printf("Hit EOF!\n");
        che = 1;
        send(c_socket, &che, sizeof(che), 0);
    } else {
        printf("Some other error!\n");
    }
    fclose(fp);
    // fclose(text);


    close(c_socket);
    return 0;
}