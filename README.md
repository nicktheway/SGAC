# SGAC

A simple genetic algorithm in C that tries to produce a target string starting from random printable ASCII characters.

Original idea coded in Python by Doug Lloyd, can be found [here](https://github.com/dlloyd09/genetic),
as it was produced live at a CS50's twitch stream which is available [here](https://www.youtube.com/watch?v=EmTAMDnDo9o).

## Files' Description
- **genetic.c** Contains the main algorithm's source.
- **cell.h** Contains the ```cell_t``` type definition and function declarations related to that type.
- **cell.c** Contatins the definitions of the functions declared in **cell.h**.
- **pool.h** Contains the ```int_pool``` type definition and function declarations related to that type.
- **pool.c** Contatins the definitions of the functions declared in **pool.h**.

## Compilation
Clone the repository and then compile the code:

1. Using the makefile. Just Run:
  ```
  make
  ```
  
2. Using gcc. If the make option doesn't work for you and you have gcc installed, you can run:
  ```
  gcc -std=c11 -O3 -Wall genetic.c pool.c cell.c -o genetic
  ```

3. Using clang. If you have clang installed, you can run:
  ```
  clang -std=c11 -O3 -Wall genetic.c pool.c cell.c -o genetic
  ```
 
## Execution
Run:
```
./genetic
```

## Clean up (if the compilation was made using make)
To remove every file that was produced by the compiler (the executable too), run:
```
make purge
```

Alternatively, to just remove the ```.o``` files run:
```
make clean
```
