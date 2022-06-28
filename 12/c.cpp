#include <stdio.h>
#include <iostream>
#include <thread>

int main(){
    unsigned long num = 0,a=0,b=0;
    auto sum = [](unsigned long i,unsigned long count,unsigned long *num){for ( i ; i <= count; i++){*num += i;}};
    std::thread th1(sum, 1,500000000,&a);
    std::thread th2(sum, 500000001,1000000000,&b);
    th1.join();
    th2.join();
    num=a+b;
    printf("num:%ld\n", num);
    return 0;
}