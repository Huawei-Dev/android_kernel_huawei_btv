/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
#include <vxWorks.h>
#include <logLib.h>
#include <usrLib.h>
#include <string.h>
#include <stdio.h>
#include "BSP_UDI.h"
#include "BSP_UDI_DRV.h"
*/
/*lint --e{750} */
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>

#include "udi_balong.h"



#define UDI_MAX_MAIN_DEV_NUM UDI_DEV_MAX
#define UDI_MAX_DEV_TYPE_NUM 32
#define UDI_MAX_OPEN_NODE_NUM 64
//#define UDI_MAX_INIT_FUNC_NUM UDI_TYPE_MAX
#define UDI_OPEN_NODE_HEADER  0x5A0000

/* Mutex ???????? */

#define UDI_DEBUG

/**************************************************************************
  ????????
**************************************************************************/
/* ???????????? */
typedef struct tagUDI_OPEN_NODE
{
	int bOpen;
	void* pPrivate;
	UDI_DRV_INTEFACE_TABLE *pstDrvTable;
}UDI_OPEN_NODE;

/* ???????????? */
typedef struct tagUDI_DEV_INSTANCE
{
	//unsigned int u32MagicNum;				/* ?????? */
	//unsigned int u32DevId;					/* ????ID */
	unsigned int u32Capability;					/* ???????? */
	//BSP_U8* strDevName;					/* ??????,???????????????????? */
	UDI_DRV_INTEFACE_TABLE *pDrvInterface;  /* ???????????? */
	void* pPrivate;					/* ???????????????? */
}UDI_DEV_INSTANCE;


/**************************************************************************
  ????????
**************************************************************************/
UDI_OPEN_NODE			g_openNodeTable[UDI_MAX_OPEN_NODE_NUM];
unsigned int					g_openNodeCurPos = 0;
UDI_DEV_INSTANCE			g_deviceTable[UDI_MAX_MAIN_DEV_NUM][UDI_MAX_DEV_TYPE_NUM];
extern UDI_ADP_INIT_CB_T	g_udiInitFuncTable[UDI_DEV_MAX+1];
/*UDI_MUTEX_T g_udiMtxOpen;*/
struct semaphore			g_udiMtxOpen;

/**************************************************************************
  ??????
**************************************************************************/
#define UDI_OFFSET_OF(type, member) ((unsigned int) (&((type *)0)->member))
#define UDI_IDX_TO_HANDLE(idx) ((UDI_HANDLE)(UDI_OPEN_NODE_HEADER | (idx)))
#define UDI_HANDLE_TO_IDX(hdl) ((unsigned int)((hdl) & 0xFFFF))

#define UDI_IS_INVALID_TABLE(pstDrvTable) \
    (0 == (unsigned long)(pstDrvTable) || (unsigned long)(-1) == (unsigned long)(pstDrvTable))

#define UDI_PARSE_DEV_ID(devId, mainId, devType) \
do{\
	mainId = UDI_GET_MAIN_DEV_ID(devId);\
	devType = UDI_GET_DEV_TYPE(devId);\
	\
	bsp_assert(mainId < UDI_MAX_MAIN_DEV_NUM);\
	bsp_assert(devType < UDI_MAX_DEV_TYPE_NUM);\
}while(0)

#define UDI_CALL_OPT_FUNC_SAFELY(handle, param1, param2, functionCB, ret) \
do{\
	unsigned int u32Idx;\
	UDI_DRV_INTEFACE_TABLE *pstDrvTable;\
	void* pPrivate;\
	\
	UDI_CHECK_HANDLE(handle);\
	u32Idx = UDI_HANDLE_TO_IDX(handle);\
	\
	if (u32Idx >= UDI_MAX_OPEN_NODE_NUM)\
	{\
		/*printk(KERN_ERR "BSP_MODU_UDI invalid handle:0x%x, line:%d\n",*/ \
		/*	handle, __LINE__);*/\
		return (-1);\
	}\
	/* ?????????????????? */\
	pstDrvTable = g_openNodeTable[u32Idx].pstDrvTable;\
	if (UDI_IS_INVALID_TABLE(pstDrvTable))\
    {\
        /*printk(KERN_ERR "pstDrvTable is Invalid, line:%d\n",*/ \
		/*	__LINE__);*/\
        return (-1);\
    }\
	if (NULL == pstDrvTable->functionCB)\
	{\
		/*printk(KERN_ERR "BSP_MODU_UDI %s callback is NULL, line:%d\n", */\
		/*	#functionCB, __LINE__);*/\
		return (-1);\
	}\
	pPrivate = g_openNodeTable[u32Idx].pPrivate;\
	\
	/* ?????????????????? */\
	ret = pstDrvTable->functionCB(pPrivate, param1, param2);\
}while(0)

