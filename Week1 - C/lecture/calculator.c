#include <stdio.h>
#include <cs50.h>

int add(int x, int y);

int main(void){
    int x = get_int("What's x? ");
    int y = get_int("What's y? ");

    int z = add(x,y);
    printf("z is %d\n",z);
}

int add(int x, int y){
    return x + y;
}
