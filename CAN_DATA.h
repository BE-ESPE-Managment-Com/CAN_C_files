#ifndef CAN_DATA_H
#define CAN_DATA_H

//CAN IDs
#define MPPT_MMS_STAT_ID 	0x4211
#define BMS_MMS_STAT 		0x4311
#define INV_MMS_STAT 		0x4411
#define LSW_MMS_STAT 		0x4511
#define MPPT_MMS_PWR 		0x3212
#define BMS_MMS_SOC 		0x3313
#define BMS_MMS_PWR 		0x3312
#define LSW_MMS_LDATA 		0x3514
#define MMS_MPPT_EN 		0x1120
#define MMS_BMS_EN 			0x1130
#define MMS_INV_EN 			0x1140
#define MMS_LSW_EN 			0x1150
#define MMS_MPPT_MAXPWR 		0x2125
#define MMS_BMS_SWINV 		0x1126
#define MMS_LSW_SWLOADS 		0x2156
#define BMS_MMS_OCH 		0x1317
#define BMS_MMS_UCH 		0x1318
#define BMS_MMS_OT 			0x1319


//CAN message lenghts
#define MPPT_MMS_STAT_LENGTH 		1
#define BMS_MMS_STAT_LENGTH 		1
#define INV_MMS_STAT_LENGTH 		1
#define LSW_MMS_STAT_LENGTH 		1
#define MPPT_MMS_PWR_LENGTH 		2
#define BMS_MMS_SOC_LENGTH 		1
#define BMS_MMS_PWR_LENGTH 		2
#define LSW_MMS_LDATA_LENGTH 		8
#define MMS_MPPT_EN_LENGTH 		1
#define MMS_BMS_EN_LENGTH 		1
#define MMS_INV_EN_LENGTH 		1
#define MMS_LSW_EN_LENGTH 		1
#define MMS_MPPT_MAXPWR_LENGTH 	2
#define MMS_BMS_SWBATT_LENGTH 	1
#define MMS_LSW_SWLOADS_LENGTH	8
#define BMS_MMS_OCH_LENGTH 		1
#define BMS_MMS_UCH_LENGTH 		1
#define BMS_MMS_OT_LENGTH 		1

#endif
