#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <stdio.h>

int main()
{
	unsigned int uiSwitchValue = 0;
	unsigned int uiButtonsValue = 0;
	unsigned int uiButtonsValuePrevious = 0;

	FILE *lcd;
	printf("Hello from Nios II!\n");
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, 0xaa);
	lcd = fopen(LCD_NAME, "w");
	while(1)
	{
		uiSwitchValue = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, uiSwitchValue);
		uiButtonsValuePrevious = uiButtonsValue;
		uiButtonsValue = IORD_ALTERA_AVALON_PIO_DATA(KEYS_BASE);
		if(lcd != NULL)
		{
			if(uiButtonsValuePrevious != uiButtonsValue)
			{
				#define ESC 27
				#define CLEAR_LCD_STRING "[2J"
				fprintf(lcd, "%c%s", ESC, CLEAR_LCD_STRING);
				fprintf(lcd, "BUTTON VALUE: %d\n", uiButtonsValue);
			}
		}
	}
	fclose(lcd);

	return 0;
}
