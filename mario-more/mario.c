#include <cs50.h>
#include <stdio.h>

void make_row(int r);
void make_pyramid(int p);
int ask_user(void);

int main(void)
{
    make_pyramid(4);
    make_pyramid(ask_user());
}

void make_pyramid(int p)
{

    for (int j = 0; j < p; j++)
    {

        for (int k = j; k < p - 1; k++)
        {
            printf(" ");
        }

        make_row(j + 1);
        printf("  ");
        make_row(j + 1);
        printf("\n");
    }
}

void make_row(int r)
{
    for (int i = 0; i < r; i++)
    {
        printf("#");
    }
}

int ask_user(void)
{
    int n;
    while (true)
    {
        n = get_int("How tall should the pyramid be? ");
        if (n >= 1 && n <= 8)
        {
            return n;
        }
    }
}
