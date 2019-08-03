#include "vm.h"

t_process *g_cur_process;

void    ft_live(t_vm *vm, t_instr *cinstr)
{
    t_champ     *champ; printf("[live]\n");
    int32_t     id;

    READ_(cinstr->arg[0].argv, &id, 4);
                                                           printf("Champion id: %d\n", id);
    champ = ch_search_champion(vm, id);                                                  printf("at cycle: %d\n", vm->corewar.cycle);
    if (!champ)
        return ;
    LOG("Player %d (%s) is said to be alive\n", champ->id + 2, champ->name);
    champ->lives++; 
    champ->last_live = vm->corewar.cycle;
}

void    ft_st(t_vm *vm, t_instr *cinstr)
{
    (void)vm;
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

void    ft_add(t_vm *vm, t_instr *cinstr)
{
    (void)vm;
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    ADD(EDI, ESI);
    MOV(ECX, EDI);
    CP->carry = !ECX;           printf("[add] add: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_sub(t_vm *vm, t_instr *cinstr)
{
    (void)vm;
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    SUB(EDI, ESI);
    MOV(ECX, EDI);
    CP->carry = !ECX;           printf("[sub] sub: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_and(t_vm *vm, t_instr *cinstr)
{
    (void)vm;
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    AND(EDI, ESI);
    MOV(ECX, EDI);
    CP->carry = !ECX;           printf("[and] and: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_or(t_vm *vm, t_instr *cinstr)
{
    (void)vm;
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    OR(EDI, ESI);
    MOV(ECX, EDI);
    CP->carry = !ECX;           printf("[or] or: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_xor(t_vm *vm, t_instr *cinstr)
{
    (void)vm;
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    XOR(EDI, ESI);
    MOV(ECX, EDI);
    CP->carry = !ECX;           printf("[xor] and: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_zjmp(t_vm *vm, t_instr *cinstr)
{
    int32_t     offset;

    (void)vm;
    if (CP->carry)
    {
        READ_(cinstr->arg[0].argv, &offset, 4);
        CP->pc = REL(CP->pc, offset);
    }
    printf("zjmp trigger!\n");
}

void    ft_ldi(t_vm *vm, t_instr *cinstr)
{
    (void)vm;
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    ADD(ESI, ECX);
    MOV(ECX, *REL(PC, ESI));
    printf("[ldi] argv: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}


/**
 *  Opcode 11. Take a registry, and two indexes (potentially registries) add the
 *  two indexes, and use this result as an address where the value of the first parameter
 *  will be copied.
 *  1. load the index of the register to edx (we are not using edi since we need to copy
 *  the content of edi to the targeted address later, and we dont wannat overwrite it)
 *  2. load the value of the second parameter into esi, the second paramter can be reg
 *  indirect, or direct. 
 *  3. load the value of the third parameter into ecx, the third paramter can be reg
 *  indirect, or direct. 
 *  4. add esi and ecx and store the result into esi, which will represents the address 
 *  5. copy the content at registers[edx] to address(esi)
*/
void    ft_sti(t_vm *vm, t_instr *cinstr)
{
    (void)vm;                               int debug; 
    LEA(EDX, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);               debug = ESI;
    LD(ECX, &cinstr->arg[2]);
    ADD(ESI, ECX);
    MOV(*REL(PC, ESI), REG(EDX));           printf("[sti] data %d, at index %d + %d\n", REG(EDX), debug, ECX);
}

void    ft_fork(t_vm *vm, t_instr *cinstr)
{
    int32_t offset;

    (void)vm;
    READ_(cinstr->arg[0].argv, &offset, 4);
    p_fork_process(vm, CP, offset, false);
    printf("[fork] offset: %d\n", offset);
}

void    ft_ld(t_vm *vm, t_instr *cinstr)
{
    (void)vm;
    XOR(EDI, EDI);
    mem_oper(READ, (t_byte *)&EDI, (t_byte *)&cinstr->arg[0].argv, 2);
    // h_rev_bytes(&EDI, 4);
    printf("--> EDI: %d\n", EDI);

    LD(EDI, &cinstr->arg[0]);
    h_rev_bytes(&EDI, sizeof(EDI));
    XOR(ESI, ESI);
    LEA(ESI, &cinstr->arg[1]);
    MOV(REG(ESI), EDI);
    CP->carry = !EDI;
    printf("[ld] argv: [ %d | %d ]\n", EDI, ESI);
}

void    ft_lld(t_vm *vm, t_instr *cinstr)
{
    (void)vm;
    LLD(EDI, &cinstr->arg[0]);
    LLEA(ESI, &cinstr->arg[1]);
    MOV(REG(ESI), EDI);
    CP->carry = !EDI;
    printf("[lld] argv: [ %d | %d | %d]\n", EDI, ESI, ECX);
}

void    ft_lldi(t_vm *vm, t_instr *cinstr)
{
    (void)vm;
    LD(EDI, &cinstr->arg[0]);
    LD(ESI, &cinstr->arg[1]);
    ADD(ESI, ECX);
    MOV(ECX, *(ABS(PC, ESI)));
    CP->carry = !ECX;
    printf("[lldi] argv: [ %d | %d | %d ]\n", EDI, ESI, ECX);
}

void    ft_lfork(t_vm *vm, t_instr *cinstr)
{
    int32_t offset;

    (void)vm;
    READ_(cinstr->arg[0].argv, &offset, 4);
    p_fork_process(vm, CP, offset, true);
    printf("[lfork] \n");
}

void    ft_aff(t_vm *vm, t_instr *cinstr)
{
    uint8_t c;

    (void)vm;
    LD(EDI, &cinstr->arg[0]);
    c = EDI % 256;
    printf("%c", c);
}

