#include "handler.h"

t_bool    ft_live(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    t_champ     *champ;
    int32_t     id;

    READ_FROM_MEM(cinstr->argv[0], (t_byte *)&id, REG_SIZE, E_BIG_ENDIAN);            printf("%d\n", id);
    champ = search_champion(vm, id);                                                  printf("at cycle: %d\n", vm->corewar.cycle);
    if (!champ)
        return true;
    champ->lives++;
    champ->last_live = vm->corewar.cycle;
    return true;
}

t_bool    ft_ld(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    int8_t      i;                          printf("ld trigger!\n");

    i = ITERATOR;
    while (++i < cinstr->argc)
    {
    }
    return true;
}

t_bool    ft_st(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    int8_t      i;                          printf("st trigger!\n");
    int32_t     reg;
    int32_t     rdi;

    rdi = 0;
    reg = 0;
    READ_FROM_MEM(cinstr->argv[0], (t_byte *)&i, 1, E_BIG_ENDIAN);                        printf("i: %d reg: %d\n", i, cp->registers[i]);
    printf("cinstr->argvt[1]: %d\n", cinstr->argvt[1]);
    if (cinstr->argvt[1] == INDIRECT_TYPE)
    {
        READ_FROM_MEM(cinstr->argv[1], (t_byte *)&rdi, IND_SIZE, E_BIG_ENDIAN);             printf("rdi: %d\n", rdi);
        // printf("pc : %p [%x]\n", cinstr->pc, *cinstr->pc);
        // printf("apc : %p [%x]\n", cinstr->pc + (rdi % IDX_MOD), *cinstr->pc + (rdi % IDX_MOD));
        // printf("content : %d\n", cp->registers[i - 1]);
        WRITE_TO_MEM(cinstr->pc + (rdi % IDX_MOD), (t_byte *)(&cp->registers[i - 1]), REG_SIZE, E_BIG_ENDIAN);
    }
    // if (cinstr->argvt[1] & T_REG)
    //     WRITE_TO_MEM(cinstr->argv[1], reg, REG_SIZE, E_BIG_ENDIAN);
    
    return true;
}

t_bool    ft_add(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("add trigger!\n");
    return true;
}

t_bool    ft_sub(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("sub trigger!\n");
    return true;
}

t_bool    ft_and(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("and trigger!\n");
    return true;
}

t_bool    ft_or(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("or trigger!\n");
    return true;
}

t_bool    ft_xor(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("xor trigger!\n");
    return true;
}

t_bool    ft_zjmp(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("zjmp trigger!\n");
    return true;
}

t_bool    ft_ldi(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("ldi trigger!\n");
    return true;
}

t_bool    ft_sti(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("sti trigger!\n");
    
    return true;
}

t_bool    ft_fork(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("fork trigger!\n");
    return true;
}

t_bool    ft_lld(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("lld trigger!\n");
    return true;
}

t_bool    ft_lldi(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("lldi trigger!\n");
    return true;
}

t_bool    ft_lfork(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("lfork trigger!\n");
    return true;
}

t_bool    ft_aff(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("aff trigger!\n");
    return true;
}

