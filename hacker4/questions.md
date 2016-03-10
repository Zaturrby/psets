# Question 0: How much colors do the image formats support

1. BMP supports colors in the range of 2^[1,2,3,4,8,16,24,32,(64)]. Using 64 bits is ‘permitted’ by GDI+, according to the wiki article. 
2. GIF supports 2^[1,2,4,(24)] colors. Using 24 bits for the color is however only possible by enclosing multiple “images” with their own color tables containing 255 colors chosen from the 24bit palette and rendering them next to each other. Note however that this method is quite inefficient and not widely supported.
3. JPEG supports a 24bit sRGB color space. However it should be noted that the encoding of a JPEG downsamples the colors more heavily than the brightness. While the ultimate range of colors remains the same, there is a cost in color detail.
4. PNG supports colors in the range of 2^[1,2,3,4,8,16,24,32,48]. The total bit depth can be 2^64 due to the alpha channel. 

# Question 1: Which format allows animation

The GIF format allows, by default, the one time display of a sequence of frames. By extension it allows it to be displayed in a continuous manner. 

# Question 2: Lossy vs lossless compression
 
Lossless compression is the algorithmic downsizing of a file that is completely reversible. Lossy compression is not completely reversible on the other hand, there is loss of information in the compression algorithm. 

# Question 3: Which format is lossy compressed

JPG is a the format which is usually compressed lossy. There are, however, JPEG-standards to do so lossless. 

# Question 4: What happens when a file is deleted from FAT

Once a file is deleted on a FAT file system the first character of the filename in the directory entry gets converted to another. Secondly the clusters on the harddrive that the file occupies get assigned to the list of free clusters, signaling that these can be overwritten if needed. 

# Question 5: What can you do to prevent recovery of files

1. Smash your harddrive into tiny parts.
2. Overwrite the harddrive with Gutmann patterns. Although simply overwriting the harddrive with two passes of random data will do just fine too.

4.  TODO
5.  TODO
6.  TODO
7.  TODO
8.  TODO
9.  TODO
10. TODO
11. TODO
12. TODO
13. TODO
14. TODO
15. TODO
16. TODO
17. TODO
18. TODO
