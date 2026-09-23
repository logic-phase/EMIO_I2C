/*
 * SHT3xI2C-Ps.h
 *
 *  Created on: Sep 23, 2026
 *      Author: Mehr Digital Center
 */

#ifndef SRC_SHT3XI2C_PS_H_
#define SRC_SHT3XI2C_PS_H_

#include "xparameters.h"
#include "xiicps.h"
#include "sleep.h"


#define SHT3x_SlaveADDR 		0x44
#define SOFT_RST_CMD			0x30A2
#define MEASURE_CMD				0x2400


#define sClk_I2C_PS				100000
#define SendBuffData			2
#define RecvBuffData			6
#define Write_CMD_Time			1000000


typedef struct {
	float temp ;
	uint16_t hum ;
}SensorData;


int I2Cinit(XIicPs *i2c);
int I2CReadData (XIicPs *i2c , SensorData *measuredData);

#endif /* SRC_SHT3XI2C_PS_H_ */
