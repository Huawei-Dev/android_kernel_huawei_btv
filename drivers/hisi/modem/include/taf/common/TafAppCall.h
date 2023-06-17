/******************************************************************************

                  ???????? (C), 2001-2011, ????????????????

 ******************************************************************************
  ?? ?? ??   : TafAppCall.h
  ?? ?? ??   : ????
  ??    ??   : y00245242
  ????????   : 2015??10??22??
  ????????   :
  ????????   : AT/APP??CALL??????????????
  ????????   :
  ????????   :
  1.??    ??   : 2015??10??22??
    ??    ??   : y00245242
    ????????   : ????????

******************************************************************************/

#ifndef __TAF_APP_CALL_H__
#define __TAF_APP_CALL_H__

#include "vos.h"
#include "MnCallApi.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/



/* ??: ????????????????????????????????????????AT??CALL????????????????????????
       ????????????????????????????????????????????TafInternalInterface.h??
       ID_TAF_CALL_INTERNAL_BASE????????!!!
 */
#define TAF_CALL_APP_MSG_START_BASE                         (0x3100)
#define TAF_XCALL_MAX_NUM                                   (2)

/*****************************************************************************
  3 ????????
*****************************************************************************/
/*****************************************************************************
 ??????    : TAF_CCA_MSG_TYPE_ENUM_UINT32
 ????????  : APP??TAF??????????????
 1.??    ??   : 2015??10??22??
   ??    ??   : y00245242
   ????????   : ????
*****************************************************************************/
enum TAF_CCA_MSG_TYPE_ENUM
{
    ID_TAF_CALL_MSG_TYPE_BEGIN                              = TAF_CALL_APP_MSG_START_BASE,

    /* ????/???????????????? */
    ID_TAF_CALL_APP_ENCRYPT_VOICE_REQ,                      /* _H2ASN_MsgChoice TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU *//**< @sa TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU */
    ID_TAF_CALL_APP_ENCRYPT_VOICE_CNF,                      /* _H2ASN_MsgChoice TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU *//**< @sa TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU */
    ID_TAF_CALL_APP_ENCRYPT_VOICE_IND,                      /* _H2ASN_MsgChoice TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU *//**< @sa TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU */

    /* KMC???????????????? */
    ID_TAF_CALL_APP_EC_REMOTE_CTRL_IND,                     /* _H2ASN_MsgChoice TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU *//**< @sa TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU */
    ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ,                 /* _H2ASN_MsgChoice TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU *//**< @sa TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU */
    ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF,                 /* _H2ASN_MsgChoice TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU *//**< @sa TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU */

    /* ?????????????????????????? */
    ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ,                    /* _H2ASN_MsgChoice TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU *//**< @sa TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU */
    ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF,                    /* _H2ASN_MsgChoice TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU *//**< @sa TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU */
    ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ,                    /* _H2ASN_MsgChoice TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU *//**< @sa TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU */
    ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF,                    /* _H2ASN_MsgChoice TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU *//**< @sa TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU */

    /* ???????????????????? */
    ID_TAF_CALL_APP_SET_EC_TEST_MODE_REQ,                   /* _H2ASN_MsgChoice TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU *//**< @sa TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU */
    ID_TAF_CALL_APP_SET_EC_TEST_MODE_CNF,                   /* _H2ASN_MsgChoice TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU *//**< @sa TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU */
    ID_TAF_CALL_APP_GET_EC_TEST_MODE_REQ,                   /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU *//**< @sa TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU */
    ID_TAF_CALL_APP_GET_EC_TEST_MODE_CNF,                   /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU *//**< @sa TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU */

    /* ???????????????????????? */
    ID_TAF_CALL_APP_GET_EC_RANDOM_REQ,                      /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU *//**< @sa TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU */
    ID_TAF_CALL_APP_GET_EC_RANDOM_CNF,                      /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU *//**< @sa TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU */

    /* ??????????KMC???????????????????????? */
    ID_TAF_CALL_APP_GET_EC_KMC_REQ,                         /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_KMC_REQ_STRU *//**< @sa TAF_CALL_APP_GET_EC_KMC_REQ_STRU */
    ID_TAF_CALL_APP_GET_EC_KMC_CNF,                         /* _H2ASN_MsgChoice TAF_CALL_APP_GET_EC_KMC_CNF_STRU *//**< @sa TAF_CALL_APP_GET_EC_KMC_CNF_STRU */

