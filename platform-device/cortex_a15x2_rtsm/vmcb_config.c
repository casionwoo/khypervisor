#include <vmcb_config.h>

/*
 * Creates a mapping table between PIRQ and VIRQ.vmid/pirq/coreid.
 * Mapping of between pirq and virq is hard-coded.
 */

static struct memmap_desc _guest_md_empty[] = {
    {       0, 0, 0, 0,  0},
};
/*  label, ipa, pa, size, attr */
static struct memmap_desc _guest0_device_md[] = {
    { "sysreg", 0x1C010000, 0x1C010000, SZ_4K, MEMATTR_DM },
    { "sysctl", 0x1C020000, 0x1C020000, SZ_4K, MEMATTR_DM },
    { "aaci", 0x1C040000, 0x1C040000, SZ_4K, MEMATTR_DM },
    { "mmci", 0x1C050000, 0x1C050000, SZ_4K, MEMATTR_DM },
    { "kmi", 0x1C060000, 0x1C060000,  SZ_64K, MEMATTR_DM },
    { "kmi2", 0x1C070000, 0x1C070000, SZ_64K, MEMATTR_DM },
    { "v2m_serial0", 0x1C090000, 0x1C0A0000, SZ_4K, MEMATTR_DM },
    { "v2m_serial1", 0x1C0A0000, 0x1C090000, SZ_4K, MEMATTR_DM },
    { "v2m_serial2", 0x1C0B0000, 0x1C0B0000, SZ_4K, MEMATTR_DM },
    { "v2m_serial3", 0x1C0C0000, 0x1C0C0000, SZ_4K, MEMATTR_DM },
    { "wdt", 0x1C0F0000, 0x1C0F0000, SZ_4K, MEMATTR_DM },
    { "v2m_timer01(sp804)", 0x1C110000, 0x1C110000, SZ_4K,
            MEMATTR_DM },
    { "v2m_timer23", 0x1C120000, 0x1C120000, SZ_4K, MEMATTR_DM },
    { "rtc", 0x1C170000, 0x1C170000, SZ_4K, MEMATTR_DM },
    { "clcd", 0x1C1F0000, 0x1C1F0000, SZ_4K, MEMATTR_DM },
    { "gicc", CFG_GIC_BASE_PA | GIC_OFFSET_GICC,
            CFG_GIC_BASE_PA | GIC_OFFSET_GICVI, SZ_8K,
            MEMATTR_DM },
    { "SMSC91c111i", 0x1A000000, 0x1A000000, SZ_16M, MEMATTR_DM },
    { "simplebus2", 0x18000000, 0x18000000, SZ_64M, MEMATTR_DM },
    { 0, 0, 0, 0, 0 }
};

static struct memmap_desc _guest1_device_md[] = {
    { "uart", 0x1C090000, 0x1C0B0000, SZ_4K, MEMATTR_DM },
    { "sp804", 0x1C110000, 0x1C120000, SZ_4K, MEMATTR_DM },
    { "gicc", 0x2C000000 | GIC_OFFSET_GICC,
       CFG_GIC_BASE_PA | GIC_OFFSET_GICVI, SZ_8K, MEMATTR_DM },
    {0, 0, 0, 0, 0}
};

#if _SMP_
static struct memmap_desc _guest2_device_md[] = {
    { "uart", 0x1C090000, 0x1C0C0000, SZ_4K, MEMATTR_DM },
    { "sp804", 0x1C110000, 0x1C120000, SZ_4K, MEMATTR_DM },
    { "gicc", 0x2C000000 | GIC_OFFSET_GICC,
       CFG_GIC_BASE_PA | GIC_OFFSET_GICVI, SZ_8K, MEMATTR_DM },
    {0, 0, 0, 0, 0}
};

static struct memmap_desc _guest3_device_md[] = {
    { "uart", 0x1C090000, 0x1C0C0000, SZ_4K, MEMATTR_DM },
    { "sp804", 0x1C110000, 0x1C120000, SZ_4K, MEMATTR_DM },
    { "gicc", 0x2C000000 | GIC_OFFSET_GICC,
       CFG_GIC_BASE_PA | GIC_OFFSET_GICVI, SZ_8K, MEMATTR_DM },
    {0, 0, 0, 0, 0}
};
#endif

/**
 * @brief Memory map for guest 0.
 */
static struct memmap_desc _guest0_memory_md[] = {
    {"start", 0x00000000, 0, 0x40000000,
     MEMATTR_NORMAL_OWB | MEMATTR_NORMAL_IWB
    },
    {0, 0, 0, 0,  0},
};

/**
 * @brief Memory map for guest 1.
 */
static struct memmap_desc _guest1_memory_md[] = {
    /* 256MB */
    {"start", 0x00000000, 0, 0x10000000,
     MEMATTR_NORMAL_OWB | MEMATTR_NORMAL_IWB
    },
    {0, 0, 0, 0,  0},
};

/* Memory Map for Guest 0 */
static struct memmap_desc *_guest0_mdlist[] = {
    _guest0_device_md,   /* 0x0000_0000 */
    _guest_md_empty,     /* 0x4000_0000 */
    _guest0_memory_md,
    _guest_md_empty,     /* 0xC000_0000 PA:0x40000000*/
    0
};

/* Memory Map for Guest 1 */
static struct memmap_desc *_guest1_mdlist[] = {
    _guest1_device_md,
    _guest_md_empty,
    _guest1_memory_md,
    _guest_md_empty,
    0
};

