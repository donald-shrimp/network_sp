#include <stdio.h>
struct data{
	int a;
	float b;
};

struct data* factory(int a, float b){
	struct data d;
	d.a = a;
	d.b = b;
	return &d;
}

int main(void){
	struct data* d;
	d = factory(10, 2.0);
	printf("%d %f\n", d->a, d->b);
	return 0;

}