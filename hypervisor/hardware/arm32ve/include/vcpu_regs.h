#ifndef     __VCPU_REGS_H__
#define     __VCPU_REGS_H__

#include <k-hypervisor-config.h>
#include <hvmm_types.h>

#define NUM_OF_GPRS 13

struct core_gprs{

    
    regs32_t cpsr;
    regs32_t pc;
    regs32_t lr;
    
    //stack pointer 18?
    regs32_t sp;

    regs32_t gprs[NUM_OF_GPRS];


};

struct banked_regs{
    
    regs32_t fiq_r8;
    regs32_t fiq_r9;
    regs32_t fiq_r10;
    regs32_t fiq_r11;
    regs32_t fiq_r12;
    regs32_t fiq_sp;
    regs32_t fiq_lr;
    regs32_t fiq_spsr;

    regs32_t svc_sp;
    regs32_t svc_lr;
    regs32_t svc_spsr;

    regs32_t abt_sp;
    regs32_t abt_lr;
    regs32_t abt_spsr;

    regs32_t irq_sp;
    regs32_t irq_lr;
    regs32_t irq_spsr;

    regs32_t und_sp;
    regs32_t und_lr;
    regs32_t und_spsr;

};

void core_gprs_init(struct core_gprs *regs);
void banked_regs_init(struct banked_regs *regs);

void core_gprs_save(struct core_gprs *regs);
void banked_regs_save(struct banked_regs *regs);

void core_gprs_restore(struct core_gprs *regs);
void banked_regs_restore(struct banked_regs *regs);

#endif      /* __VCPU_REGS_H__ */
