// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Define the type of the dat in the file
typedef uint8_t BYTE;
typedef int16_t TWO_BYTE;


// Number of bytes in .wav header
const int HEADER_SIZE = 44;


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file

    // Cannot do it byte by byte...
    // int counter = 0;
    // BYTE header_buffer;
    // while (fread(&header_buffer, sizeof(BYTE), 1, input) != 0
    //          && counter < HEADER_SIZE)
    // {
    //     fwrite(&header_buffer, sizeof(BYTE), 1, output);
    //     counter++;
    // }

    BYTE header_buffer[HEADER_SIZE];
    fread(header_buffer, HEADER_SIZE, 1, input);
    fwrite(header_buffer, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file

    TWO_BYTE audio_buffer;

    while (fread(&audio_buffer, sizeof(audio_buffer), 1, input) != 0)
    {
        audio_buffer *= factor;
        fwrite(&audio_buffer, sizeof(audio_buffer), 1, output);
    }



    // Close files
    fclose(input);
    fclose(output);
}
