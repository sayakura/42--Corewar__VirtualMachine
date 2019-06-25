#include "handler.h"

t_bool    ft_live(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    
    return true;
}

t_bool    ft_ld(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("ld trigger!\n");
    return true;
}

t_bool    ft_st(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("st trigger!\n");
    return true;
}

t_bool    ft_add(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("add trigger!\n");
    return true;
}

t_bool    ft_sub(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("sub trigger!\n");
    return true;
}

t_bool    ft_and(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("and trigger!\n");
    return true;
}

t_bool    ft_or(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("or trigger!\n");
    return true;
}

t_bool    ft_xor(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("xor trigger!\n");
    return true;
}

t_bool    ft_zjmp(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("zjmp trigger!\n");
    return true;
}

t_bool    ft_ldi(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("ldi trigger!\n");
    return true;
}

t_bool    ft_sti(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("sti trigger!\n");
    
    return true;
}

t_bool    ft_fork(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("fork trigger!\n");
    return true;
}

t_bool    ft_lld(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("lld trigger!\n");
    return true;
}

t_bool    ft_lldi(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("lldi trigger!\n");
    return true;
}

t_bool    ft_lfork(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("lfork trigger!\n");
    return true;
}

t_bool    ft_aff(t_vm *vm, t_byte *argvt, t_byte **argv, t_bool *carry)
{
    printf("aff trigger!\n");
    return true;
}

