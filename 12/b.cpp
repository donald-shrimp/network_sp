#include <stdio.h>
#include <iostream>
#include <thread>

void Thnum(unsigned long i,unsigned long count,unsigned long *num){
    for ( i ; i <= count; i++){
        *num += i;
    }
}

int main(){
    unsigned long num = 0,a=0,b=0;
    std::thread th1(Thnum, 1,500000000,&a);
    std::thread th2(Thnum, 500000001,1000000000,&b);
    th1.join();
    th2.join();
    num=a+b;
    printf("num:%ld\n", num);
    return 0;
}