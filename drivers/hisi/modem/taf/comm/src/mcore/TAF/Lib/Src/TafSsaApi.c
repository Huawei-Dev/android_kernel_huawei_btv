/************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSsaApi.c
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2015年09月09日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2015年09月09日
    作    者   : l00198894
    修改内容   : 创建文件

************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "TafSsaApi.h"





/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define THIS_FILE_ID                    PS_FILE_ID_TAF_SSA_API_C
/*lint +e767*/


/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*****************************************************************************
   3 外部函数声明
*****************************************************************************/

extern VOS_UINT32 AT_GetDestPid(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulRcvPid
);


/*****************************************************************************
   4 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_SSA_SndTafMsg
 功能描述  : 发送补充业务相关请求
 输入参数  : TAF_SSA_MSG_ID_ENUM_UINT32          enMsgId
             VOS_VOID                           *pData
             -- 消息结构需要以TAF_CTRL_STRU开头
             VOS_UINT32                          ulLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月9日
    作    者   : l00198894
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SSA_SndTafMsg(
    TAF_SSA_MSG_ID_ENUM_UINT32          enMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    TAF_SSA_MSG_STRU                   *pstMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulPid;

    TAF_CTRL_STRU                      *pstCtrl  = VOS_NULL_PTR;

    pstCtrl = (TAF_CTRL_STRU *)pData;

    /* 填写消息头 */
    ulPid = AT_GetDestPid(pstCtrl->usClientId, WUEPS_PID_TAF);

    /* 构造消息 */
    pstMsg = (TAF_SSA_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                ulPid,
                                sizeof(MSG_HEADER_STRU) + ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stHeader.ulReceiverPid      = ulPid;
    pstMsg->stHeader.ulMsgName          = enMsgId;

    /* 填写消息内容 */
    PS_MEM_CPY(pstMsg->aucContent, pData, ulLength);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(ulPid, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_SetCmolrInfo
 功能描述  : 发起/停止MO-LR流程 LCS定位请求
 输入参数  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月12日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SSA_SetCmolrInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_SSA_LCS_MOLR_PARA_SET_STRU     *pstMolrPara
)
{
    TAF_SSA_SET_LCS_MOLR_REQ_STRU       stSetCmolrReq;

    /* 初始化 */
    PS_MEM_SET(&stSetCmolrReq, 0x00, sizeof(stSetCmolrReq));

    /* 填写CTRL信息 */
    TAF_API_CTRL_HEADER(&stSetCmolrReq, ulModuleId, usClientId, ucOpId);

    stSetCmolrReq.stMolrPara  = *pstMolrPara;

    /* 发送消息 */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_SET_LCS_MOLR_REQ,
                      &stSetCmolrReq,
                      sizeof(stSetCmolrReq));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_GetCmolrInfo
 功能描述  : 获取+CMOLR命令信息
 输入参数  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月12日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SSA_GetCmolrInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_SSA_GET_LCS_MOLR_REQ_STRU       stGetCmolrReq;

    /* 初始化 */
    PS_MEM_SET(&stGetCmolrReq, 0x00, sizeof(stGetCmolrReq));

    /* 填写CTRL信息 */
    TAF_API_CTRL_HEADER(&stGetCmolrReq, ulModuleId, usClientId, ucOpId);

    /* 发送消息 */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_GET_LCS_MOLR_REQ,
                      &stGetCmolrReq,
                      sizeof(stGetCmolrReq));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_SetCmtlrInfo
 功能描述  : 设置网络定位请求指示方式
 输入参数  : VOS_UINT32                              ulModuleId,
             VOS_UINT16                              usClientId,
             VOS_UINT8                               ucOpId,
             TAF_SSA_LCS_MTLR_SUBSCRIBE_ENUM_UINT8   enSubscribe
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月12日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SSA_SetCmtlrInfo(
    VOS_UINT32                              ulModuleId,
    VOS_UINT16                              usClientId,
    VOS_UINT8                               ucOpId,
    TAF_SSA_LCS_MTLR_SUBSCRIBE_ENUM_UINT8   enSubscribe
)
{
    TAF_SSA_SET_LCS_MTLR_REQ_STRU       stSetCmtlrReq;

    /* 初始化 */
    PS_MEM_SET(&stSetCmtlrReq, 0x00, sizeof(stSetCmtlrReq));

    /* 填写CTRL信息 */
    TAF_API_CTRL_HEADER(&stSetCmtlrReq, ulModuleId, usClientId, ucOpId);

    stSetCmtlrReq.enSubscribe   = enSubscribe;

    /* 发送消息 */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_SET_LCS_MTLR_REQ,
                      &stSetCmtlrReq,
                      sizeof(stSetCmtlrReq));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_GetCmtlrInfo
 功能描述  : 获取+CMTLR命令信息
 输入参数  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月12日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SSA_GetCmtlrInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_SSA_GET_LCS_MTLR_REQ_STRU       stGetCmtlrReq;

    /* 初始化 */
    PS_MEM_SET(&stGetCmtlrReq, 0x00, sizeof(stGetCmtlrReq));

    /* 填写CTRL信息 */
    TAF_API_CTRL_HEADER(&stGetCmtlrReq, ulModuleId, usClientId, ucOpId);

    /* 发送消息 */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_GET_LCS_MTLR_REQ,
                      &stGetCmtlrReq,
                      sizeof(stGetCmtlrReq));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_SetCmtlraInfo
 功能描述  : 响应MT-LR流程 网络LCS定位请求
 输入参数  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             TAF_SSA_LCS_MTLRA_PARA_SET_STRU     *pstCmtlraPara
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月12日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SSA_SetCmtlraInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_SSA_LCS_MTLRA_PARA_SET_STRU    *pstCmtlraPara
)
{
    TAF_SSA_SET_LCS_MTLRA_REQ_STRU      stSetCmtlraReq;

    /* 初始化 */
    PS_MEM_SET(&stSetCmtlraReq, 0x00, sizeof(stSetCmtlraReq));

    /* 填写CTRL信息 */
    TAF_API_CTRL_HEADER(&stSetCmtlraReq, ulModuleId, usClientId, ucOpId);

    stSetCmtlraReq.stCmtlraPara  = *pstCmtlraPara;

    /* 发送消息 */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_SET_LCS_MTLRA_REQ,
                      &stSetCmtlraReq,
                      sizeof(stSetCmtlraReq));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SSA_GetCmtlraInfo
 功能描述  : 获取+CMTLRA命令信息
 输入参数  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月12日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SSA_GetCmtlraInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_SSA_GET_LCS_MTLRA_REQ_STRU      stGetCmtlraReq;

    /* 初始化 */
    PS_MEM_SET(&stGetCmtlraReq, 0x00, sizeof(stGetCmtlraReq));

    /* 填写CTRL信息 */
    TAF_API_CTRL_HEADER(&stGetCmtlraReq, ulModuleId, usClientId, ucOpId);

    /* 发送消息 */
    TAF_SSA_SndTafMsg(ID_TAF_SSA_GET_LCS_MTLRA_REQ,
                      &stGetCmtlraReq,
                      sizeof(stGetCmtlraReq));

    return;
}