#ifdef UDI_DEBUG
#define UDI_CHECK_HANDLE(handle) \
do{\
	if ((handle & 0xFF0000) != UDI_OPEN_NODE_HEADER || \
	UDI_HANDLE_TO_IDX(handle) >= UDI_MAX_OPEN_NODE_NUM)\
	{\
		/*printk(KERN_ERR "BSP_MODU_UDI invalid handle:0x%x, line:%d\n",*/ \
		/*	handle, __LINE__);*/\
		return (-1);\
	}\
}while(0)
#else
#define UDI_CHECK_HANDLE(handle)
#endif

/**************************************************************************
  ????????
**************************************************************************/
static UDI_HANDLE udiGetOutOpenNode(void)
{
	unsigned int u32Cnt;
	UDI_HANDLE handle = UDI_INVALID_HANDLE;

	down(&g_udiMtxOpen);
	/* ???????????????? */
	for (u32Cnt = g_openNodeCurPos; u32Cnt < UDI_MAX_OPEN_NODE_NUM; u32Cnt++)
	{
		if (0 == g_openNodeTable[u32Cnt].bOpen)
		{
			handle = UDI_IDX_TO_HANDLE(u32Cnt);
			break;
		}
	}

	/* ????, ???????? */
	if(UDI_INVALID_HANDLE == handle)
	{
		for (u32Cnt = 0; u32Cnt < g_openNodeCurPos; u32Cnt++)
		{
			if (0 == g_openNodeTable[u32Cnt].bOpen)
			{
				handle = UDI_IDX_TO_HANDLE(u32Cnt);
				break;
			}
		}
	}

	/* ??????????????handle */
	if (UDI_INVALID_HANDLE != handle)
	{
		g_openNodeCurPos = (u32Cnt+1) % UDI_MAX_OPEN_NODE_NUM;
		g_openNodeTable[u32Cnt].bOpen = 1;
	}
	up(&g_udiMtxOpen);

	return handle;
}

static int udiReturnOpenNode(unsigned int u32Idx)
{
	bsp_assert(u32Idx < UDI_MAX_OPEN_NODE_NUM);
    /*lint 661*/
	if( u32Idx >=UDI_MAX_OPEN_NODE_NUM )
	{
		printk("BSP_UDI_SetCapability para error: u32Idx=%u\n", u32Idx);
		return (-1);
	}
	down(&g_udiMtxOpen);
	g_openNodeTable[u32Idx].bOpen = 0;
	g_openNodeTable[u32Idx].pstDrvTable = (UDI_DRV_INTEFACE_TABLE*)(-1);
	up(&g_udiMtxOpen);

	return 0;
}

/**************************************************************************
  ????????
**************************************************************************/

