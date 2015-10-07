#include <vmcb_macro.h>

void VMCB_REGIST(struct vmcb *vmcb){
    vmcbs[vmcbs_number++] = vmcb;
}
//return current vmcb
static struct vmcb * GET_CURRENT_VMCB(vmid_t vmid){
    int i = 0;
    for(i = 0 ; i < vmcbs_number ; i++){
        if(vmcbs[i]->id == vmid)
            return vmcbs[i];
    }
}

//return current vmcb->vttbr
union lpaed* GET_VTTBR(vmid_t vmid){
    return GET_CURRENT_VMCB(vmid)->vttbr;
}

//return current vmcb->ttbr0
vm_ttb32_t GET_TTBR0(vmid_t vmid){
    return GET_CURRENT_VMCB(vmid)->ttbr0;
}

//return current vmcb->ttbr1
vm_ttb32_t GET_TTBR1(vmid_t vmid){
    return GET_CURRENT_VMCB(vmid)->ttbr1;
}

//return current vmcb->ttbcr
vm_ttb32_t GET_TTBCR(vmid_t vmid){
    return GET_CURRENT_VMCB(vmid)->ttbcr;
}

//return current vmcb->sctlr
vm_ttb32_t GET_SCTLR(vmid_t vmid){
    return GET_CURRENT_VMCB(vmid)->sctlr;
}

//return current vmcb->vttbcr
vm_ttb32_t GET_VBAR(vmid_t vmid){
    return GET_CURRENT_VMCB(vmid)->vbar;
}

/*
//return current vmcb->vttbcr
vm_ttb32_t GET_VTTBCR(vmid_t vmid){
    return GET_CURRENT_VMCB(vmid)->vttbcr;
}
*/

