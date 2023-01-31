#include "ICM20948.h"
#include <string.h>
#include <stdio.h>

ICM20948_ST_SENSOR_DATA gstGyroOffset ={0,0,0};

HAL_StatusTypeDef ret; // to store return status
int16_t val; // data from IMU


HAL_StatusTypeDef IMU_WriteOneByte(ICM20948 *dev, uint8_t reg, uint8_t data);
HAL_StatusTypeDef IMU_ReadOneByte(ICM20948 *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef Gyro_calibrate(ICM20948 *dev);

int16_t gyro_offset[3] = {0};  // gyro_offset value calibrated by Gyro_calibrate()

/*
 * INITIALISATION
 */
uint8_t* IMU_Initialise(ICM20948 *dev, I2C_HandleTypeDef *i2cHandle, UART_HandleTypeDef *uart)
{

	 char hex[2];
	 uint8_t uartbuf[20]="  IMU ID =      "; // buffer for data
     uint8_t regData;

	 dev->i2cHandle = i2cHandle;
	 dev->uart = uart;

	//select bank 0
/*	  //buf[0] = REG_BANK_SEL;  // register number
	  buf[0] = REG_ADD_REG_BANK_SEL;  // bank select register
	  buf[1] = REG_VAL_REG_BANK_0;           // bank 0
	  ret = HAL_I2C_Master_Transmit(i2cHandle, IMU_ADDR, buf, I2C_MEMADD_SIZE_16BIT, HAL_MAX_DELAY);

*/
	  ret = IMU_WriteOneByte(dev, REG_ADD_REG_BANK_SEL, REG_VAL_REG_BANK_0);
	  if ( ret != HAL_OK ){
	       strcpy((char*)uartbuf, "Error 1\r\n");
	       return &uartbuf[0];
	  	   }

	  //check ID
/*	  buf[0] = REG_WHO_AM_I;  //(Should return ID =  0xEA)
	  ret = HAL_I2C_Mem_Read(i2cHandle, IMU_ADDR, REG_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, buf, I2C_MEMADD_SIZE_8BIT, HAL_MAX_DELAY);  */
	  ret = IMU_ReadOneByte(dev, REG_WHO_AM_I, &regData);
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 2\r\n");
	       return &uartbuf[0];
	       }
	  else{
		  //sprintf(hex, "%x", buf[0]); // change to hexidecimal
		  sprintf(hex, "%x", regData); // change to hexidecimal
	      strcpy(uartbuf, hex); // copy back to buf
	      uartbuf[12] = uartbuf[0]-32; // change to upper case
	      uartbuf[13] = uartbuf[1]-32;
	      uartbuf[14] = '\r';
	      uartbuf[15] = '\n';
	      uartbuf[16] = '\0';
	      uartbuf[0]  = '\r';
	      uartbuf[1]  = '\n';
	      uartbuf[2]  = 'I';
	      }


      // for debuggiing - send to uart and return to main to display on OLED and UART
	  HAL_UART_Transmit(dev->uart, uartbuf, strlen((char*)uartbuf), HAL_MAX_DELAY);
	  //return &buf[0];

	  // Initialize
	  // Bank 0 - Reset the device and then auto selects the best available clock source
      ret = IMU_WriteOneByte(dev, REG_ADD_REG_BANK_SEL, REG_VAL_REG_BANK_0);
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 3\r\n");
	       return &uartbuf[0];
	       }
      ret = IMU_WriteOneByte(dev, REG_ADD_PWR_MGMT_1,  REG_VAL_ALL_RGE_RESET); // reset device - check hearder file value should be 0xF1
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 4a\r\n");
	       return &uartbuf[0];
	       }
      HAL_Delay(10);
      ret = IMU_WriteOneByte(dev, REG_ADD_PWR_MGMT_1,  REG_VAL_RUN_MODE); // auto selects the best available clock source for device
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 4b\r\n");
	       return &uartbuf[0];
	       }


	  // Turn off and on Accelator and Gyro - page 28
      HAL_Delay(10);
      ret = IMU_WriteOneByte(dev, REG_ADD_PWR_MGMT_2,  REG_VAL_ACCEL_GYROLL_OFF); // OFF
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 5a\r\n");
	       return &uartbuf[0];
	       }

      HAL_Delay(10);
      ret = IMU_WriteOneByte(dev, REG_ADD_PWR_MGMT_2,  REG_VAL_ACCEL_GYROLL_ON); // ON
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 5b\r\n");
	       return &uartbuf[0];
	       }

      ret = IMU_WriteOneByte(dev, REG_ADD_INT_ENABLE_1,  REG_VAL_INT_ENABLED); // Turn on inteerup on pin INT1


      // Bank 2 - Gyro and Acce and start running
      /* user bank 2 register */
      ret = IMU_WriteOneByte(dev, REG_ADD_REG_BANK_SEL, REG_VAL_REG_BANK_2);
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 6\r\n");
	       return &uartbuf[0];
	       }
      ret = IMU_WriteOneByte(dev, REG_ADD_GYRO_SMPLRT_DIV, 0x07);  // pg 59  Gyro sample rate divider Output data rate = 1.11K/7 = 157 Hz
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 7\r\n");
	       return &uartbuf[0];
	       }
      ret = IMU_WriteOneByte(dev, REG_ADD_GYRO_CONFIG_1, REG_VAL_BIT_GYRO_DLPCFG_6 | REG_VAL_BIT_GYRO_FS_500DPS | REG_VAL_BIT_GYRO_DLPF); // enable low pass filter and set Gyro FS
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 8\r\n");
	       return &uartbuf[0];
	       }

      ret = IMU_WriteOneByte(dev, REG_ADD_ACCEL_SMPLRT_DIV_2,  0x07); //  pg 63 Acce sample rate divider: ODR = 1.125KHz/7 = 161
      ret = IMU_WriteOneByte(dev, REG_ADD_ACCEL_SMPLRT_DIV_1,  0x00); // upper 3 bit of sample rate = 0
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 9\r\n");
	       return &uartbuf[0];
	       }

	  // enable LPF and set accel full scale to +/-2G, sensitivity scale factor = 16384 LSB/g
      ret = IMU_WriteOneByte(dev, REG_ADD_ACCEL_CONFIG, REG_VAL_BIT_ACCEL_DLPCFG_6 | REG_VAL_BIT_ACCEL_FS_2g | REG_VAL_BIT_ACCEL_DLPF);
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 10\r\n");
	       return &uartbuf[0];
	       }

	  IMU_WriteOneByte(dev, REG_ADD_TEMP_CONFIG, REG_VAL_TEMP_CONFIG); // Temp configuration pg 67



      // back to bank 0
      ret = IMU_WriteOneByte(dev, REG_ADD_REG_BANK_SEL, REG_VAL_REG_BANK_0);
	  if ( ret != HAL_OK )	  {
	       strcpy((char*)uartbuf, "Error 11\r\n");
	       return &uartbuf[0];
	       }
      HAL_Delay(100);

      /* offset */
      Gyro_calibrate(dev);  // calibrate the offset of the gyroscope

      // everthing OK
      //strcpy((char*)buf, "Initialize OK\r\n");
      //return &buf;
      return 0; // 0 means 0 error

}


