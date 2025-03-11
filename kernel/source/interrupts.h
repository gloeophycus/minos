#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#define PIC_VECTOR_OFFSET 0x60
#define KEYBOARD_DATA_PORT 0x0060

enum PIC0 // programmable interrupt controller
{
	PIC0_ICW1 = 0x0020, // iterrupt control word
	PIC0_ICW2 = 0x0021,
	PIC0_ICW3 = 0x0021,
	PIC0_ICW4 = 0x0021,
	PIC0_OCW2 = 0x0020, // operation control word
	PIC0_IMR = 0x0021, // interrupt mask register

};

enum PIC1
{
	PIC1_ICW1 = 0x00A0,
	PIC1_ICW2 = 0x00A1,
	PIC1_ICW3 = 0x00A1,
	PIC1_ICW4 = 0x00A1,
	PIC1_OCW2 = 0x00A0,
	PIC1_IMR = 0x00A1,
};

void initialize_pic(void);
void keyboard_interrupt_handler(__attribute__((unused))int *esp);
void mouse_interrupt_handler(__attribute__((unused))int *esp);

#endif