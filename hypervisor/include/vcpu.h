#ifndef __VCPU_H__
#define __VCPU_H__

#include <vcpu_regs.h>
#include <hvmm_types.h>
#include <interrupt.h>

#define MAX_SIZE_OF_VM_NAME 32

struct vcpu{

    //id assigned to vcpu
    vcpu_id_t id;

    //id assigned to vcpu from vmcb
    vcpu_id_t id_from_vmcb;

    //general purposed registers
    struct core_gprs gp_regs;

    //banked registers
    struct banked_regs banked_regs; 
    
    //state of vcpu
    vcpu_state_t state;

    //schedulable state of vcpu
    //vcpu_sched_able_state_t sched_able_state;

    sched32_t period;
    sched32_t deadline;

    sched32_t timeslice;

    regs32_t vmpidr;

    //the time from boot
    vm_runtime64_t running_time;

};

//Init vcpu 
hvmm_status_t vcpu_init(struct vcpu* vcpu, vcpu_id_t id_from_vmcb_);

//Save context of vcpu when context switching
void vcpu_save(struct vcpu *vcpu);

//Resotre context of vcpu when context switching
void vcpu_restore(struct vcpu *vcpu);

#endif /* __VCPU_H__ */