    /* ??????????KMC???????????????????????? */
    ID_TAF_CALL_APP_SET_EC_KMC_REQ,                         /* _H2ASN_MsgChoice TAF_CALL_APP_SET_EC_KMC_REQ_STRU *//**< @sa TAF_CALL_APP_SET_EC_KMC_REQ_STRU */
    ID_TAF_CALL_APP_SET_EC_KMC_CNF,                         /* _H2ASN_MsgChoice TAF_CALL_APP_SET_EC_KMC_CNF_STRU *//**< @sa TAF_CALL_APP_SET_EC_KMC_CNF_STRU */

    ID_TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND,               /* _H2ASN_MsgChoice TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU *//**< @sa TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU */

    ID_TAF_CALL_APP_PRIVACY_MODE_SET_REQ,                       /* _H2ASN_MsgChoice TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU *//**< @sa TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU */
    ID_TAF_CALL_APP_PRIVACY_MODE_SET_CNF,                       /* _H2ASN_MsgChoice TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU *//**< @sa TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU */
    ID_TAF_CALL_APP_PRIVACY_MODE_QRY_REQ,                       /* _H2ASN_MsgChoice TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU *//**< @sa TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU */
    ID_TAF_CALL_APP_PRIVACY_MODE_QRY_CNF,                       /* _H2ASN_MsgChoice TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU *//**< @sa TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU */
    ID_TAF_CALL_APP_PRIVACY_MODE_IND,                           /* _H2ASN_MsgChoice TAF_CALL_APP_PRIVACY_MODE_ACT_IND_STRU *//**< @sa TAF_CALL_APP_PRIVACY_MODE_IND_STRU */

    ID_TAF_CALL_APP_TYPE_BUTT
};
typedef VOS_UINT32 TAF_CCA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
??????      : TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT8
????????    : ECC??????????????????
  1.??    ??   : 2015??10??16??
    ??    ??   : y00322978
    ????????   : ??????????
*****************************************************************************/
enum TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM
{
    TAF_CALL_REMOTE_CTRL_SEC_INFO_ERASE = 0,
    TAF_CALL_REMOTE_CTRL_PASSWORD_RESET = 1,
    TAF_CALL_REMOTE_CTRL_OTHER          = 2,

    TAF_CALL_REMOTE_CTRL_APP_TYPE_BUTT
};
typedef VOS_UINT32   TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT32;

/*****************************************************************************
??????      : TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM_UINT32
????????    : ECC??????????????????
  1.??    ??   : 2015??10??16??
    ??    ??   : y00322978
    ????????   : ??????????
*****************************************************************************/
enum TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM
{
    TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_SUCC = 0,
    TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_FAIL,

    TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_BUTT

};
typedef VOS_UINT32   TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM_UINT32;

/*****************************************************************************
??????      : TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM_UINT8
????????    : ECC??????????????????
  1.??    ??   : 2015??10??16??
    ??    ??   : y00322978
    ????????   : ??????????
*****************************************************************************/
enum TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM
{
    TAF_CALL_REMOTE_CTRL_APP_SUCC = 0,
    TAF_CALL_REMOTE_CTRL_APP_FAIL,

    TAF_CALL_REMOTE_CTRL_APP_RESULT_BUTT
};
typedef VOS_UINT32 TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM_UINT32;

/*****************************************************************************
??????      : TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM_UINT32
????????    : ECC????????????????????
  1.??    ??   : 2015??10??26??
    ??    ??   : y00245242
    ????????   : ??????????
*****************************************************************************/
enum TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM
{
    TAF_CALL_SEND_RESULT_SUCC               = 0x00,
    TAF_CALL_SEND_RESULT_FAIL               = 0x01,
    TAF_CALL_SEND_RESULT_XSMS_POOL_FULL     = 0x02,
    TAF_CALL_SEND_RESULT_XSMS_LINK_ERR      = 0x03,
    TAF_CALL_SEND_RESULT_XSMS_NO_TL_ACK     = 0x04,
    TAF_CALL_SEND_RESULT_XSMS_ENCODE_ERR    = 0x05,
    TAF_CALL_SEND_RESULT_OPER_NOT_ALLOWED   = 0x06,
    TAF_CALL_SEND_RESULT_OPER_TYPE_ERROR    = 0x07,
    TAF_CALL_SEND_RESULT_INT_ERRROR         = 0x08,

