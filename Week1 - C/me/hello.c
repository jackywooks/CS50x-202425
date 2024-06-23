#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your Name? ");
    printf("Hello, %s\n", name);
}
