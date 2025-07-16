#ifndef LGP30_DRUM_H
#define LGP30_DRUM_H

#include <stdint.h>
#include <stdbool.h>

#define LGP30_DRUM_CAPACITY     4096    // 4K of 31 bit words
#define LGP30_DRUM_DELAY_MS     17      // Drum rotation latency (16.7ms per full rev at 3600 RPM)
#define LGP30_SECTOR_DELAY_US   4       // ~4µs per sector (4096 sectors / 16.7ms)

typedef int32_t     lgp30_word_t;
typedef uint16_t    lgp30_size_t;

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
