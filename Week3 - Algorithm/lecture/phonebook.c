#include <cs50.h>
#include <stdio.h>
#include <string.h>

//create object person
typedef struct{
        string name;
        string number;
}
person;

int main(void)
{

    //Phone book by two string arrays
    // string names[] = {"Carter", "David", "John"};
    // string numbers[] = {"+416-23231-213123", "12312312-232233", "21312313"};

    // string name = get_string("String: ");

    // for (int i = 0; i < 3; i++)
    // {
    //     if (strcmp(names[i],name) == 0)
    //     {
    //         printf("Found %s\n", numbers[i]);
    //         return 0;
    //     }
    // }
    // printf("NOt Found\n");
    // return 1;


    person people[3];
    people[0].name = "Carter";
    people[0].number = "123123";
    people[1].name = "David";
    people[1].number = "1232183838";
    people[2].name = "John";
    people[2].number = "4412415125";

    string name = get_string("String: ");

    for (int i = 0; i < 3; i++)
    {
        if (strcmp(people[i].name,name) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("NOt Found\n");
    return 1;
}
