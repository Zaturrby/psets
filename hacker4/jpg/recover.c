/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
  // initialize
  FILE* file = fopen("card.raw", "r");
  BYTE signature[3] = {0,0,0};

  // loop over the blocks while there is something to read
  int itemsread = 3;
  int filenum = 1;
  while (itemsread == 3)
  {
    itemsread = fread(&signature, 1, 3, file);
    // check if image
    if (
      signature[0] == 0xff && 
      signature[1] == 0xd8 && 
      signature[2] == 0xff)
    {
      // found an block aligned image -> let's start over    
      fseek(file, -3, SEEK_CUR);

      // prepare the write file
      char filename[8] = {0, 0, 0, '.', 'j', 'p', 'g', '\0'};
      filename[0] = ((filenum / 100) % 10) + '0';
      filename[1] = ((filenum / 10) % 10) + '0';
      filename[2] = (filenum % 10) + '0';

      printf("filename: %s, filenum: %i \n", filename, filenum);
      
      FILE* imgfile = fopen(filename, "w");

      // loop over the blocks
      int EOI = 0;
      BYTE prev = 0;
      BYTE this = 0;      
      while (EOI == 0 && itemsread == 3)
      {
        // loop over the bytes in the block
        for (int i = 0; i < 512; i++)
        {
          // read the current byte, and if they form a marker
          // with the previous byte, inform the outer while 
          // loop that it's done. 
          fread(&this, 1, 1, file);
          if(prev == 0xff && this == 0xd9)
          {
            filenum++;
            EOI = 1;
          }

          // write the byte away, this includes some trailing zeroes
          fwrite(&this, 1, 1, imgfile);

          // remember the byte to be able to find marker
          prev = this;
        }
      }
      // Close the imagefile
      fclose(imgfile);
    } else 
    {
      // no image this block: skip
      fseek(file, 509, SEEK_CUR);
    }
  }
}

// fwrite(&triple, 512, 1, outptr);