#pragma once
void uart_init(/*int baudrate*/);

void uart_putc(char c);

char uart_getc();

void uart_puts(char* str);

void uart_char_printf(void *p, char c);

void uart_echo();
