#ifndef __ARCH_TYPES_H__
#define __ARCH_TYPES_H__

typedef int                 int32_t;
typedef unsigned int        uint32_t;
typedef unsigned short      uint16_t;
typedef unsigned long long  uint64_t;
typedef unsigned char       uint8_t;

typedef uint8_t     vmid_t;
typedef uint64_t    vm_ttb64_t;
typedef uint32_t    vm_ttb32_t;

typedef uint64_t    vm_runtime64_t;
typedef uint32_t    vm_runtime32_t;

typedef uint8_t     vcpu_id_t;    

typedef uint32_t    sched32_t;
typedef uint64_t    sched64_t;

typedef uint32_t    regs32_t;
typedef uint64_t    regs64_t;

typedef uint32_t    mem32_t;
typedef uint64_t    mem64_t;
#endif
