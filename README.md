# SGAC

A simple genetic algorithm in C that tries to produce a target string starting from random printable ASCII characters.

Original idea coded in Python by Doug Lloyd, can be found [here](https://github.com/dlloyd09/genetic),
as it was produced live at a CS50's twitch stream which is available [here](https://www.youtube.com/watch?v=EmTAMDnDo9o).

![image](https://user-images.githubusercontent.com/16711717/159817355-9e7db23f-f2d8-4279-a7e3-27e50e7eaa1b.png)

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

Example run (with time):

```
➜  time ./genetic
Gen   1:	aJkc /v[LL,e'L)vQaVmw"f	Best Score:  1
Gen   1:	"o\-LM) p55&0;[Ea];4N<c	Best Score:  2
Gen   2:	a$ks /43LL,B'L) ea:YS"f	Best Score:  3
Gen   2:	"o\#sC) 0V50 ;CEy^~gN<c	Best Score:  4
Gen   3:	a$ks 6s3SL,B'NW tk:Yc"f	Best Score:  6
Gen   4:	"h,qCL# (S`0do| lMv,:ho	Best Score:  7
Gen   6:	TC's%ss3w#)&qct yw_t@h!	Best Score:  8
Gen   6:	Th{] q4 |_50)oDfT-htc"k	Best Score:  9
Gen   9:	yhis 6s FIz& onwtmKOkD.	Best Score: 10
Gen   9:	Thw8cq" pUx0 on t';tchA	Best Score: 12
Gen  11:	T04s>^2 ~J5e on twitNhc	Best Score: 13
Gen  13:	ThHs ~s }r5y B| tOit@h!	Best Score: 14
Gen  16:	Th~s &V CtzW'on twi.ch!	Best Score: 15
Gen  17:	Thks &s Ctz0'on*twitc2!	Best Score: 16
Gen  18:	phiuz^s Ct50 on twitSh!	Best Score: 17
Gen  23:	T>is )s 9S50 on t"itc"!	Best Score: 18
Gen  26:	This 6" Cj50 on tw]tch!	Best Score: 19
Gen  32:	This Es CS50 onntvitch!	Best Score: 20
Gen  36:	This Zs mS50 on twitch!	Best Score: 21
Gen  48:	This ys CS50 on twitch!	Best Score: 22
Gen  57:	This is CS50 on twitch!	Best Score: 23
./genetic  0.02s user 0.00s system 97% cpu 0.017 total
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
