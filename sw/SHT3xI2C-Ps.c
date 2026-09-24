/*
 * SHT3xI2C-Ps.c
 *
 *  Created on: Sep 23, 2026
 *      Author: Mehr Digital Center
 */

#include "SHT3xI2C-Ps.h"

XIicPs_Config *cfgPSi2c;


int I2Cinit(XIicPs *i2c){

	int Status ;

	cfgPSi2c = XIicPs_LookupConfig(XPAR_XIICPS_0_DEVICE_ID);
	if (cfgPSi2c == NULL){
		xil_printf("Failed to LookUp Configuration I2C \r\n");
		return XST_FAILURE ;
	}
	Status = XIicPs_CfgInitialize(i2c,
								  cfgPSi2c,
								  cfgPSi2c->BaseAddress);
	if (Status != XST_SUCCESS){
		xil_printf("Failed to Initialize Configuration with status : %d \r\n", Status);
		return XST_FAILURE ;
	}
	Status = XIicPs_SetSClk(i2c, sClk_I2C_PS);
	if (Status != XST_SUCCESS){
		xil_printf("Failed to Set Clock with status : %d \r\n", Status);
		xil_printf("I2C Clock Frequency : %d \r\n",cfgPSi2c->InputClockHz);
		return XST_FAILURE ;
	}


	return XST_SUCCESS;

}

int I2CReadData (XIicPs *i2c , SensorData *measuredData){
	int Status ;;
	u8 sendBuff[2];
	u8 recvBuff[6];


	sendBuff[0] = ( MEASURE_CMD >> 8) & ( 0xFF );
	sendBuff[1] = ( MEASURE_CMD )     &   0xFF;

	Status = XIicPs_MasterSendPolled(i2c,
									 sendBuff,
									 SendBuffData,
									 SHT3x_SlaveADDR);
	if(Status != XST_SUCCESS){
		xil_printf("Failed to send read cmd with status %d \r\n",Status);
		return XST_FAILURE;
	}
	usleep(Write_CMD_Time);
	Status = XIicPs_MasterRecvPolled(i2c,
									 recvBuff,
									 RecvBuffData,
									 SHT3x_SlaveADDR);
	if(Status != XST_SUCCESS){
		xil_printf("Failed to send read data with status %d \r\n",Status);
		return XST_FAILURE;
	}

	usleep(Write_CMD_Time);

	u16 rawTempData = (recvBuff[0]<<8) | recvBuff[1];
	u16 rawHumData =  (recvBuff[3]<<8) | recvBuff[4];

	measuredData ->temp = (-46.85f) + ((175.72f)*((float)rawTempData/65536.0f));
	measuredData ->hum = (-6.0f) + ((125.0)*((float)rawHumData/65536.0f));

	return XST_SUCCESS;

}


