#ifndef ASSEMBLY_FUNCTIONS_H
#define ASSEMBLY_FUNCTIONS_H

void hlt(void);
void cli(void);
void sti(void);
void sti_hlt(void);
void in_8bit(int port);
void in_16bit(int port);
void in_32bit(int port);
void out_8bit(int port, int data);
void out_16bit(int port, int data);
void out_32bit(int port, int data);
int load_eflags(void);
void store_eflags(int eflags);
void load_gdtr(int limit, int address);
void load_idtr(int limit, int address);
void _keyboard_interrupt_handler(void);
void _mouse_interrupt_handler(void);

#endif