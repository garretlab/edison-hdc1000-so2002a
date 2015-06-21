#include "so2002a.h"

#include <mraa.h>
#include <string.h>

static uint8_t displayMode = 0x00;
static uint8_t functionMode = 0x00;
static mraa_i2c_context i2c;

int so2002aConfigure(unsigned int bus, uint8_t address) {
	mraa_result_t ret;

	ret = mraa_init();
	if ((ret != MRAA_SUCCESS) && (ret != MRAA_ERROR_PLATFORM_ALREADY_INITIALISED)) {
		fprintf(stderr, "so2002: mraa_init() failed.\n");
		return SO2002A_FAILURE;
	}

	if ((i2c = mraa_i2c_init(bus)) == NULL) {
		fprintf(stderr, "so2002: mraa_i2c_init() failed.\n");
		return SO2002A_FAILURE;
	}

	if (mraa_i2c_address(i2c, SO2002A_I2C_ADDRESS) != MRAA_SUCCESS) {
		fprintf(stderr, "so2002: mraa_i2c_address() failed.\n");
		return SO2002A_FAILURE;
	}

	if (so2002aDisplayOff() || so2002aClearDisplay() || so2002aDisplayOn()) {
		return SO2002A_FAILURE;
	}

	return SO2002A_SUCCESS;
}

int so2002aWriteCommand(uint8_t rs, uint8_t data) {
	uint8_t value[2];

	value[0] = rs;
	value[1] = data;

	if (mraa_i2c_write(i2c, value, 2) != MRAA_SUCCESS) {
		return SO2002A_FAILURE;
	}

	return SO2002A_SUCCESS;
}

int so2002aSetFunctionMode() {
	int ret = so2002aWriteCommand(SO2002A_COMMAND,  SO2002A_COMMAND_FUNCTION_SET | functionMode);
	usleep(37);
	return ret;
}

int so2002aClearDisplay() {
	int ret = so2002aWriteCommand(SO2002A_COMMAND, SO2002A_COMMAND_CLEAR_DISPLAY);
	usleep(1520);
	return ret;
}

int so2002aReturnHome() {
	int ret = so2002aWriteCommand(SO2002A_COMMAND, SO2002A_COMMAND_RETURN_HOME);
	usleep(1520);
	return ret;
}

int so2002aSetDisplayMode() {
	int ret = so2002aWriteCommand(SO2002A_COMMAND, SO2002A_COMMAND_DISPLAY_ON_OFF | displayMode);
	usleep(37);
	return ret;
}

int so2002aDisplayOn() {
	displayMode |= SO2002A_DISPLAY_MODE_DISPLAY_ON;
	return so2002aSetDisplayMode();
}

int so2002aDisplayOff() {
	displayMode &= SO2002A_DISPLAY_MODE_DISPLAY_OFF;
	return so2002aSetDisplayMode();
}

int so2002aCursorOn() {
	displayMode |= SO2002A_DISPLAY_MODE_CURSOR_ON;
	return so2002aSetDisplayMode();
}

int so2002aCursorOff() {
	displayMode &= SO2002A_DISPLAY_MODE_CURSOR_OFF;
	return so2002aSetDisplayMode();
}

int so2002aBlinkOn() {
	displayMode |= SO2002A_DISPLAY_MODE_BLINK_ON;
	return so2002aSetDisplayMode();
}

int so2002aBlinkOff() {
	displayMode &= SO2002A_DISPLAY_MODE_BLINK_OFF;
	return so2002aSetDisplayMode();
}

int so2002aSetDdramAddress(uint8_t address) {
	int ret = so2002aWriteCommand(SO2002A_COMMAND, SO2002A_COMMAND_SET_DDRAM_ADDRESS | address);
	usleep(37);
	return ret;
}

int so2002aSetCursor(uint8_t col, uint8_t row) {
	int row_begin[] = {0, 32};

	return so2002aSetDdramAddress(col + row_begin[row] );
}

int so2002aWriteChar(uint8_t c) {
	return so2002aWriteCommand(SO2002A_DATA, c);
}

int so2002aWriteString(char *s) {
	int length = strlen(s);
	int ret;
	int i;

	for (i = 0; i < length; i++) {
		if ((ret = so2002aWriteCommand(SO2002A_DATA, s[i])) < 0) {
			return ret;
		}
	}
	return SO2002A_SUCCESS;
}

