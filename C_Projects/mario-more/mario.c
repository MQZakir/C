#include <cs50.h>
#include <stdio.h>


void wall(int height);


int main(void)
{
    int size = 1;

    //to get user input from 1 to 8,
    do
    {
        size = get_int("Height: ");
    }
    while (size <= 0 || size >= 9);

    wall(size);
}



//function for printing the wall,
void wall(int height)
{
    for (int row = 0; row < height; row++)
    {
        //printing the spaces,
        for (int spaces = row + 1; spaces < height; spaces++)
        {
            printf(" ");
        }

        //printing the left hashes,
        for (int hashes = height + row + 1; hashes > height; hashes--)
        {
            printf("#");
        }

        //printing the space between left and right hashes,
        printf("  ");

        //printing the right hashes,
        for (int hashes = height + row + 1; hashes > height; hashes--)
        {
            printf("#");
        }

        //going to the next line after printing the first iteration,
        printf("\n");
    }
}