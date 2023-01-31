#ifndef __ICM_20948_H
#define __ICM_20948_H

#include <stdint.h> /* need for data type declarations */
#include "stm32f4xx_hal.h" /* Needed for I2C */

static const uint8_t IMU_ADDR = 0x68<<1; //8-bit I2C address for IMU, 110 1000b (the upper seven bit)

static const uint8_t REG_BANK_SEL = 0x7f; //Register to select different bank
#define USER_BANK_0		(0x00)
#define USER_BANK_1		(0x10)
#define USER_BANK_2		(0x20)
#define USER_BANK_3		(0x30)

static const uint8_t REG_WHO_AM_I = 0x00; // address of  WHO_AM_I register (@Bank 0)
static const uint8_t REG_TEMP_H = 0x39; // address of temperature register (@Bank 0)
static const uint8_t REG_TEMP_L = 0x3A; // address of temperature register (@Bank 0)



//#include "Public_StdTypes.h"
//#include "sys.h"
//#include "system.h"
/* define ICM-20948 Device I2C address*/
#define I2C_ADD_ICM20948            0xD0
#define I2C_ADD_ICM20948_AK09916    0x0C
#define I2C_ADD_ICM20948_AK09916_READ  0x80
#define I2C_ADD_ICM20948_AK09916_WRITE 0x00
/* define ICM-20948 Register */
/* user bank 0 register */
#define REG_ADD_WIA             0x00
#define REG_VAL_WIA             0xEA
#define REG_ADD_USER_CTRL       0x03
#define REG_VAL_BIT_DMP_EN          0x80
#define REG_VAL_BIT_FIFO_EN         0x40
#define REG_VAL_BIT_I2C_MST_EN      0x20
#define REG_VAL_BIT_I2C_IF_DIS      0x10
#define REG_VAL_BIT_DMP_RST         0x08
#define REG_VAL_BIT_DIAMOND_DMP_RST 0x04

#define REG_ADD_PWR_MGMT_1     0x06
//#define REG_VAL_ALL_RGE_RESET   0x01    // Should be 0xF1 if want to reset - pg 27 of datasheet
#define REG_VAL_ALL_RGE_RESET   0xF1    //  reset device registers - pg 27 of datasheet
#define REG_VAL_RUN_MODE        0x01    //device run with auto selects the best available clock source - pg 37 of datasheeet
#define REG_ADD_LP_CONFIG       0x05
//#define REG_ADD_PWR_MIGMT_1      0x06

#define REG_ADD_PWR_MGMT_2      0x07
#define REG_VAL_ACCEL_GYROLL_OFF   (0x38 | 0x07)  // see page 28
#define REG_VAL_ACCEL_GYROLL_ON   (0x00 | 0x00)

#define REG_ADD_INT_PIN_CFG     0x0F // see pg 38

#define REG_ADD_INT_ENABLE_1    0x10
#define REG_VAL_INT_ENABLED     0x01  // see pg 39  - Enable INT1 pin

#define REG_ADD_ACCEL_XOUT_H    0x2D
#define REG_ADD_ACCEL_XOUT_L    0x2E
#define REG_ADD_ACCEL_YOUT_H    0x2F
#define REG_ADD_ACCEL_YOUT_L    0x30
#define REG_ADD_ACCEL_ZOUT_H    0x31
#define REG_ADD_ACCEL_ZOUT_L    0x32
#define REG_ADD_GYRO_XOUT_H     0x33
#define REG_ADD_GYRO_XOUT_L     0x34
#define REG_ADD_GYRO_YOUT_H     0x35
#define REG_ADD_GYRO_YOUT_L     0x36
#define REG_ADD_GYRO_ZOUT_H     0x37
#define REG_ADD_GYRO_ZOUT_L     0x38
#define REG_ADD_TEMP_OUT_H      0x39
#define REG_ADD_TEMP_OUT_L      0x3A
#define REG_ADD_EXT_SENS_DATA_00 0x3B
#define REG_ADD_REG_BANK_SEL    0x7F
#define REG_VAL_REG_BANK_0  0x00
#define REG_VAL_REG_BANK_1  0x10
#define REG_VAL_REG_BANK_2  0x20
#define REG_VAL_REG_BANK_3  0x30

/* user bank 1 register */
/* user bank 2 register */
#define REG_ADD_GYRO_SMPLRT_DIV 0x00
#define REG_ADD_GYRO_CONFIG_1   0x01
#define REG_VAL_BIT_GYRO_DLPCFG_2   0x10 /* bit[5:3] */
#define REG_VAL_BIT_GYRO_DLPCFG_4   0x20 /* bit[5:3] */
#define REG_VAL_BIT_GYRO_DLPCFG_6   0x30 /* bit[5:3]  LPF = 5.7 Hz pg 59 */
#define REG_VAL_BIT_GYRO_FS_250DPS  0x00 /* bit[2:1] */
#define REG_VAL_BIT_GYRO_FS_500DPS  0x02 /* bit[2:1] Gyro Full Scale = +/- 500 degree per second */
#define REG_VAL_BIT_GYRO_FS_1000DPS 0x04 /* bit[2:1] */
#define REG_VAL_BIT_GYRO_FS_2000DPS 0x06 /* bit[2:1] */
#define REG_VAL_BIT_GYRO_DLPF       0x01 /* bit[0]    enable LPF */
#define REG_ADD_ACCEL_SMPLRT_DIV_1  0x10
#define REG_ADD_ACCEL_SMPLRT_DIV_2  0x11
#define REG_ADD_ACCEL_CONFIG        0x14
#define REG_VAL_BIT_ACCEL_DLPCFG_2  0x10 /* bit[5:3] */
#define REG_VAL_BIT_ACCEL_DLPCFG_4  0x20 /* bit[5:3] */
#define REG_VAL_BIT_ACCEL_DLPCFG_6  0x30 /* bit[5:3] */
#define REG_VAL_BIT_ACCEL_FS_2g     0x00 /* bit[2:1] */
#define REG_VAL_BIT_ACCEL_FS_4g     0x02 /* bit[2:1] */
#define REG_VAL_BIT_ACCEL_FS_8g     0x04 /* bit[2:1] */
#define REG_VAL_BIT_ACCEL_FS_16g    0x06 /* bit[2:1] */
#define REG_VAL_BIT_ACCEL_DLPF      0x01 /* bit[0]   */
#define REG_ADD_TEMP_CONFIG         0x53
#define REG_VAL_TEMP_CONFIG         0x00 // page 67 , set temp sensor bandwidth to 17Hz

