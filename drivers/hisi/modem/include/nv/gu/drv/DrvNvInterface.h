/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : DrvNvInterface.h
  Description     : DrvNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __DRVNVINTERFACE_H__
#define __DRVNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

/*****************************************************************************
  2 Macro
*****************************************************************************/
#if defined(__OS_VXWORKS__)
#else
typedef signed int          BSP_S32;
typedef signed short        BSP_S16;
typedef signed char         BSP_S8;
typedef char                BSP_CHAR;

typedef unsigned int        BSP_U32;
typedef unsigned short      BSP_U16;
typedef unsigned char       BSP_U8;
#endif

#define KPD_NV_UNIT               (16)  /* total 16 * 32Bit = 64bytes */
#define KPD_EVENT_MAX             (KPD_NV_UNIT-3)

#define NV_WLCOUNTRY_CODE_LEN     (5)
#define NV_WLMODE_LEN             (5)
#define NV_WLSSID_LEN             (33)

#define NV_FACTORY_INFO_I_SIZE    (78)

#define DYN_MAX_PORT_CNT          (17)

/* ???????????????????? */
#if defined (DYNAMIC_PID_MAX_PORT_NUM)
#undef DYNAMIC_PID_MAX_PORT_NUM
#endif
#define DYNAMIC_PID_MAX_PORT_NUM  (17)

/* ?????????????????????? */
#if defined (VER_MAX_LENGTH)
#undef VER_MAX_LENGTH
#endif
#define VER_MAX_LENGTH            (30)

#define NV_HW_CFG_LENTH           (0x40)

/*NPNP ????????????????????*/
#define NPNP_OPEN    1
#define NPNP_CLOSE    0

/*NPNP????NV??????????*/
#define NV_NPNP_ENABLE    1
#define NV_NPNP_DISABLE    0
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ????????????????                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 ??????    : RESUME_FLAG_STRU
 ????????  : RESUME_FLAG????
*****************************************************************************/
typedef struct
{
    BSP_U16   usResumeFlag; /*Range:[0, 1]*/
}RESUME_FLAG_STRU;

/*****************************************************************************
 ??????    : LED_CONTROL_NV_STRU
 ????????  : LED_CONTROL_NV???? ID=7
*****************************************************************************/
typedef struct
{
    BSP_U8   ucLedColor;      /*????????????????LED_COLOR????*/
    BSP_U8   ucTimeLength;    /*??????????????????????????100ms*/
}LED_CONTROL_NV_STRU;

/*****************************************************************************
 ??????    : LED_CONTROL_STRU
 ????????  : LED_CONTROL????
*****************************************************************************/
typedef struct
{
    LED_CONTROL_NV_STRU   stLED[10];
}LED_CONTROL_STRU;

/*****************************************************************************
 ??????    : LED_CONTROL_STRU_ARRAY
 ????????  : ??????????????????????
*****************************************************************************/
typedef struct
{
    LED_CONTROL_STRU    stLED_Control[32];
}LED_CONTROL_STRU_ARRAY;

/*****************************************************************************
 ??????    : NV_WDT_TIMEOUT_STRU
 ????????  : NV_WDT_TIMEOUT???? ID=11
*****************************************************************************/
typedef struct
{
    BSP_U32   ulWdtTimeOut;
}NV_WDT_TIMEOUT_STRU;


/*****************************************************************************
 ??????    : USIM_TEMP_SENSOR_TABLE
 ????????  : USIM_TEMP_SENSOR_TABLE????
*****************************************************************************/
typedef struct
{
    BSP_S16   Temperature;
    BSP_U16   Voltage;
}USIM_TEMP_SENSOR_TABLE;

/*****************************************************************************
 ??????    : USIM_TEMP_SENSOR_TABLE_STRU
 ????????  : USIM_TEMP_SENSOR_TABLE????
*****************************************************************************/
typedef struct
{
    USIM_TEMP_SENSOR_TABLE UsimTempSensorTable[19];
}USIM_TEMP_SENSOR_TABLE_STRU;


/*****************************************************************************
 ??????    : EXCEPTION_RECORD_STRU
 ????????  : EXCEPTION_RECORD????
*****************************************************************************/
typedef struct
{
    BSP_U32     IsEnable;
    BSP_U32     Config;
    BSP_U32     Reserve;
}EXCEPTION_RECORD_STRU;


/*****************************************************************************
 ??????    : NV_SYS_PRT_STRU
 ????????  : NV_SYS_PRT????
*****************************************************************************/
typedef struct
{
    BSP_U32    uintValue;
}NV_SYS_PRT_STRU;


/*****************************************************************************
 ??????    : USB_ENUM_STATUS_STRU
 ????????  : USB_ENUM_STATUS????
*****************************************************************************/
typedef struct
{
    BSP_U32    status;
    BSP_U32    value;
    BSP_U32    reserve1;
    BSP_U32    reserve2;
}USB_ENUM_STATUS_STRU;


/*****************************************************************************
 ??????    : LIVE_TIME_CONTROL_STRU
 ????????  : LIVE_TIME_CONTROL????
*****************************************************************************/
typedef struct
{
    BSP_U32    ulEnable;
    BSP_U32    ulCycle;
} LIVE_TIME_CONTROL_STRU;


/*****************************************************************************
 ??????    : LIVE_TIME_STRU
 ????????  : LIVE_TIME????
*****************************************************************************/
typedef struct
{
    BSP_U32    ulLiveTime;
}LIVE_TIME_STRU;


