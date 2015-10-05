#include "vcpu.h"

static int num_of_vcpus = 0;

hvmm_status_t vcpu_init(struct vcpu* vcpu, vcpu_id_t id_from_vmcb_){
    hvmm_status_t ret = HVMM_STATUS_SUCCESS;

    vcpu->id = (num_of_vcpus++);
    vcpu->id_from_vmcb = id_from_vmcb_;
    
    //Decide about vmpidr
    
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

void vcpu_save(struct vcpu *vcpu){
    //Read vcpu info from H/W 
    core_gprs_save(&(vcpu->gp_regs));
    banked_regs_save(&(vcpu->banked_regs));
}

void vcpu_restore(struct vcpu *vcpu){
    //Write vcpu info to H/W 
    core_gprs_restore(&(vcpu->gp_regs));
    banked_regs_restore(&(vcpu->banked_regs));
    //Restore ttbr0, ttbr1, vbar, ttbcr, vttbr, sctlr
}

