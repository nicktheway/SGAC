/**
 * @file cell.h
 *
 * @brief Declares custom type named <cell_t> and some basic functions for interacting with this type.
 *
 * Description:
 *  <cell_t> can be used to store information in a simple cell-like structure. Each cell has a
 *  probability to mutate any of each data -given the chance- and a generation number that is used
 *  when working with multiple cells. Cells can also crossover and produce new cells as their combination.
 *
 *  More complex crossover behaviours can be based on this/or an extended definition of cell and be utilized in the future.
 *
 *  It is strongly advised to interact with the <cell_t> type using the functions declared here
 *  unless you completely understand how it works.
 *
 * @author nicktheway
 */

 /**
 * Making sure the symbols from this header will not be parsed more than once.
 */
#ifndef CELL_H
#define CELL_H


/**
 * @brief Declaration of the cell_t type.
 */
typedef struct cell_t
{
    char* data;         /**< The data of the cell. */
    int dataLength;     /**< The length of the cell's data. */
    int generation;     /**< The cell's generation. */
    float mutationProb; /**< Range [0-1]. The cell's probability to mutate any of its data part given the chance.
                             No point in providing more than 2 decimal digits. */
} cell_t;


/**
 * @brief Assigns a cell to manage the @a data.
 *
 * @param cell The cell.
 * @param data The data assigned to the cell. Shouldn't be freed while in use by the cell!
 * @param dataLength The length of the data.
 * @param generation The generation of the cell.
 * @param mutationProb The probability that a cell's data segment will mutate.
 */
void assignCell(cell_t* restrict cell, char* data, int const dataLength, int const generation, float const mutationProb);

/**
 * @brief Randomizes the data of the @a cell usin random generated printable ASCII chars.
 *
 * @param cell The cell whose data will be randomized.
 */
void randomizeData(cell_t* restrict cell);

/**
 * @brief Gives the chance to the @a cell's data to mutate.
 */
void mutate(cell_t* restrict cell);

/**
 * @brief Crossovers @a parentA's and @a parentB's data and stores them to the @a child.
 *
 * @a child's generation will also be updated.
 *
 * @param parentA One parent.
 * @param parentB The other parent.
 * @param child Reference to their child.
 */
void crossover(cell_t const parentA, cell_t const parentB, cell_t* restrict child);

#endif