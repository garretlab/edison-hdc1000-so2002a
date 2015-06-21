#ifndef HDC1000_H_
#define HDC1000_H_

#include <mraa.h>

#define HDC1000_SUCCESS 0
#define HDC1000_FAILURE -1

#define HDC1000_I2C_ADDRESS 0x40

#define HDC1000_TEMPERATURE_POINTER     0x00
#define HDC1000_HUMIDITY_POINTER        0x01
#define HDC1000_CONFIGURATION_POINTER   0x02
#define HDC1000_SERIAL_ID1_POINTER      0xfb
#define HDC1000_SERIAL_ID2_POINTER      0xfc
#define HDC1000_SERIAL_ID3_POINTER      0xfd
#define HDC1000_MANUFACTURER_ID_POINTER 0xfe

#define HDC1000_CONFIGURE_MSB 0x10 /* Get both temperature and humidity */
#define HDC1000_CONFIGURE_LSB 0x00 /* 14 bit resolution */

int hdc1000Configure(int bus);
int hdc1000GetManufacturerId(uint16_t *id);
int hdc1000GetTemperatureAndHumidity(double *temperature, double *humidity);

#endif /* HDC1000_H_ */
