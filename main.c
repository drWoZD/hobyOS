/**
 * This file contains the function of main, and some auxiliary functions
 */

#include "multiboot.h"
#include "asm.h"

char current_row = 0, current_col = 0;

void cls()
{
    int i;
    for (i = 0; i < LINES * COLUMS; i++)
	 putchar(' ');
    current_col = 0;
    current_row = 0;
}

void set_cur_pos(unsigned char col, unsigned char row)
{
    unsigned short pos = (row * 80) + col;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos&0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char )((pos>>8)&0xFF));
    cpuid_m(0,0);
}

int putchar(char ch)
{
    unsigned short* video_buff =(unsigned short*) VIDEO_BUFF;
    if (ch == '\n')
    {
	current_row++;
	current_col = 0;
	return 0;
    }
    if (current_col >= COLUMS)
    {
	current_col = 0;
	current_row++;
    }
    video_buff[(current_row * COLUMS) + current_col++] = (unsigned short)((BLACK << 12) | (WHITE << 8) | (ch));
    return 0;
}

void shr(int n, char* str, int len)
{
    while(n > 0)
    {
	str[n] = str[n-1];
	n--;
    }
    
}

void itoa (char *buf, int base, int d)
{
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;
   
    switch(base)
    {
	case 'x':
	    divisor = 16;
	    break;
	    
	case 'b':
	    divisor = 2;
	    break;
	    
	default:
	    if (d < 0)
	    {
		*p++ = '-';
		buf++;
		ud = -d;
	    }
	    break;
    } 

    do
    {
	int remainder = ud % divisor;
     
	*p++ = (remainder < 10) ? ('0' + remainder) : ('A' - 10 + remainder);
    }
    while (ud /= divisor);
     
    *p = 0;
     
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2)
    {
	char tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	p1++;
	p2--;
    }
}

void printf(char* format, ...)
{
    void** arg = (void**) &format;
    char c;
    char buf[32];
    
    arg++;
    
    while ((c = *format++) != 0)
    {
	if (c != '%')
	    putchar(c);
	else
	{
            c = *format++;
            switch (c)
            {
		case 'd':
                case 'u':
                case 'x':
		case 'b':
		    
                    itoa (buf, c, *((int*) arg++));
                    puts(buf);
                   
                    break;

                case 's':
                    puts ((*arg)?((char*) *arg++):"null");
                    break;
		    
                default:
                   putchar (c);
                   break;
	    }
	}
    }
}

int puts(char* str)
{
    while (*str != 0)
    {
	putchar(*str);
	str++;
    }
    putchar('\n');
    set_cur_pos(current_col, current_row);
    return 0;
}

int cmain(multiboot_info_t* mbi)
{
    cls();
    uint32_t r[4];
    cpuid_m(1, r);
    puts((r[3] & (1 << 9))?"APIC support":"APIC not support");
    
    uint64_t ret = rdmsr(0x1B);
    printf("%x", ret & 0xFFFFFFFFFFFFF000);
    
    return 0;
}