void setup_interrupt_from_config(vmid_t vmid)
{
    int j;
    struct virqmap_entry *map;

    map = guest_virqmapping.map;
    for (j = 0; j < MAX_IRQS; j++) {
        map[j].enabled = GUEST_IRQ_DISABLE;
        map[j].virq = VIRQ_INVALID;
        map[j].pirq = PIRQ_INVALID;
    }

    /*
     *  vimm-0, pirq-69, virq-69 = pwm timer driver
     *  vimm-0, pirq-32, virq-32 = WDT: shared driver
     *  vimm-0, pirq-34, virq-34 = SP804: shared driver
     *  vimm-0, pirq-35, virq-35 = SP804: shared driver
     *  vimm-0, pirq-36, virq-36 = RTC: shared driver
     *  vimm-0, pirq-38, virq-37 = UART: dedicated driver IRQ 37 for guest 0
     *  vimm-0, pirq-43, virq-43 = ACCI: shared driver
     *  vimm-0, pirq-44, virq-44 = KMI: shared driver
     *  vimm-0, pirq-45, virq-45 = KMI: shared driver
     *  vimm-0, pirq-47, virq-47 = SMSC 91C111, Ethernet - etc0
     *  vimm-0, pirq-41, virq-41 = MCI - pl180
     *  vimm-0, pirq-42, virq-42 = MCI - pl180
     *
     *  vimm-1, pirq-39, virq-37 = UART: dedicated driver IRQ 37 for guest 1
     *  vimm-2, pirq,40, virq-37 = UART: dedicated driver IRQ 37 for guest 2
     *  vimm-3, pirq,48, virq-37 = UART: dedicated driver IRQ 38 for guest 3 -ch

     */
    if(vmid == FIRST_GUEST){
        DECLARE_VIRQMAP_(guest_virqmapping, 1, 1);
        DECLARE_VIRQMAP_(guest_virqmapping, 16, 16);
        DECLARE_VIRQMAP_(guest_virqmapping, 17, 17);
        DECLARE_VIRQMAP_(guest_virqmapping, 18, 18);
        DECLARE_VIRQMAP_(guest_virqmapping, 19, 19);
        DECLARE_VIRQMAP_(guest_virqmapping, 31, 31);
        DECLARE_VIRQMAP_(guest_virqmapping, 32, 32);
        DECLARE_VIRQMAP_(guest_virqmapping, 33, 33);
        DECLARE_VIRQMAP_(guest_virqmapping, 34, 34);
        DECLARE_VIRQMAP_(guest_virqmapping, 35, 35);
        DECLARE_VIRQMAP_(guest_virqmapping, 36, 36);
        DECLARE_VIRQMAP_(guest_virqmapping, 37, 38);
        DECLARE_VIRQMAP_(guest_virqmapping, 38, 37);
        DECLARE_VIRQMAP_(guest_virqmapping, 41, 41);
        DECLARE_VIRQMAP_(guest_virqmapping, 42, 42);
        DECLARE_VIRQMAP_(guest_virqmapping, 43, 43);
        DECLARE_VIRQMAP_(guest_virqmapping, 44, 44);
        DECLARE_VIRQMAP_(guest_virqmapping, 45, 45);
        DECLARE_VIRQMAP_(guest_virqmapping, 46, 46);
        DECLARE_VIRQMAP_(guest_virqmapping, 47, 47);
        DECLARE_VIRQMAP_(guest_virqmapping, 69, 69);
    }

    else if(vmid == SECOND_GUEST){
        DECLARE_VIRQMAP_(guest_virqmapping, 39, 37);
    //    DECLARE_VIRQMAP(guest_virqmapping, 2, 40, 37);
    //    DECLARE_VIRQMAP(guest_virqmapping, 3, 48, 37);
    }
}

void setup_memory_from_config(vmid_t vmid)
{

    /*
     * VA: 0x00000000 ~ 0x3FFFFFFF,   1GB
     * PA: 0xA0000000 ~ 0xDFFFFFFF    guest_bin_start
     * PA: 0xB0000000 ~ 0xEFFFFFFF    guest2_bin_start
     */

    if(vmid == FIRST_GUEST)
        _guest0_memory_md[0].pa = (uint64_t)((uint32_t) &_guest0_bin_start);
    else if(vmid == SECOND_GUEST)
        _guest1_memory_md[0].pa = (uint64_t)((uint32_t) &_guest1_bin_start);
}

/** @brief Registers generic timer irqs such as hypervisor timer event
 *  (GENERIC_TIMER_HYP), non-secure physical timer event(GENERIC_TIMER_NSP)
 *  and virtual timer event(GENERIC_TIMER_NSP).
 *  Each interrup source is identified by a unique ID.
 *  cf. "Cortex??-A15 Technical Reference Manual" 8.2.3 Interrupt sources
 *
 *  DEVICE : IRQ number
 *  GENERIC_TIMER_HYP : 26
 *  GENERIC_TIMER_NSP : 30
 *  GENERIC_TIMER_VIR : 27
 *
 *  @note "Cortex??-A15 Technical Reference Manual", 8.2.3 Interrupt sources
 */

 /*
void setup_timer(vmid_t vmid)
{
    _timer_irq = 26; // GENERIC_TIMER_HYP 
}
*/
struct memmap_desc ** get_memory(vmid_t vmid){

    setup_memory_from_config(vmid);

    if(vmid == FIRST_GUEST)
        return _guest0_mdlist;
    else if(vmid == SECOND_GUEST)
        return _guest1_mdlist;
}

struct guest_virqmap get_interrupt(vmid_t vmid){
    
    setup_interrupt_from_config(vmid);

    if(vmid == FIRST_GUEST)
        return guest_virqmapping;
    else if(vmid == SECOND_GUEST)
        return guest_virqmapping;
}


