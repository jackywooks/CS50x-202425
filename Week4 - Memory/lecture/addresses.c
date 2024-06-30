// #include <cs50.h>
#include <stdio.h>

typedef char *string;

int main (void)
{
    // int n = 50;
    // int *p = &n; // when delcaring, mean create a pointer and go to that memory location
    // printf("%i\n", *p); // * mean go there
    // printf("%p\n", p); // * mean go there

    // string s = "HI!";
    // string ss = "HI!";
    // printf("%p\n", ss);
    // printf("%p\n", &ss[0]);

    // printf("%s\n", ss);

    char *s = "HI!";
    printf("%c", *s);
    printf("%c", *(s + 1));
    printf("%c\n", *(s + 2));



}
