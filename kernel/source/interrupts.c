#include <stdio.h>
#include "assembly_functions.h"
#include "entrypoint.h"
#include "graphics.h"
#include "interrupts.h"
#include "queue.h"

Queue keyboard_queue;
Queue mouse_queue;

void wait_input_buffer_available(void)
{
	while (1)
	{
		if ((in_8bit(STATUS_PORT) & INPUT_BUFFER_STATE) == 0)
		{
			break;
		}
	}
}

void initialize_pic(void)
{
	out_8bit(PIC0_IMR, 0xFF); // disable all interrupts
	out_8bit(PIC1_IMR, 0xFF); // disable all interrupts
	out_8bit(PIC0_ICW1, 0x11); // edge trigger mode
	out_8bit(PIC0_ICW2, 0x20); // irq0: int 0x20 ~ irq7: int 0x27
	out_8bit(PIC0_ICW3, 1 << 2); // irq2: pic1
	out_8bit(PIC0_ICW4, 0x01); // nonbuffer mode
	out_8bit(PIC1_ICW1, 0x11); // edge trigger mode
	out_8bit(PIC1_ICW2, 0x28); // irq8: int 0x28 ~ irq15: int 0x2F
	out_8bit(PIC1_ICW3, 2); // irq2: pic1
	out_8bit(PIC1_ICW4, 0x01); // nonbuffer mode
	out_8bit(PIC0_IMR, 0xFB); // disable all interrupts except pic1
	out_8bit(PIC1_IMR, 0xFF); // disable all interrupts
}

void initialize_keyboard_controller(void)
{
	wait_input_buffer_available();
	out_8bit(COMMAND_PORT, WRITE_MODE);
	wait_input_buffer_available();
	out_8bit(DATA_PORT, KEYBOARD_INTERRUPT_ENABLE | MOUSE_INTERRUPT_ENABLE | SYSTEM_FLAG | KEYBOARD_TRANSLATION);
}

void enable_mouse(MouseData *mouse_data)
{
	mouse_data->phase = 0;
	wait_input_buffer_available();
	out_8bit(COMMAND_PORT, SEND_TO_MOUSE);
	wait_input_buffer_available();
	out_8bit(DATA_PORT, ENABLE_REPORTING);
}

void keyboard_interrupt_handler(__attribute__((unused))int *esp)
{
	out_8bit(PIC0_OCW2, PIC_VECTOR_OFFSET + 1);
	enqueue(in_8bit(DATA_PORT), &keyboard_queue);
}

void mouse_interrupt_handler(__attribute__((unused))int *esp)
{
	out_8bit(PIC1_OCW2, PIC_VECTOR_OFFSET + 4);
	out_8bit(PIC0_OCW2, PIC_VECTOR_OFFSET + 2);
	enqueue(in_8bit(DATA_PORT), &mouse_queue);
}

int decode_mouse(unsigned char data, MouseData *mouse_data)
{
	switch (mouse_data->phase)
	{
	case 0:
		if (data == ACK)
		{
			mouse_data->phase++;
		}
		break;
	case 1:
		if ((data & (X_OVERFLOW | Y_OVERFLOW | SYNC)) == SYNC)
		{
			mouse_data->phase++;
			mouse_data->buffer[0] = data;
		}
		break;
	case 2:
		mouse_data->phase++;
		mouse_data->buffer[1] = data;
		break;
	case 3:
		mouse_data->phase = 1;
		mouse_data->buffer[2] = data;
		mouse_data->button = mouse_data->buffer[0] & (BUTTON_LEFT | BUTTON_RIGHT | BUTTON_MIDDLE);
		mouse_data->x = mouse_data->buffer[1];
		if ((mouse_data->buffer[0] & X_SIGN) != 0)
		{
			mouse_data->x |= SIGN_EXTENSION_MASK;
		}

		mouse_data->y = mouse_data->buffer[2];
		if ((mouse_data->buffer[0] & Y_SIGN) != 0)
		{
			mouse_data->y |= SIGN_EXTENSION_MASK;
		}
		mouse_data->y *= -1;
		return 1;
	}
	return 0;
}