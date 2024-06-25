#include <stdio.h>
#include <cs50.h>

int main(void){
    int x = get_int("What's x? ");
    int y = get_int("What's y? ");

    double z = (double)x/(double)y;
    printf("%.20f\n", z);
}
