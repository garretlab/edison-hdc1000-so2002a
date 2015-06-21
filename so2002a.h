#ifndef SO2002A_H
#define SO2002A_H

#include <mraa.h>

#define SO2002A_SUCCESS 0
#define SO2002A_FAILURE -1

#define SO2002A_I2C_ADDRESS	0x3c

#define SO2002A_COMMAND 0x00
#define SO2002A_DATA    0x40

#define SO2002A_COMMAND_CLEAR_DISPLAY    	0x01
#define SO2002A_COMMAND_RETURN_HOME    		0x02
#define SO2002A_COMMAND_DISPLAY_ON_OFF   	0x08
#define SO2002A_COMMAND_FUNCTION_SET     	0x20
#define SO2002A_COMMAND_SET_DDRAM_ADDRESS    0x80

#define SO2002A_DISPLAY_MODE_BLINK_ON   0x01
#define SO2002A_DISPLAY_MODE_BLINK_OFF  (~SO2002A_DISPLAY_MODE_BLINK_ON)
#define SO2002A_DISPLAY_MODE_CURSOR_ON   0x02
#define SO2002A_DISPLAY_MODE_CURSOR_OFF  (~SO2002A_DISPLAY_MODE_CURSOR_ON)
#define SO2002A_DISPLAY_MODE_DISPLAY_ON  0x04
#define SO2002A_DISPLAY_MODE_DISPLAY_OFF (~SO2002A_DISPLAY_MODE_DISPLAY_ON)

int so2002aConfigure(unsigned int bus, uint8_t address);
int so2002aWriteCommand(uint8_t rs, uint8_t data);
int so2002aSetFunctionMode();
int so2002aClearDisplay();
int so2002aReturnHome();
int so2002aSetDisplayMode();
int so2002aDisplayOn();
int so2002aDisplayOff();
int so2002aCursorOn();
int so2002aCursorOff();
int so2002aBlinkOn();
int so2002aBlinkOff();
int so2002aSetDdramAddress(uint8_t address);
int so2002aSetCursor(uint8_t col, uint8_t row);
int so2002aWriteChar(uint8_t c);
int so2002aWriteString(char *s);

#endif /* SO2002A_H */
