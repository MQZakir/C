#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Constant variables

//BYTE for 8 bytes of data
typedef uint8_t BYTE;

//BLOCK_SIZE for 512 bytes of jpeg data
int BLOCK_SIZE = 512;


int main(int argc, char *argv[])
{
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./recovery IMAGE\n");
        return 1;
    }
    FILE *raw_file = fopen(argv[1], "r");

    if (!raw_file)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    char file[8];
    FILE *image = NULL;
    BYTE buffer[BLOCK_SIZE];
    int count = 0;

    //Loop for reading each of the 8 bytes in the file
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                sprintf(file, "%03i.jpg", count);
                image = fopen(file, "w");
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, image);
                count++;
            }
            else if (count > 0)
            {
                fclose(image);
                sprintf(file, "%03i.jpg", count);
                image = fopen(file, "w");
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, image);
                count++;
            }
        }

        //If laready found a jpeg file
        else if (count > 0)
        {
            fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, image);
        }
    }

    //closing files
    fclose(raw_file);
    fclose(image);

    return 0;
}