#ifndef __VMCB_H_
#define __VMCB_H_

#include <hvmm_types.h>
#include <vgic.h>
#include <guest_hw.h>
#include <vcpu.h>
#include <lpae.h>

/****************************************************
*   Bellow Header(vmcb_config.h) is just for before DTB
*   This file contains some data for booting vm & vmm
****************************************************/
#include <vmcb_config.h>

#define MAX_SIZE_OF_VM_NAME 32

struct physical_memmap{
    //base address of vm in physical memory
    mem32_t mem_base;

    //offset from base address (size of vm) in physical memory
    mem32_t mem_offset;
};


typedef struct vmcb{
    
    //vcpus which assigned to this vm.
    struct vcpu vcpus;

    //id, name that this vm have assigned.
    vmid_t id;
    char name[MAX_SIZE_OF_VM_NAME];

    //state of vm
    vmcb_state_t state;
    
    //vttbr(virtual Translation Table Base Register) used in stage-2 Address Translation
    union lpaed *vttbr;

    //ttbr(Translation Table Base Register) used in stage-1 Address Translation
    vm_ttb32_t ttbr;

    //vttbcr(Virtual Translation Table Base Control Register) 
    vm_ttb32_t vttbcr;

    //virq vm has.
    struct vgic_status status;


    //irq mapping info used only when vm boot
    struct guest_virqmap _guest_virqmap;

    //memory mapping info used only when vm boot
    struct memmap_desc **guest_memmap;
    


    //guest_type(General Purposed , RTOS, ...)
    vm_type_t vm_type;

    //physical memory mapping
    //struct physical_memmap memmap;
    
    //the time from boot
    vm_runtime64_t running_time;

    //actually during time when run
    vm_runtime64_t actual_running_time;
                
} vmcb_t;



// Just setting variables in vmcb & vcpu
void vmcb_init(vmcb_t *vm);

//Deleting vmcb from this hypervisor (vmcb & vcpu)
void vmcb_delete(vmid_t vmid);

//Regist this vmcb & vcpu to be scheduled 
void vmcb_start(vmid_t vmid);

//Just Change this vm & vcpu to be not scheduled
void vmcb_stop(vmid_t vmid);

void set_pmemmap(struct physical_memmap *memmap);

/********************************************
*   Array for VMCBs
********************************************/
static vmcb_t *vmcbs[2];
static uint32_t vmcbs_number = 0;

#endif // __VMCB_H__ 
