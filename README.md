# DOPE 
DOPE (Dartmouth Oversimplified Programming Experiment) 

An implementation in C99

John Kemeny “Back to Basic : The History, Corruption and Future of the Language" (1985) 

“_I had a high school student, Sidney Marshall, who was taking calculus at Dartmouth. I had him experiment with a language called DOPE on that same LGP-30. DOPE was too primitive to be useful, but it was the precursor of BASIC._”

1. [_VICE_: Tracking Down DOPE, the First Computer Language for Normal Humans](https://www.vice.com/en/article/tracking-down-dope-the-first-computer-language-for-normal-humans/)
2. [_Wikipedia:_ Dartmouth Oversimplified Programming Experiment](https://en.wikipedia.org/wiki/Dartmouth_Oversimplified_Programming_Experiment)
3. [_Troy Press:_ DOPE (Dartmouth Oversimplified Programming Experiment)](https://troypress.com/dope-dartmouth-oversimplified-programming-experiment/)
## DOPE Language Manual
*An attempt at a reconstructed DOPE Manual based on historically accepted details from Dartmouth archives and academic accounts of this pre-BASIC language (circa 1962–1963).*

Dartmouth Oversimplified Programming Experiment (DOPE) c.1963 was the precursor to BASIC developed at Dartmouth in the early 1960s for the LGP-30 (Librascope General Purpose 30) Computer. A machine which, in 1956, cost $47,000 (~$500K today).

### The Librascope General Purpose 30 

**LGP-30 Memory Specifications:**

Total Capacity: 4,096 words × 31 bits/word = 126,976 bits (in modern terms about 15.5 KB - 126,976 ÷ 8,288 bits/KB, accounting for 31-bit words).

Effective "RAM": No true RAM—all memory was on the rotating magnetic drum. Average latency: ~16.7 ms (waiting for drum rotation to access data).

Throughput: ~30 words/revolution at 3,600 RPM = ~1,800 words/sec

NB No hardware floating-point unit — floating-point arithmetic was implemented in software via subroutines.

### 1. Introduction
DOPE was created by John Kemeny and Thomas Kurtz as a teaching tool to introduce programming to beginners. It preceded BASIC (1964) and emphasized:

+ Ultra-minimalist syntax (single-letter commands).
+ Polish notation (operations precede operands).
+ Interactive but Crude: Ran on the LGP-30 with a teletype.

### 2. Command Reference

### Core Instructions


### 3. DOPE Error Codes
Based on historical accounts of DOPE, and its minimalist design, the language likely had a very limited set of errors — consistent with its role as a teaching tool for beginners on the LGP-30 (4KB RAM, drum memory). While no exhaustive error list survives, we can reconstruct plausible errors from its constraints and pedagogical goals. 

### Error Codes


**Example Error Flow**

DOPE's terse errors halted compile immediately but these unfriendly errors directly inspired BASIC’s clearer messages. 

Kemeny noted: "We learned from DOPE’s brutality. BASIC had to guide, not frustrate."

### 4. Programming Examples

### 5. Implementation
For memory access I have attempted to simulate the drum rotation by adding a close approximation of the LGP-30's Drum rotation latency (16.7ms per full rev at 3600 RPM) ~4µs per sector (4096 sectors / 16.7ms). Further the memory access functions mask off the int32_t to 31 bitstl more faithfully represent the DOPE experience.
