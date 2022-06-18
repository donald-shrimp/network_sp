#include <stdio.h>
struct data{
	int a;
	float b;
};

void factory(struct data* d , int a, float b){
	d->a = a;
	d->b = b;
}

int main(void){
	struct data d;
	factory(&d,10, 2.0);
	printf("%d %f\n", d.a, d.b);
	return 0;
}