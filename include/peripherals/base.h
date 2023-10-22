#pragma once

#include "mm.h"

#define DEVICE_BASE 		0x3F000000	
#define VA_START 			0xffff000000000000
#define PBASE 			(VA_START + DEVICE_BASE)

#define CORE_CLOCK_SPEED 250*1000000