/*****************************************************************************
 ??????    : USB_SN_NV_INFO_STRU
 ????????  : USB_SN_NV_INFO????
*****************************************************************************/
typedef struct
{
    BSP_U32    usbSnNvStatus;
    BSP_U32    usbSnNvSucFlag;
    BSP_U32    usbSnReserved1;
    /*BSP_U32    usbSnReserved2;*/
}USB_SN_NV_INFO_STRU;


/*****************************************************************************
 ??????    : NVHWVER
 ????????  : NVHWVER????
*****************************************************************************/
typedef struct
{
    BSP_U32    NV_HW_VER_Flag;
    BSP_U8     NV_HW_VER_VAL[8];
} NVHWVER;

/*****************************************************************************
 ??????    : nv_pid_enable_type
 ????????  : nv_pid_enable_type????
*****************************************************************************/
typedef struct
{
    BSP_U32    pid_enabled;
}nv_pid_enable_type;


/*****************************************************************************
 ??????    : NV_AT_SHELL_OPEN_FLAG_STRU
 ????????  : NV_AT_SHELL_OPEN_FLAG????
*****************************************************************************/
typedef struct
{
    BSP_U32    NV_AT_SHELL_OPEN_FLAG;
}NV_AT_SHELL_OPEN_FLAG_STRU;

/*****************************************************************************
 ??????    : TEMP_ADC_STRU
 ????????  : TEMP_ADC????
*****************************************************************************/
typedef struct
{
    BSP_S16    sTemp;
    BSP_U16    usADC;
}TEMP_ADC_STRU;

/*****************************************************************************
 ??????    : TEMP_ADC_STRU_ARRAY
 ????????  : TEMP_ADC_STRU_ARRAY????
*****************************************************************************/
typedef struct
{
    TEMP_ADC_STRU    stTempAdc[28];
}TEMP_ADC_STRU_ARRAY;

/*****************************************************************************
 ??????    : nv_drv_customize_type
 ????????  : nv_drv_customize_type????
*****************************************************************************/
typedef struct DRV_CUSTOMIZE_TYPE
{
    BSP_U32 drv_customize_type;
} nv_drv_customize_type;

/*****************************************************************************
 ??????    : NV_ITEM_MODIFY_LINKINFO_FLAG_STRU
 ????????  : NV_ITEM_MODIFY_LINKINFO_FLAG????
*****************************************************************************/
typedef struct
{
    BSP_U16    NV_ITEM_MODIFY_LINKINFO_FLAG;  /*Range:[0,1]*/
}NV_ITEM_MODIFY_LINKINFO_FLAG_STRU;


/*****************************************************************************
 ??????    : CHG_TEMP_ADC_TYPE
 ????????  : CHG_TEMP_ADC_TYPE????
*****************************************************************************/
typedef struct
{
    BSP_S16   temperature;
    BSP_U16   voltage;
}CHG_TEMP_ADC_TYPE;

/*****************************************************************************
 ??????    : FACTORY_MODE_TYPE
 ????????  : FACTORY_MODE_TYPE????
             ????????nv??,0 : ???????? 1: ?????????? 36
*****************************************************************************/
typedef struct
{
    BSP_U32 factory_mode;
}FACTORY_MODE_TYPE;

/*****************************************************************************
 ??????    : NV_WEBNAS_SD_WORKMODE_STRU
 ????????  : NV_WEBNAS_SD_WORKMODE????
*****************************************************************************/
typedef struct
{
    BSP_U32 ulSDWorkMode;
}NV_WEBNAS_SD_WORKMODE_STRU;

/*****************************************************************************
 ??????    : HW_WDT_FLAG_STRU
 ????????  : HW_WDT_FLAG????
*****************************************************************************/
typedef struct
{
    BSP_U32   HW_WDT_FLAG;
}HW_WDT_FLAG_STRU;

/*****************************************************************************
 ??????    : POWER_LED_ENABLE_STRU
 ????????  : POWER_LED_ENABLE????
*****************************************************************************/
typedef struct
{
    BSP_U32   POWER_LED_ENABLE;
}POWER_LED_ENABLE_STRU;

/*****************************************************************************
 ??????    : NV_HW_CONFIG_STRU
 ????????  : NV_HW_CONFIG????
*****************************************************************************/
/* PMU??????????,8Byte */
typedef struct
{
	BSP_U8 PowerEn;
	BSP_U8 ModuleID;
	BSP_U8 DevID;
	BSP_U8 PowerID;
	BSP_U8 ConsumerID;
	BSP_U8 Reserve;
	BSP_U16 Voltage;
}PMU_POWER_CFG;

/*????????????????????????????????,??????????????,????????????*/
/*BUCK1*/
typedef struct
{
	BSP_U8 PowerEn;
	BSP_U8 ModuleID;
	BSP_U8 DevID;
	BSP_U8 PowerID;
	BSP_U8 ConsumerID;
	BSP_U8 Reserve;
	BSP_U16 Voltage;  /*Range:[0,2200]*/
}PMU_POWER_CFG_RFICTX;

