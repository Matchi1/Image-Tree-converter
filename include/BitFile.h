#ifndef __IOFILE__
#define __IOFILE__

typedef struct {
	FILE* file;
	int nb_bit;
	unsigned char buf;
}BitFile;

/**
 * @brief Create an BitFile depending the file name
 * and the format of the file. (read-only...)
 * @ret an BitFile if enough memory space else NULL.
 */
BitFile* create_BitFile(char* file_name, char* format);

/**
 * @brief Initialize the BitFile depending the file name
 * and the format.
 * @ret 1 if executed correctly else 0.
 */
void init_BitFile(BitFile* f, char* file_name, char* format);

/**
 * @brief Close the file contained in the BitFile.
 * @ret the return value of the fclose function.
 */
int close_BitFile(BitFile* f);

/**
 * @brief Read the file in the BitFile and put
 * the character in a buffer.
 * @ret the last bit read.
 */
int read_BitFile(BitFile* in);

/**
 * @brief Write the buffer into the file contained in out.
 * @ret 1 if executed correctly else 0.
 */ 
int write_BitFile(BitFile* out, int bit);

#endif
