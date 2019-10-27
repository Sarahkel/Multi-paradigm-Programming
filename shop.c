#include <stdio.h>
#include <string.h>

struct Customer {
    char * name;
    double budget;
};

int main(void)
{
    struct Customer sarah = { "Sarah", 100.0 };
    return 0;
}