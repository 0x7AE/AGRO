#include <avr/io.h>
#include <util/delay.h>

void UART_init(unsigned int baud_rate) {
    // Calculate the UBRR value
    unsigned int ubrr = (F_CPU / 16 / baud_rate) - 1;

    // Set the baud rate (UBRRnL and UBRRnH)
    UBRR0H = (unsigned char)(ubrr >> 8); // High byte of UBRR
    UBRR0L = (unsigned char)(ubrr);      // Low byte of UBRR

    // Enable transmitter (TXEN0) and receiver (RXEN0)
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // Set frame format: 8 data bits, no parity, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
}

void UART_transmit(char data) {
    // Wait for the transmit buffer to be empty
    while (!(UCSR0A & (1 << UDRE0))) {
        // Do nothing until the buffer is ready
    }

    // Load the data into the UART data register
    UDR0 = data;
}

void UART_print(const char *str) {
    // Transmit each character of the string
    while (*str) {
        UART_transmit(*str++);
    }
}


int main(void) 
{

    UART_init(9600); // Initialize UART with 9600 baud rate

    // Set pins 2, 3, 4, and 5 as inputs (PE4, PE5, PG5, PE3)
    PORTE &= ~((1 << PE4) | (1 << PE5) | (1 << PE3));
    PORTG &= ~(1 << PG5);
    // Set pins 6, 7, 8, and 9 as outputs (PH3, PH4, PH5, PH6)
    DDRH |= (1 << PH3) | (1 << PH4);
    DDRH |= (1 << PH5) | (1 << PH6);

    int NumpadInput = 0;

    while(1)
    {

        int NumPrev = NumpadInput;

        int ButtonPress = 0;

        //ROW5
        PORTH |= (1 << PH3);
        if ((PINE & (1 << PE4)))
        {
            NumpadInput = 1;
            ButtonPress = 1;
        }
        if ((PINE & (1 << PE5)))
        {
            NumpadInput = 2;
            ButtonPress = 1;
        }
        if ((PING & (1 << PG5)))
        {
            NumpadInput = 3;
            ButtonPress = 1;
        }
        if ((PINE & (1 << PE3)))
        {
            NumpadInput = 4;
            ButtonPress = 1;
        }
        PORTH &= ~(1 << PH3);


        //ROW2
        PORTD |= (1 << PH4);
        if (PINH & (1 << PE4)) 
        {
            NumpadInput = 5;
            ButtonPress = 1;
        }
        if (PINH & (1 << PE5)) 
        {
            NumpadInput = 6;
            ButtonPress = 1;
        }
        if (PINH & (1 << PG5)) 
        {
            NumpadInput = 7;
            ButtonPress = 1;
        }
        if (PINH & (1 << PE3)) 
        {
            NumpadInput = 8;
            ButtonPress = 1;
        }
        PORTD &= ~(1 << PH4);


        //ROW3
        PORTB |= (1 << PH5);
        if (PINH & (1 << PE4)) 
        {
            NumpadInput = 9;
            ButtonPress = 1;
        }
        if (PINH & (1 << PE5)) 
        {
            NumpadInput = 10;
            ButtonPress = 1;
        }
        if (PINH & (1 << PG5)) 
        {
            NumpadInput = 11;
            ButtonPress = 1;
        }
        if (PINH & (1 << PE3)) 
        {
            NumpadInput = 12;
            ButtonPress = 1;
        }
        PORTB &= ~(1 << PH5);


        //ROW4
        PORTB |= (1 << PH6);
        if (PINH & (1 << PE4)) 
        {
            NumpadInput = 13;
            ButtonPress = 1;
        }
        if (PINH & (1 << PE5)) 
        {
            NumpadInput = 14;
            ButtonPress = 1;
        }
        if (PINH & (1 << PG5)) 
        {
            NumpadInput = 15;
            ButtonPress = 1;
        }
        if (PINH & (1 << PE3)) 
        {
            NumpadInput = 16;
            ButtonPress = 1;
        }
        PORTB &= ~(1 << PH6);

        if (ButtonPress == 0)
        {
            NumpadInput = 0;
        }

        if ((NumpadInput != 0) && (NumpadInput != NumPrev))
        {        
        
            switch(NumpadInput)
            {    
                case(1):
                {
                    UART_print("1\r\n");
                    break;
                }
                case(2):
                {
                    UART_print("2\r\n");
                    break;
                }
                case(3):
                {
                    UART_print("3\r\n");
                    break;
                }
                case(4):
                {
                    UART_print("A\r\n");
                    break;
                }
                case(5):
                {
                    UART_print("4\r\n");
                    break;
                }
                case(6):
                {
                    UART_print("5\r\n");
                    break;
                }
                case(7):
                {
                    UART_print("6\r\n");
                    break;
                }
                case(8):
                {
                    UART_print("B\r\n");
                    break;
                }
                case(9):
                {
                    UART_print("7\r\n");
                    break;
                }
                case(10):
                {
                    UART_print("8\r\n");
                    break;
                }
                case(11):
                {
                    UART_print("9\r\n");
                    break;
                }
                case(12):
                {
                    UART_print("C\r\n");
                    break;
                }
                case(13):
                {
                    UART_print("*\r\n");
                    break;
                }
                case(14):
                {
                    UART_print("0\r\n");
                    break;
                }
                case(15):
                {
                    UART_print("#\r\n");
                    break;
                }
                case(16):
                {
                    UART_print("D\r\n");
                    break;
                }

            }

        }
    
    }

}
