#include <mraa.h>
#include "hdc1000.h"
#include "so2002a.h"

int main(void) {
	uint16_t hdc1000Id;
	double temperature, humidity;
	char string[20];

	if (so2002aConfigure(1, SO2002A_I2C_ADDRESS) != SO2002A_SUCCESS) {
		fprintf(stderr, "so2002Configure() failed.\n");
	}

	if (hdc1000Configure(1) != HDC1000_SUCCESS) {
		fprintf(stderr, "hdc1000Configure() failed.\n");
	}

	if (hdc1000GetManufacturerId(&hdc1000Id) == HDC1000_SUCCESS) {
		printf("hdc1000 manufacturer id = 0x%x\n", hdc1000Id);
	}

	for (;;) {
		hdc1000GetTemperatureAndHumidity(&temperature, &humidity);

		sprintf(string, "Temp    : %3.1f C", temperature);
		if (so2002aSetCursor(0, 0) || so2002aWriteString(string)) {
			so2002aClearDisplay();
			continue;
		}

		sprintf(string, "Humidity: %-3.1f %%", humidity);
		if (so2002aSetCursor(0, 1) || so2002aWriteString(string)) {
			so2002aClearDisplay();
			continue;
		}

		sleep(1);
	}
}
