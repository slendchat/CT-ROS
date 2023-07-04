#define MMU_ENABLED 0b1
#define MMU_DISABLED 0b0

//mask int, selectEL2h
#define SPSR_EL2_VAL (7 << 6) | (0b1001) 
#define SPSR_EL1_VAL (7 << 6) | (0b0101) 

#define HCR_EL2_VAL (3 << 28) | (1 << 11) | (1 << 31)   // 1<<31 to make it 64bit
#define SCR_VAL (1 << 10) | (3 << 4) | (1 << 0)
#define SCTRL_EL1_VAL (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11) | (MMU_DISABLED)
#define SCTRL_EL2_VAL (3 << 28) | (3 << 22) | (1 << 18) | (1 << 16) | (1 << 11) | (3 << 4) | (MMU_DISABLED)
#define CPACR_VAL (3 << 20)