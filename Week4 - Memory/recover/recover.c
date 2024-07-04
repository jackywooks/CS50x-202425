#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_SIZE 512

// Define the type of the data in the file
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BYTE_SIZE];

    // Counter of the jpg created
    int counter = 0;

    // Jpef output
    char jpgName[8];

    // Open a jpeg file pointer
    FILE *jpeg = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BYTE_SIZE, card) == BYTE_SIZE && !feof(card))
    {
        // Create JPEGs from the data when found this pattern
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) &&
            (buffer[3] & 0xe0) == 0xe0)
        {
            // If the jpeg file is already open, close it
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }
            // create a new jpg file
            sprintf(jpgName, "%03d.jpg", counter);
            jpeg = fopen(jpgName, "w");
            counter++;
            fwrite(buffer, 1, BYTE_SIZE, jpeg);
        }
        else if (jpeg != NULL)
        {
            fwrite(buffer, 1, BYTE_SIZE, jpeg);
        }
    }

    if (jpeg != NULL)
    {
        fclose(jpeg);
    }

    fclose(card);
}
