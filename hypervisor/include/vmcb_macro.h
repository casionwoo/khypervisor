#ifndef __MACRO_H__
#define __MACRO_H__

#include <vcpu.h>
#include <hvmm_types.h>
#include <lpae.h>
#include <vmcb.h>

#define SIZE_OF_VMCBS   10

static struct vmcb *vmcbs[SIZE_OF_VMCBS];
static uint32_t vmcbs_number = 0;

void VMCB_REGIST(struct vmcb *vmcb);

//return current vmcb
static struct vmcb* GET_CURRENT_VMCB(vmid_t vmid);

//return current vmcb->vttbr
union lpaed* GET_VTTBR(vmid_t vmid);

//return current vmcb->ttbr0
vm_ttb32_t GET_TTBR0(vmid_t vmid);

//return current vmcb->ttbr1
vm_ttb32_t GET_TTBR1(vmid_t vmid);

//return current vmcb->ttbcr
vm_ttb32_t GET_TTBCR(vmid_t vmid);

//return current vmcb->sctlr
vm_ttb32_t GET_SCTLR(vmid_t vmid);

//return current vmcb->vttbcr
vm_ttb32_t GET_VBAR(vmid_t vmid);

/*
//return current vmcb->vttbcr
vm_ttb32_t GET_VTTBCR(vmid_t vmid);
*/
#endif //__MACRO_H__
