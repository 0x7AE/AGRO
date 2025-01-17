/*
   Provided by: 
   http://www.electronicwings.com

   Original code modified to suit the project's needs

 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "include/io.h"
#include "include/lcd.h"


// LED pin
// #define LED_PIN1        PB7
// #define LED_PIN2        PB6
// #define LED_PIN3        PB5
// #define LED_PIN4        PB4
// #define LED_PORT        PORTB
// #define LED_DDR         DDRB

// Keypad lay out mapping
unsigned char keypad[4][4] = {
    {'1', '2', '3', '-'},
    {'4', '5', '*'}
};

// Function declarations
char keyfind();

// Keypad scanning function
char keyfind()
{
    unsigned char rowloc, colloc;

    while (1)
    {
        KEYPAD_DDR |= (1 << OUTPUT4) | (1 << OUTPUT3) | (1 << OUTPUT2) | (1 << OUTPUT1); // Rows as output
        KEYPAD_PORT = 0xFF; // Enable pull-ups on columns
   
        do
        {
            KEYPAD_PORT &= 0x0F; // Mask PORT for column read only
            asm("NOP");
            colloc = (KEYPAD_PIN & 0xF0) >> 4; // Read upper nibble for columns
        } while (colloc == 0x0F); // Wait for all keys to be released

        do
        {
            _delay_ms(20); // Debounce delay
            colloc = (KEYPAD_PIN & 0xF0) >> 4;
        } while (colloc == 0x0F); // Wait for key press stability

        // Check rows
        KEYPAD_PORT = ~(1 << OUTPUT1); // Activate row 1
        asm("NOP");
        colloc = (KEYPAD_PIN & 0xF0) >> 4;
        if (colloc != 0x0F) { rowloc = 0; break; }

        KEYPAD_PORT = ~(1 << OUTPUT2); // Activate row 2
        asm("NOP");
        colloc = (KEYPAD_PIN & 0xF0) >> 4;
        if (colloc != 0x0F) { rowloc = 1; break; }
    }

    // Decode column location
    if (colloc == 0x0E) return keypad[rowloc][0];
    else if (colloc == 0x0D) return keypad[rowloc][1];
    else if (colloc == 0x0B) return keypad[rowloc][2];
    else return keypad[rowloc][3];
}


// int main(void)
// {
// 	// Initialize LED
// 	LED_DDR |= ((1 << LED_PIN1) |  (1 << LED_PIN2) | (1 << LED_PIN3) | (1 << LED_PIN4)) ; // Set PB7 as output

// 	while (1)
// 	{
// 		char key = keyfind(); 
//         if (key == '1')            /* If any key is pressed except blank (' ') */
// 		{
// 			LED_DDR  &= ~(1 << LED_PIN1); // Turn off LED
// 			 // Turn off LED
// 		} else {
//             LED_DDR |= (1 << LED_PIN1);
//         }
//         if (key == '2')            /* If any key is pressed except blank (' ') */
// 		{
// 			LED_DDR  &= ~(1 << LED_PIN2); // Turn off LED
// 			 // Turn off LED
// 		} else {
//             LED_DDR |= (1 << LED_PIN2);
//         }
//         if (key == '3')            /* If any key is pressed except blank (' ') */
// 		{
// 			LED_DDR  &= ~(1 << LED_PIN3); // Turn off LED
// 			 // Turn off LED
// 		} else {
//             LED_DDR |= (1 << LED_PIN3);
//         }      /* Wait for a key press */
// 		if (key == '4')            /* If any key is pressed except blank (' ') */
// 		{
// 			LED_DDR  &= ~(1 << LED_PIN4); // Turn off LED
// 			 // Turn off LED
// 		} else {
//             LED_DDR |= (1 << LED_PIN4);
//         }
//         if (key == '5')            /* If any key is pressed except blank (' ') */
// 		{
// 			LED_DDR  &= ~(1 << LED_PIN2); // Turn off LED
// 			 // Turn off LED
// 		} else {
//             LED_DDR |= (1 << LED_PIN2);
//         }
// 	}
// }