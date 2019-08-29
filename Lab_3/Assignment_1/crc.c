#include<stdio.h>
#include<string.h>

void crc(char temp[], char data[], char div[], int divLen, int dataLen){
    // Processing the data;

    for(int i=0; i<dataLen; i++){
        char comp[2]="01";
        char tempArr[divLen];
        if(comp[0]==temp[i]){
            printf("Both are equal.\n");
            for(int j=i; j<divLen+i; j++){
                break;
            } 
        } else {
            int k=0;
            for(int j=i; j<divLen+i; j++){
                printf("The value of temp[j]: %c\nThe value of div[k]: %c\n",temp[j], div[k]);
                printf("The value of j : %d\n",j);
                printf("The value of temp is : %s\n",temp);
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
    printf("Enter number of bits in Data: ");
    int dataBits;
    scanf("%d",&dataBits);
    char data[dataBits];
    printf("Enter the Data: ");
    scanf("%s",data);
    printf("Enter number of bits in Divisor : ");
    int divBits;
    scanf("%d", &divBits);
    char div[divBits];
    printf("Enter the Divisor: ");
    scanf("%s",div);
    int dataLen = sizeof(data)/sizeof(*data);
    int divLen = sizeof(div)/sizeof(*div);
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
    return 0;
}