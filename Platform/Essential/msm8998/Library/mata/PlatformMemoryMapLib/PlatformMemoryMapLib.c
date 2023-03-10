#include <Library/BaseLib.h>
#include <Library/PlatformMemoryMapLib.h>

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
    /* Name               Address     Length      HobOption        ResourceAttribute    ArmAttributes
                                                          ResourceType          MemoryType */

    /* DDR Regions */
    {"RAM Partition",     0x80000000, 0x01AC0000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    {"HLOS 1",            0x81AC0000, 0x03C40000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"Runtime Data",      0x85700000, 0x00080000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, WRITE_BACK_XN},
    {"Runtime Code",      0x85780000, 0x00080000, AddMem, SYS_MEM, SYS_MEM_CAP, RtCode, WRITE_BACK_XN},
    {"Hypervisor",        0x85800000, 0x00600000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, NS_DEVICE},
    {"MPSS_EFS",          0x85E00000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"SMEM",              0x86000000, 0x00200000, AddMem, MEM_RES, WRITE_COMBINEABLE, Reserv, UNCACHED_UNBUFFERED},
    {"TZ",                0x86200000, 0x00400000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, NS_DEVICE},
    // secapp-region
    {"TZApps",            0x86600000, 0x02200000, NoHob,  SYS_MEM, SYS_MEM_CAP, Reserv, NS_DEVICE},
    // no qseecom_mem found in dt
    {"TGCM",              0x87B00000, 0x01400000, AddMem, MEM_RES, WRITE_COMBINEABLE, Reserv, UNCACHED_UNBUFFERED_XN},
    {"HLOS 2",            0x88F00000, 0x01E00000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},

    // not sure about this, but the original value in edk2-msm8998 doesn't make sense

	  // {"PIL_REGION",        0x8AD00000, 0x0AB00000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    // test
    {"PIL_REGION",        0x8AB00000, 0x0AD15000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"HLOS 3",            0x95800000, 0x07B30000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    {"DBI Dump",          0x9D330000, 0x000D0000, NoHob,  MMAP_IO, INITIALIZED, Reserv, UNCACHED_UNBUFFERED_XN},
    {"Display Reserved",  0x9D400000, 0x02400000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_THROUGH_XN},
    {"FV Region",         0x9F800000, 0x00400000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"HLOS 4",            0x9FC00000, 0x00300000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"SEC Heap",          0x9FF00000, 0x0008C000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"CPU Vectors",       0x9FF8C000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"MMU PageTables",    0x9FF8D000, 0x00003000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"UEFI Stack",        0x9FF90000, 0x00040000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},

    // Note: Runtime memory has to be on an alignment of 0x10000
    {"RSRV1",             0x9FFD0000, 0x0000A000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"TPMControl",        0x9FFDA000, 0x00003000, AddMem, MEM_RES, WRITE_COMBINEABLE, Reserv, UNCACHED_UNBUFFERED_XN},
    {"Reset Data",        0x9FFDD000, 0x00004000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"RSRV3",             0x9FFE1000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Capsule Header",    0x9FFE2000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"RSRV2",             0x9FFE3000, 0x00014000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Log Buffer",        0x9FFF7000, 0x00008000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Info Blk",          0x9FFFF000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},

    /* RAM partition regions */
    {"DXE Heap",          0xA0000000, 0x2E000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    {"UEFI FD",           0xCE000000, 0x02000000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},

    /* 4GiB Memory */
    {"RAM Partition",     0xD0000000, 0x0AE4C0000, Mem4G,  SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    /* 6GiB Memory */
    {"RAM Partition",     0xD0000000, 0x030000000, Mem6G,  SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    {"RAM Partition",     0x100000000,0x0BD8C0000, Mem6G,  SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},

    /* Other memory regions */
    {"IMEM Base",         0x14680000, 0x00040000,  NoHob,  MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"IMEM Cookie Base",  0x146BF000, 0x00001000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"QDSS_STM",          0x16000000, 0x01000000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},

    /* Register regions */
    {"BOOT_CONFIG",       0x00070000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"GCC CLK CTL",       0x00100000, 0x000B0000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"UFS_RUMI",          0x00620000, 0x00020000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"RPM MSG RAM",       0x00778000, 0x00008000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SECURITY CONTROL",  0x00780000, 0x00007000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"PRNG_CFG_PRNG",     0x00790000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_SLP_CNTR",     0x010A3000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_TSENS0",       0x010AA000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_TSENS0_TM",    0x010AB000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_PSHOLD",       0x010AC000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_TSENS1",       0x010AD000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_TSENS1_TM",    0x010AE000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"A1_NOC",            0x01680000, 0x00009000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"PCIE WRAPPER AHB",  0x01C00000, 0x00007000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"UFS UFS REGS",      0x01DA0000, 0x00020000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"CRYPTO0 CRYPTO",    0x01DC0000, 0x00040000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"TCSR_TCSR_REGS",    0x01FC0000, 0x00026000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"TLMM CSR",          0x03400000, 0x00C00000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"GPMU_DRAM",         0x05026000, 0x00002000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"GPMU_BLOCK0",       0x0502A000, 0x00002000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"GPU_ISENSE",        0x05030000, 0x00002000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"GPUCC",             0x05065000, 0x00009000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"QDSS_QDSS",         0x06000000, 0x00100000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"HMSS_QLL",          0x06400000, 0x00200000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"PMIC ARB SPMI",     0x08000000, 0x02800000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"USB30_PRIM",        0x0A800000, 0x0011B000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"USB_RUMI",          0x0A920000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"PERIPH_SS",         0x0C000000, 0x00200000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MMSS",              0x0C800000, 0x00800000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"APCS_CC",           0x17800000, 0x00100000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"QTIMER",            0x17900000, 0x00030000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"APCS_GIC500_GICD",  0x17A00000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"APCS_GIC500_GICR",  0x17B00000, 0x00100000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"APCS_GIC500_GICC",  0x17C00000, 0x00040000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"PCIE WRAPPER AXI",  0x1B000000, 0x01000000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},

    /* Terminator for MMU */
    {"Terminator", 0, 0, 0, 0, 0, 0, 0}};

ARM_MEMORY_REGION_DESCRIPTOR_EX *GetPlatformMemoryMap()
{
  return gDeviceMemoryDescriptorEx;
}