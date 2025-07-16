# DOSDOPE 
DOPE (Dartmouth Oversimplified Programming Experiment) for DOS

## DOPE Language Manual
Dartmouth Oversimplified Programming Experiment (1963)
*For the LGP-30 Computer (4KB RAM, Drum Memory)*

### 1. Introduction
DOPE was created by John Kemeny and Thomas Kurtz as a teaching tool to introduce programming to beginners. It preceded BASIC (1964) and emphasized:

Ultra-minimalist syntax (single-letter commands).

Polish notation (operations precede operands).

Memory-centric programming (no variables, only addresses).

### 2. Command Reference

Core Instructions
Command	Operation	Example	Explanation
Z	Zero memory	Z100	Sets address [100] to 0.
I	Input	I100	Reads a number into [100].
O	Output	O100	Prints [100] to teletype.
A	Add	A100 200 300	[300] = [100] + [200].
S	Subtract	S100 200 300	[300] = [100] - [200].
U	Multiply	U100 200 300	[300] = [100] * [200].
D	Divide	D100 200 300	[300] = [100] / [200].
E	Equal-loop	E100 20	If [100] = 0, jump to step 20.
G	Greater-loop	G100 30	If [100] > 0, jump to step 30.
J	Jump (GOTO)	J50	Unconditional jump to step 50.

### 3. Programming Examples

A. Sum Two Numbers
```
I100    ! Read into [100]  
I200    ! Read into [200]  
A100 200 300  ! [300] = [100] + [200]  
O300    ! Print result
```  
Input: 5 3 → Output: 8

B. Countdown Loop
```
Z100    ! [100] = 0  
A100 10 ! [100] = 10 (counter)  
O100    ! Print counter  
S100 1  ! Decrement counter  
G100 3  ! Loop if [100] > 0  
```
Output: 10 9 8 ... 1

### 4. Hardware Constraints
Memory: 4KB RAM (addresses [0]–[4095]).

No Variables: Only absolute addressing (e.g., [100]).

No Subroutines: All control flow via GOTO/loops.

Teletype I/O: Input/output via punch tape or keyboard.

### 5. Design Philosophy
Teach Fundamentals: Loops, branches, and memory management without abstraction.

Polish Notation: Simplified parsing for the LGP-30’s limited compiler.

Interactive: Immediate feedback (unlike batch-processing FORTRAN).

### 6. Legacy
Direct Precursor to BASIC: DOPE proved simplicity was viable, inspiring BASIC’s LET, PRINT, and GOTO.

Historical Context: Demonstrates 1960s trade-offs between usability and hardware limits.


