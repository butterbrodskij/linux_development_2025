/* Program limitations */
#define MIN_VALUE 1    /**< Minimum number that can be guessed */
#define MAX_VALUE 3999 /**< Maximum number that can be guessed */
#define MAX_NUM_LEN 17 /**< Maximum lenght of string represantation of numbers */

int from_roman(const char *);

char *to_roman(int, char *);

char *itoa_default(int, char *);

/** Convert integer to decimal string representation.
 *
 * @param num Number to convert.
 * @param str Buffer to store result (must be at least MAX_NUM_LEN bytes).
 * @return @p Pointer to str with decimal representation of the number.
 */
typedef char *(itoa_func)(int, char *);
