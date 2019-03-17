/**
 * @file genetic.c
 *
 * @brief A simple genetic algorithm that uses reinforcement learning techniques to produce a target string.
 *
 * Original idea coded in Python by Doug Lloyd, can be found here: https://github.com/dlloyd09/genetic
 * as it was produced live at a CS50's twitch stream which you can view here: https://www.youtube.com/watch?v=EmTAMDnDo9o
 *
 * To compile, if the makefile doesn't work for you, you can use:
 *  gcc -std=c11 -O3 -Wall genetic.c pool.c cell.c -o genetic
 * Or (with clang)
 *  clang -std=c11 -O3 -Wall genetic.c pool.c cell.c -o genetic
 *
 * Then, run with:
 *  ./genetic
 *
 * @author nicktheway
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "pool.h"
#include "cell.h"

/**
 * @brief Evaluates the @a cell based on its resemblance to the @a target.
 *
 * @param cell The cell.
 * @param target The target string.
 * @return int The evaluation of the cell.
 */
int evaluation(cell_t const cell, char const* restrict target);

/**
 * @brief Method that summarizes a cell's data and value/score.
 *
 * @param cell The cell.
 * @param target The target string of the cell.
 * @param score The score of the cell.
 */
void summarize(cell_t const cell, char const* restrict target, int const score);

/**
 * @brief Method for printing a phrase in a way to visually see the resemblance with the @a target.
 *
 * Prints the @a phrase's letters with red and green colours depending to their match with
 * the @a target's letters.
 *
 * @param cell The cell whose data will be colourfully printed.
 * @param target The target string of the @a cell.
 * @param appendNewLine Should a new Line be printed at the end?
 */
void prettyPrint(cell_t const cell, char const* restrict target, bool const appendNewLine);



int main(void)
{
    // The target string and its length.
    const char target[] = "This is CS50 on twitch!";
    const size_t target_len = sizeof(target) - 1; // Last char is '\0', we don't need it.

    // The size of each cell population.
    const int POP_SIZE = 500;

    // The maximum number of generations that the program will try to produce while a perfect cell does not emerge.
    const int GENERATIONS_LIMIT = 1000;

    // Pass the current time as seed to the RNG.
    srand(time(0));

    // Create two cell_t arrays.
    cell_t* population = malloc(POP_SIZE * sizeof *population);
    cell_t* children = malloc(POP_SIZE * sizeof *children);

    // Allocate memory for storing the population's cells' fitness values.
    int* fitness = calloc(POP_SIZE, sizeof *fitness);

    // Allocate memory for the cells' data on the heap.
    char* cellDataSpace = malloc(POP_SIZE * target_len * sizeof *cellDataSpace);
    char* cellDataSpace2 = malloc(POP_SIZE * target_len * sizeof *cellDataSpace2);

    // Make sure the memory was allocated without problems.
    if (!population || !children || !fitness || !cellDataSpace || !cellDataSpace2)
    {
        perror("Error: ");
        exit(EXIT_FAILURE);
    }

    // Assign the allocated memory to the created cells.
    for (int i = 0; i < POP_SIZE; i++)
    {
        // Population has the 1st generation of cells at start. They all have random strings as data.
        assignCell(&population[i], &cellDataSpace[i * target_len], target_len, 1, 0.01f);
        randomizeData(&population[i]);

        // Children do not need randomization as their data will be replaced anyway when their parents crossover.
        // They are going to be the 2nd generation of cells. (Will be overwritten but no harm passing 2 here too.)
        assignCell(&children[i], &cellDataSpace2[i * target_len], target_len, 2, 0.01f);
    }

    // Create an <int_pool> for storing the parents' indices. The better the parent cell the more times its index
    // will be stored in the pool.
    int_pool matingPool = createPool(POP_SIZE * target_len);

    // Initialization.
    int best_score = 0;
    int generation = 1;

    // While the generation hasn't gone off limits:
    while (generation < GENERATIONS_LIMIT)
    {
        // Evaluate each cell of the population and add its id into the matingPool as many
        // times as its evaluation.
        for (int i = 0; i < POP_SIZE; i++)
        {
            const int eval = evaluation(population[i], target);
            fitness[i] = eval;

            if (eval > best_score)
            {
                best_score = eval;
                summarize(population[i], target, best_score);

                // ------------- Possible EXIT Point -----------------
                // Exit if the target has been reached.
                if (best_score == target_len)
                {
                    exit(EXIT_SUCCESS);
                }
            }

            for (int j = 0; j < eval; j++)
            {
                addToPool(&matingPool, i);
            }
        }

        // Check if there is any cell's id in the matingPool.
        if (matingPool.size > 0)
        {
            // Produce the new generation by combining parents whose ids come from the mating pool.
            // Cells with better evaluation will have a greater chance to be selected from the pool as their indices
            // were added more times in the pool.
            for (int i = 0; i < POP_SIZE; i++)
            {
                int xID = getRandomElement(matingPool);
                int yID = getRandomElement(matingPool);

                crossover(population[xID], population[yID], &children[i]);

                // Give the chance to child's data to mutate.
                mutate(&children[i]);
            }

            // Now the old generation can be swapped with the new one.
            cell_t* temp = population;
            population = children;
            children = temp;
        }
        else
        {
            // No cell was in the mating pool. Give them a chance to mutate.
            for (int i = 0; i < POP_SIZE; i++)
            {
                mutate(&population[i]);
            }
        }

        // Empty the matingPool to be ready for the next generation of parents.
        emptyPool(&matingPool);

        generation++;
    }

    // Free resources (not really needed as the program will exit anyway)
    // Included just to show how they can be freed.
    free(fitness);
    free(population);
    free(children);
    free(cellDataSpace);
    free(cellDataSpace2);
    deletePool(&matingPool);

    // The algorithm has failed to reach the target withing the limit.
    return EXIT_FAILURE;
}


