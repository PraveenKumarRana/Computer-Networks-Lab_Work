#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

void crc(char temp[], char div[], int divLen, int dataLen){
    // Processing the data;

    for(int i=0; i<dataLen; i++){
        char comp[2]="01";
        char tempArr[divLen];
        if(comp[0]==temp[i]){
            // printf("Both are equal.\n");
            for(int j=i; j<divLen+i; j++){
                break;
            } 
        } else {
            int k=0;
            for(int j=i; j<divLen+i; j++){
                // printf("The value of temp[j]: %c\nThe value of div[k]: %c\n",temp[j], div[k]);
                // printf("The value of j : %d\n",j);
                // printf("The value of temp is : %s\n",temp);
                if(temp[j]==div[k]){
                    temp[j]=comp[0];
                }else{
                    temp[j]=comp[1];
                }
                k++;
            }
        }
    }
    // Making the final data to be sent here.
    // for(int i=0; i<dataLen+divLen-1; i++){
    //     printf("%c", temp[i]);
    // }
    printf("\n");
}

int main(){
    int s_socket, s_server;
    char buf[1000]="Hi,Server Started";
    char temp[100];
    char div[100];
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
    
    send(s_server, buf, sizeof(buf), 0);
    printf("Data from the client: ");
    bzero(buf,sizeof(buf));
    int dataBits;
    recv(s_server, &dataBits, sizeof(dataBits), 0);
    int divBits;
    recv(s_server, &divBits, sizeof(divBits), 0);

    int dataLen = dataBits;
    int divLen = divBits;

    recv(s_server, temp, sizeof(temp), 0);
    printf("%s\n", temp);
    printf("Divisor from the client: ");
    
    recv(s_server, div, sizeof(div), 0);
    printf("%s\n", div);
    int tempLen = dataLen+divLen-1;

    printf("The value of dataLen: %d\nThe value of divLen: %d\n",dataLen, divLen);

    crc(temp, div, divLen, dataLen);

    int count = 0;
    for(int i=0; i<tempLen; i++){
        if(temp[i]=='0'){
            count++;
        }
    }

    if(count==tempLen){
        printf("There is no error in recived data.\n\n");
        strcpy(buf,"Data recieved Successfully");
        send(s_server, buf, sizeof(buf), 0);
    } else {
        printf("Error in the recieved data.\n\n");
        strcpy(buf,"Data recieved with error, Please send it again.");
        send(s_server, buf, sizeof(buf), 0);
    }

    close(s_server);
    return 0;
}