/* PMU????,16?? */
typedef struct
{
	PMU_POWER_CFG 		 RF0_PA;
	PMU_POWER_CFG_RFICTX RFIC0_TX;
	PMU_POWER_CFG 		 RFIC0_RX;
	PMU_POWER_CFG 		 FEM0;
	PMU_POWER_CFG 		 RF0_VBIAS;

	PMU_POWER_CFG 		 RF1_PA;
	PMU_POWER_CFG_RFICTX RFIC1_TX;
	PMU_POWER_CFG 		 RFIC1_RX;
	PMU_POWER_CFG 		 FEM1;
	PMU_POWER_CFG 		 RF1_VBIAS;

	PMU_POWER_CFG FEM0_AUX;
	PMU_POWER_CFG PMU_RESERVE1;
	PMU_POWER_CFG PMU_RESERVE2;
	PMU_POWER_CFG PMU_RESERVE3;
	PMU_POWER_CFG PMU_RESERVE4;
	PMU_POWER_CFG PMU_RESERVE5;
}PMU_CFG_STRU;


typedef struct
{
    BSP_U16 ConsumerID;
    BSP_U16 PowerEn;/*0:??????????????1: ????????*/
    BSP_U16 Voltage;
    BSP_U16 ModuleID;
    BSP_U16 DevID;
    BSP_U16 PowerID;
    BSP_U16 Reserve;
}RF_PMU_CFG_STRU;

#define RF_POWER_MAX_NUM (24)
#define RF_POWER_RESERVE_NUM  (8)/*??????24-14-2??????HIMS??????????*/

typedef struct
{
    BSP_U16 W_PA_VCC;
    BSP_U16 G_PA_VCC;
    BSP_U16 CH0_W_RFIC_TX_ANA;
    BSP_U16 CH0_G_RFIC_TX_ANA;
    BSP_U16 CH1_W_RFIC_TX_ANA;
    BSP_U16 CH1_G_RFIC_TX_ANA;
    RF_PMU_CFG_STRU CH0_PA_VCC;
    RF_PMU_CFG_STRU CH0_PA_VBIAS;
    RF_PMU_CFG_STRU CH0_SWITCH_VCC;
    RF_PMU_CFG_STRU CH0_RFIC_TX_ANA;
    RF_PMU_CFG_STRU CH0_RFIC_RX_ANA;
    RF_PMU_CFG_STRU CH0_FEM_VIO;
    RF_PMU_CFG_STRU CH0_TUNNER_VCC;
    RF_PMU_CFG_STRU CH1_PA_VCC;
    RF_PMU_CFG_STRU CH1_PA_VBIAS;
    RF_PMU_CFG_STRU CH1_SWITCH_VCC;
    RF_PMU_CFG_STRU CH1_RFIC_TX_ANA;
    RF_PMU_CFG_STRU CH1_RFIC_RX_ANA;
    RF_PMU_CFG_STRU CH1_FEM_VIO;
    RF_PMU_CFG_STRU CH1_TUNNER_VCC;
    RF_PMU_CFG_STRU CH0_RFIC_XO_2P85;
    RF_PMU_CFG_STRU CH1_RFIC_XO_2P85;
    RF_PMU_CFG_STRU PMU_CFG[RF_POWER_RESERVE_NUM];
 }RF_VOLT_CONFIG_STRU;

/*----------------------??RF RSE??????Begin--------------------------------*/
/* gpio???? ????????????NV*/
#define DRV_ANT_SW_UNPD_ENFLAG_DISABLE 0
#define DRV_ANT_SW_UNPD_ENFLAG_ENABLE  1
typedef struct
{
    BSP_U32 is_enable;/*Range [0,1] ????: 0-???????? 1-????????*/
 }DRV_ANT_SW_UNPD_ENFLAG;

#define DRV_ANT_GPIO_CFG_UNUSED 0
#define DRV_ANT_GPIO_CFG_USED   1
typedef struct
{
    BSP_U32 gpio_num;/*gpio????*//*????????RF_GPIO_NUM ??*/
    BSP_U32 is_used;  /*Range[0,1]*//*????????*/
    BSP_U32 value;   /*??????*/
}DRV_ANT_GPIO_CFG;

#define GPIO_RF_ANT_SW_MAX 8
typedef struct{
    DRV_ANT_GPIO_CFG antn_switch[GPIO_RF_ANT_SW_MAX];
} DRV_ANT_SW_UNPD_CFG;

typedef struct
{
    DRV_ANT_SW_UNPD_CFG  all_switch[3];/*??????????0??????????????1??????????????2????????*/
} NV_DRV_ANT_SW_UNPD_CFG;


/* mipi???? ????????????NV*/
#define DRV_ANT_SW_MIPI_ENFLAG_DISABLE 0
#define DRV_ANT_SW_MIPI_ENFLAG_ENABLE  1
typedef struct
{
	BSP_U32 is_enable;/*Range:[0,1] ??????0-???????? 1-????????*/
} DRV_ANT_SW_MIPI_ENFLAG;

#define DRV_ANT_SW_MIPI_INVALID 0
#define DRV_ANT_SW_MIPI_VALID   1
typedef struct
{
    BSP_U32 is_invalid;/*Range:[0,1] ??????0-???????????? 1-????????????*/
    BSP_U8 mipi_chn;/*Range:[0,1]*/
    BSP_U8 slave_id;
    BSP_U8 reg_offset;
    BSP_U8 value;
} DRV_ANT_SW_MIPI;

#define MIPI_RF_ANT_SW_MAX 8
typedef struct
{
	DRV_ANT_SW_MIPI modem_switch[MIPI_RF_ANT_SW_MAX];
} DRV_ANT_SW_MIPI_CONFIG;

typedef struct
{
	DRV_ANT_SW_MIPI_CONFIG all_switch[2];/*??????????0??????????1????????*/
} DRV_DRV_ANT_SW_MIPI_CONFIG;

