#ifndef __VCPU_H__
#define __VCPU_H__

#include "armv7_p15.h"
#include <vcpu_regs.h>
#include <hvmm_types.h>
#include <interrupt.h>
#include <vgic.h>

#define MAX_SIZE_OF_VM_NAME 32

struct vcpu{

    //id assigned to vcpu
    vcpu_id_t id;

    //VMCB's ID
    vmid_t vmcb_id;

    //Virtual Multiprocessor Affinity Register
    regs32_t vmpidr;

    //general purposed registers
    struct core_gprs gp_regs;

    //banked registers
    struct banked_regs banked_regs; 
    
    //state of vcpu
    vcpu_state_t state;

    //virq vm has.
    struct vgic_status status;

    //schedulable state of vcpu
    //vcpu_sched_able_state_t sched_able_state;

    sched32_t period;
    sched32_t deadline;

    sched32_t timeslice;

    //the time from boot
    vm_runtime64_t running_time;

};

//Init vcpu 
hvmm_status_t vcpu_init(struct vcpu* vcpu, vmid_t vmcb_id);

//Save context of vcpu when context switching
void vcpu_save(struct vcpu *vcpu, struct core_gprs *hw_gp_regs);

//Resotre context of vcpu when context switching
void vcpu_restore(struct vcpu *vcpu, struct core_gprs *hw_gp_regs);

#endif /* __VCPU_H__ */

