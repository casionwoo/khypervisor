#include <vcpu_regs.h>

void core_gprs_init(struct core_gprs *regs){

    //Initialize loader status for reboot
    regs->gprs[11] = 0;

    //Supervisor Mode
    regs->cpsr = 0x1d3;
    regs->pc = CFG_GUEST_START_ADDRESS;

    //Don't care about the r0~r12 initialization.
}

void banked_regs_init(struct banked_regs *regs){
    regs->fiq_r8    = 0;
    regs->fiq_r9    = 0;
    regs->fiq_r10   = 0;
    regs->fiq_r11   = 0;
    regs->fiq_r12   = 0;
    //regs->fiq_sp    = 0;     /* Cortex-A15 processor does not support sp_fiq */
    regs->fiq_lr    = 0;
    regs->fiq_spsr  = 0;

    regs->svc_sp    = 0;
    regs->svc_lr    = 0;
    regs->svc_spsr  = 0;

    regs->abt_sp    = 0;
    regs->abt_lr    = 0;
    regs->abt_spsr  = 0;

    regs->irq_sp    = 0;
    regs->irq_lr    = 0;
    regs->irq_spsr  = 0;

    regs->und_sp    = 0;
    regs->und_lr    = 0;
    regs->und_spsr  = 0;
}


void core_gprs_save(struct core_gprs *regs){

//    regs->sp    = 
//    regs->lr    = 
//    regs->pc    = 
//    regs->cpsr  = 


}
void banked_regs_save(struct banked_regs *regs){
    banked_regs_save_hardware(regs);
}
void core_gprs_restore(struct core_gprs *regs){
    
}
void banked_regs_restore(struct banked_regs *regs){
    banked_regs_restore_hardware(regs);
}
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









