//HCR_EL2 p2487
//SPSR_EL1 p377
//CPACR_EL1 p2411
//SCR_EL3 p2648
//SCTLR_EL1 p2654
// ESR_EL1 p1899 p2431 p2436
#pragma once

#define SCTLR_RESERVED              (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)
#define SCTLR_EE_LITTLE_ENDIAN      (0 << 25)
#define SCTLR_EOE_LITTLE_ENDIAN     (0 << 24)
#define SCTLR_I_CACHE_DISABLED      (0 << 12)
#define SCTLR_D_CACHE_DISABLED      (0 << 2)
#define SCTLR_MMU_DISABLED          (0 << 0)
#define SCTLR_MMU_ENABLED           (1 << 0)

#define SCTLR_VALUE_MMU_DISABLED    (SCTLR_RESERVED | SCTLR_EE_LITTLE_ENDIAN | SCTLR_I_CACHE_DISABLED | SCTLR_D_CACHE_DISABLED | SCTLR_MMU_DISABLED)


#define HCR_RW	    		(1 << 31)
#define HCR_VALUE			HCR_RW


#define SCR_RESERVED	    (3 << 4)
#define SCR_RW				(1 << 10)
#define SCR_NS				(1 << 0)
#define SCR_VALUE	    	(SCR_RESERVED | SCR_RW | SCR_NS)


#define SPSR_MASK_ALL 		(7 << 6)
#define SPSR_64             (0<<4)
#define SPSR_EL1h			(5 << 0)
#define SPSR_VALUE			(SPSR_MASK_ALL | SPSR_EL1h | SPSR_64)

#define ESR_ELX_EC_SHIFT 26
#define ESR_ELX_EC_SVC64 0x15
#define ESR_ELX_EC_DABT_LOW 0x24 //Data Abort from a lower Exception level.

#define CPACR_VAL (3 << 20)