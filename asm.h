typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
#ifndef __uint32_t_defined
typedef unsigned int		uint32_t;
# define __uint32_t_defined
#endif
#if __WORDSIZE == 64
typedef unsigned long int	uint64_t;
#else
__extension__
typedef unsigned long long int	uint64_t;
#endif

inline void outb(uint16_t port, uint8_t val);
inline void outw(uint16_t port, uint16_t val);
inline void outl(uint16_t port, uint32_t val);

inline uint8_t inb(uint16_t port);
inline uint16_t inw(uint16_t port);
inline uint32_t inl(uint16_t port);

inline void cpuid(int code, uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d);
inline void cpuid_m(int code, uint32_t* mass);
inline uint64_t rdmsr(uint32_t msr_id);