    TAF_CALL_REMOTE_CTRL_OPER_RESULT_BUTT
};
typedef VOS_UINT32 TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
??????      : TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT8
????????    : ECC????????????
  1.??    ??   : 2015??10??16??
    ??    ??   : y00322978
    ????????   : ??????????
*****************************************************************************/
enum TAF_CALL_APP_ECC_SRV_CAP_ENUM
{
    TAF_CALL_APP_ECC_SRV_CAP_DISABLE = 0,
    TAF_CALL_APP_ECC_SRV_CAP_NO_CHANGE,
    TAF_CALL_APP_ECC_SRV_CAP_ENABLE,

    TAF_CALL_APP_ECC_SRV_CAP_BUTT
};
typedef VOS_UINT32   TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32;
/*****************************************************************************
??????      : TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT8
????????    : ECC????????????
  1.??    ??   : 2015??10??16??
    ??    ??   : y00322978
    ????????   : ??????????
*****************************************************************************/
enum TAF_CALL_APP_ECC_SRV_STATUS_ENUM
{
    TAF_CALL_APP_ECC_SRV_STATUS_CLOSE = 0,
    TAF_CALL_APP_ECC_SRV_STATUS_OPEN,

    TAF_CALL_APP_ECC_SRV_STATUS_BUTT
};
typedef VOS_UINT32   TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32;

/*****************************************************************************
??????      : TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT8
????????    : ECC??????????????
  1.??    ??   : 2015??10??16??
    ??    ??   : y00322978
    ????????   : ??????????
*****************************************************************************/
enum TAF_CALL_APP_SET_EC_TEST_MODE_ENUM
{
    TAF_CALL_APP_SET_EC_TEST_MODE_DISABLE = 0,
    TAF_CALL_APP_SET_EC_TEST_MODE_ENABLE,

    TAF_CALL_APP_SET_EC_TEST_MODE_BUTT
};
typedef VOS_UINT32   TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32;

/*****************************************************************************
??????      : TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32
????????    : ecc????????????
  1.??    ??   : 2015??10??16??
    ??    ??   : y00322978
    ????????   : ??????????
*****************************************************************************/
enum TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM
{
    TAF_CALL_APP_ENCRYPT_VOICE_SUCC                     = 0x0000,

    /* KMC?????????????????? */
    TAF_CALL_APP_ENCRYPT_VOICE_TIMEOUT,
    TAF_CALL_APP_ENCRYPT_VOICE_LOCAL_TERMINAL_NO_AUTHORITY,
    TAF_CALL_APP_ENCRYPT_VOICE_REMOTE_TERMINAL_NO_AUTHORITY,
    TAF_CALL_APP_ENCRYPT_VOICE_LOCAL_TERMINAL_ILLEGAL,
    TAF_CALL_APP_ENCRYPT_VOICE_REMOTE_TERMINAL_ILLEGAL,
    TAF_CALL_APP_ENCRYPT_VOICE_UNKNOWN_ERROR,

    /* ???????????? */
    TAF_CALL_APP_ENCRYPT_VOICE_SIGNTURE_VERIFY_FAILURE,

    /* ???????????? */
    TAF_CALL_APP_ENCRYPT_VOICE_MT_CALL_NOTIFICATION,

    /***********************************************************************************************
     * ????????????????????
     **********************************************************************************************/
    /* XSMS???????????? */
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_FAIL     = 0x1000,
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_POOL_FULL,
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_LINK_ERR,
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_NO_TL_ACK,
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_ENCODE_ERR,
    TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_UNKNOWN,

