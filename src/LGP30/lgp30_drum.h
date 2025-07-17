#ifndef LGP30_DRUM_H
#define LGP30_DRUM_H

#include <stdint.h>
#include <stdbool.h>

#define LGP30_DRUM_CAPACITY     4096    // 4K of 31 bit words
#define LGP30_BITMASK_31        0x7FFFFFFF  // Mask for 31 usable bits (bits 0-30)

// LGP-30 instruction timing approximations
// From the LGP-30 manual “over 400 additions per second” (Programming Manual, p.7)
#define LGP30_ADD_RATE    400  // ops/sec
#define LGP30_ADD_TIME    (1000000 / LGP30_ADD_RATE)  // = 2500µs per add
#define LGP30_DRUM_DELAY_MS     17      // Drum rotation latency (16.7ms per full rev at 3700 RPM)
#define LGP30_SECTOR_DELAY_US   4       // ~4µs per sector (4096 sectors / 16.7ms)

// Approximate how many sectors will have passed the read head per op
#define SECTORS_PER_ADD       (LGP30_ADD_TIME / LGP30_SECTOR_DELAY_US)
#define SECTORS_PER_MUL       (SECTORS_PER_ADD * 3)  // intuitive guess
#define SECTORS_PER_DIV       (SECTORS_PER_ADD * 12) // longer for division
#define SECTORS_PER_IO        (SECTORS_PER_ADD * 2)

typedef int32_t     lgp30_word_t;
typedef uint16_t    lgp30_size_t;

/*
 * The LGP-30 word size was 32 bits with the 32nd bit used as a spacer (on the magnetic drum)
 * and always zero in memory, making for effective 31 bits (0…30)
 */
typedef struct {
    lgp30_word_t memory[LGP30_DRUM_CAPACITY];
    lgp30_size_t pc;                // 12-bit program counter
    lgp30_size_t current_sector;    // 0-4095
    bool is_spinning;
} drum_memory_t;

// historically plausible drum spin-up simulation several accelerating drum spins ~50ms total at 3600RPM
// zeros the program counter and randomizes the current sector
void lgp30_drum_spinup(drum_memory_t* drum);

void lgp30_drum_sector_rotate(drum_memory_t* drum); // ~4µs delay

void lgp30_drum_sector_locate(drum_memory_t* drum, lgp30_size_t sector);

lgp30_word_t lgp30_drum_sector_read(drum_memory_t* drum, lgp30_size_t sector);

void lgp30_drum_sector_write(drum_memory_t *drum, lgp30_size_t sector);

void lgp30_drum_wipe(drum_memory_t* drum);



#endif