/*****************************************************************************
* ?? ?? ??  : BSP_UDI_SetPrivate
*
* ????????  : ????????????????????
*
* ????????  : devId: ????ID
*             pPrivate: ????????
* ????????  : ??
* ?? ?? ??  : ????/????
*****************************************************************************/
int BSP_UDI_SetPrivate(UDI_DEVICE_ID_E devId, void* pPrivate)
{
	unsigned int u32MainId;
	unsigned int u32DevType;
    /*lint  e661 e662*/
	UDI_PARSE_DEV_ID(devId, u32MainId, u32DevType);
	if((u32MainId >= UDI_MAX_MAIN_DEV_NUM)||(u32DevType >= UDI_MAX_DEV_TYPE_NUM))
	{
      printk("BSP_UDI_SetCapability para error: u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);
	  return (-1);
	}
	g_deviceTable[u32MainId][u32DevType].pPrivate = pPrivate;

	return 0;
}

/*****************************************************************************
* ?? ?? ??  : BSP_UDI_SetCapability
*
* ????????  : ??????????????
*
* ????????  : devId: ????ID
*             u32Capability: ??????????
* ????????  : ??
* ?? ?? ??  : ????/????
*****************************************************************************/
int BSP_UDI_SetCapability(UDI_DEVICE_ID_E devId, unsigned int u32Capability)
{
	unsigned int u32MainId;
	unsigned int u32DevType;

    /*lint e662 e661*/
	UDI_PARSE_DEV_ID(devId, u32MainId, u32DevType);
	if((u32MainId >= UDI_MAX_MAIN_DEV_NUM)||(u32DevType >= UDI_MAX_DEV_TYPE_NUM))
	{
      printk("BSP_UDI_SetCapability para error: u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);
	  return (-1);
	}
	g_deviceTable[u32MainId][u32DevType].u32Capability = u32Capability;
	//printk("BSP_UDI_SetCapability **********************  u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);


	return 0;
}

/*****************************************************************************
* ?? ?? ??  : BSP_UDI_SetInterfaceTable
*
* ????????  : ????????????????????(????????????)
*
* ????????  : devId: ????ID
*             pDrvInterface: ????????????????????
* ????????  : ??
* ?? ?? ??  : ????/????
*****************************************************************************/
int BSP_UDI_SetInterfaceTable(UDI_DEVICE_ID_E devId, UDI_DRV_INTEFACE_TABLE *pDrvInterface)
{
	unsigned int u32MainId;
	unsigned int u32DevType;
    /*lint e661 e662*/
	UDI_PARSE_DEV_ID(devId, u32MainId, u32DevType);
	if((u32MainId >= UDI_MAX_MAIN_DEV_NUM)||(u32DevType >= UDI_MAX_DEV_TYPE_NUM))
	{
      printk("BSP_UDI_SetInterfaceTable para error: u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);
	  return (-1);
	}
	g_deviceTable[u32MainId][u32DevType].pDrvInterface = pDrvInterface;
	//printk("BSP_UDI_SetInterfaceTable  **********************  u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);

	return 0;
}

/*****************************************************************************
* ?? ?? ??  : bsp_udi_init
*
* ????????  : UDI ??????????
*
* ????????  : ??
* ????????  : ??
* ?? ?? ??  : ????/????
*****************************************************************************/
int bsp_udi_init(void)
{
	UDI_ADP_INIT_CB_T initCB;
	unsigned int u32Cnt;

	memset(g_deviceTable, 0, sizeof(g_deviceTable));
	memset(g_openNodeTable, 0, sizeof(g_openNodeTable));

	sema_init(&g_udiMtxOpen, 1);

	/* ?????????????? */
	for (u32Cnt = 0; u32Cnt < (unsigned int)UDI_DEV_MAX; u32Cnt++)
	{
		initCB = g_udiInitFuncTable[u32Cnt];
		if (initCB)
		{
			if (initCB() != 0)
			{
				printk(KERN_ERR "BSP_MODU_UDI usr initCB fail, line:%d\n", __LINE__);
				return (-1);
			}
		}
	}
	return 0;
}

/*****************************************************************************
* ?? ?? ??  : udi_get_capability
*
* ????????  : ????????ID??????????????????????
*
* ????????  : devId: ????ID
* ????????  : ??
* ?? ?? ??  : ????????????
*****************************************************************************/
int udi_get_capability(UDI_DEVICE_ID_E devId)
{
	unsigned int u32MainId;
	unsigned int u32DevType;

	UDI_PARSE_DEV_ID(devId, u32MainId, u32DevType);
	/* lint e661 e662*/
	if((u32MainId >= UDI_MAX_MAIN_DEV_NUM)||(u32DevType >= UDI_MAX_DEV_TYPE_NUM))
	{
      printk("udi_get_capability para error: u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);
	  return (-1);
	}
	return (int)g_deviceTable[u32MainId][u32DevType].u32Capability;
}
/*****************************************************************************
* ?? ?? ??  : mdrv_udi_open
*
* ????????  : ????????(????????)
*
* ????????  : pParam: ??????????????????
* ????????  : ??
* ?? ?? ??  : -1:???? / ????:????
*****************************************************************************/
UDI_HANDLE mdrv_udi_open(UDI_OPEN_PARAM_S *pParam)
{
	unsigned int u32MainId = 0;
	unsigned int u32DevType = 0;
	unsigned int u32Idx = 0;
	UDI_HANDLE handle;
	UDI_DRV_INTEFACE_TABLE *pstDrvTable;

	if (NULL == pParam)
	{
		goto UDI_OPEN_ERR;
	}
	/*lint e662 e661*/
	UDI_PARSE_DEV_ID(pParam->devid, u32MainId, u32DevType);
   if((u32MainId >= UDI_MAX_MAIN_DEV_NUM)||(u32DevType >= UDI_MAX_DEV_TYPE_NUM))
	{
      /*printk("mdrv_udi_open para error: u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);*/
	  goto UDI_OPEN_ERR;
	}
	/* ?????????????????? */
	handle = udiGetOutOpenNode();
	if (UDI_INVALID_HANDLE == handle)
	{
		/*printk(KERN_ERR "BSP_MODU_UDI can't find open node, line:%d\n", __LINE__);*/
		goto UDI_OPEN_ERR;
	}
	u32Idx = UDI_HANDLE_TO_IDX(handle);

	/* ???????????????? */
	pstDrvTable = g_deviceTable[u32MainId][u32DevType].pDrvInterface;
	if (NULL == pstDrvTable || NULL == pstDrvTable->udi_open_cb)
	{
		/*printk(KERN_ERR "BSP_MODU_UDI usr open cb is NULL, line:%d\n", __LINE__);*/
		goto UDI_OPEN_ERR_RET_NODE;
	}
	if (pstDrvTable->udi_open_cb(pParam, handle))
	{
		/*printk(KERN_ERR "BSP_MODU_UDI usr open fail, line:%d\n", __LINE__);*/
		goto UDI_OPEN_ERR_RET_NODE;
	}

	/* ???????????????? */
	g_openNodeTable[u32Idx].pstDrvTable =
	g_deviceTable[u32MainId][u32DevType].pDrvInterface;
	g_openNodeTable[u32Idx].pPrivate =
	g_deviceTable[u32MainId][u32DevType].pPrivate;

	return handle;

UDI_OPEN_ERR_RET_NODE:
	(void)udiReturnOpenNode(u32Idx);
UDI_OPEN_ERR:
	return UDI_INVALID_HANDLE;
}
EXPORT_SYMBOL(mdrv_udi_open);

/*****************************************************************************
* ?? ?? ??  : mdrv_udi_close
*
* ????????  : ????????(????????)
*
* ????????  : handle: ??????handle
* ????????  : ??
* ?? ?? ??  : ??
*****************************************************************************/
int mdrv_udi_close(UDI_HANDLE handle)
{
	int s32Ret = -1;
	unsigned int u32Idx;
	UDI_DRV_INTEFACE_TABLE *pstDrvTable;

	UDI_CHECK_HANDLE(handle);

	u32Idx = UDI_HANDLE_TO_IDX(handle);

	if (u32Idx >= UDI_MAX_OPEN_NODE_NUM)
	{
		/*printk(KERN_ERR "BSP_MODU_UDI invalid handle:0x%x, line:%d\n", handle, __LINE__);*/
		return (-1);
	}
	/* ?????????????????? */
	pstDrvTable = g_openNodeTable[u32Idx].pstDrvTable;
	if (UDI_IS_INVALID_TABLE(pstDrvTable))/*lint !e58*/
    {
        /*printk(KERN_ERR "pstDrvTable is Invalid, line:%d\n", __LINE__);*/
        return (-1);
    }
	if (NULL == pstDrvTable->udi_close_cb)
	{
		/*printk(KERN_ERR "BSP_MODU_UDI udi_close_cb is NULL, line:%d\n", __LINE__);*/
		return (-1);
	}
	s32Ret = pstDrvTable->udi_close_cb(g_openNodeTable[u32Idx].pPrivate);

	/* ???? Open Node */
	(void)udiReturnOpenNode(u32Idx);

	return s32Ret;
}
EXPORT_SYMBOL(mdrv_udi_close);

/*****************************************************************************
* ?? ?? ??  : mdrv_udi_write
*
* ????????  : ??????
*
* ????????  : handle:  ??????handle
*             pMemObj: buffer???? ?? ????????????
*             u32Size: ?????????? ?? ????????????????????
* ????????  :
*
* ?? ?? ??  : ?????????? ?? ????/????
*****************************************************************************/
int mdrv_udi_write(UDI_HANDLE handle, void* pMemObj, unsigned int u32Size)
{
	int s32Ret = -1;
    /*lint -e58*/
	UDI_CALL_OPT_FUNC_SAFELY(handle, pMemObj, u32Size, udi_write_cb, s32Ret);
    /*lint +e58*/
	return s32Ret;
}
EXPORT_SYMBOL(mdrv_udi_write);

/*****************************************************************************
* ?? ?? ??  : mdrv_udi_read
*
* ????????  : ??????
*
* ????????  : handle:  ??????handle
*             pMemObj: buffer???? ?? ????????????
*             u32Size: ?????????? ?? ????????????????????
* ????????  :
*
* ?? ?? ??  : ?????????? ?? ????/????
*****************************************************************************/
int mdrv_udi_read(UDI_HANDLE handle, void* pMemObj, unsigned int u32Size)
{
	int s32Ret = -1;
    /*lint -e58*/
	UDI_CALL_OPT_FUNC_SAFELY(handle, pMemObj, u32Size, udi_read_cb, s32Ret);
    /*lint +e58*/
	return s32Ret;
}
EXPORT_SYMBOL(mdrv_udi_read);

/*****************************************************************************
* ?? ?? ??  : mdrv_udi_ioctl
*
* ????????  : ????????????????
*
* ????????  : handle: ??????handle
*             u32Cmd: IOCTL??????
*             pParam: ????????
* ????????  :
*
* ?? ?? ??  : ????/????
*****************************************************************************/
int mdrv_udi_ioctl(UDI_HANDLE handle, unsigned int u32Cmd, void* pParam)
{
	int s32Ret = -1;
    /*lint -e58*/
	UDI_CALL_OPT_FUNC_SAFELY(handle, u32Cmd, pParam, udi_ioctl_cb, s32Ret);
    /*lint +e58*/
	return s32Ret;
}
EXPORT_SYMBOL(mdrv_udi_ioctl);


arch_initcall(bsp_udi_init);




