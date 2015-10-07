#include <vcpu_regs_hw.h>

void banked_regs_save_hardware(struct banked_regs * regs)
{
    /* USR banked register : sp_usr is not banked in vcpu*/
    //asm volatile(" mrs     %0, sp_usr\n\t"
    //        : "=r"(regs_banked->sp_usr) : : "memory", "cc");

    /* SVC banked register */
    asm volatile(" mrs     %0, spsr_svc\n\t"
            : "=r"(regs->svc_spsr) : : "memory", "cc");
    asm volatile(" mrs     %0, sp_svc\n\t"
            : "=r"(regs->svc_sp) : : "memory", "cc");
    asm volatile(" mrs     %0, lr_svc\n\t"
            : "=r"(regs->svc_lr) : : "memory", "cc");
    /* ABT banked register */
    asm volatile(" mrs     %0, spsr_abt\n\t"
            : "=r"(regs->abt_spsr) : : "memory", "cc");
    asm volatile(" mrs     %0, sp_abt\n\t"
            : "=r"(regs->abt_sp) : : "memory", "cc");
    asm volatile(" mrs     %0, lr_abt\n\t"
            : "=r"(regs->abt_lr) : : "memory", "cc");
    /* UND banked register */
    asm volatile(" mrs     %0, spsr_und\n\t"
            : "=r"(regs->und_spsr) : : "memory", "cc");
    asm volatile(" mrs     %0, sp_und\n\t"
            : "=r"(regs->und_sp) : : "memory", "cc");
    asm volatile(" mrs     %0, lr_und\n\t"
            : "=r"(regs->und_lr) : : "memory", "cc");
    /* IRQ banked register */
    asm volatile(" mrs     %0, spsr_irq\n\t"
            : "=r"(regs->irq_spsr) : : "memory", "cc");
    asm volatile(" mrs     %0, sp_irq\n\t"
            : "=r"(regs->irq_sp) : : "memory", "cc");
    asm volatile(" mrs     %0, lr_irq\n\t"
            : "=r"(regs->irq_lr) : : "memory", "cc");
    /* FIQ banked register  R8_fiq ~ R12_fiq, LR and SPSR */
    asm volatile(" mrs     %0, spsr_fiq\n\t"
            : "=r"(regs->fiq_spsr) : : "memory", "cc");
    asm volatile(" mrs     %0, lr_fiq\n\t"
            : "=r"(regs->fiq_lr) : : "memory", "cc");
    asm volatile(" mrs     %0, r8_fiq\n\t"
            : "=r"(regs->fiq_r8) : : "memory", "cc");
    asm volatile(" mrs     %0, r9_fiq\n\t"
            : "=r"(regs->fiq_r9) : : "memory", "cc");
    asm volatile(" mrs     %0, r10_fiq\n\t"
            : "=r"(regs->fiq_r10) : : "memory", "cc");
    asm volatile(" mrs     %0, r11_fiq\n\t"
            : "=r"(regs->fiq_r11) : : "memory", "cc");
    asm volatile(" mrs     %0, r12_fiq\n\t"
            : "=r"(regs->fiq_r12) : : "memory", "cc");
}


void banked_regs_restore_hardware(struct banked_regs *regs)
{
    /* USR banked register : usr_sp is not banked register in vcpu */
    //asm volatile(" msr    sp_usr, %0\n\t"
    //        : : "r"(regs_banked->sp_usr) : "memory", "cc");
    /* SVC banked register */
    asm volatile(" msr    spsr_svc, %0\n\t"
            : : "r"(regs->svc_spsr) : "memory", "cc");
    asm volatile(" msr    sp_svc, %0\n\t"
            : : "r"(regs->svc_sp) : "memory", "cc");
    asm volatile(" msr    lr_svc, %0\n\t"
            : : "r"(regs->svc_lr) : "memory", "cc");
    /* ABT banked register */
    asm volatile(" msr    spsr_abt, %0\n\t"
            : : "r"(regs->abt_spsr) : "memory", "cc");
    asm volatile(" msr    sp_abt, %0\n\t"
            : : "r"(regs->abt_sp) : "memory", "cc");
    asm volatile(" msr    lr_abt, %0\n\t"
            : : "r"(regs->abt_lr) : "memory", "cc");
    /* UND banked register */
    asm volatile(" msr    spsr_und, %0\n\t"
            : : "r"(regs->und_spsr) : "memory", "cc");
    asm volatile(" msr    sp_und, %0\n\t"
            : : "r"(regs->und_sp) : "memory", "cc");
    asm volatile(" msr    lr_und, %0\n\t"
            : : "r"(regs->und_lr) : "memory", "cc");
    /* IRQ banked register */
    asm volatile(" msr     spsr_irq, %0\n\t"
            : : "r"(regs->irq_spsr) : "memory", "cc");
    asm volatile(" msr     sp_irq, %0\n\t"
            : : "r"(regs->irq_sp) : "memory", "cc");
    asm volatile(" msr     lr_irq, %0\n\t"
            : : "r"(regs->irq_lr) : "memory", "cc");
    /* FIQ banked register */
    asm volatile(" msr     spsr_fiq, %0\n\t"
            : : "r"(regs->fiq_spsr) : "memory", "cc");
    asm volatile(" msr     lr_fiq, %0\n\t"
            : : "r"(regs->fiq_lr) : "memory", "cc");
    asm volatile(" msr    r8_fiq, %0\n\t"
            : : "r"(regs->fiq_r8) : "memory", "cc");
    asm volatile(" msr    r9_fiq, %0\n\t"
            : : "r"(regs->fiq_r9) : "memory", "cc");
    asm volatile(" msr    r10_fiq, %0\n\t"
            : : "r"(regs->fiq_r10) : "memory", "cc");
    asm volatile(" msr    r11_fiq, %0\n\t"
            : : "r"(regs->fiq_r11) : "memory", "cc");
    asm volatile(" msr    r12_fiq, %0\n\t"
            : : "r"(regs->fiq_r12) : "memory", "cc");
}