    /* ????XCALL?????????? */
    TAF_CALL_APP_ENCRYPT_VOICE_SO_NEGO_FAILURE           = 0x2000,
    TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST,
    TAF_CALL_APP_ENCRYPT_VOICE_NO_MO_CALL,
    TAF_CALL_APP_ENCRYPT_VOICE_NO_MT_CALL,
    TAF_CALL_APP_ENCRYPT_VOICE_NO_CALL_EXIST,
    TAF_CALL_APP_ENCRYPT_VOICE_CALL_STATE_NOT_ALLOWED,
    TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH,
    TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH,
    TAF_CALL_APP_ENCRYPT_VOICE_MSG_ENCODE_FAILUE,
    TAF_CALL_APP_ENCRYPT_VOICE_MSG_DECODE_FAILUE,
    TAF_CALL_APP_ENCRYPT_VOICE_GET_TEMP_PUB_PIVA_KEY_FAILURE,
    TAF_CALL_APP_ENCRYPT_VOICE_FILL_CIPHER_TEXT_FAILURE,
    TAF_CALL_APP_ENCRYPT_VOICE_ECC_CAP_NOT_SUPPORTED,
    TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_MODE_UNKNOWN,
    TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_MODE_MIMATCH,
    TAF_CALL_APP_ENCRYPT_VOICE_CALL_RELEASED,
    TAF_CALL_APP_ENCRYPT_VOICE_CALL_ANSWER_REQ_FAILURE,
    TAF_CALL_APP_ENCRYPT_VOICE_DECRYPT_KS_FAILURE,
    TAF_CALL_APP_ENCRYPT_VOICE_FAILURE_CAUSED_BY_INCOMING_CALL,
    TAF_CALL_APP_ENCRYPT_VOICE_INIT_VOICE_FUNC_FAILURE,
    TAF_CALL_APP_ENCRYPT_VOICE_TX01_TIMEOUT,
    TAF_CALL_APP_ENCRYPT_VOICE_TX02_TIMEOUT,


    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_BUTT
};
typedef VOS_UINT32  TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32;

/*****************************************************************************
??????      : TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32
????????    : ECC????????
  1.??    ??   : 2015??10??16??
    ??    ??   : y00322978
    ????????   : ??????????
*****************************************************************************/
enum TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM
{
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_MUNAUL_MODE = 0,
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_AUTO_MODE,
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_MUNAUL_MODE,
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_AUTO_MODE,

    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_BUTT
};
typedef VOS_UINT32 TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32;

/*****************************************************************************
 ??????    : TAF_CALL_PRIVACY_MODE_ENUM
 ????????  : Privary mode
 1.??    ??   : 2014??09??04??
   ??    ??   : l60609
   ????????   : ????
*****************************************************************************/
enum TAF_CALL_PRIVACY_MODE_ENUM
{
    TAF_CALL_PRIVACY_MODE_PUBLIC        = 0x00,

    TAF_CALL_PRIVACY_MODE_PRIVATE       = 0x01,

    TAF_CALL_PRIVACY_MODE_BUTT          = 0x02
};
typedef VOS_UINT8 TAF_CALL_PRIVACY_MODE_ENUM_UINT8;

/*****************************************************************************
??????      : TAF_CALL_APP_RESULT_TYPE_ENUM
????????    : ECC??????????????????
  1.??    ??   : 2015??12??22??
    ??    ??   : y00245242
    ????????   : ??????????
*****************************************************************************/
enum TAF_CALL_APP_RESULT_TYPE_ENUM
{
    TAF_CALL_APP_RESULT_TYPE_SUCCESS,
    TAF_CALL_APP_RESULT_TYPE_FAILURE,