/*----------------------??RF RSE??????End--------------------------------*/

/*----------------------??TDS/L B34/39 & GSM B3????????????????Begin--------------------------------*/

#define NV_GSM_GPIO_RESERVED_NUM_L 2
/*****************************************************************************
 ??????    : UCOM_NV_GSM_GPIO_FUNC_SEL_STRU
 ????????  :
 ASN.1???? :
 ????????  : GPIO2~5????????
*****************************************************************************/
typedef struct
{
    BSP_U16 uhwGpioAndOrSel;        /* GPIO????????????
                                        bit0~1	 	Reserved
                                        bit2    	GPIO2??????????    0--GPIO??modem????????(????)??1--GPIO??modem????????
                                        bit3 		GPIO3??????????    ????
                                        bit4 		GPIO4??????????    ????
                                        bit5 		GPIO5??????????    ????
                                        bit6~15	Reserved*/
    BSP_U16 uhwGpioCtrlAbbTxSel;    /* GPIO????????????????abb tx
                                        bit0~1	 	Reserved
                                        bit2    	GPIO2??????????????????abb tx   0--??????abb??tx(????)??1--????abb??tx
                                        bit3 		GPIO3??????????????????abb tx   	????
                                        bit4~15	Reserved*/
}UCOM_NV_GSM_GPIO_FUNC_SEL_STRU;

/*----------------------??TDS/L B34/39 & GSM B3????????????????End--------------------------------*/

/*????????????*/
typedef struct
{
	BSP_U8 OTMP_TMP;          /*????????????????*/
	BSP_U8 OTMP_PWR_DOWN;     /*??????????????????????????*/
	BSP_U8 OTMP_RESET;        /*??????????????????????*/
	BSP_U8 RESERVE;
}PMU_PROTECT_STRU;

typedef struct
{
	BSP_U32 RESERVE0;           	/* ????,4Byte */
	BSP_U16 W_PA_V;            		/* W PA???? 2Byte */
	BSP_U16 G_PA_V;             	/* G PA???? 2Byte */
	BSP_U32 USB_EYE_CFG;        	/* USB???? 4Byte */
	BSP_U32 APT_MODE;           	/* APT ???? 4Byte??????DR_APT_CFG_ENUM */
	PMU_PROTECT_STRU PMU_PROTECT;   /* PMU ???????? 4Byte*/
	BSP_U32 DRV_LOG_CTRL;       	/* DRVLOG???????? 4Byte */
	BSP_U32 DRV_LOG_LEVEL;      	/* DRVLOG???????? 4Byte */
	BSP_U32 RESERVE7;           	/* ????,4Byte */

	/*PMU NV??????*/
	PMU_CFG_STRU PMU_CFG;
	BSP_U32 PMU_CRC32;	     /* PMU CRC????,4Byte */

	/* ????,????23(*)4Byte */
	BSP_U32 RESERVE41;
	BSP_U32 RESERVE42;
	BSP_U32 RESERVE43;
	BSP_U32 RESERVE44;
	BSP_U32 RESERVE45;
	BSP_U32 RESERVE46;
	BSP_U32 RESERVE47;
	BSP_U32 RESERVE48;
	BSP_U32 RESERVE49;
	BSP_U32 RESERVE50;
	BSP_U32 RESERVE51;
	BSP_U32 RESERVE52;
	BSP_U32 RESERVE53;
	BSP_U32 RESERVE54;
	BSP_U32 RESERVE55;
	BSP_U32 RESERVE56;
	BSP_U32 RESERVE57;
	BSP_U32 RESERVE58;
	BSP_U32 RESERVE59;
	BSP_U32 RESERVE60;
	BSP_U32 RESERVE61;
	BSP_U32 RESERVE62;
	BSP_U32 ANT_MODE;
}NV_HW_CONFIG_STRU;

/*****************************************************************************
 ??????    : UART_SWITCH_ENUM
 ????????  : UART????????????

  1.??    ??   : 2013??12??19??
    ??    ??   : f00204170
    ????????   : UART????????
*****************************************************************************/
enum UART_SWITCH_ENUM
{
    UART_SWITCH_DISABLE = 0,
    UART_SWITCH_ENABLE  = 1,
    UART_SWITCH_BUTT
};

typedef BSP_U8 UART_SWITCH_ENUM_UINT8;
/*****************************************************************************
 ??????    : NV_UART_SWITCH_STRU
 ????????  : ??
 ????????  :  ????????UART????????????????????

 ????????      :
  1.??    ??   : 2013??12??19??
    ??    ??   : f00204170
    ????????   :
*****************************************************************************/
typedef struct
{
    UART_SWITCH_ENUM_UINT8  enUartEnableCfg;
    BSP_U8  uartRsv[3];
}NV_UART_SWITCH_STRU;

/*****************************************************************************
 ??????    : KPD_NV_VERSION_1_1_T
 ????????  : KPD_NV_VERSION_1_1_T????
*****************************************************************************/
typedef struct
{
    BSP_U32  ulversion;                    /* Should be 0x0001_0000. major + minor */
    BSP_U32  ulkeyupdatetime;              /* 0 means not support. non-zero is the update check time */
    BSP_U32  ultickunit;                   /* the tick unit. ms */
    BSP_U32  ulitemtable[ KPD_EVENT_MAX ]; /* sizeof(versio_1_1) = 64bytes */
}KPD_NV_VERSION_1_1_T;                     /* version 1.1 structure */

