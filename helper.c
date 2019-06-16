
#include "vm.h"

unsigned int reverseBits(unsigned int num) 
{ 
    unsigned int count; 
    unsigned int reverse_num; 
    
    count = sizeof(num) * 8 - 1;
    reverse_num = num;
    num >>= 1;  
    while(num) 
    { 
       reverse_num <<= 1;        
       reverse_num |= num & 1; 
       num >>= 1; 
       count--; 
    } 
    reverse_num <<= count; 
    return reverse_num; 
} 
  