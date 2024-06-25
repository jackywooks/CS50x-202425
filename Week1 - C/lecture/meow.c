#include <cs50.h>
#include <stdio.h>

void meow(int input);

int main(void)
{
    meow(3);
}

void meow(int input)
{
    for (int i = 0; i < input; i++)
    {
        printf("meow\n");
    }
}
