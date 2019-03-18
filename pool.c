/**
 * @file pool.c
 * @brief Definitions of the functions declared at pool.h
 * @author nicktheway
 */

#include <stdio.h>
#include <stdlib.h>
#include "pool.h"

/**
 * @brief Creates and returns a new pool with the specified @a capacity.
 *
 * @param capacity The capacity to give to the new pool.
 * @return int_pool The created pool.
 */
int_pool createPool(size_t const capacity)
{
    int_pool newPool;

    newPool.size = 0;
    newPool.capacity = capacity;
    newPool.elements = malloc(capacity * sizeof *newPool.elements);

    if (!newPool.elements)
    {
        perror("Error: ");
        exit(EXIT_FAILURE);
    }

    return newPool;
}

/**
 * @brief Cleans up the @a pool to free up its memory.
 *
 * Pool's memory resources are freed here.
 *
 * @param pool The pool that will have its memory freed.
 */
void deletePool(int_pool* restrict pool)
{
    pool->capacity = 0;
    free(pool->elements);
}

/**
 * @brief Empties the @a pool. This function does NOT change the pool's capacity.
 *
 * Pool's memory resources are not freed here.
 *
 * @param pool The pool that will be emptied.
 */
void emptyPool(int_pool* restrict pool)
{
    pool->size = 0;
}

/**
 * @brief Adds a new element to the @a pool.
 *
 * @param pool The pool.
 * @param newNumber The new element.
 */
void addToPool(int_pool* restrict pool, int const newNumber)
{
    if (isFull(*pool))
    {
        fprintf(stderr, "Tried to add a new element into a full pool.\n");
        exit(EXIT_FAILURE);
    }

    pool->elements[pool->size++] = newNumber;
}

/**
 * @brief Returns true if the @a pool is currently empty.
 *
 * @param pool The pool.
 */
bool isEmpty(int_pool const pool)
{
    return pool.size == 0;
}

/**
 * @brief Returns true if the @a pool is currently full.
 *
 * @param pool The pool.
 */
bool isFull(int_pool const pool)
{
    return pool.size == pool.capacity;
}

/**
 * @brief Returns a random element from @a pool.
 *
 * @param pool The pool.
 */
int getRandomElement(int_pool const pool)
{
    if (!isEmpty(pool))
    {
        return pool.elements[rand() % pool.size];
    }
    else
    {
        fprintf(stderr, "Tried to fetch element from an empty pool.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Returns a random element from @a pool.
 *
 * Does NOT check if the pool is empty. If that's the case, the program will crash.
 * Therefore, make sure to call it only in places where that can never happen.
 *
 * @param pool The pool.
 */
int getRandomElementUnsafe(int_pool const pool)
{
    return pool.elements[rand() % pool.size];
}