/* user bank 3 register */
#define REG_ADD_I2C_SLV0_ADDR   0x03
#define REG_ADD_I2C_SLV0_REG    0x04
#define REG_ADD_I2C_SLV0_CTRL   0x05
#define REG_VAL_BIT_SLV0_EN     0x80
#define REG_VAL_BIT_MASK_LEN    0x07
#define REG_ADD_I2C_SLV0_DO     0x06
#define REG_ADD_I2C_SLV1_ADDR   0x07
#define REG_ADD_I2C_SLV1_REG    0x08
#define REG_ADD_I2C_SLV1_CTRL   0x09
#define REG_ADD_I2C_SLV1_DO     0x0A

/* define ICM-20948 Register  end */

/* define ICM-20948 MAG Register  */
#define REG_ADD_MAG_WIA1    0x00
#define REG_VAL_MAG_WIA1    0x48
#define REG_ADD_MAG_WIA2    0x01
#define REG_VAL_MAG_WIA2    0x09
#define REG_ADD_MAG_ST2     0x10
#define REG_ADD_MAG_DATA    0x11
#define REG_ADD_MAG_CNTL2   0x31
#define REG_VAL_MAG_MODE_PD     0x00
#define REG_VAL_MAG_MODE_SM     0x01
#define REG_VAL_MAG_MODE_10HZ   0x02
#define REG_VAL_MAG_MODE_20HZ   0x04
#define REG_VAL_MAG_MODE_50HZ   0x05
#define REG_VAL_MAG_MODE_100HZ  0x08
#define REG_VAL_MAG_MODE_ST     0x10
/* define ICM-20948 MAG Register  end */

#define MAG_DATA_LEN    6

#define ICM20948_TASK_PRIO		3
#define ICM20948_STK_SIZE 		256

typedef struct {
	/* I2C handle */
	I2C_HandleTypeDef *i2cHandle;
	UART_HandleTypeDef *uart;
	/* Acceleration data (X, Y, Z) in m/s^2 */
	float acc[3];
	float gyro[3];
	/* Temperature data in deg */
	float temp_C;
} ICM20948;



typedef struct icm20948_st_sensor_data_tag
{
	int16_t s16X;
	int16_t s16Y;
	int16_t s16Z;
}ICM20948_ST_SENSOR_DATA;

typedef struct icm20948_st_avg_data_tag
{
	uint8_t u8Index;
	int16_t s16AvgBuffer[8];
}ICM20948_ST_AVG_DATA;

typedef struct imu_st_sensor_data_tag
{
	int16_t s16X;
	int16_t s16Y;
	int16_t s16Z;
}IMU_ST_SENSOR_DATA;

void ICM20948_task(void *pvParameters);
//bool invmsICM20948Check(void);
void invmsICM20948Init(void);
void invmsICM20948GyroRead(int16_t* ps16X, int16_t* ps16Y, int16_t* ps16Z);
void invmsICM20948AccelRead(int16_t* ps16X, int16_t* ps16Y, int16_t* ps16Z);
void invmsICM20948MagRead(int16_t* ps16X, int16_t* ps16Y, int16_t* ps16Z);
void invmsICM20948ReadSecondary(uint8_t u8I2CAddr, uint8_t u8RegAddr, uint8_t u8Len, uint8_t *pu8data);
//bool invmsICM20948MagCheck(void);
void invmsICM20948WriteSecondary(uint8_t u8I2CAddr, uint8_t u8RegAddr, uint8_t u8data);
void invmsICM20948CalAvgValue(uint8_t *pIndex, int16_t *pAvgBuffer, int16_t InVal, int32_t *pOutVal);
void invmsICM20948GyroOffset(void);
void TestMagn(void);
void invMSInit(void);
void invMSAccelRead(int16_t* ps16AccelX, int16_t* ps16AccelY, int16_t* ps16AccelZ);
void invMSGyroRead(int16_t* ps16GyroX, int16_t* ps16GyroY, int16_t* ps16GyroZ);
void invMSMagRead(int16_t* ps16MagnX, int16_t* ps16MagnY, int16_t* ps16MagnZ);


HAL_StatusTypeDef IMU_TempRead(ICM20948 *dev);


//u8 MPU_Get_Gyroscope(void);
extern  int16_t TestmagnBuff[9];
extern uint32_t KeyAndJostickValue;
extern  int16_t magn[3];
extern	short gyro[3], accel[3],magnet[3];
extern  short Deviation_gyro[3],Original_gyro[3];
extern int Deviation_Count;
#endif //__ICM_20948_H
