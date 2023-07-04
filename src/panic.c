#include "funcs/printf.h"
volatile void panic()
{
	printf("Kernel panic");
	for(;;);
}