#ifndef ASSEMBLY_FUNCTIONS_H
#define ASSEMBLY_FUNCTIONS_H

void hlt(void);
void cli(void);
void sti(void);
void sti_hlt(void);
int in_8bit(int port);
int in_16bit(int port);
int in_32bit(int port);
void out_8bit(int port, int data);
void out_16bit(int port, int data);
void out_32bit(int port, int data);
int read_eflags(void);
void write_eflags(int eflags);
int read_cr0(void);
void write_cr0(int cr0);
void load_gdtr(int limit, int address);
void load_idtr(int limit, int address);
void _keyboard_interrupt_handler(void);
void _mouse_interrupt_handler(void);

#endif