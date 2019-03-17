/**
 * @file cell.c
 *
 * @brief Definitions of the functions declared at cell.h
 *
 * @author nicktheway
 */

 #include "cell.h"
 #include <stdlib.h>
 #include <assert.h>

/**
 * @brief Assigns a cell to manage the @a data.
 *
 * @param cell The cell.
 * @param data The data assigned to the cell. Shouldn't be freed while in use by the cell!
 * @param dataLength The length of the data.
 * @param generation The generation of the cell.
 * @param mutationProb The probability that a cell's data segment will mutate.
 */
void assignCell(cell_t* restrict cell, char* data, int const dataLength, int const generation, float const mutationProb)
{
    cell->data = data;
    cell->dataLength = dataLength;
    cell->generation = generation;
    cell->mutationProb = mutationProb;
}

/**
 * @brief Randomizes the data of the @a cell usin random generated printable ASCII chars.
 *
 * @param cell The cell whose data will be randomized.
 */
void randomizeData(cell_t* restrict cell)
{
    for (int i = 0; i < cell->dataLength; i++)
    {
        cell->data[i] = rand() % 95 + 32;
    }
}

/**
 * @brief Gives the chance to the @a cell's data to mutate.
 */
void mutate(cell_t* restrict cell)
{
    // mutationProb should always be in [0, 1]. Assert that this is true.
    assert(cell->mutationProb >= 0 && cell->mutationProb <= 1);

    for (int i = 0; i < cell->dataLength; i++)
    {
        // Just a random multiplication that will give better than +-0.1% accuracy.
        if (rand() % 1024 < cell->mutationProb * 1024)
        {
            cell->data[i] = rand() % 95 + 32;
        }
    }
}

/**
 * @brief Crossovers @a parentA's and @a parentB's data and stores them to the @a child.
 *
 * @a child's generation will also be updated.
 *
 * @param parentA One parent.
 * @param parentB The other parent.
 * @param child Reference to their child.
 */
void crossover(cell_t const parentA, cell_t const parentB, cell_t* restrict child)
{
    // Make sure that every cell contains the same amount of data.
    assert(parentA.dataLength == parentB.dataLength);
    assert(parentA.dataLength == child->dataLength);

    // The child gets characteristics from its two parents with the same probability.
    for (int i = 0; i < child->dataLength; i++)
    {
        child->data[i] = (rand() % 2) ? parentA.data[i] : parentB.data[i];
    }

    child->generation = parentA.generation + 1;
}
