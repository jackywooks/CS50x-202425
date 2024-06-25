#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");
    for (int i = 0, n =strlen(s); i < n; i++)
    {
        //if lower case
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            // Underlying Logic by minusing the position in the ASCII table
            printf("%c", s[i] - ('a' - 'A')); // 32
            printf("%c", toupper(s[i])); //ctype library function

        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}
