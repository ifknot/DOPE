#ifndef PORTABLE_SLEEP_H
#define PORTABLE_SLEEP_H

//Cross-platform millisecond sleep

#include <stdint.h>

// Detect Watcom C compiler
#if defined(__WATCOMC__)
  #define IS_WATCOM 1
  #include <dos.h>  // For Watcom's delay()
#else
  #define IS_WATCOM 0
  #if __STDC_VERSION__ >= 199901L
    #include <unistd.h>  // For usleep() in C99
  #elif defined(_WIN32)
    #include <windows.h> // For Sleep() on Windows
  #endif
#endif

// Portable microsecond sleep
static inline void portable_sleep_us(uint32_t microseconds) {
  #if __STDC_VERSION__ >= 199901L
    usleep(microseconds);  // Microsecond precision
  #endif
  // otherwise unable to achieve µs timing
}

// Portable millisecond sleep
static inline void portable_sleep_ms(uint32_t milliseconds) {
  #if IS_WATCOM
    /* Watcom-specific (DOS) */
    delay(milliseconds);  // Watcom's DOS delay() (max 65535 ms)
  #elif __STDC_VERSION__ >= 199901L
    /* C99/POSIX fallback */
    usleep(milliseconds * 1000);  // Microsecond precision
  #elif defined(_WIN32)
    /* Windows fallback */
    Sleep(milliseconds);  // Windows Sleep() (caps at 49.7 days)
  #else

  #endif
}

#endif
