#include "vmcb.h"

static int num_of_vms = 0;

void vmcb_init(vmcb_t *vm){
    
    /*************************************************************
    *   Todo :  1. Init the name, type of VM.
    *           2. Init the vcpu.
    *           3. Init memory (guest_memmap, ttbr, vttbr, vttbcr)
    *           4. Init irq (mapping info, virq_status)
    *************************************************************/

    //Todo. 1 : Init the name, type of VM.
    //vm->name = "Linux etc";   
    vm->id = (num_of_vms++);
    vm->state = VMCB_INIT;

    vm->vbar  = 0;
    vm->ttbr0 = 0;
    vm->ttbr1 = 0;
    vm->ttbcr = 0;
    vm->sctlr = 0;
    
    //Todo. 2 : Init the vcpu.    
    vcpu_init(&(vm->vcpus), vm->id);


    /*Get memory and irq from vmcb_config.h*/

    //Todo. 3 : memory
    vm->guest_memmap = get_memory(vm->id);    

    //Todo. 4 : Irq
    vm->_guest_virqmap = get_interrupt(vm->id);


    vm->running_time = 0;
    vm->actual_running_time = 0;

    VMCB_REGIST(vm); 
    vmcb_start(vm->id);
}

void vmcb_delete(vmid_t vmid){
    //Delete vmcb's config(memory, interrupt..) from hypervisor.
    vmcb_stop(vmid); 
}

void vmcb_start(vmid_t vmid){

    //Register vcpu to Scheduler with API.
}

void vmcb_stop(vmid_t vmid){
    //Unregister vcpus from Scheduler.
}

void set_pmemmap(struct physical_memmap *memmap){

    /**********************************************************
    *   Todo :  1. Get the base and offset of vm from outside.
    *           2. assign to the base and offset to 
    *              the bellow base and offset variables.
    **********************************************************/
    mem32_t base, offset;

    memmap->mem_base = base;
    memmap->mem_offset = offset;
}


