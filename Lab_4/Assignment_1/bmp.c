#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    FILE *fp, *text;
    // printf("Error generated before while.\n");
    fp = fopen("logo.bmp", "rb");
    text = fopen("logo.txt", "wb");
    // Reading the data out.
    int c;
    
    while(EOF != (c = fgetc(fp))){
        fputc(c,text);
    }
    printf("\n\n");

    if(feof(fp)){
        printf("Hit EOF!\n");
    } else {
        printf("Some other error!\n");
    }
    fclose(fp);
    fclose(text);

    fp = fopen("newLogo.bmp", "wb");
    text = fopen("logo.txt", "rb");

    while(EOF != (c = fgetc(text))){
        fputc(c,fp);
    }
    printf("\n\n");

    if(feof(text)){
        printf("Hit EOF!\n");
    } else {
        printf("Some other error!\n");
    }

    fclose(fp);
    fclose(text);
    return 0;
}