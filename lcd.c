#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */

#define F_CPU 16000000UL   // Define the CPU frequency for delay calculations

// LCD pin configurations (based on your previous pin definitions)
#define LCD_PORT PORTA
#define LCD_DDR  DDRA
#define LCD_RS    PA1   // Register Select pin
#define LCD_EN    PA2   // Enable pin
#define LCD_D4    PA3   // Data pins for LCD (4-bit mode)
#define LCD_D5    PA4
#define LCD_D6    PA5
#define LCD_D7    PA6

// LCD control functions
void LCD_Command(unsigned char cmnd)
{
	LCD_PORT = (LCD_PORT & 0x0F) | (cmnd & 0xF0);   // Sending upper nibble
	LCD_PORT &= ~ (1 << LCD_RS);       // RS = 0 for command register
	LCD_PORT |= (1 << LCD_EN);         // Enable pulse
	_delay_us(1);
	LCD_PORT &= ~ (1 << LCD_EN);       // Disable pulse
	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | (cmnd << 4);  // Sending lower nibble
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~ (1 << LCD_EN);       // Disable pulse
	_delay_ms(2);
}

void LCD_Char(unsigned char data)
{
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0); // Sending upper nibble
	LCD_PORT |= (1 << LCD_RS);         // RS = 1 for data register
	LCD_PORT |= (1 << LCD_EN);         // Enable pulse
	_delay_us(1);
	LCD_PORT &= ~ (1 << LCD_EN);       // Disable pulse
	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);  // Sending lower nibble
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~ (1 << LCD_EN);       // Disable pulse
	_delay_ms(2);
}

void LCD_Init(void)
{
	LCD_DDR = 0xFF;  // Set LCD port as output
	_delay_ms(20);   // LCD Power ON delay

	LCD_Command(0x02);    // 4-bit mode initialization
	LCD_Command(0x28);    // 2-line, 5x7 matrix in 4-bit mode
	LCD_Command(0x0C);    // Display ON, cursor OFF
	LCD_Command(0x06);    // Increment cursor (shift cursor to right)
	LCD_Command(0x01);    // Clear display screen
	_delay_ms(2);
}

void LCD_String(char *str)
{
	int i;
	for(i = 0; str[i] != 0; i++)   // Send each char of string until NULL
	{
		LCD_Char(str[i]);
	}
}

void LCD_String_xy(char row, char pos, char *str)
{
	if (row == 0 && pos < 16)
		LCD_Command((pos & 0x0F) | 0x80);   // Command for first row and required position < 16
	else if (row == 1 && pos < 16)
		LCD_Command((pos & 0x0F) | 0xC0);   // Command for second row and required position < 16
	LCD_String(str);  // Send string to LCD
}

void LCD_Clear()
{
	LCD_Command(0x01);   // Clear display
	_delay_ms(2);
	LCD_Command(0x80);   // Set cursor at home position
}

int main(void)
{
	LCD_Init();
	LCD_String_xy(0, 0, "Hello");  // Display "Hello" on the first row

	while(1)
	{
		// Keep displaying "Hello" indefinitely
	}
}