HAL_StatusTypeDef IMU_WriteOneByte(ICM20948 *dev, uint8_t reg, uint8_t data)
{
	 uint8_t regData = data;
	 return HAL_I2C_Mem_Write(dev->i2cHandle, IMU_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &regData, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef IMU_ReadOneByte(ICM20948 *dev, uint8_t reg, uint8_t *data)
{
	ret=HAL_I2C_Mem_Read(dev->i2cHandle, IMU_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, I2C_MEMADD_SIZE_8BIT, HAL_MAX_DELAY);
	return ret;
}

HAL_StatusTypeDef IMU_TempRead(ICM20948 *dev)
{
    uint8_t u8Buf[2];
    int16_t tempRaw;
    int32_t tempC;// temperature in deg C, with sensitivity 333.87.   Offset value 0 = 21 deg C

    ret=IMU_ReadOneByte(dev, REG_ADD_TEMP_OUT_L, &u8Buf[0]);
    ret=IMU_ReadOneByte(dev, REG_ADD_TEMP_OUT_H, &u8Buf[1]);
    tempRaw = (u8Buf[1]<<8)|u8Buf[0];
    dev->temp_C = (tempRaw)/333.81 + 21;   // assuming no further offset apart from 21 dec C
}

HAL_StatusTypeDef IMU_AccelRead(ICM20948 *dev)
{
    uint8_t u8Buf[2] = {0}; // reset to zero
    int16_t accRaw[3] = {0};  // reset to zero

    ret=IMU_ReadOneByte(dev, REG_ADD_ACCEL_XOUT_L, &u8Buf[0]);
    ret=IMU_ReadOneByte(dev, REG_ADD_ACCEL_XOUT_H, &u8Buf[1]);
    accRaw[0] =	(u8Buf[1]<<8)|u8Buf[0];


    ret=IMU_ReadOneByte(dev, REG_ADD_ACCEL_YOUT_L, &u8Buf[0]);
    ret=IMU_ReadOneByte(dev, REG_ADD_ACCEL_YOUT_H, &u8Buf[1]);
    accRaw[1] =	(u8Buf[1]<<8)|u8Buf[0];


    ret=IMU_ReadOneByte(dev, REG_ADD_ACCEL_ZOUT_L, &u8Buf[0]);
    ret=IMU_ReadOneByte(dev, REG_ADD_ACCEL_ZOUT_H, &u8Buf[1]);
    accRaw[2] =	(u8Buf[1]<<8)|u8Buf[0];

	/* Convert to SIGNED integers (two's complement) */
	int32_t accRawSigned[3];

	if ( (accRaw[0] & 0x00080000) == 0x00080000 )
		accRawSigned[0] = accRaw[0] | 0xFFF00000;
	else
		accRawSigned[0] = accRaw[0];

	if ( (accRaw[1] & 0x00080000) == 0x00080000 )
		accRawSigned[1] = accRaw[1] | 0xFFF00000;
	else
		accRawSigned[1] = accRaw[1];

	if ( (accRaw[2] & 0x00080000) == 0x000080000 )
		accRawSigned[2] = accRaw[2] | 0xFFF00000;
	else
		accRawSigned[2] = accRaw[2];


	// accel full scale set to +/-2G, sensitivity scale factor = 16384 LSB/g
	dev->acc[0] = 9.81f * 0.00006103515625f * accRawSigned[0];
	dev->acc[1] = 9.81f * 0.00006103515625f * accRawSigned[1];
	dev->acc[2] = 9.81f * 0.00006103515625f * accRawSigned[2];

	return ret;

}

HAL_StatusTypeDef Gyro_calibrate(ICM20948 *dev)  // calibrate the offset of the gyro
// store the offset in int16_t gyro_offset[3]
{
    uint8_t u8Buf[2] = {0}; // reset to zero upon entry
    int32_t gyroRaw[3] = {0}; // reset to zero upon entry
    int8_t i;
    int16_t temp;

    for (i=0; i< 32; i++){
    	IMU_ReadOneByte(dev, REG_ADD_GYRO_XOUT_L, &u8Buf[0]);
    	IMU_ReadOneByte(dev, REG_ADD_GYRO_XOUT_H, &u8Buf[1]);
    	temp = (u8Buf[1]<<8)|u8Buf[0]; // for debugging
    	gyroRaw[0] = temp + gyroRaw[0];
    	//gyroRaw[0] = (u8Buf[1]<<8)|u8Buf[0] + gyroRaw[0];

    	IMU_ReadOneByte(dev, REG_ADD_GYRO_YOUT_L, &u8Buf[0]);
    	IMU_ReadOneByte(dev, REG_ADD_GYRO_YOUT_H, &u8Buf[1]);
    	gyroRaw[1] = (u8Buf[1]<<8)|u8Buf[0] + gyroRaw[1];

    	IMU_ReadOneByte(dev, REG_ADD_GYRO_ZOUT_L, &u8Buf[0]);
    	ret=IMU_ReadOneByte(dev, REG_ADD_GYRO_ZOUT_H, &u8Buf[1]);
    	gyroRaw[2] = (u8Buf[1]<<8)|u8Buf[0] + gyroRaw[2];

    	HAL_Delay(100); // wait for 100msec
    }

    gyro_offset[0] = gyroRaw[0]>>5;  // average of 32 reads
    gyro_offset[1] = gyroRaw[1]>>5;
    gyro_offset[2] = gyroRaw[2]>>5;

	return ret;
}


HAL_StatusTypeDef IMU_GyroRead(ICM20948 *dev)
{   // return the change in value instead of current value
    uint8_t u8Buf[2] = {0}; // reset to zero
    int16_t gyroRaw[3] = {0};  // reset to zero
    int16_t gyroDiff[3];
    int16_t temp;
    static int16_t gyroOld[3]= {0, 0, 0};  // previous value

    ret=IMU_ReadOneByte(dev, REG_ADD_GYRO_YOUT_L, &u8Buf[0]);
    ret=IMU_ReadOneByte(dev, REG_ADD_GYRO_YOUT_H, &u8Buf[1]);
    gyroRaw[1] = (u8Buf[1]<<8)|u8Buf[0] -  gyro_offset[1];
    gyroDiff[1] = gyroRaw[1] - gyroOld[1];  // change in value
    gyroOld[1] = gyroRaw[1];

    ret=IMU_ReadOneByte(dev, REG_ADD_GYRO_ZOUT_L, &u8Buf[0]);
    ret=IMU_ReadOneByte(dev, REG_ADD_GYRO_ZOUT_H, &u8Buf[1]);
    gyroRaw[2] = (u8Buf[1]<<8)|u8Buf[0] -  gyro_offset[2];
    gyroDiff[2] = gyroRaw[2] - gyroOld[2];  // change in value
    gyroOld[2] = gyroRaw[2];

    ret=IMU_ReadOneByte(dev, REG_ADD_GYRO_XOUT_L, &u8Buf[0]);
    ret=IMU_ReadOneByte(dev, REG_ADD_GYRO_XOUT_H, &u8Buf[1]);
    temp = (u8Buf[1]<<8)|u8Buf[0]; // for debugging
    gyroRaw[0] = (u8Buf[1]<<8)|u8Buf[0] - gyro_offset[0];
    gyroDiff[0] = gyroRaw[0] - gyroOld[0];  // change in value
    gyroOld[0] = gyroRaw[0];

	/* extend to 32 bit SIGNED integers (two's complement)*/
    int32_t gyroRawSigned[3];


	//if ( (gyroDiff[0] & 0x00008000) == 0x00008000 )  //32 bit - no need to check
	//	gyroRawSigned[0] = gyroRaw[0] | 0xFFFF0000;
	//else
		gyroRawSigned[0] = gyroRaw[0];

	//if ( (gyroDiff[1] & 0x00008000) == 0x00008000 )
	//	gyroRawSigned[1] = gyroRaw[1] | 0xFFFF0000;
	//else
		gyroRawSigned[1] = gyroRaw[1];

	//if ( (gyroDiff[2] & 0x00008000) == 0x800008000 )
	//	gyroRawSigned[2] = gyroRaw[2] | 0xFFFF0000;
	//else
		gyroRawSigned[2] = gyroRaw[2];


	// gyro full scale set to +/-500 dps, sensitivity scale factor = 65.5 LSB/dps
	// degree per second = value/65.5
	dev->gyro[0] = 0.0152671755725191f * gyroRawSigned[0];
	dev->gyro[1] = 0.0152671755725191f * gyroRawSigned[1];
	dev->gyro[2] = 0.0152671755725191f * gyroRawSigned[2];

	return ret;

}

/*
void invmsICM20948GyroOffset(void)
{
	uint8_t i;
    int16_t	s16Gx = 0, s16Gy = 0, s16Gz = 0;
	int32_t	s32TempGx = 0, s32TempGy = 0, s32TempGz = 0;
    for(i = 0; i < 32; i ++)
 	{
        invmsICM20948GyroRead(&s16Gx, &s16Gy, &s16Gz);
        s32TempGx += s16Gx;
		s32TempGy += s16Gy;
		s32TempGz += s16Gz;
        HAL_Delay(10);
    }
    gstGyroOffset.s16X = s32TempGx >> 5;
	gstGyroOffset.s16Y = s32TempGy >> 5;
	gstGyroOffset.s16Z = s32TempGz >> 5;
    return;
}

void invmsICM20948GyroRead(int16_t* ps16X, int16_t* ps16Y, int16_t* ps16Z)
{
   uint8_t u8Buf[6];
   int16_t s16Buf[3] = {0};
   uint8_t i;
   int32_t s32OutBuf[3] = {0};
   static ICM20948_ST_AVG_DATA sstAvgBuf[3];
   static int16_t ss16c = 0;
   ss16c++;



   u8Buf[0]=I2C_ReadOneByte(I2C_ADD_ICM20948,REG_ADD_GYRO_XOUT_L);
   u8Buf[1]=I2C_ReadOneByte(I2C_ADD_ICM20948,REG_ADD_GYRO_XOUT_H);
   s16Buf[0]=	(u8Buf[1]<<8)|u8Buf[0];

   u8Buf[0]=I2C_ReadOneByte(I2C_ADD_ICM20948,REG_ADD_GYRO_YOUT_L);
   u8Buf[1]=I2C_ReadOneByte(I2C_ADD_ICM20948,REG_ADD_GYRO_YOUT_H);
   s16Buf[1]=	(u8Buf[1]<<8)|u8Buf[0];

   u8Buf[0]=I2C_ReadOneByte(I2C_ADD_ICM20948,REG_ADD_GYRO_ZOUT_L);
   u8Buf[1]=I2C_ReadOneByte(I2C_ADD_ICM20948,REG_ADD_GYRO_ZOUT_H);
   s16Buf[2]=	(u8Buf[1]<<8)|u8Buf[0];

#if 1
   for(i = 0; i < 3; i ++)
   {
       invmsICM20948CalAvgValue(&sstAvgBuf[i].u8Index, sstAvgBuf[i].s16AvgBuffer, s16Buf[i], s32OutBuf + i);
   }
   *ps16X = s32OutBuf[0] - gstGyroOffset.s16X;
   *ps16Y = s32OutBuf[1] - gstGyroOffset.s16Y;
   *ps16Z = s32OutBuf[2] - gstGyroOffset.s16Z;
#else
   *ps16X = s16Buf[0];
   *ps16Y = s16Buf[1];
   *ps16Z = s16Buf[2];
#endif
   return;
}

*/

/*
void invMSInit()
{
    if(invmsICM20948Check())//检测是否能识别到ICM20498器件
		{
			invmsICM20948Init(); //ICM20498初始化
			 printf("ICM20948 init_successful");
		}
    return;
}




 bool invmsICM20948Check(void)
{
    bool bRet = false;
    if(REG_VAL_WIA == I2C_ReadOneByte(I2C_ADD_ICM20948, REG_ADD_WIA))
    {
        bRet = true;
    }
    return bRet;
}

*/



