#ifdef __TEST__
#define __TEST__

/**
 * Test all main functions of the program.
 * @return 1 if all the tested functions are operational
 * else 0.
 */
int test();

/**
 * Test all the main functions in the Quadtree module.
 * @return 1 if all those functions are operational
 * else 0.
 */
int test_Quadtree();

/**
 * Test the function add_sons from the Quadtree module.
 * @return 1 if the function have the expected behavior
 * else 0.
 */
int test_add_sons();

/**
 * Test all the main functions in the Test module.
 * @return 1 if all those functions are operational
 * else 0.
 */
int test_BitFile();

/**
 * Test the functions read_BitFile and write_BitFile
 * in the BitFile module.
 * @return 1 if those functions have the expected behavior
 * else 0.
 */
int test_read_write_BitFile();

/**
 * Generate an array of representing a color.
 * [0]: r
 * [1]: g
 * [2]: b
 * [3]: a
 * @return this array if there is enough memory space
 * else NULL
 */
Byte* generate_rgba();

/**
 * Generate 'len_color' random Color.
 * @return an array of Color if there is enough memory space
 * else NULL.
 */
Color* generate_color(int len_color);

/**
 * Generate 'len_color' Node.
 * Each node will have a color from 'arr_color'.
 * @return an array of Node if there is enough memory space
 * else NULL.
 */
Node* generate_node(int len_colorn, Color* arr_color);

#endif
