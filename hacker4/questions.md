# Question 0: How much colors do the image formats support

1. BMP supports colors in the range of 2^[1,2,4,8,16,24,32,(48),(64)]. The upper limit seems to shift depending on which documentation you read, although 32 is definitely supported. 24 seems to be the most common.
2. GIF supports 2^[1-8,(24)] colors. Using 24 bits for the color is however only possible by enclosing multiple “images” with their own color tables containing 255 colors chosen from the 24bit palette and rendering them next to each other. Note however that this method is quite inefficient and not widely supported.
3. JPEG supports a 24bit sRGB color space. However it should be noted that the encoding of a JPEG downsamples the colors more heavily than the brightness. While the ultimate range of colors remains the same, there is a cost in color detail.
4. PNG supports colors in the range of 2^[1,2,3,4,8,24,32,48]. The total bit depth can be 2^64 due to the alpha channel (transparency). 

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

# Question 6: stdint.h

“The <stdint.h> header shall declare sets of integer types having specified widths, and shall define corresponding sets of macros. It shall also define macros that specify limits of integer types corresponding to types defined in other standard headers.”
(http://pubs.opengroup.org/onlinepubs/009695399/basedefs/stdint.h.html)

The standard header for integers defines integer types with a specified width.

# Question 7: Rationale of stdint.h

“RATIONALE: The ISO/IEC 9899:1990 standard specified that the language should support four signed and unsigned integer data types- char, short, int, and long- but placed very little requirement on their size other than that int and short be at least 16 bits and long be at least as long as int and not smaller than 32 bits. For 16-bit systems, most implementations assigned 8, 16, 16, and 32 bits to char, short, int, and long, respectively. For 32-bit systems, the common practice has been to assign 8, 16, 32, and 32 bits to these types. This difference in int size can create some problems for users who migrate from one system to another which assigns different sizes to integer types, because the ISO C standard integer promotion rule can produce silent changes unexpectedly. The need for defining an extended integer type increased with the introduction of 64-bit systems.”
(http://pubs.opengroup.org/onlinepubs/009695399/basedefs/inttypes.h.html)

Apparently the default typing can cause problems on different systems. However I suspect it also gives clarity to know how big items are in memory of files. It might also save space and be a bit faster. stdint.h is a subset of inttypes.h, with the rationele that the whole set might not be supported everywhere. 

# Question 8: Bytes in integer types

typedef uint8_t  BYTE;  -> 1 byte
typedef uint32_t DWORD; -> 4 bytes
typedef int32_t  LONG;  -> 4 bytes
typedef uint16_t WORD;  -> 2 bytes

# Question 9: BMP fire signature or “magic number”

“The header field used to identify the BMP and DIB file is 0x42 0x4D in hexadecimal, same as BM in ASCII. The following entries are possible:
BM – Windows 3.1x, 95, NT, … etc.
BA – OS/2 struct bitmap array
CI – OS/2 struct color icon
CP – OS/2 const color pointer
IC – OS/2 struct icon
PT – OS/2 pointer”
(https://en.wikipedia.org/wiki/BMP_file_format)

BM seems to be the most obvious signature of a Bitmap file. However there are others used by OS/2.

# Question 10: Difference between bfSize and biSize

The first, bitmap-file-size, hold the size of the entire file. The second, bitmap-info-size, holds the size of the info header.

# Question 11: Meaning of biHeight of negative

If the biHeight is negative it means that the image top-left to bottom-right. The default way of storing the image data is upside down.

# Question 12: Which field specifies BMP color depth

The field biBitCount specifies the BMP color depth.

# Question 13: Why might open return “NULL”

Multiple reasons, the file might not exist or something else might have gone wrong.

# Question 14: Why is fread always 1

The stream is read with one byte at a time. It makes sense because the minimum unit of a bitmap might be 1 bit. Although it could be different for the headers because the size is known, this remains the safest and easiest way.

# Question 15: Padding if bit width is 3

Line 70:
int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

The scan line must finish on a multiple of four. An RGB-triple is defined with three bytes. The bit width is subtracted from this, in this case three bits. This gives:

(3 * 3) % 4 = 1
(4 - 1) % 4 = 3

# Question 16: the purpose of fseek

It changes the position indicator of the file reading process. This allows you to read a different part of a file. There could be various reasons to do this, but I suppose something like this really makes sense for video’s where you often skip back and ahead.

# Question 17: SEEK_CUR

It inputs the current position of the file pointer as offset for the next pointer position.