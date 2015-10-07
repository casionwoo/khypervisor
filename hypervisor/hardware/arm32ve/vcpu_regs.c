#include <vcpu_regs.h>

void core_gprs_init(struct core_gprs *regs){

    //Initialize loader status for reboot
    regs->gprs[10] = 0;

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


void core_gprs_save_(struct core_gprs *vcpu_regs, struct core_gprs *hw_regs){
    /************************************
    *   SAVE : HW_REGS => VCPU_REGS   
    *        (source)  => (destination)
    ************************************/

    core_gprs_copy(vcpu_regs, hw_regs);
}

void core_gprs_restore_(struct core_gprs *vcpu_regs, struct core_gprs *hw_regs){
    /************************************
    *   RESTORE : VCPU_REGS => HW_REGS   
    *             (source)  => (destination)
    ************************************/
    core_gprs_copy(hw_regs, vcpu_regs);
   
}

void banked_regs_save(struct banked_regs *regs){
    //READ regs from H/W
    banked_regs_save_hardware(regs);
}

void banked_regs_restore(struct banked_regs *regs){
    //WRITE regs to H/W
    banked_regs_restore_hardware(regs);
}

void core_gprs_copy(struct core_gprs *dst_regs, struct core_gprs *src_regs){

    int i = 0;

    dst_regs->sp    = src_regs->sp;
    dst_regs->lr    = src_regs->lr;
    dst_regs->pc    = src_regs->pc;
    dst_regs->cpsr  = src_regs->cpsr;

    for(i = 0 ; i < NUM_OF_GPRS ; i++)
        dst_regs->gprs[i] = src_regs->gprs[i];
}
