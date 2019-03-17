/**
 * @file pool.h
 *
 * @brief Declares custom type named <int_pool> and some basic functions for interacting with this type.
 *
 * Description:
 *
 *  <int_pool> represents a vector that can store a variable number of integers up to
 *  a max capacity that is specified upon the <int_pool>'s creation.
 *  It occupies constant space in memory independently of its currently used number of elements.
 *
 *  It is strongly advised to interact with the <int_pool> type using the functions declared here
 *  unless you completely understand how it works.
 *
 * @author nicktheway
 */

/**
 * Making sure the symbols from this header will not be parsed more than once.
 */
#ifndef POOL_H
#define POOL_H

#include <stdbool.h>

/**
 * @brief A handler for a fixed memory space int array.
 *
 * The definition of type <int_pool>
 */
typedef struct int_pool
{
    int *elements;      /**< The pool's elements. */
    size_t size;        /**< The number of the pool elements that are currently used. */
    size_t capacity;    /**< The maximum capacity of the pool. */
} int_pool;

/**
 * @brief Creates and returns a new pool with the specified @a capacity.
 *
 * @param capacity The capacity to give to the new pool.
 * @return int_pool The created pool.
 */
int_pool createPool(size_t const capacity);

/**
 * @brief Cleans up the @a pool to free up its memory.
 *
 * Pool's memory resources are freed here.
 *
 * @param pool The pool that will have its memory freed.
 */
void deletePool(int_pool* restrict pool);

/**
 * @brief Empties the @a pool. This function does NOT change the pool's capacity.
 *
 * Pool's memory resources are not freed here.
 *
 * @param pool The pool that will be emptied.
 */
void emptyPool(int_pool* restrict pool);

/**
 * @brief Adds a new element to the @a pool.
 *
 * @param pool The pool.
 * @param newNumber The new element.
 */
void addToPool(int_pool* restrict pool, int const newNumber);

/**
 * @brief Returns true if the @a pool is currently empty.
 *
 * @param pool The pool.
 */
bool isEmpty(int_pool const pool);

/**
 * @brief Returns true if the @a pool is currently full.
 *
 * @param pool The pool.
 */
bool isFull(int_pool const pool);

/**
 * @brief Returns a random element from @a pool.
 *
 * @param pool The pool.
 */
int getRandomElement(int_pool const pool);

/**
 * @brief Returns a random element from @a pool.
 *
 * Does NOT check if the pool is empty. If that's the case, the program will crash.
 * Therefore, make sure to call it only in places where that can never happen.
 *
 * @param pool The pool.
 */
int getRandomElementUnsafe(int_pool const pool);

#endif