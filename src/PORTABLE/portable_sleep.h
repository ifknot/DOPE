#ifndef PORTABLE_SLEEP_H
#define PORTABLE_SLEEP_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

// Platform detection
#if defined(__WATCOMC__)
  #include <dos.h>
  #define HAS_WATCOM_DELAY 1
#elif defined(_WIN32)
  #include <windows.h>
  #define HAS_WIN32_SLEEP 1
#elif __STDC_VERSION__ >= 199901L
  #include <unistd.h>  // POSIX usleep
  #define HAS_POSIX_USLEEP 1
#endif

//--------------------------------------------------
// Microsecond sleep (POSIX-only)
static inline void portable_sleep_us(uint32_t us) {
  #ifdef HAS_POSIX_USLEEP
    usleep(us);
  #else
    assert(false && "usleep() unavailable: Needs POSIX or C99");
    (void)us;
  #endif
}

//--------------------------------------------------
// Millisecond sleep (multi-platform)
static inline void portable_sleep_ms(uint32_t ms) {
  #ifdef HAS_WATCOM_DELAY
    delay(ms);  // DOS/Watcom
  #elif defined(HAS_WIN32_SLEEP)
    Sleep(ms);  // Windows
  #elif defined(HAS_POSIX_USLEEP)
    usleep(ms * 1000);  // POSIX fallback
  #else
    assert(false && "No sleep implementation available");
    (void)ms;
  #endif
}

#endif