/*****************************************************************************
 ??????    : HWIFI_TARGET_ASSERT_ENABLE_STRU
 ????????  : HWIFI_TARGET_ASSERT_ENABLE????
*****************************************************************************/
typedef struct
{
    BSP_U32   WIFI_TARGET_ASSERT_ENABLE;
}HWIFI_TARGET_ASSERT_ENABLE_STRU;


/*****************************************************************************
 ??????    : HILINK_AUTORUN_FLAG_STRU
 ????????  : HILINK_AUTORUN_FLAG????
*****************************************************************************/
typedef struct
{
    BSP_U16   HILINK_AUTORUN_FLAG;
}HILINK_AUTORUN_FLAG_STRU;

/*****************************************************************************
 ??????    : VBAT_CALIBART_TYPE
 ????????  : ????????????????????
*****************************************************************************/
typedef struct
{
    BSP_U16 min_value;
    BSP_U16 max_value;
}VBAT_CALIBART_TYPE;

/*****************************************************************************
 ??????    : NV_FACTORY_INFO_I_STRU
 ????????  : NV_FACTORY_INFO_I????
*****************************************************************************/
typedef struct
{
    BSP_CHAR aucFactoryInfo[NV_FACTORY_INFO_I_SIZE];
}NV_FACTORY_INFO_I_STRU;

/*****************************************************************************
 ??????    : NV_USB_LOG_SAVE_LEV
 ????????  : NV_USB_LOG_SAVE_LEV????
*****************************************************************************/
typedef struct
{
    BSP_U32 NV_USB_LOG_SAVE_LEV;
}NV_USB_LOG_SAVE_LEV_STRU;


/*****************************************************************************
 ??????    : DR_NV_ENHANCE_SIMCARD_LOCK_STATUS_STRU
 ????????  : ????????????????????   ID=8517
*****************************************************************************/
typedef struct
{
    BSP_U8  EnhanceSimcardStatus;     /* ?????????????????????? 0:??????, 1: ???? */
    BSP_U8  SimcardStatus;            /* SimCardLockStatus???????? 1: ????????, 2: ?????????? */
}DR_NV_ENHANCE_SIMCARD_LOCK_STATUS_STRU;

/*****************************************************************************
 ??????    : NV_BREATH_LED_STR
 ????????  : NV_BREATH_LED????     ID=9051
*****************************************************************************/
typedef struct
{
    BSP_U8 ucBreathOnTime;
    BSP_U8 ucBreathOffTime;
    BSP_U8 ucBreathRiseTime;
    BSP_U8 ucBreathFallTime;
}NV_BREATH_LED_STR;

/*****************************************************************************
 ??????    : CHG_BATTERY_TEMP_PROTECT_NV_TYPE
 ????????  : CHG_BATTERY_TEMP_PROTECT_NV_TYPE????     ID=50016
*****************************************************************************/
typedef struct
{
    BSP_U32  ulIsEnable;
    BSP_S32  lCloseAdcThreshold;
    BSP_U32  ulTempOverCount;
}CHG_BATTERY_TEMP_PROTECT_NV_TYPE;

/*****************************************************************************
 ??????    : nv_huawei_connect_display_rate_type
 ????????  : nv_huawei_connect_display_rate_type????     ID=50027
*****************************************************************************/
typedef struct
{
    BSP_U8 gsm_connect_rate;
    BSP_U8 gprs_connect_rate;
    BSP_U8 edge_connect_rate;
    BSP_U8 wcdma_connect_rate;
    BSP_U8 hspda_connect_rate;
    BSP_U8 reserved;           /*????????*/
}nv_huawei_connect_display_rate_type;


/*****************************************************************************
 ??????    : PROIDNvInfo
 ????????  : PROIDNvInfo????     ID=50018,ID=50048
*****************************************************************************/
typedef struct _productIDNvInfo
{
    BSP_U32   NvStatus;
    BSP_U8    ucCompVer[VER_MAX_LENGTH];
} PROIDNvInfo;

/*****************************************************************************
 ??????    : NV_HUAWEI_PCCW_HS_HSPA_BLUE_STRU
 ????????  : NV_HUAWEI_PCCW_HS_HSPA_BLUE???? ID=50032
*****************************************************************************/
typedef struct
{
    BSP_U32  NVhspa_hs_blue; /*Range:[0,3]*/
}NV_HUAWEI_PCCW_HS_HSPA_BLUE_STRU;


/*****************************************************************************
 ??????    : nvi_cust_pid_type
 ????????  : nvi_cust_pid_type????
*****************************************************************************/
typedef struct
{
    BSP_U32  nv_status;
    BSP_U16  cust_first_pid;
    BSP_U16  cust_rewind_pid;
}nvi_cust_pid_type;


/*****************************************************************************
 ??????    : nv_protocol_base_type
 ????????  : nv_protocol_base_type????
*****************************************************************************/
typedef struct
{
    BSP_U32  nv_status;
    BSP_U32  protocol_base;
}nv_protocol_base_type;

/*****************************************************************************
 ??????    : nv_huawei_dynamic_pid_type
 ????????  : nv_huawei_dynamic_pid_type???? ID=50091 ????????
*****************************************************************************/
typedef struct PACKED_POST
{
    BSP_U32 nv_status;
    BSP_U8  first_port_style[DYNAMIC_PID_MAX_PORT_NUM];
    BSP_U8  rewind_port_style[DYNAMIC_PID_MAX_PORT_NUM];
    BSP_U8  reserved[22];
} nv_huawei_dynamic_pid_type;


