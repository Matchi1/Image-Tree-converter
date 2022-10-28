#ifdef __TEST__
#define __TEST__

/**
 * @brief Generate an array of representing a color.
 * [0]: r
 * [1]: g
 * [2]: b
 * [3]: a
 * @ret this array if there is enough memory space else NULL
 */
Byte* generate_rgba();

/**
 * @brief Generate 'len_color' random MLV_Color.
 * @ret an array of MLV_Color if there is enough memory space else NULL.
 */
MLV_Color* generate_color(int len_color);

/**
 * @brief Generate 'len_color' Node.
 * Each node will have a color from 'arr_color'.
 * @ret an array of Node if there is enough memory space else NULL.
 */
Node* generate_node(int len_colorn, MLV_Color* arr_color);

/**
 * @brief Test all the main functions in the Quadtree module.
 * @ret 1 if all those functions are operational else 0.
 */
int test_Quadtree();

/**
 * @brief Test the function add_sons from the Quadtree module.
 * @ret 1 if the function have the expected behavior else 0.
 */
int test_add_sons();

/**
 * @brief Test all the main functions in the Test module.
 * @ret 1 if all those functions are operational else 0.
 */
int test_BitFile();

/**
 * @brief Test the functions read_BitFile and write_BitFile
 * in the BitFile module.
 * @ret 1 if those functions have the expected behavior else 0.
 */
int test_read_write_BitFile();

/**
 * @brief Test all main functions of the program.
 * @ret 1 if all the tested functions are operational else 0.
 */
int test();

#endif
