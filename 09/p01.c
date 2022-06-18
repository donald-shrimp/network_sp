#include <stdio.h>
struct TestScore{
    char string_byte;
    char text[32];
    int num;
    char score1;
    short score2;
};

int main(){
    char buff[] = {0x11, 0x73, 0x6F, 0x63, 0x6B, 0x65, 0x74, 0x20, 0x70, 0x72, 0x6F, 0x67, 0x72, 0x61, 0x6D, 0x69, 0x6E, 0x67, 0xFF, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x0F};
    struct TestScore data;
    data.string_byte = *buff;
    for (int i = 0; i < data.string_byte+1; i++){
        if (i!=data.string_byte){
            data.text[i]=*(buff+1+i);
        }else{
            data.text[i]='\0';
        }        
    }
    data.num=*(int*)(buff+data.string_byte+1);
    data.score1=*(buff+data.string_byte+5);
    data.score2=*(short*)(buff+data.string_byte+6);

    printf("文字列のバイト数:%d,文字列:%s,整数:%d,整数:%d,整数:%d\n",data.string_byte,data.text,data.num,data.score1,data.score2);
}
