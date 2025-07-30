# **DOPE: A Recreation in C**

*Exploring the spirit and implementation of Dartmouth's precursor to BASIC as an interpreter written in C.*

## Synopsis

> The Dartmouth Oversimplified Programming Experiment (DOPE) was a programming language developed at Dartmouth College by John G. Kemeny and others in the early 1960s, specifically for the LGP-30 computer. It was designed as a simplified tool for teaching programming to non-science students. [Wikipedia ](https://en.wikipedia.org/wiki/Dartmouth_Oversimplified_Programming_Experiment), [VICE Article ](https://vice.com/...link-to-vice-article-if-available)

DOPE is largely lost to history, overshadowed by its famous successor, BASIC. For decades, details were scarce, existing mostly in academic footnotes and a single, unpublished manuscript by Kemeny. Recently, efforts like Sean Haas's work for VICE unearthed crucial documents, offering a rare glimpse into this "radically different approach to programming" that, while not successful in its own right, was the essential stepping stone to BASIC.

Recreating DOPE, even in a simplified form, isn't about nostalgia. It's about understanding the foundational ideas of making computing accessible and the constraints under which early pioneers worked. It forces a confrontation with the simplicity that was *possible* when the goal was clarity over capability.

## **Motivations**

Why implement a language that was deemed "too primitive to be useful" by its own creator, surviving only a single semester?

The motivation is not utility in the modern sense, but understanding. DOPE represents a pure distillation of Kemeny's goal: to make programming learnable in a few hours by non-specialists. Its constraints – the LGP-30's limited memory, the lack of advanced features, the single-character commands – shaped its design in a way that I found fascinating to dissect.

Implementing DOPE in C99 was an exercise in minimalism. Could I simulate, even roughly, the unique experience of programming on an LGP-30 with its drum memory and lack of hardware floating-point support?

The answer, embodied in `dope.c` and `lgp30_sim.h`, was a surprisingly functional, if extremely quirky, recreation. It is not a practical tool, but it's a tangible way to engage with a pivotal moment in programming history.

## **DOPE Core Concepts**

DOPE's design is driven by two overriding principles: extreme simplicity for the user and minimal complexity for the interpreter. This manifests in several key ways.

The language does away with almost any notion of complex data types. Every variable is a floating-point number. There is no need for declarations; you just use them. Four special variables, `E`, `F`, `G`, and `H`, are implicitly understood to be fixed-size arrays, a small concession to needing slightly more complex data structures without adding syntax.

Program structure is entirely linear and based on numbered lines. These numbers are not just for ordering; they are the labels you jump to. This eliminates the need for separate `GOTO` labels or complex control flow constructs at the syntax level. Sorting lines by number gives you your execution order automatically.

The commands themselves are brutally fixed. Each operation takes a predetermined number of arguments. This is not just a design choice; it was a necessity for a system that needed to parse quickly and simply on limited hardware. The operation character is always in the same relative spot after the line number, making parsing almost trivial.

Each line performs exactly one action. Want to add two numbers and print the result? That is two lines. This single-mindedness gives DOPE programs a distinctive, almost assembly-like feel, but it also makes the consequence of each line crystal clear.

Finally, the syntax itself is stripped down. Spaces are ignored as delimiters. Instead, single quotes (`'`) separate parts of the command. So, `5'+'A'B'C` means "add A and B, put the result in C". It looks cryptic, but it is also unambiguous and easy for a simple parser to handle.

Understanding these concepts is key to grasping how a program is structured and executed in DOPE. It is less like modern programming and more like assembling simple instructions in a very specific order.

## **DOPE Syntax and Semantics**

The most immediately striking feature of DOPE is its syntax. Forget spaces; single quotes (`'`) are the primary separator.

`5'+'A'B'C` means: "On line 5, add the values in variables `A` and `B`, storing the result in variable `C`."

This unusual convention reflects the machine constraints and the goal of absolute simplicity in parsing. Everything fits into a rigid pattern.

Lines follow the format: `<line_number>'<operation>'<operand1>'<operand2>...`

- **Line Numbers (1-99):** Dictate execution order and serve as targets for jumps. They are implicit labels.
- **Operations:** Mostly single letters for common tasks (`+`, `-`, `*`, `/`, `P` for print, `J` for input, `T` for jump, `Z` for loop start, `E` for loop end). Three-letter codes handle mathematical functions (`EXP`, `LOG`, `SIN`, `SQR`).
- **Operands:** The number is fixed for each operation. This eliminates the need for complex parsing. Variables are typically single letters optionally followed by a single digit (e.g., `X`, `X1`). Arrays `E`, `F`, `G`, `H` are indexed implicitly when used in context (e.g., `P'E3` prints the 4th element of array `E`).

This leads to programs that look more like assembly language flowcharts than modern code.

For example, a simple infinite loop adding 1+1 into `A`:

```
1'+’1’1’A
2’T’2
```

Initially this may seem cryptic but with familiarity your mind's eye becomes used to it and parser benefits from the rigid structure and single character commands.

## **Command Reference**

This table summarizes the core operations implemented in this recreation, reflecting the historically plausible set.

|       |                     |      |                  |
| ----- | ------------------- | ---- | ---------------- |
| `+`   | Addition            | 3    | `5'+'A'B'C`      |
| `-`   | Subtraction         | 3    | `6'-'C'B'D`      |
| `*`   | Multiplication      | 3    | `7'*'D'2'X`      |
| `/`   | Division            | 3    | `8'/'X'3'Y`      |
| `EXP` | e to the power      | 2    | `10'EXP'2'A`     |
| `LOG` | Logarithm           | 2    | `11'LOG'A'B`     |
| `SIN` | Sine                | 2    | `12'SIN'B'C`     |
| `SQR` | Square root         | 2    | `13'SQR'C'D`     |
| `P`   | Print variable      | 1    | `20'P'A`         |
| `N`   | Print newline       | 0    | `21'N`           |
| `J`   | Input into variable | 1    | `30'J'X`         |
| `A`   | Ask (prompt input)  | 2    | `31'A'Enter X'X` |
| `T`   | Jump                | 1    | `50’T’10`        |
| `C`   | Arithmetic IF       | 4    | `60'C'A'0'70'80` |
| `Z`   | For loop start      | ?    | `100'Z'...`      |
| `E`   | End loop            | ?    | `...’E`          |

*Note: The exact operand counts for `Z` and `E` require deeper analysis of the original manuscript, but they manage loop iteration. I am waiting to hear back from Dartmouth Library about my online request for a copy of the original DOPE teaching plan*

## **Implementation Notes**

The implementation in C99 (`dope.c`) focuses on faithfully recreating the *feel* and *constraints* of DOPE, rather than optimizing for speed or modern usability.

Parsing line tokenization is straightforward due to the fixed format. Splitting on `'` and accessing elements by index replicates the simplicity of the original parser's task. Variables are stored as `double` internally, simulating DOPE's use of floating-point for everything. The special arrays `E`, `F`, `G`, `H` are implemented as fixed-size `double` arrays. A simple loop reads, sorts (by line number), and executes instructions sequentially.

To approximate the experience, a basic simulation layer (`lgp30_sim.h`) introduces artificial delays mimicking the LGP-30's drum memory access latency (~16.7ms average rotational delay). Memory accesses mask the internal `int32_t` representation to 31 bits, reflecting the LGP-30's word size. Floating-point operations rely on the host's software implementation, as the LGP-30 lacked hardware FP.

The program reads DOPE code from standard input, parses it, and executes it line by line, echoing output and accepting input as specified by `P`, `J`, and `A` commands. This approach prioritizes understandability and fidelity to the original *constraints* over raw performance.

## **Limitations and Considerations**

This is a *recreation* and an *interpretation* based on limited historical documents. It is not, and cannot be, a perfect replica of the original DOPE system.

Details on exact operand counts for some commands (`Z`, `E`), precise error handling, and all nuances of the original LGP-30 interaction are unclear. This implementation makes reasonable assumptions. DOPE is extremely limited. It lacks strings, complex data structures, subroutines, and almost any feature we consider standard - it is an historical artefact, not a tool.

The LGP-30 simulation is a rough approximation. True emulation would require significantly more effort and detail about the original hardware. The original DOPE's main legacy is what it taught its creators – that simplicity needed to be balanced with usability, leading directly to BASIC's more forgiving design. This recreation serves the same purpose: a learning tool about the history of programming language design.
