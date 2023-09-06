#include "printf.h"
#include "utils.h"
void welcomeScreen()
{
    char *welcome = "\n\r░█░█░█▀▀░█░░░█▀▀░█▀█░█▄█░█▀▀░░░▀█▀░█▀█░░░█▀▄░█▀█░▀█▀░░░█▀█░█▀▀\n\r░█▄█░█▀▀░█░░░█░░░█░█░█░█░█▀▀░░░░█░░█░█░░░█▀▄░█▀▀░░█░░░░█░█░▀▀█\n\r░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░▀░░▀▀▀░░░▀░▀░▀░░░▀▀▀░░░▀▀▀░▀▀▀\n\r";
    char *cat_sleepin = "      |\\      _,,,---,,_\n\rZZZzz /,`.-'`'    -.  ;-;;,_\n\r     |,4-  ) )-,_. ,\\ (  `'-'\n\r    '---''(_/--'  `-'\\_)  ARTHUR's General Purpose OS\n\rart by Felix Lee\n\r";
    printf(welcome);
    printf("\n\n\r");
    printf(cat_sleepin);
    printf("\n\n\r");
    printf("Raspberry PI General Purpose OS initializing...\n\r");
    printf("Board[ RPI 3B+ ]\n\r");
    printf("Exception Level[ %d ]\n\r",get_el());
    printf("Processor ID[ %d ]\n\r",get_pid());
    printf("Initializing...\n\n\r");
}