    TAF_CALL_APP_RESULT_TYPE_BUTT
};
typedef VOS_UINT32 TAF_CALL_APP_RESULT_TYPE_ENUM_UINT32;
/*****************************************************************************
  3 ????????????
*****************************************************************************/
/** ****************************************************************************
 * Name        : TAF_CALL_APP_EC_RANDOM_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_INT8                                                aucEccData[TAF_CALL_APP_EC_RANDOM_DATA_LENGTH];
    VOS_UINT8                                               aucReserved[3];
} TAF_CALL_APP_EC_RANDOM_DATA_STRU;

/*****************************************************************************
 ??????    : TAF_CCA_CTRL_STRU
 ????????  : CCA??????????

 ????????      :
  1.??    ??   : 2015??10??22??
    ??    ??   : y00245242
    ????????   : ????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulModuleId;         /* ????PID */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
}TAF_CCA_CTRL_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ENCRYPT_VOICE_TYPE_ENUM_UINT32             enEccVoiceType;
    TAF_ECC_CALL_BCD_NUM_STRU                               stDialNumber;          /* Call Number */
} TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU;
/** ****************************************************************************
 * Name        : TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enEccTestModeStatus;
} TAF_CALL_APP_SET_EC_TEST_MODE_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
} TAF_CALL_APP_GET_EC_TEST_MODE_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT32               enRemoteCtrlEvtType;
    TAF_CALL_REMOTE_CTRL_APP_RESULT_ENUM_UINT32             enResult;
} TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM_UINT32            enResult;              /* ???????????? */
} TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap;
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus;
} TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM_UINT32         enResult;
} TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU;
/** ****************************************************************************
 * Name        : TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
} TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap;
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus;
} TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
} TAF_CALL_APP_GET_EC_RANDOM_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    VOS_UINT32                                              ulResult;
    TAF_CALL_APP_EC_RANDOM_DATA_STRU                        stEccRandom[TAF_CALL_APP_EC_RANDOM_NUM];
} TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_KMC_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
} TAF_CALL_APP_GET_EC_KMC_REQ_STRU;


/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_KMC_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    MN_CALL_APP_EC_KMC_DATA_STRU                            stKmcData;
    VOS_UINT32                                              ulResult;
} TAF_CALL_APP_GET_EC_KMC_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_SET_EC_KMC_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    MN_CALL_APP_EC_KMC_DATA_STRU                            stKmcData;

} TAF_CALL_APP_SET_EC_KMC_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_SET_EC_KMC_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    VOS_UINT32                                              ulResult;
} TAF_CALL_APP_SET_EC_KMC_CNF_STRU;


/** ****************************************************************************
 * Name        : TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT32               enRemoteCtrlType;
} TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEccVoiceStatus;
} TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEccVoiceStatus;
    TAF_ECC_CALL_BCD_NUM_STRU                               stCallingNumber;          /* Call Number */
} TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    VOS_UINT16                                              usLength;
    VOS_UINT8                                               aucRsved[2];
    VOS_INT8                                                aucData[TAF_CALL_APP_ENCRYPTED_VOICE_DATA_MAX_LENGTH];
} TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    VOS_UINT32                                              ulResult;
} TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enEccTestModeStatus;
    VOS_UINT32                                              ulResult;
} TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyMode;         /* privacy mode */
    VOS_UINT8                                               aucReserved[3];
} TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_APP_RESULT_TYPE_ENUM_UINT32                    enResult;
} TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
} TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucCallId;
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyMode;
    VOS_UINT8                                               aucReserved[2];
} TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU;


/** ****************************************************************************
 * Name        : TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyMode;         /* ????privacy mode???? */
    VOS_UINT8                                               ucCallNums;
    VOS_UINT8                                               aucReserved[2];
    TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU                    astCallVoicePrivacyInfo[TAF_XCALL_MAX_NUM];
} TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU;

/** ****************************************************************************
 * Name        : TAF_CALL_APP_PRIVACY_MODE_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                 /*_H2ASN_Skip*/
    TAF_CCA_MSG_TYPE_ENUM_UINT32                            enMsgName;             /*_H2ASN_Skip*/
    TAF_CCA_CTRL_STRU                                       stCtrl;
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyMode;         /* ????privacy mode???? */
    VOS_UINT8                                               aucReserved[2];
    TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU                    stCallVoicePrivacyInfo; /* ??????????privacy mode???? */
} TAF_CALL_APP_PRIVACY_MODE_IND_STRU;

/*****************************************************************************
  H2ASN????????????????
*****************************************************************************/
typedef struct
{
    TAF_CCA_MSG_TYPE_ENUM_UINT32        ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_PS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_CCA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}TAF_APP_CALL_DATA_STRU;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_APP_CALL_DATA_STRU               stTafAppCall;
}TafAppCall_MSG;
#if ((VOS_OS_VER == VOS_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafAppCall.h */
