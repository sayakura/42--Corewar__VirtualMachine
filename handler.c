#include "handler.h"
t_process *g_cur_process;

void    ft_live(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    t_champ     *champ; printf("[live]\n");
    int32_t     id;

    read_m(cinstr->arg[0].argv, &id, 4);
                                                           printf("Champion id: %d\n", id);
    champ = search_champion(vm, id);                                                  printf("at cycle: %d\n", vm->corewar.cycle);
    if (!champ)
        return ;
    LOG("Player %d (%s) is said to be alive\n", champ->id + 2, champ->name);
    champ->lives++; 
    champ->last_live = vm->corewar.cycle;
}

void    ft_ld(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    LD(EDI, &cinstr->arg[0]);
    LEA(ESI, &cinstr->arg[1]);
    MOV(REG(ESI), EDI);
                                printf("[ld] argv: [ %d | %d ]\n", EDI, ESI);
}

void    ft_st(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    LD(EDI, &cinstr->arg[0]);
    LEA(ESI, &cinstr->arg[1]);
    if (cinstr->arg[1].argvt == REGISTER_TYPE)
    {
        MOV(REG(ESI), EDI);
    }
    else
        MOV(*(REL(PC, ESI)), EDI);
                                                printf("[st] argv: [ %d | %d ]\n", EDI, ESI);
}

void    ft_add(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    ADD(EDI, ESI);
    MOV(ECX, EDI);
    CP->carry = !ECX;           printf("[st] add: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_sub(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    SUB(EDI, ESI);
    MOV(ECX, EDI);
    CP->carry = !ECX;           printf("[st] sub: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_and(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    AND(EDI, ESI);
    MOV(ECX, EDI);
    CP->carry = !ECX;           printf("[st] and: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_or(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    OR(EDI, ESI);
    MOV(ECX, EDI);
    CP->carry = !ECX;           printf("[or] and: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_xor(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    XOR(EDI, ESI);
    MOV(ECX, EDI);
    CP->carry = !ECX;           printf("[xor] and: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_zjmp(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    int32_t     offset;

    if (CP->carry)
    {
        read_m(cinstr->arg[0].argv, &offset, 4);
        CP->pc = REL(CP->pc, offset);
    }
    printf("zjmp trigger!\n");
}

void    ft_ldi(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("ldi trigger!\n");
}

void    ft_sti(t_vm *vm, t_process *cp, t_instr *cinstr)
{
  
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    LD(ECX, cinstr->arg + 2);
    ADD(ESI, ECX);
    MOV(*REL(PC, ESI), EDI);        printf("[sti] argv: [ %d | %d | %d]\n", EDI, ESI, ECX);
    
}

void    ft_fork(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("fork trigger!\n");
}

void    ft_lld(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    LD(EDI, &cinstr->arg[0]);
    LLEA(ESI, &cinstr->arg[1]);
    MOV(REG(ESI), EDI);
    printf("[lld] argv: [ %d | %d | %d]\n", EDI, ESI, ECX);
}

void    ft_lldi(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("lldi trigger!\n");
}

void    ft_lfork(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("lfork trigger!\n");
}

void    ft_aff(t_vm *vm, t_process *cp, t_instr *cinstr)
{
    printf("aff trigger!\n");
}

