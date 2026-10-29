#include <LPC21xx.h>
#include "delay.h"

char key_map[4][4] =
{
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'C', '0', '=', '+'}
};

void KEYPAD_INIT(void)
{
    // Set rows as output and columns as input.
    IODIR1 |= (0x0F << 16);
}

void Scan_Row(unsigned int row)
{
    // Keep all rows OFF first.
    IOSET1 = (0x0F << 16);

    // Turn ON the selected row.
    IOCLR1 = (1 << (16 + row));
}

int Check_Columns(void)
{
    unsigned int cols;

    // Read the column status.
    cols = (IOPIN1 >> 20) & 0x0F;

    // Check which column is pressed.
    if (cols == 0x0E) return 0; // Column 0
    if (cols == 0x0D) return 1; // Column 1
    if (cols == 0x0B) return 2; // Column 2
    if (cols == 0x07) return 3; // Column 3

    return -1; // No key pressed
}

char Read_Keypad(void)
{
    int r, c;

    for (r = 0; r < 4; r++)
    {
        Scan_Row(r);
        c = Check_Columns();

        if (c != -1)
        {
            delay_ms(20); // Small delay for debounce.

            if (Check_Columns() == c)
            {
                // Wait until the key is released.
                while (Check_Columns() == c);

                return key_map[r][c];
            }
        }
    }

    return '\0'; // No key pressed.
}