/*****************************************************************************
 ??????    : USB_NV_SN_INFO_T
 ????????  : USB_NV_SN_INFO_T????
*****************************************************************************/
typedef struct tagUSB_NV_SN_INFO_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
    BSP_U32 u32USBNvResult;
} USB_NV_SN_INFO_T;

/*****************************************************************************
 ??????    : USB_NV_DEV_INFO_T
 ????????  : USB_NV_DEV_INFO_T????
*****************************************************************************/
typedef struct tagUSB_NV_DEV_INFO_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBDevTypeIdx;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
/*    BSP_U32 u32USBNvResult;*/
} USB_NV_DEV_INFO_T;

/*****************************************************************************
 ??????    : USB_NV_SERIAL_NUM_T
 ????????  : USB_NV_SERIAL_NUM_T????
*****************************************************************************/
typedef struct tagUSB_NV_SERIAL_NUM_T
{
    BSP_U32 u32USBSerialNumSupp;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
    BSP_U32 u32USBNvResult;
} USB_NV_SERIAL_NUM_T;

/*****************************************************************************
 ??????    : USB_NV_NEW_PID_INFO_T
 ????????  : USB_NV_NEW_PID_INFO_T????
*****************************************************************************/
typedef struct tagUSB_NV_NEW_PID_INFO_T
{
    BSP_U32 u32USBNewPidSupp;
} USB_NV_NEW_PID_INFO_T;

/*****************************************************************************
 ??????    : USB_NV_PID_UNION_T
 ????????  : USB_NV_PID_UNION_T????
*****************************************************************************/
typedef struct tagUSB_NV_PID_UNION_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBProtOfs;   /* change from "u32USBVDFCust" to "u32USBProtOfs" */
    BSP_U32 u32USBCdromPid;
    BSP_U32 u32USBUniquePid;
} USB_NV_PID_UNION_T;

/*****************************************************************************
 ??????    : USB_NV_DEV_PROFILE_T
 ????????  : USB_NV_DEV_PROFILE_T????
*****************************************************************************/
typedef struct tagUSB_NV_DEV_PROFILE_T
{
    BSP_U32 u32USBNvState;
    BSP_U8  u8USBFirstPortSeq[DYN_MAX_PORT_CNT];
    BSP_U8  u8USBMultiPortSeq[DYN_MAX_PORT_CNT];
    BSP_U8  u8USBPortReserved[2];
} USB_NV_DEV_PROFILE_T;


/*****************************************************************************
 ??????    : NV_SECBOOT_ENABLE_FLAG
 ????????  : NV_SECBOOT_ENABLE_FLAG???? ID=50201
*****************************************************************************/
typedef struct
{
    BSP_U16 usNVSecBootEnableFlag; /*Range:[0,1]*/
}NV_SECBOOT_ENABLE_FLAG;


/*****************************************************************************
 ??????    : nv_wifibs_type
 ????????  : nv_wifibs_type????
*****************************************************************************/
typedef struct
{
    BSP_U8   aucwlSsid[NV_WLSSID_LEN];
    BSP_U32  ulwlChannel;
    BSP_U32  ulwlHide;
    BSP_U8   aucwlCountry[NV_WLCOUNTRY_CODE_LEN];
    BSP_U8   aucwlMode[NV_WLMODE_LEN];
    BSP_U32  ulwlRate;
    BSP_U32  ulwlTxPwrPcnt;
    BSP_U32  ulwlMaxAssoc;
    BSP_U8   ucwlEnbl;
    BSP_U32  ulwlFrgThrshld;
    BSP_U32  ulwlRtsThrshld;
    BSP_U32  ulwlDtmIntvl;
    BSP_U32  ulwlBcnIntvl;
    BSP_U32  ulwlWme;
    BSP_U32  ulwlPamode;
    BSP_U32  ulwlIsolate;
    BSP_U32  ulwlProtectionmode;
    BSP_U32  ulwloffenable;
    BSP_U32  ulwlofftime;
    BSP_U8   aucwlExtends[12];
}nv_wifibs_type;


/*****************************************************************************
 ??????    : CHG_BATTERY_LOW_TEMP_PROTECT_NV
 ????????  : CHG_BATTERY_LOW_TEMP_PROTECT_NV???? ID=52005
*****************************************************************************/
typedef struct
{
    BSP_U32  ulIsEnable;
    BSP_S32  lCloseAdcThreshold;
    BSP_U32  ulTempLowCount;
}CHG_BATTERY_LOW_TEMP_PROTECT_NV;

/*****************************************************************************
 ??????    : NV_SCI_CFG_STRU
 ????????  : NV_SCI_CFG???? ID=128
*****************************************************************************/
typedef struct
{
    BSP_U32 value;
} NV_SCI_CFG_STRU;

/*****************************************************************************
 ??????    : NV_GCF_TYPE_CONTENT_STRU
 ????????  : NV_GCF_TYPE_CONTENT???? ID=8250
*****************************************************************************/
typedef struct
{
    BSP_U8 GCFTypeContent[4];
}NV_GCF_TYPE_CONTENT_STRU;

