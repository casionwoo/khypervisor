#ifndef __HVMM_TYPES_H__
#define __HVMM_TYPES_H__

#include <arch_types.h>
#define VMID_INVALID    0xFF
#define PIRQ_INVALID    0xFFFFFFFF
#define VIRQ_INVALID    PIRQ_INVALID

typedef enum hvmm_status {
    HVMM_STATUS_SUCCESS             =  0,
    HVMM_STATUS_UNKNOWN_ERROR       = -1,
    HVMM_STATUS_UNSUPPORTED_FEATURE = -2,
    HVMM_STATUS_BUSY                = -3,
    HVMM_STATUS_BAD_ACCESS          = -4,
    HVMM_STATUS_NOT_FOUND           = -5,
    HVMM_STATUS_IGNORED             = -6
} hvmm_status_t;

typedef enum vm_type {
    VM_GENERAL_PURPOSED = 0,
    VM_RTOS             = 1
} vm_type_t;

//typedef uint8_t vmid_t;


/********************************************
*
*
*
*
*
********************************************/
/*
typedef enum vcpu_sched_able_state{
    VCPU_SCHEDULABLE        = 0,
    VCPU_NOT_SCHEDULABLE    = 1
} vcpu_sched_able_state_t;
*/
typedef enum vcpu_state {
    VCPU_RUNNING      = 0,
    VCPU_SLEEP        = 1,
    VCPU_WAIT         = 2,
    VCPU_INITIALIZED  = 3
} vcpu_state_t;

typedef enum vmcb_state {
    VMCB_INIT       = 0,
    VMCB_RUNNING    = 1,
    VMCB_STOP       = 2,
    VMCB_DELETE     = 3
} vmcb_state_t;

#endif

