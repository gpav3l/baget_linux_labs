#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "i2c.h"

#define MPU6050_ADDR 0x68

#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

/** Function declarations */
void signal_handler(int signum);

/** Global variables */
struct I2cDevice dev;


/**
 * Main: application start point
 */
int main() {
	int rc;
	uint8_t Rec_Data[6];
	uint16_t Accel_Raw[3];
	/*
	 * Set the I2C bus filename and slave address,
	 */
	dev.filename = "/dev/i2c-0";
	dev.addr = MPU6050_ADDR;

	/*
	 * Start the I2C device.
	 */
	rc = i2c_start(&dev);
	if (rc) {
		printf("failed to start i2c device\r\n");
		return rc;
	}

	if(i2c_read_reg(&dev, WHO_AM_I_REG) == 0x68)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		i2c_write_reg(&dev, PWR_MGMT_1_REG, 0);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		i2c_write_reg(&dev, SMPLRT_DIV_REG, 0x07);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ± 2g
		i2c_write_reg(&dev, ACCEL_CONFIG_REG, 0x00);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ± 250 °/s
		i2c_write_reg(&dev, GYRO_CONFIG_REG, 0x00);

		// Read data in loop
		while(1){
			if(i2c_readn_reg(&dev, ACCEL_XOUT_H_REG, Rec_Data, 6) == 6) {
				for(int i=0; i<3; i++) {
					Accel_Raw[i] = (int16_t)(Rec_Data[i*2] << 8 | Rec_Data [i*2+1]);
				}
				printf("ACCEL (RAW): X=%d Y=%d Z=%d\n\r", Accel_Raw[0], Accel_Raw[1], Accel_Raw[2]);
				sleep(5);
			}
			/*** convert the RAW values into acceleration in 'g'
				we have to divide according to the Full scale value set in FS_SEL
				We have configured FS_SEL = 0. So dividing by 16384.0
				for more details check ACCEL_CONFIG Register              ****/
			//Ax = Accel_X_RAW/16384.0;
			//Ay = Accel_Y_RAW/16384.0;
			//Az = Accel_Z_RAW/16384.0;
		}
	}

	printf("wrong id read, close");

	i2c_stop(&dev);

    return 0;
}


/**
 * Catch signal for correct exit
 */
void signal_handler( int signum ) {
	printf("Finish application");

	i2c_stop(&dev);

	exit(signum);
}
