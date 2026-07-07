#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];

    // Create a buffer for image name
    char imgName[8];

    // Counting to know which image number we are writing
    int countImage = 0;

    // Initiate image pointer to NULL
    FILE *img = NULL;

    // While there's still data left to read from the memory card
    while (fread(&buffer, 1, 512, card) ==
           512) // loop while we are still reading blocks of only 512 bytes
    {
        // check for JPEG signature header: 0xff 0xd8 0xff 0xe0(any combination on the last 4 bits)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            // Create JPEGs from the data
            if (img != NULL)
            {
                fclose(img); // close current image
            }
            sprintf(imgName, "%03i.jpg", countImage); // format image name
            img = fopen(imgName, "w");                // create new image
            fwrite(&buffer, 1, 512, img);             // write data block to image FILE
            countImage++;                             // update image number for next one
        }
        else // if header not found
        {
            if (img != NULL)
            {
                fwrite(&buffer, 1, 512, img); // write data block to image FILE
            }
        }
    }

    fclose(card);
    fclose(img);
}
