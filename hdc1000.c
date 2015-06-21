#include "hdc1000.h"
#include <mraa.h>

static mraa_i2c_context i2c;

int hdc1000Configure(int bus) {
	uint8_t mode[3] = {HDC1000_CONFIGURATION_POINTER,
			HDC1000_CONFIGURE_MSB, HDC1000_CONFIGURE_LSB};

	if ((i2c = mraa_i2c_init(bus)) == NULL) {
		fprintf(stderr, "hdc1000: mraa_i2c_init failed().\n");
		return HDC1000_FAILURE;
	}

	if (mraa_i2c_address(i2c, HDC1000_I2C_ADDRESS) != MRAA_SUCCESS) {
		fprintf(stderr, "hdc1000: mraa_i2c_address() failed.\n");
		return HDC1000_FAILURE;
	}

	if (mraa_i2c_write(i2c, mode, 3) != MRAA_SUCCESS) {
		fprintf(stderr, "hdc1000: mraa_i2c_write() failed.\n");
		return HDC1000_FAILURE;
	}

	return HDC1000_SUCCESS;
}

int hdc1000GetManufacturerId(uint16_t *id) {
	uint8_t data[2];
	if (mraa_i2c_read_bytes_data(i2c, HDC1000_MANUFACTURER_ID_POINTER, data, 2) == -1) {
		fprintf(stderr, "hdc1000: mraa_i2c_read_bytes_data() failed.\n");
		return HDC1000_FAILURE;
	}
	*id = data[0] << 8 | data[1];
	return HDC1000_SUCCESS;
}

int hdc1000GetTemperatureAndHumidity(double *temperature, double *humidity) {
	uint16_t tData, hData;
	uint8_t data[4];

	data[0] = HDC1000_TEMPERATURE_POINTER;
	if (mraa_i2c_write(i2c, data, 1) != MRAA_SUCCESS) {
		fprintf(stderr, "hdc1000: mraa_i2c_write() failed.\n");
		return HDC1000_FAILURE;
	}
	usleep(20000);
	if (mraa_i2c_read(i2c, data, 4) != 4) {
		fprintf(stderr, "hdc1000: mraa_i2c_read() failed.\n");
		return HDC1000_FAILURE;
	}

	tData = data[0] << 8 | data[1];
	hData = data[2] << 8 | data[3];

	*temperature = tData / 65536.0 * 165.0 - 40.0;
	*humidity = hData / 65536.0 * 100.0;

	return HDC1000_SUCCESS;
}
