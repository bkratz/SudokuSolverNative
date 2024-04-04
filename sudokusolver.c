#include "sudokusolver.h"

/**
 * @file
 * @brief Sudoku Solver using recursive implementation of brute-force algorithm
 *
 * @details
 * Given an incomplete N*N Sudoku and asked to solve it using the
 * following recursive algorithm:
 * 1. Scan the Sudoku from left to right row-wise to search for an empty cell.
 * 2. If there are no empty cells, print the Sudoku. Go to step 5.
 * 3. In the empty cell, try putting numbers 1 to N
 * while ensuring that no two numbers in a single row, column, or box are same.
 * Go back to step 1.
 * 4. Declare that the Sudoku is Invalid.
 * 5. Exit.
 *
 * @authors [Anuj Shah](https://github.com/anujms1999)
 * @authors [Krishna Vedala](https://github.com/kvedala)
 */
#include <stdbool.h>
#include <string.h>

/** @addtogroup sudoku Sudoku solver
 * @{
 */

/**
 * Check if `x`^th row is valid
 * @param a ::sudoku to check
 * @param x row to check
 * @param y ignored column
 * @param v value to check if it repeats
 * @returns `true` if valid
 * @returns `false` if in-valid
 */
bool OKrow(const Sudoku *a, int x, int y, int v)
{
    int offset = x * a->N;
    for (int j = 0; j < a->N; j++)
        if (a->a[offset + j] == v)
            // if the value is found in the row
            return false;
    return true;
}

/**
 * Check if `y`^th column is valid
 * @param a ::sudoku to check
 * @param x ignored row
 * @param y column to check
 * @param v value to check if it repeats
 * @returns `true` if valid
 * @returns `false` if in-valid
 */
bool OKcol(const Sudoku *a, int x, int y, int v)
{
    for (int i = 0; i < a->N; i++)
        if (a->a[i * a->N + y] == v)
            // if the value is found in the column
            return false;
    return true;
}

/**
 * Check if a 3x3 box is valid
 * @param a matrix to check
 * @param x row index of the element to check
 * @param y column index of the element to check
 * @param v value to check if it repeats
 * @returns `true` if valid
 * @returns `false` if in-valid
 */
bool OKbox(const Sudoku *a, int x, int y, int v)
{
    /* get start indices of the box that the current (x,y) lies in
       remember that in C/C++, division operation always rounds towards
       -infinity for signed integers and towards 0 for unsigned integers
    */
    int bi = x - x % a->N2, bj = y - y % a->N2;

    for (int i = bi; i < (bi + a->N2); i++)
        for (int j = bj; j < (bj + a->N2); j++)
            if (a->a[i * a->N + j] == v)
                // if the value is found in the box
                return false;
    return true;
}

/**
 * Check if element `v` is valid to place at (x,y) location.
 * @param a ::sudoku to check
 * @param x row to place value
 * @param y column to place value
 * @param v value to check if it is valid
 * @returns `true` if valid
 * @returns `false` if in-valid
 */
bool OK(const Sudoku *a, int x, int y, int v)
{
    bool result = OKrow(a, x, y, v);
    if (result)
        result = OKcol(a, x, y, v);
    if (result)
        result = OKbox(a, x, y, v);

    return result;
}

/**
 * @brief Find and get the location for next empty cell.
 *
 * @param [in] a pointer to sudoku instance
 * @param [out] x pointer to row index of next unknown
 * @param [out] y pointer to column index of next unknown
 * @returns `true` if an empty location was found
 * @returns `false` if no more empty locations found
 */
bool get_next_unknown(const Sudoku *a, int *x, int *y)
{
    for (int i = 0; i < a->N; i++)
    {
        for (int j = 0; j < a->N; j++)
        {
            if (a->a[i * a->N + j] == 0)
            {
                *x = i;
                *y = j;
                return true;
            }
        }
    }

    /* no unknown locations found */
    return false;
}

/**
 * @brief Function to solve a partially filled sudoku matrix. For each unknown
 * value (0), the function fills a possible value and calls the function again
 * to check forvalid solution.
 *
 * @param [in,out] a sudoku matrix to solve
 * @return `true` if solution found
 * @return `false` if no solution found
 */
bool solve(Sudoku *a)
{
    static uint32_t counter = 0;
    int i, j;
    static char prefix[500] = "";  // enough memory

    if (!get_next_unknown(a, &i, &j))
    {
        /* no more empty location found
           implies all good in the matrix
         */
        return true;
    }

    /* try all possible values for the unknown */
    for (uint8_t v = 1; v <= a->N; v++)
    { /* try all possible values 1 thru N */
        counter++;
        if (OK(a, i, j, v))
        {
            /* if assignment checks satisfy, set the value and
             continue with remaining elements */
            a->a[i * a->N + j] = v;
            strcat(prefix, "  ");
            if (solve(a))
            {
                /* solution found */
                return true;
            }

            prefix[strlen(prefix) - 2] = '\0';  // truncate the prefix
            a->a[i * a->N + j] = 0;
        }
    }

    return false;
}
