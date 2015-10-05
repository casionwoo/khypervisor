#ifndef __VMCB_CONFIG_H__
#define __VMCB_COBFIG_H__

#include <k-hypervisor-config.h>
//#include <guest.h>
//#include <interrupt.h>
//#include <timer.h>
//#include <vdev.h>
#include <memory.h>
#include <gic_regs.h>
//#include <test/tests.h>
//#include <smp.h>
#include <vmcb.h>


#define DEBUG
#include "hvmm_trace.h"
#include <log/uart_print.h>


#define DECLARE_VIRQMAP_(name, _pirq, _virq)    \
    do {                                       \
        name.map[_pirq].virq = _virq;          \
        name.map[_virq].pirq = _pirq;          \
    } while (0)

extern uint32_t _guest0_bin_start;
extern uint32_t _guest0_bin_end;
extern uint32_t _guest1_bin_start;
static struct guest_virqmap guest_virqmapping;

/**
 * \defgroup Guest_memory_map_descriptor
 *
 * Descriptor setting order
 * - label
 * - Intermediate Physical Address (IPA)
 * - Physical Address (PA)
 * - Size of memory region
 * - Memory Attribute
 * @{
 */


//static uint32_t _timer_irq;

/*********************************************************************
*  Bellow functions need vmid now but this should be removed later.
**********************************************************************/
void setup_memory_from_config(vmid_t vmid);
void setup_interrupt_from_config(vmid_t vmid);
//void setup_timer(vmid_t vmid);

struct memmap_desc ** get_memory(vmid_t vmid);
struct guest_virqmap get_interrupt(vmid_t vmid);
//uint32_t get_timer(vmid_t vmid);

#endif /* __VMCB_CONFIG_H__ */
