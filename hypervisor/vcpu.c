#include "vcpu.h"


static int num_of_vcpus = 0;

hvmm_status_t vcpu_init(struct vcpu* vcpu, vmid_t vmcb_id){
    hvmm_status_t ret = HVMM_STATUS_SUCCESS;

    vcpu->id = (num_of_vcpus++);
    vcpu->vmcb_id = vmcb_id;
    
    //Decide about vmpidr
    vcpu->vmpidr = read_vmpidr();
    vcpu->vmpidr &= 0XFFFFFFFC;

    vcpu->vmpidr |= 0;

    //init general purposed registers.
    core_gprs_init(&(vcpu->gp_regs));

    //init banked registers.
    banked_regs_init(&(vcpu->banked_regs));

    vcpu->state = VCPU_INITIALIZED;
    //vcpu->sched_able_state = VCPU_NOT_SCHEDULABLE;

    //Decide Policy for RTOS : period, deadline 

    vcpu->running_time = 0;

    
    return ret;

}

/*****************************************************
*   SAVE & RESTORE When Context Switching.
******************************************************/

void vcpu_save(struct vcpu *vcpu, struct core_gprs *hw_gp_regs){
    //Read vcpu info from H/W 
    core_gprs_save_(&(vcpu->gp_regs), hw_gp_regs);
    banked_regs_save(&(vcpu->banked_regs));

    vgic_save_status(&(vcpu->status));

}

void vcpu_restore(struct vcpu *vcpu, struct core_gprs *hw_gp_regs){
    //Write vcpu info to H/W 
    core_gprs_restore_(&(vcpu->gp_regs), hw_gp_regs);
    banked_regs_restore(&(vcpu->banked_regs));

    /**************************************************
    *   Also Restore VM's info (memory registers)  => guest_hw.c (198) 
    ***************************************************/

    write_vbar(GET_VBAR(vcpu->vmcb_id));
    write_ttbr0(GET_TTBR0(vcpu->vmcb_id));
    write_ttbr1(GET_TTBR1(vcpu->vmcb_id));
    write_ttbcr(GET_TTBCR(vcpu->vmcb_id));
    write_sctlr(GET_SCTLR(vcpu->vmcb_id));

    vgic_restore_status(&(vcpu->status), vcpu->vmcb_id);

}

