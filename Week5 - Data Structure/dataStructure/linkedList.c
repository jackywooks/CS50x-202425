// Implement a sorte list of numbers using a linked list

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    // Memory for numbers
    node *list = NULL;
    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n->number = number;
        n->next = NULL;

        // If list is empty
        if (list == NULL)
        {
            list = n;
        }
        // If number belongs at beginning of list
        else if (n->number < list->number)
        {
            n->next = list;
            list = n;
        }
        else
        // iterate through the list and append the n at the end
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // if at end of list
                if (ptr->next == NULL)
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    break;
                }

                // if in middle of list
                if (n->number < ptr->next->number)
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    // Print whole list
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    // free the memory of the list
    node *tmp = list;
    node *counter = list;
    while (tmp != NULL)
    {
        counter = tmp;
        tmp = tmp->next;
        free(counter);
    }

}
