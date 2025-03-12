#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#define PIC_VECTOR_OFFSET 0x60
#define ENABLE_REPORTING 0xF4
#define ACK 0xFA
#define SIGN_EXTENSION_MASK 0xFFFFFF00

enum PIC // programmable interrupt controller
{
	PIC0_ICW1 = 0x0020, // iterrupt control word
	PIC0_ICW2 = 0x0021,
	PIC0_ICW3 = 0x0021,
	PIC0_ICW4 = 0x0021,
	PIC0_OCW2 = 0x0020, // operation control word
	PIC0_IMR = 0x0021, // interrupt mask register
	PIC1_ICW1 = 0x00A0,
	PIC1_ICW2 = 0x00A1,
	PIC1_ICW3 = 0x00A1,
	PIC1_ICW4 = 0x00A1,
	PIC1_OCW2 = 0x00A0,
	PIC1_IMR = 0x00A1,
};

enum KEYBOARD_CONTROLLER_PORT
{
	DATA_PORT = 0x60,
	STATUS_PORT = 0x64,
	COMMAND_PORT = 0x64,
};

enum KEYBOARD_STATUS_REGISTER_BIT
{
	INPUT_BUFFER_STATE = 1 << 1,
};

enum KEYBOARD_CONTROLLER_COMMAND
{
	WRITE_MODE = 0x60,
	SEND_TO_MOUSE = 0xD4,
};

enum KEYBOARD_CONTROLLER_CONFIGURATION_BIT
{
	KEYBOARD_INTERRUPT_ENABLE = 1 << 0,
	MOUSE_INTERRUPT_ENABLE = 1 << 1,
	SYSTEM_FLAG = 1 << 2,
	KEYBOARD_PORT_DISABLE = 1 << 4,
	KEYBOARD_MOUSE_PORT_DISABLE = 1 << 5,
	KEYBOARD_TRANSLATION = 1 << 6,
};

enum MOUSE_PACKET_BIT
{
	BUTTON_LEFT = 1 << 0,
	BUTTON_RIGHT = 1 << 1,
	BUTTON_MIDDLE = 1 << 2,
	SYNC = 1 << 3,
	X_SIGN = 1 << 4,
	Y_SIGN = 1 << 5,
	X_OVERFLOW = 1 << 6,
	Y_OVERFLOW = 1 << 7,
};

typedef struct
{
	int x;
	int y;
	int button;
	int phase;
	unsigned char buffer[3];
} MouseData;


void wait_input_buffer_available(void);
void initialize_pic(void);
void initialize_keyboard_controller(void);
void enable_mouse(MouseData *mouse_data);
void keyboard_interrupt_handler(__attribute__((unused))int *esp);
void mouse_interrupt_handler(__attribute__((unused))int *esp);
int decode_mouse(unsigned char data, MouseData *mouse_data);

#endif