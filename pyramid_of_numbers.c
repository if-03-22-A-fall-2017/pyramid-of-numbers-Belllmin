	/*----------------------------------------------------------
*			HTBLA-Leonding / Class: 2AHIF
* ---------------------------------------------------------
* Exercise Number: 2
 * Title:		Pyramid of Numbers
 * Author:	Coralic Belmin
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80
// My defines
#define INVALID_CHARACTER -2
#define MAX_CHARACTERS - 1
#define FACTOR 2

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt
{
    int digits_count; /** number of digits of the big int. */
    unsigned int the_int[MAX_DIGITS];/** array of digits of big int. */
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);
/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int);
/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);
/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);
/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);
/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[])
{
    struct BigInt big_int;
    struct BigInt big_result;
    char string_input[MAX_DIGITS];

    printf("\nPyramid of Numbers\n");
    printf("Please enter a number: ");
    scanf("%s", string_input);

    printf("\n");
    int length = strlen(string_input);
    if(length > MAX_DIGITS)
    {
        printf("Error, input is bigger than Max Digits!\n");
        return MAX_CHARACTERS;
    }
    int converted_chars = strtobig_int(string_input, length, &big_int);
    if(converted_chars == INVALID_CHARACTER)
    {
        printf("Error, invalid character!\n");
        return INVALID_CHARACTER;
    }

    for(int i = FACTOR; i <= 9; i++) // Multiply
    {
      print_big_int(&big_int);
      printf(" * %i = ", i);
      multiply(&big_int, i, &big_result);
      copy_big_int(&big_result, &big_int);
      print_big_int(&big_int);
      printf("\n");
    }
    printf("\n");
    for(int i = FACTOR; i <= 9; i++) // Divide
    {
      print_big_int(&big_int);
      printf(" / %i = ", i);
      divide(&big_int, i, &big_result);
      copy_big_int(&big_result, &big_int);
      print_big_int(&big_int);
      printf("\n");
    }
    printf("\n");
    return 0;
}
int strtobig_int(const char *str, int len, struct BigInt *big_int)
{
    big_int->digits_count = 0;

    for(int i = len - 1; i >= 0; i--)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            big_int->the_int[i] = str[i] - '0';
            big_int->digits_count++;
        }
        else return INVALID_CHARACTER;
    }
    return big_int->digits_count;
}
void print_big_int(const struct BigInt *big_int)
{
  for(int i = 0; i < big_int->digits_count; i++)
  {
    if(big_int->the_int[i] > 9) return; 
    printf("%i", big_int->the_int[i]);
  }
}
void copy_big_int(const struct BigInt *from, struct BigInt *to)
{
    for(int i = 0; i <= from->digits_count; i++)
    {
      to->the_int[i] = from->the_int[i];
    }
    to->digits_count = from->digits_count + 1;
}
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result)
{
    int carry = 0;
    bool go = false;
    bool copy = false;
    big_result->digits_count = big_int->digits_count;

    for(int i = big_result->digits_count; i >= 1 ; i--)
    {
        go = false;
        big_result->the_int[i] = ((big_int->the_int[i - 1] * factor) % 10) + carry;
        if((((big_int->the_int[i - 1] * factor) % 10) + carry) > 0)
        {
            big_result->the_int[i] = ((big_int->the_int[i - 1] * factor) + carry) % 10;
            carry = (((big_int->the_int[i - 1] * factor) + carry) - (((big_int->the_int[i - 1] * factor) + carry) % 10)) / 10;
            go = true;
        }
        if(!go) carry = ((big_int->the_int[i - 1] * factor) - ((big_int->the_int[i - 1] * factor) % 10)) / 10;
        if(i == 1 && carry != 0) big_result->the_int[0] = carry;
        if(i == 1 && carry == 0) copy = true;
    }
    if(copy)
    {
      struct BigInt temp;
      temp.digits_count = big_result->digits_count;

      for(int i = 0; i < temp.digits_count; i++) temp.the_int[i] = big_result->the_int[i + 1];
      for(int i = 0; i < temp.digits_count; i++) big_result->the_int[i] = temp.the_int[i];
      big_result->digits_count = big_result->digits_count - 1;
    }
}
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result)
{
  int rest = 0;

  for(int i = big_int->digits_count; i >= 0; i--)
  {
    int current_digit = big_result->the_int[i];
    int number = (current_digit + rest * 10) / divisor;

    if(number == 0) rest = current_digit % 10;
    else rest = (current_digit + rest * 10) - (number * divisor);

    big_result->the_int[i] = number % 10;
  }

  if(rest > 0)
  {
    big_result->digits_count = big_int->digits_count;

    for(int i = big_int->digits_count; i >= 0; i--)
    {
      int cross = big_result->the_int[i];
      big_result->the_int[i + 1] = cross;
    }
    big_result->the_int[big_int->digits_count + 1] = rest;
  }
}
