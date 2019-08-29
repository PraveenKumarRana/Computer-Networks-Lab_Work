#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

void crc(char temp[], char data[], char div[], int divLen, int dataLen){
    // Processing the data;

    for(int i=0; i<dataLen; i++){
        char comp[2]="01";
        char tempArr[divLen];
        if(comp[0]==temp[i]){
            for(int j=i; j<divLen+i; j++){
                break;
            } 
        } else {
            int k=0;
            for(int j=i; j<divLen+i; j++){
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
    for(int i=0; i<dataLen; i++){
        temp[i]=data[i];
    }
}

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
    
    printf("Message from server: ");
    recv(c_socket,buf,sizeof(buf),0);
    printf("%s\n", buf);
    printf("Enter number of bits in Data: ");
    int dataBits;
    scanf("%d",&dataBits);
    send(c_socket, &dataBits, sizeof(dataBits), 0);
    char data[dataBits];
    printf("Enter the Data: ");
    scanf("%s",data);

    printf("Enter number of bits in Divisor : ");
    int divBits;
    scanf("%d", &divBits);
    send(c_socket, &divBits, sizeof(dataBits), 0);


    char div[divBits];
    printf("Enter the Divisor: ");
    scanf("%s",div);

    int dataLen = dataBits;
    int divLen = divBits;
    printf("The length of data : %d\nThe length of div: %d\n", dataLen, divLen);
    char temp[dataLen+divLen-1];

    for(int i=0; i<dataLen+divLen-1; i++){
        if(i<dataLen){
            temp[i]=data[i];
        } else {
            strcpy(&temp[i],"0");
        }
    }

    printf("Printing the manipulated data.");
    for(int i=0; i<dataLen+divLen-1; i++){
        printf("%c", temp[i]);
    }
    printf("\n");
    
    crc(temp, data, div, divLen, dataLen);

    printf("\nFinal data to be pushed. ");
    for(int i=0; i<dataLen+divLen; i++){
        printf("%c", temp[i]);
    }
    printf("\n");
    printf("The value in div is : %s\n", div);

    
    temp[6]=temp[7];
    printf("Sending the data to server\n");
    send(c_socket, temp, sizeof(temp), 0);
    strcpy(buf,div);
    send(c_socket, buf, sizeof(buf), 0);

    // sending bit counts;
    printf("The value of dataLen: %d\nThe value of divLen: %d\n", dataLen, divLen);
    


    recv(c_socket, buf, sizeof(buf), 0);
    printf("Server Message : %s\n", buf);

    close(c_socket);
    return 0;
}