/*****************************************************************************
 ??????    : nv_wifi_info
 ????????  : nv_wifi_info????
*****************************************************************************/
typedef struct
{
    BSP_U32 ulOpSupport;
    BSP_U8  usbHighChannel;
    BSP_U8  usbLowChannel;
    BSP_U8  aucRsv1[2];
    BSP_U16 ausbPower[2];
    BSP_U8  usgHighsChannel;
    BSP_U8  usgLowChannel;
    BSP_U8  aucRsv2[2];
    BSP_U16 ausgPower[2];
    BSP_U8  usnHighsChannel;
    BSP_U8  usnLowChannel;
    BSP_U8  ausnRsv3[2];
    BSP_U16 ausnPower[2];
}nv_wifi_info;

/*****************************************************************************
 ??????    : NV_ITEM_USB_PKT_HOOK_STRU
 ????????  : NV_ITEM_USB_PKT_HOOK???? ID=119
*****************************************************************************/
typedef struct
{
    BSP_U16 usUsbPktHookFlag;
}NV_ITEM_USB_PKT_HOOK_STRU;   /*USB????NV??????*/

/*****************************************************************************
 ??????    : TEM_VOLT_TABLE
 ????????  : TEM_VOLT_TABLE????
*****************************************************************************/
typedef struct tem_volt_table
{
    BSP_S16   temperature;
    BSP_U16   voltage;
}TEM_VOLT_TABLE;

/*****************************************************************************
 ??????    : UE_POINT_CTRL_STRU
 ????????  : UE_POINT_CTRL???? ID=15
*****************************************************************************/
typedef struct
{
    BSP_U32     Status;
    BSP_U32     ProductForm;
    BSP_U16     Pid;
    BSP_U16     FakePid;
    BSP_U8      Mac[8];
}UE_POINT_CTRL_STRU;

/*****************************************************************************
 ??????    : NV_CUSTOMIZE_REWIND_DELAY_TIME_I_STRU
 ????????  : NV_CUSTOMIZE_REWIND_DELAY_TIME_I???? ID=25
*****************************************************************************/
typedef struct
{
    BSP_U32     Status;    /*Range:[0,1]*/
    BSP_U16     Timeout;
}NV_CUSTOMIZE_REWIND_DELAY_TIME_I_STRU;

/*****************************************************************************
 ??????    : NV_OLED_TEMP_ADC_STRU
 ????????  : NV_OLED_TEMP_ADC????
*****************************************************************************/
typedef struct
{
    BSP_S16       sTemp;
    BSP_S16       sADC;
}NV_OLED_TEMP_ADC_STRU;

/*****************************************************************************
 ??????    : NV_OLED_TEMP_ADC_STRU_ARRAY
 ????????  : NV_OLED_TEMP_ADC_STRU_ARRAY????  ID=49
*****************************************************************************/
typedef struct
{
    NV_OLED_TEMP_ADC_STRU          stNV_OLED_TEMP_ADC[28];
}NV_OLED_TEMP_ADC_STRU_ARRAY;

/*****************************************************************************
 ??????    : NV_SW_VER_STRU
 ????????  : NV_SW_VER????
*****************************************************************************/
typedef struct
{
    BSP_S32        nvStatus;
    BSP_S8         nv_version_info[30];
}NV_SW_VER_STRU;

/*****************************************************************************
 ??????    : NV_TCXO_CFG_STRU
 ????????  : NV_TCXO_CFG???? ID=9217
*****************************************************************************/
typedef struct
{
    BSP_U32 tcxo_cfg;
}NV_TCXO_CFG_STRU;

/*****************************************************************************
 ??????    : NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG_STRU
 ????????  : NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG???? ID=9216
*****************************************************************************/
typedef struct
{
    BSP_U16 hkadc[14];
}NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG_STRU;

/*****************************************************************************
 ??????    : NV_THERMAL_HKADC_CONFIG
 ????????  : NV_THERMAL_HKADC_CONFIG???? ID=9232
*****************************************************************************/
typedef struct
{
    BSP_U16 hkadc[32];
}NV_KADC_CHANNEL_CFG_STRU;
typedef struct
{
    BSP_U32   outconfig;
    BSP_U16   outperiod;
    BSP_U16   convertlistlen;
    BSP_U32   reserved[2];
}NV_THERMAL_HKADC_CONFIG;

/*****************************************************************************
 ??????    : NV_THERMAL_HKADC_CONFIG_STRU
 ????????  : NV_THERMAL_HKADC_CONFIG???? ID=9215
*****************************************************************************/
typedef struct
{
    NV_THERMAL_HKADC_CONFIG   hkadcCfg[14];
}NV_THERMAL_HKADC_CONFIG_STRU;

/*****************************************************************************
 ??????    : NV_THERMAL_BAT_CONFIG_STRU
 ????????  : NV_THERMAL_BAT_CONFIG???? ID=9214
*****************************************************************************/
typedef struct
{
    BSP_U16       enable;
    BSP_U16       hkadcid;
    BSP_S16       highthres;
    BSP_U16       highcount;
    BSP_S16       lowthres;
    BSP_U16       lowcount;
    BSP_U32       reserved[2];

}NV_THERMAL_BAT_CONFIG_STRU;

/*****************************************************************************
 ??????    : NV_THERMAL_TSENSOR_CONFIG_STRU
 ????????  : NV_THERMAL_TSENSOR_CONFIG???? ID=9213
*****************************************************************************/
typedef struct
{
    BSP_U32       enable;
    BSP_U32       lagvalue0;
    BSP_U32       lagvalue1;
    BSP_U32       thresvalue0;
    BSP_U32       thresvalue1;
    BSP_U32       rstthresvalue0;
    BSP_U32       rstthresvalue1;
    BSP_U32       alarmcount1;
    BSP_U32       alarmcount2;
    BSP_U32       resumecount;
    BSP_U32       acpumaxfreq;
    BSP_U32       gpumaxfreq;
    BSP_U32       ddrmaxfreq;
    BSP_U32       reserved[4];
}NV_THERMAL_TSENSOR_CONFIG_STRU;

