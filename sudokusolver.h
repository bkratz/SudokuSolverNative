#ifndef SUDOKUSOLVER_SUDOKUSOLVER_H
#define SUDOKUSOLVER_SUDOKUSOLVER_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sudoku
{
    uint8_t *a; /**< matrix as a flattened 1D row-major array */
    uint8_t N;  /**< number of elements */
    uint8_t N2; /**< block of elements */
} Sudoku;

bool solve(Sudoku *a);

#ifdef __cplusplus
}
#endif

#endif //SUDOKUSOLVER_SUDOKUSOLVER_H
