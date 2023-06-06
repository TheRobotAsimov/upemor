#include <stdio.h>

int main() 
{
    int *ap, **apD; 
    int x = 5,y = 7;

    ap=&x;

    apD=&ap;

    printf("%p, %p\n", ap, &x);
    printf(" %-13d, %14d\n", *ap, x);
    printf("\n");
    printf("%p, %p\n", *apD, &x);
    printf(" %-13d, %14d\n", **apD, x);

    return 0;
}