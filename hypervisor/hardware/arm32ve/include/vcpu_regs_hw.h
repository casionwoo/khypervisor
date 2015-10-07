#ifndef __VCPU_REGS_HW_H__
#define __VCPU_REGS_HW_H__

#include <vcpu_regs.h>

void banked_regs_save_hardware(struct banked_regs * regs);
void banked_regs_restore_hardware(struct banked_regs *regs);

#endif //__VCPU_REGS_HW_H__