/*****************************************************************************
 ??????    : NV_TUNER_MIPI_INIT_CONFIG_STRU
 ????????  : NV_TUNER_MIPI_INIT_CONFIG_STRU???? ID=10046
*****************************************************************************/
#define TUNER_USER_DATA_MAX_NUM (9)
#define TUNER_MAX_NUM           (2)
typedef struct
{
    BSP_U8 mipiChan;
    BSP_U8 validNum;
    BSP_U16 cmdFrame[TUNER_USER_DATA_MAX_NUM];
    BSP_U16 dataFrame[TUNER_USER_DATA_MAX_NUM];
}NV_TUNER_MIPI_FRAME_CONFIG_STRU;

typedef struct
{
    NV_TUNER_MIPI_FRAME_CONFIG_STRU RFInitReg[TUNER_MAX_NUM];
}NV_GU_RF_FEND_MIPI_INIT_CONFIG_STRU;
/*****************************************************************************
 ??????    : WG_DRX_RESUME_TIME_STRU
 ????????  : WG_DRX_RESUME_TIME_STRU???? ID=10031
*****************************************************************************/
typedef struct
{
    unsigned long ulAbbPwrRsmTime;
    unsigned long ulRfPwrRsmTime;
    unsigned long ulAntSwitchPwrRsmTime;
    unsigned long ulAbbWpllRsmTime;
    unsigned long ulAbbGpllRsmTime;
    unsigned long ulBbpPllRsmTime;
    unsigned long ulPaStarRsmTime;
    unsigned long ulSysProtectTime;
    unsigned long ulTcxoRsmTime;
    unsigned long ulDcxoRsmTime;
    unsigned long ulSlowToMcpuRsmTime;
    unsigned long ulWphyRsmTime;
    unsigned long ulGphyRsmTime;
    unsigned long ulTaskSwitchRsmTime;
    unsigned long ulPaPwrRsmTime;
}WG_DRX_RESUME_TIME_STRU;

/*****************************************************************************
 ??????    : NV_NPNP_CONFIG_INFO
 ????????  : NV_NPNP_CONFIG_INFO
*****************************************************************************/
typedef struct
{
    BSP_U32 npnp_open_flag;                           /* NPNP ????????NV????, 0??????????????????, 1?????????????? */
    BSP_U32 npnp_enable_flag;                         /* NPNP ????????NV??, 0????????????, 1??????????             */
}NV_NPNP_CONFIG_INFO;
/*****************************************************************************
 ??????    : NV_RF_GPIO_CFG_STRU
 ????????  : RF_GPIO??????????????????DRV_GPIO
             ??????????????????????????????RF_GPIO????????????????????????
             ??????NV???? ID=10047
*****************************************************************************/
typedef struct
{
    BSP_U16 is_used;    /*Range:[0,1]*/
	BSP_U16 gpio_level; /*Range:[0,1]*/
}RF_MODEM_CONTROL;
typedef struct
{
    BSP_U32 rf_gpio_num;
    RF_MODEM_CONTROL modem_inside;
    RF_MODEM_CONTROL modem_outside;
}RF_GPIO_CFG;
typedef struct
{
    RF_GPIO_CFG rf_switch_cfg[16];
}NV_RF_SWITCH_CFG_STRU;
/*****************************************************************************
 ??????    : NV_RF_ANT_OTG_CFG_STRU
 ????????  : ????????????????????????????????????????????????????????????????
             ??????NV????????????????NV??????????????GPIO????????????????
             ID=10051
*****************************************************************************/
typedef struct
{
    BSP_U16 ANT0_GPIO_NUM;
    BSP_U16 ANT1_GPIO_NUM;
}NV_RF_ANT_OTG_CFG_STRU;

/*****************************************************************************
 ??????    : NV_T1_CTRL_PARA_STRU
 ????????  : NV_T1_CTRL_PARA_STRU ID=71
*****************************************************************************/
typedef struct
{
    BSP_U32             TMode;
    BSP_U32             enEDM;
    BSP_U32             aulRsv[4];
}NV_T1_CTRL_PARA_STRU;

/*****************************************************************************
 ??????    : NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY
 ????????  : NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY ID=148
*****************************************************************************/
typedef struct
{
    BSP_U16         usProductType;/*0:MBB V3R3 stick/E5,etc.; 1:V3R3 M2M & V7R2; 2:V9R1 phone; 3:K3V3&V8R1;*/
    BSP_U16         usRsv;
}NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY;

/*****************************************************************************
 ??????    : UCOM_NV_NV_ITEM_XO_DEFINE_STRU
 ????????  :
 ASN.1???? :
 ????????  : ?????????????? ID=10056
*****************************************************************************/
typedef struct
{
    BSP_U16      enSingleXoType;                     /* ??????????????,0:????????1:??tcxo??2:??dcxo */
    BSP_U16      en32kType;                          /* 0:32000,1:32764??2:32768*/
}DRV_NV_SINGLE_XO_DEFINE_STRU;
/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of DrvNvInterface.h */
