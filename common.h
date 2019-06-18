#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define bool uint8_t;
#define REVERSE_BIT reverseBits
#define PERROR perror_
#define ERROR(s) ({ printf(s); exit(1);})

//lib	
void			perror_(const char *s);
void            *memcpy_(void *dst, const void *src, size_t n);
int             strlen_(char *str);
#endif