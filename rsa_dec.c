#include<stdio.h>
#define P 11
#define Q 17
#define E 3
#define D 107

int main(){
    long int ans=1,c;
    printf("c:");
    scanf("%ld",&c);
    for ( int i = 0; i < D ; i++){
        ans=ans*c%(P*Q);
    }
    printf("Ans:%ld\n",ans);
}