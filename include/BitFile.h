#ifndef __IOFILE__
#define __IOFILE__

typedef struct {
	FILE* file;
	int nb_bit;
	char buf;
}BitFile;

/**
 * Create an BitFile depending the file name
 * and the format of the file. (read-only...)
 * @return an BitFile if enough memory space else NULL.
 */
BitFile* create_BitFile(char* file_name, char* format);

/**
 * Initialize the BitFile depending the file name
 * and the format.
 * @return 1 if executed correctly else 0.
 */
void init_BitFile(BitFile* f, char* file_name, char* format);

/**
 * Close the file contained in the BitFile.
 * @return the return value of the fclose function.
 */
int close_BitFile(BitFile* f);

/**
 * Read the file in the BitFile and put
 * the character in a buffer.
 * @return the last bit read.
 */
int read_BitFile(BitFile* in);

/**
 * Write the buffer into the file contained in out.
 * @return 1 if executed correctly else 0.
 */ 
void write_BitFile(BitFile* out, int bit);

#endif
