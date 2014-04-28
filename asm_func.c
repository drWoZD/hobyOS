#include "asm.h"

inline void outb(uint16_t port, uint8_t val)
{
  asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port));
}

inline void outw(uint16_t port, uint16_t val)
{
  asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) );
}

inline void outl(uint16_t port, uint32_t val)
{
  asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port));
}

inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

inline uint16_t inw(uint16_t port)
{
    uint16_t ret;
    asm volatile ( "inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

inline uint32_t inl(uint16_t port)
{
    uint32_t ret;
    asm volatile ( "inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

inline void cpuid(int code, uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d)
{
    asm volatile ( "cpuid" : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d) : "0"(code) );
}

inline void cpuid_m(int code, uint32_t* mass)
{
    asm volatile ( "cpuid" : "=a"(mass[0]), "=b"(mass[1]), "=c"(mass[2]), "=d"(mass[3]) : "0"(code));
}

inline uint64_t rdmsr(uint32_t msr_id)
{
    uint64_t msr_value;
    asm volatile ( "rdmsr" : "=A" (msr_value) : "c" (msr_id) );
    return msr_value;
}

inline void wrmsr(uint32_t msr_id, uint64_t msr_value)
{
    asm volatile ( "wrmsr" : : "c" (msr_id), "A" (msr_value) );
}