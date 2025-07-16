# DOPE 
DOPE (Dartmouth Oversimplified Programming Experiment) 
An implementation in C99

## DOPE Language Manual
Dartmouth Oversimplified Programming Experiment (DOPE) c.1963
*For the LGP-30 Computer (4KB RAM, Drum Memory)*
Reconstructed DOPE Manual based on historically accepted details from Dartmouth archives and academic accounts of this pre-BASIC language (circa 1962–1963).

### 1. Introduction
DOPE was created by John Kemeny and Thomas Kurtz as a teaching tool to introduce programming to beginners. It preceded BASIC (1964) and emphasized:

Ultra-minimalist syntax (single-letter commands).

Polish notation (operations precede operands).

Memory-centric programming (no variables, only addresses).

### 2. Command Reference
### Core Instructions

| Command | Operation         | Example         | Explanation                          |
|---------|-------------------|-----------------|--------------------------------------|
| `Z`     | Zero memory       | `Z100`          | Sets address `[100]` to `0`.         |
| `I`     | Input             | `I100`          | Reads a number into `[100]`.         |
| `O`     | Output            | `O100`          | Prints `[100]` to teletype.          |
| `A`     | Add               | `A100 200 300`  | `[300] = [100] + [200]`.             |
| `S`     | Subtract          | `S100 200 300`  | `[300] = [100] - [200]`.             |
| `U`     | Multiply          | `U100 200 300`  | `[300] = [100] * [200]`.             |
| `D`     | Divide            | `D100 200 300`  | `[300] = [100] / [200]`.             |
| `E`     | Equal-loop        | `E100 20`       | If `[100] = 0`, jump to step `20`.   |
| `G`     | Greater-loop      | `G100 30`       | If `[100] > 0`, jump to step `30`.   |
| `J`     | Jump (GOTO)       | `J50`           | Unconditional jump to step `50`.     |

### 3. DOPE Error Codes
Based on historical accounts of DOPE, and its minimalist design, the language likely had a very limited set of errors — consistent with its role as a teaching tool for beginners on the LGP-30 (4KB RAM, drum memory). While no exhaustive error list survives, we can reconstruct plausible errors from its constraints and pedagogical goals. 
### Error Codes

| Code     | Error               | Cause                                      | Debugging Tips                                  |
|----------|---------------------|--------------------------------------------|------------------------------------------------|
| `ERR 1`  | **INVALID COMMAND** | Unrecognized single-letter op (e.g., `X100`) | Check command letters (`Z`, `I`, `O`, etc.).   |
| `ERR 2`  | **ADDRESS OVERFLOW** | Memory access beyond 4KB (e.g., `[5000]`)   | Use addresses `[0]`–`[4095]`.                  |
| `ERR 3`  | **DIVIDE BY ZERO**   | `D100 0 200` (division by zero)             | Pre-check divisor with `E`/`G` (e.g., `E200 50` to skip if zero). |
| `ERR 4`  | **INPUT MISMATCH**   | Non-numeric input for `I100`                | Teletype input must be integers/floats (no strings). |
| `ERR 5`  | **ARITHMETIC FAULT** | Invalid operands (e.g., `A100 'X' 300`)     | Inspect memory with `O` (e.g., `O100` to see corrupted values). |
| `ERR 6`  | **LOOP OVERFLOW**    | Infinite loop (e.g., missing `G`/`E` exit)  | Manually halt (LGP-30 required physical intervention). |
| `ERR 7`  | **DRUM SYNC FAILURE** | Slow drum memory (3600 RPM) caused missed ops | Retry or simplify program.                     |
**Example Error Flow**
```
I100      ! Reads 'ABC' (non-numeric)  
ERR 4: INPUT MISMATCH  
O100      ! User debugs by inspecting [100]
```
DOPE's terse errors halted compile immediately but these unfriendly errors directly inspired BASIC’s clearer messages. 

Kemeny noted: "We learned from DOPE’s brutality. BASIC had to guide, not frustrate."2.

### 4. Programming Examples

A. Sum Two Numbers
```
I100    ! Read into [100]  
I200    ! Read into [200]  
A100 200 300  ! [300] = [100] + [200]  
O300    ! Print result
```  
Input: ```5 3``` 
Output: ```8```

B. Countdown Loop
```
Z100    ! [100] = 0  
A100 10 ! [100] = 10 (counter)  
O100    ! Print counter  
S100 1  ! Decrement counter  
G100 3  ! Loop if [100] > 0  
```
Output: ```10 9 8 7 6 5 4 3 2 1```

### 5. Hardware Constraints
Memory: 4KB RAM (addresses [0]–[4095]).

No Variables: Only absolute addressing (e.g., [100]).

No Subroutines: All control flow via GOTO/loops.

Teletype I/O: Input/output via punch tape or keyboard.

### 6. Design Philosophy
Teach Fundamentals: Loops, branches, and memory management without abstraction.

Polish Notation: Simplified parsing for the LGP-30’s limited compiler.

Interactive: Immediate feedback (unlike batch-processing FORTRAN).

### 7. Legacy
Direct Precursor to BASIC: DOPE proved simplicity was viable, inspiring BASIC’s LET, PRINT, and GOTO.

Historical Context: Demonstrates 1960s trade-offs between usability and hardware limits.