/**
 * @brief Evaluates the @a cell based on its resemblance to the @a target.
 *
 * @param cell The cell.
 * @param target The target string.
 * @return int The evaluation of the cell.
 */
int evaluation(cell_t const cell, char const* restrict target)
{
    int points = 0;
    for (int i = 0; i < cell.dataLength; i++)
    {
        if (cell.data[i] == target[i])
        {
            points++;
        }
    }

    return points;
}

/**
 * @brief Method that summarizes a cell's data and value/score.
 *
 * @param cell The cell.
 * @param target The target string of the cell.
 * @param score The score of the cell.
 */
void summarize(cell_t const cell, char const* restrict target, int const score)
{
    printf("Gen %3d:\t", cell.generation);
    prettyPrint(cell, target, false);
    printf("\tBest Score: %2d\n", score);
}

/**
 * @brief Method for printing a phrase in a way to visually see the resemblance with the @a target.
 *
 * Prints the @a phrase's letters with red and green colours depending to their match with
 * the @a target's letters.
 *
 * @param cell The cell whose data will be colourfully printed.
 * @param target The target string of the @a cell.
 * @param appendNewLine Should a new Line be printed at the end?
 */
void prettyPrint(cell_t const cell, char const* restrict target, bool const appendNewLine)
{
    for (int i = 0; i < cell.dataLength; i++)
    {
        bool same = cell.data[i] == target[i];
        if (same)
        {
            printf("\033[0;32m"); // Sets color to green.
        }
        else
        {
            printf("\033[0;31m"); // Sets color to bold red.
        }

        if (cell.data[i] != ' ')
        {
            printf("%c", cell.data[i]);
        }
        else if (same)
        {
            printf("\e[42m ");
        }
        else
        {
            printf("\e[41m ");
        }
    }

    printf("\033[0m\e[49m"); // Reset colours

    if (appendNewLine)
    {
        printf("\n");
    }
}

