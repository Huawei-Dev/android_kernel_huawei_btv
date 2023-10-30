#include <linux/moduleparam.h>
#include <linux/delay.h>
#include <linux/rtc.h>
#include "plat_debug.h"
#include "plat_firmware.h"
#include "plat_sdio.h"
#include "plat_uart.h"
#include "plat_cali.h"
#include "plat_pm.h"
#include "oal_sdio_host_if.h"

#include "hw_bfg_ps.h"
#include "plat_efuse.h"

#define BFGX_AND_WIFI_CFG_PATH        "/vendor/firmware/bfgx_and_wifi_cfg"
#define WIFI_CFG_PATH                 "/vendor/firmware/wifi_cfg"
#define BFGX_CFG_PATH                 "/vendor/firmware/bfgx_cfg"
#define RAM_CHECK_CFG_PATH            "/vendor/firmware/ram_reg_test_cfg"

#define BFGX_AND_WIFI_CFG_BUILDIN_PATH        "/bfgx_and_wifi_cfg"
#define WIFI_CFG_BUILDIN_PATH                 "/wifi_cfg"
#define BFGX_CFG_BUILDIN_PATH                 "/bfgx_cfg"
#define RAM_CHECK_CFG_BUILDIN_PATH            "/ram_reg_test_cfg"

#define FILE_COUNT_PER_SEND           (1)
#define MIN_FIRMWARE_FILE_TX_BUF_LEN  (4096)

unsigned char *g_auc_cfg_in_system_path[CFG_FILE_TOTAL] =
                    {
                        BFGX_AND_WIFI_CFG_PATH,
                        WIFI_CFG_PATH,
                        BFGX_CFG_PATH,
                        RAM_CHECK_CFG_PATH,
                    };

unsigned char *g_auc_cfg_in_boot_path[CFG_FILE_TOTAL] =
                    {
                        BFGX_AND_WIFI_CFG_BUILDIN_PATH,
                        WIFI_CFG_BUILDIN_PATH,
                        BFGX_CFG_BUILDIN_PATH,
                        RAM_CHECK_CFG_BUILDIN_PATH,
                    };

unsigned char **g_auc_cfg_path = g_auc_cfg_in_system_path;

struct st_wifi_dump_mem_info nfc_buffer_data = {0x30000000+0x000f9d00, OMLNFCDATABUFFLEN, "nfc_buffer_data"};

FIRMWARE_GLOBALS_STRUCT  g_st_cfg_info;

unsigned char *g_pucDataBuf = NULL;

unsigned int g_ulDataBufLen = 0;

unsigned int g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_SUCC;

extern oal_uint32   oam_send_device_data2sdt(oal_uint8* pc_string, oal_uint16 len);

unsigned char* g_pucNfcLog= NULL;

int read_msg(unsigned char *data, int len)
{
    int  l_len;

    if (unlikely((NULL == data)))
    {
        PS_PRINT_ERR("data is NULL\n ");
        return -EFAIL;
    }

    l_len = sdio_patch_readsb(data, len, READ_MEG_TIMEOUT);
    PS_PRINT_DBG("Receive l_len=[%d], data = [%s]\n", l_len, data);

    return l_len;
}

int read_msg_timeout(unsigned char *data, int len, unsigned int timeout)
{
    int  l_len;

    if (unlikely((NULL == data)))
    {
        PS_PRINT_ERR("data is NULL\n ");
        return -EFAIL;
    }

    l_len = sdio_patch_readsb(data, len, timeout);
    PS_PRINT_DBG("Receive l_len=[%d], data = [%s]\n", l_len, data);

    return l_len;
}

int send_msg(unsigned char *data, int len)
{
    int   l_ret;

    PS_PRINT_DBG("len = %d\n", len);
#ifdef HW_DEBUG
    print_hex_dump_bytes("send_msg :", DUMP_PREFIX_ADDRESS, data,
                        (len < 128 ? len : 128));
#endif
    l_ret = sdio_patch_writesb(data, len);

    return l_ret;
}

int recv_expect_result(const unsigned char *expect)
{
    unsigned char auc_buf[RECV_BUF_LEN];
    int l_len;
    int i;

    if (!OS_STR_LEN(expect))
    {
        PS_PRINT_DBG("not wait device to respond!\n");
        return SUCC;
    }

    OS_MEM_SET(auc_buf, 0, RECV_BUF_LEN);
    for (i = 0; i < HOST_DEV_TIMEOUT; i++)
    {
        l_len = read_msg(auc_buf, RECV_BUF_LEN);
        if (0 > l_len)
        {
            PS_PRINT_ERR("recv result fail\n");
            return -EFAIL;
        }

        if (!OS_MEM_CMP(auc_buf, expect, OS_STR_LEN(expect)))
        {
            PS_PRINT_DBG(" send SUCC, expect [%s] ok\n", expect);
            return SUCC;
        }
        else
        {
            PS_PRINT_WARNING(" error result[%s], expect [%s], read result again\n", auc_buf, expect);
        }
    }

    return -EFAIL;
}

int recv_expect_result_timeout(const unsigned char *expect, unsigned int timeout)
{
    unsigned char auc_buf[RECV_BUF_LEN];
    int l_len;

    if (!OS_STR_LEN(expect))
    {
        PS_PRINT_DBG("not wait device to respond!\n");
        return SUCC;
    }

    OS_MEM_SET(auc_buf, 0, RECV_BUF_LEN);
    l_len = read_msg_timeout(auc_buf, RECV_BUF_LEN, timeout);
    if (0 > l_len)
    {
        PS_PRINT_ERR("recv result fail\n");
        return -EFAIL;
    }

    if (!OS_MEM_CMP(auc_buf, expect, OS_STR_LEN(expect)))
    {
        PS_PRINT_DBG(" send SUCC, expect [%s] ok\n", expect);
        return SUCC;
    }
    else
    {
        PS_PRINT_WARNING(" error result[%s], expect [%s], read result again\n", auc_buf, expect);
    }

    return -EFAIL;
}

int msg_send_and_recv_except(unsigned char *data, int len, const unsigned char *expect)
{
    int  i;
    int  l_ret;

    for(i = 0; i < HOST_DEV_TIMEOUT; i++)
    {
        l_ret = send_msg(data, len);
        if (0 > l_ret)
        {
            continue;
        }

        l_ret = recv_expect_result(expect);
        if (0 == l_ret)
        {
            return SUCC;
        }
    }

    return -EFAIL;
}

void *malloc_cmd_buf(unsigned char *puc_cfg_info_buf, unsigned int ul_index)
{
    int           l_len;
    unsigned char          *flag;
    unsigned char          *p_buf;

    if (NULL == puc_cfg_info_buf)
    {
        PS_PRINT_ERR("malloc_cmd_buf: buf is NULL!\n");
        return NULL;
    }

    flag = puc_cfg_info_buf;
    g_st_cfg_info.al_count[ul_index] = 0;
    while(NULL != flag)
    {
        flag = OS_STR_CHR(flag, CMD_LINE_SIGN);
        if (NULL == flag)
        {
            break;
        }
        g_st_cfg_info.al_count[ul_index]++;
        flag++;
    }
    PS_PRINT_DBG("cfg file cmd count: al_count[%d] = %d\n", ul_index, g_st_cfg_info.al_count[ul_index]);

    l_len = ((g_st_cfg_info.al_count[ul_index]) + CFG_INFO_RESERVE_LEN) * sizeof(struct cmd_type_st);
    p_buf = OS_KMALLOC_GFP(l_len);
    if (NULL == p_buf)
    {
        PS_PRINT_ERR("kmalloc cmd_type_st fail\n");
        return NULL;
    }
    OS_MEM_SET((void *)p_buf, 0, l_len);

    return p_buf;
}

unsigned char *delete_space(unsigned char *string, int *len)
{
    int i;

    if ((NULL == string) || (NULL == len))
    {
        return NULL;
    }

    for(i = *len - 1; i >= 0; i--)
    {
        if (COMPART_KEYWORD != string[i])
        {
            break;
        }
        string[i] = '\0';
    }

    if (i < 0)
    {
        PS_PRINT_ERR(" string is Space bar\n");
        return NULL;
    }

    *len = i + 1;

    for(i = 0; i < *len; i++)
    {
        if (COMPART_KEYWORD != string[i])
        {
            *len = *len - i;
            return &string[i];
        }
    }

    return NULL;
}

int string_to_num(unsigned char *string, int *number)
{
    int       i;
    int       l_num;

    if (NULL == string)
    {
        PS_PRINT_ERR("string is NULL!\n");
        return -EFAIL;
    }

    l_num = 0;
    for (i = 0; (string[i] >= '0') && (string[i] <= '9'); i++)
    {
        l_num = (l_num * 10) + (string[i] - '0');
    }

    *number = l_num;

    return SUCC;
}

int num_to_string(unsigned char *string, unsigned int number)
{
    int  i = 0, j = 0;
    int  tmp[INT32_STR_LEN];
    unsigned int num = number;

    if (NULL == string)
    {
        PS_PRINT_ERR("string is NULL!\n");
        return -EFAIL;
    }

    do{
        tmp[i] = num % 10;
        num    = num / 10;
        i++;
    }while(num != 0);

    do{
        string[j] = tmp[i-1-j] + '0';
        j++;
    }while(j != i);

    string[j] = '\0';

    return SUCC;
}

OS_KERNEL_FILE_STRU * open_file_to_readm(unsigned char *name)
{
    OS_KERNEL_FILE_STRU *fp;
    unsigned char *file_name = NULL;

    if (WARN_ON(NULL == name))
    {
#if (_PRE_HI110X_LOG_VERSION == _PRE_HI110X_LOG_V2)
        file_name = "/data/log/wifi/memdump/readm_wifi";
#else
        file_name = "/data/memdump/readm_wifi";
#endif
    }
    else
    {
        file_name = name;
    }

    fp = filp_open(file_name, O_RDWR | O_CREAT, 0664);

    return fp;
}

int recv_device_mem(OS_KERNEL_FILE_STRU *fp, unsigned char *pucDataBuf, int len)
{
    int l_ret = -EFAIL;
    mm_segment_t fs;
    unsigned char retry = 3;
    int lenbuf = 0;

    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("fp is error,fp = 0x%p\n", fp);
        return -EFAIL;
    }

    if (NULL == pucDataBuf)
    {
        PS_PRINT_ERR("pucDataBuf is NULL\n");
        return -EFAIL;
    }

    PS_PRINT_DBG("expect recv len is [%d]\n", len);

    fs = get_fs();
    set_fs(KERNEL_DS);
    //l_ret = vfs_llseek(fp, 0, SEEK_END);
    PS_PRINT_DBG("pos = %d\n", (int)fp->f_pos);
    while (len > lenbuf)
    {
        l_ret = read_msg(pucDataBuf + lenbuf, len - lenbuf);
        if (l_ret > 0)
        {
            lenbuf += l_ret;
        }
        else
        {
            retry--;
            lenbuf = 0;
            if (0 == retry)
            {
                l_ret = -EFAIL;
                PS_PRINT_ERR("time out\n");
                break;
            }
        }
    }

    if (len <= lenbuf)
    {
        vfs_write(fp, pucDataBuf, len, &fp->f_pos);
    }
    vfs_fsync(fp, 0);
    set_fs(fs);

    return l_ret;
}

int check_version(void)
{
    int   l_ret;
    int   l_len;
    int   i;
    unsigned char   rec_buf[VERSION_LEN];

    for (i = 0; i < HOST_DEV_TIMEOUT; i++)
    {
        OS_MEM_SET(rec_buf, 0, VERSION_LEN);

        OS_MEM_CPY(rec_buf, (unsigned char *)VER_CMD_KEYWORD, OS_STR_LEN(VER_CMD_KEYWORD));
        l_len = OS_STR_LEN(VER_CMD_KEYWORD);

        rec_buf[l_len] = COMPART_KEYWORD;
        l_len++;

        l_ret = send_msg(rec_buf, l_len);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send version fail![%d]\n", i);
            continue;
        }

        OS_MEM_SET(g_st_cfg_info.auc_DevVersion, 0, VERSION_LEN);
        OS_MEM_SET(rec_buf, 0, VERSION_LEN);
        msleep(1);

        l_ret = read_msg(rec_buf, VERSION_LEN);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("read version fail![%d]\n", i);
            continue;
        }

        OS_MEM_CPY(g_st_cfg_info.auc_DevVersion, rec_buf, VERSION_LEN);

        if (!OS_MEM_CMP((char *)g_st_cfg_info.auc_DevVersion,
                              (char *)g_st_cfg_info.auc_CfgVersion,
                              OS_STR_LEN(g_st_cfg_info.auc_CfgVersion)))
        {
            PS_PRINT_INFO("Device Version = [%s], CfgVersion = [%s].\n",
                        g_st_cfg_info.auc_DevVersion, g_st_cfg_info.auc_CfgVersion);
            return SUCC;
        }
        else
        {
            PS_PRINT_ERR("ERROR version,Device Version = [%s], CfgVersion = [%s].\n",
                        g_st_cfg_info.auc_DevVersion, g_st_cfg_info.auc_CfgVersion);
        }
    }

    return -EFAIL;
}

int number_type_cmd_send(unsigned char *Key, unsigned char *Value)
{
    int       l_ret;
    int       data_len;
    int       Value_len;
    int       i;
    int       n;
    unsigned char       auc_num[INT32_STR_LEN];
    unsigned char       buff_tx[SEND_BUF_LEN];

    Value_len = OS_STR_LEN((char *)Value);

    OS_MEM_SET(auc_num, 0, INT32_STR_LEN);
    OS_MEM_SET(buff_tx, 0, SEND_BUF_LEN);

    data_len = 0;
    data_len = OS_STR_LEN(Key);
    OS_MEM_CPY(buff_tx, Key, data_len);

    buff_tx[data_len] = COMPART_KEYWORD;
    data_len = data_len + 1;

    for (i = 0, n = 0; (i <= Value_len) && (n < INT32_STR_LEN); i++)
    {
        if ((',' == Value[i]) || (i == Value_len ))
        {
            PS_PRINT_DBG("auc_num = %s, i = %d, n = %d\n", auc_num,  i, n);
            if (0 == n)
            {
                continue;
            }
            OS_MEM_CPY((unsigned char *)&buff_tx[data_len], auc_num, n);
            data_len = data_len + n;

            buff_tx[data_len] = COMPART_KEYWORD;
            data_len = data_len + 1;

            OS_MEM_SET(auc_num, 0, INT32_STR_LEN);
            n = 0;
        }
        else if (COMPART_KEYWORD == Value[i])
        {
            continue;
        }
        else
        {
            auc_num[n] = Value[i];
            n++;
        }

    }

    l_ret = send_msg(buff_tx, data_len);

    return l_ret;
}

int update_device_cali_count(unsigned char *Key, unsigned char *Value)
{
    int  l_ret;
    unsigned int len, Value_len;
    unsigned int number = 0;
    unsigned char *addr;
    unsigned char  buff_tx[SEND_BUF_LEN];

    len = 0;
    OS_MEM_SET(buff_tx, 0, SEND_BUF_LEN);

    /* buff_tx="" */
    buff_tx[len] = '4';
    len++;
    buff_tx[len] = ',';
    len++;

    /* buff_tx="4," */
    Value_len = OS_STR_LEN(Value);
    addr = delete_space(Value, &Value_len);
    if (NULL == addr)
    {
        PS_PRINT_ERR("addr is NULL, Value[%s] Value_len[%d]", Value, Value_len);
        return -EFAIL;
    }
    OS_MEM_CPY(&buff_tx[len], addr, Value_len);
    len += Value_len;
    buff_tx[len] = ',';
    len++;

    /* buff_tx="4,0xXXX," */
    l_ret = get_cali_count(&number);
    l_ret = num_to_string(&buff_tx[len], number);

    l_ret = number_type_cmd_send(WMEM_CMD_KEYWORD, buff_tx);
    if (0 > l_ret)
    {
        PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", Key, buff_tx);
        return l_ret;
    }

    l_ret = recv_expect_result(MSG_FROM_DEV_WRITEM_OK);
    if (0 > l_ret)
    {
        PS_PRINT_ERR("recv expect result fail!\n");
        return l_ret;
    }

    return SUCC;
}

int download_bfgx_cali_data(unsigned char *Key, unsigned char *Value)
{
    int  l_ret;
    unsigned int len = 0, Value_len;
    unsigned char *addr;
    unsigned char  buff_tx[SEND_BUF_LEN];

    OS_MEM_SET(buff_tx, 0, SEND_BUF_LEN);

    /* buff_tx="" */
    len = OS_STR_LEN(Key);
    OS_MEM_CPY(buff_tx, Key, len);
    buff_tx[len] = COMPART_KEYWORD;
    len++;

    /* buff_tx="FILES " */
    buff_tx[len] = '1';
    len++;
    buff_tx[len] = COMPART_KEYWORD;
    len++;

    /* buff_tx="FILES 1 " */
    Value_len = OS_STR_LEN(Value);
    addr = delete_space(Value, &Value_len);
    if (NULL == addr)
    {
        PS_PRINT_ERR("addr is NULL, Value[%s] Value_len[%d]", Value, Value_len);
        return -EFAIL;
    }
    OS_MEM_CPY(&buff_tx[len], addr, Value_len);
    len += Value_len;
    buff_tx[len] = COMPART_KEYWORD;
    len++;

    /* buff_tx="FILES 1 0xXXXX " */

    l_ret = msg_send_and_recv_except(buff_tx, len, MSG_FROM_DEV_READY_OK);
    if (0 > l_ret)
    {
        PS_PRINT_ERR("SEND [%s] addr error\n", Key);
        return -EFAIL;
    }

    l_ret = get_bfgx_cali_data(buff_tx, &len, sizeof(buff_tx));
    if (0 > l_ret  || len > SEND_BUF_LEN)
    {
        PS_PRINT_ERR("get bfgx cali data failed, len=%d\n", len);
        return -EFAIL;
    }

    /* Wait at least 5 ms */
    usleep_range(FILE_CMD_WAIT_TIME_MIN, FILE_CMD_WAIT_TIME_MAX);

    l_ret = msg_send_and_recv_except(buff_tx, sizeof(buff_tx), MSG_FROM_DEV_FILES_OK);
    if(0 > l_ret)
    {
        PS_PRINT_ERR(" sdio send data fail\n");
        return -EFAIL;
    }

    return SUCC;
}

int parse_file_cmd(unsigned char *string, ulong *addr, char **file_path)
{
    unsigned char *tmp;
    int count = 0;
    char *after;

    if (string == NULL || addr == NULL || file_path == NULL)
    {
        PS_PRINT_ERR("param is error!\n");
        return -EFAIL;
    }

    tmp = string;
    while(COMPART_KEYWORD == *tmp)
    {
        tmp++;
    }
    string_to_num(tmp, &count);
    if (count != FILE_COUNT_PER_SEND)
    {
        PS_PRINT_ERR("the count of send file must be 1, count = [%d]\n", count);
        return -EFAIL;
    }

    tmp = OS_STR_CHR(string, ',');
    if (tmp == NULL)
    {
        PS_PRINT_ERR("param string is err!\n");
        return -EFAIL;
    }
    else
    {
        tmp++;
        while(COMPART_KEYWORD == *tmp)
        {
            tmp++;
        }
    }

    *addr = simple_strtoul(tmp, &after, 16);

    PS_PRINT_DBG("file to send addr:[0x%lx]\n", *addr);

    after++;
    while(COMPART_KEYWORD == *after)
    {
        after++;
    }

    PS_PRINT_DBG("after:[%s]\n", after);

    *file_path = after;

    return SUCC;
}

#ifdef CONFIG_MMC
extern void oal_sdio_sdt_print_wcpu_reg(oal_uint32* pst_buf, oal_uint32 ul_size);
#endif

int sdio_read_device_mem(struct st_wifi_dump_mem_info *pst_mem_dump_info,
                                  OS_KERNEL_FILE_STRU *fp,
                                  unsigned char *pucDataBuf,
                                  unsigned int ulDataBufLen)
{
    unsigned char buf_tx[SEND_BUF_LEN];
    int ret = 0;
    unsigned int size = 0;
    unsigned int offset;
    unsigned int remainder = pst_mem_dump_info->size;

    offset=0;
    while(remainder > 0)
    {
        OS_MEM_SET(buf_tx, 0, SEND_BUF_LEN);

        size = min(remainder, ulDataBufLen);
        snprintf(buf_tx,sizeof(buf_tx),"%s%c0x%lx%c%d%c",
                                                RMEM_CMD_KEYWORD,
                                                COMPART_KEYWORD,
                                                pst_mem_dump_info->mem_addr + offset,
                                                COMPART_KEYWORD,
                                                size,
                                                COMPART_KEYWORD);
        PS_PRINT_DBG("read mem cmd:[%s]\n", buf_tx);
        send_msg(buf_tx, OS_STR_LEN(buf_tx));

        ret = recv_device_mem(fp, pucDataBuf, size);
        if(ret < 0)
        {
            PS_PRINT_ERR("wifi mem dump fail, filename is [%s],ret=%d\n", pst_mem_dump_info->file_name,ret);
            break;
        }

#ifdef CONFIG_PRINTK
        if( 0 == offset)
        {
            oal_int8* pst_file_name = (pst_mem_dump_info->file_name ? ((oal_int8*)pst_mem_dump_info->file_name):(oal_int8*)"default: ");
            if(!oal_strcmp("wifi_device_panic_mem", pst_file_name))
            {
                /*dump the device cpu reg mem when panic,
                  24B mem header + 24*4 reg info*/
                if(size > (24 + 24*4))
                {
                    oal_print_hex_dump(pucDataBuf + 24, 24*4, 32, pst_file_name);
                    /*print sdt log*/
#ifdef CONFIG_MMC
                    /*dump 24*4B*/
                    oal_sdio_sdt_print_wcpu_reg((oal_uint32*)(pucDataBuf + 24), 24);
#endif
                }
            }
        }
#endif

        offset += size;

        remainder -= size;
    }

    return ret;
}

int sdio_device_mem_dump(struct st_wifi_dump_mem_info *pst_mem_dump_info, unsigned int count)
{
    OS_KERNEL_FILE_STRU *fp;
    int ret = -EFAIL;
    unsigned int i;
    char filename[100] = {0};

    ktime_t time_start, time_stop;
    oal_uint64  trans_us;
    unsigned char *pucDataBuf = NULL;
    unsigned int sdio_transfer_limit = oal_sdio_func_max_req_size(oal_get_sdio_default_handler());

    sdio_transfer_limit = OAL_MIN(PAGE_SIZE, sdio_transfer_limit);

    if (NULL == pst_mem_dump_info)
    {
        PS_PRINT_ERR("pst_wifi_dump_info is NULL\n");
        return -EFAIL;
    }

    do
    {
        PS_PRINT_INFO("try to malloc mem dump buf len is [%d]\n", sdio_transfer_limit);
        pucDataBuf = (unsigned char *)OS_KMALLOC_GFP(sdio_transfer_limit);
        if (NULL == pucDataBuf)
        {
            PS_PRINT_WARNING("malloc mem  len [%d] fail, continue to try in a smaller size\n", sdio_transfer_limit);
            sdio_transfer_limit = sdio_transfer_limit >> 1;
        }
    }while((NULL == pucDataBuf) && (sdio_transfer_limit >= MIN_FIRMWARE_FILE_TX_BUF_LEN));

    if (NULL == pucDataBuf)
    {
        PS_PRINT_ERR("pucDataBuf KMALLOC failed\n");
        return -EFAIL;
    }

    PS_PRINT_INFO("mem dump data buf len is [%d]\n", sdio_transfer_limit);

    plat_wait_last_rotate_finish();

    for (i = 0; i < count; i++)
    {
        time_start = ktime_get();
        OS_MEM_SET(filename, 0, sizeof(filename));
#if (_PRE_HI110X_LOG_VERSION == _PRE_HI110X_LOG_V2)
        snprintf(filename, sizeof(filename), "/data/log/wifi/memdump/%s_%s.bin", SDIO_STORE_WIFI_MEM, pst_mem_dump_info[i].file_name);
#else
        snprintf(filename, sizeof(filename),"/data/memdump/%s_%s.bin", SDIO_STORE_WIFI_MEM, pst_mem_dump_info[i].file_name);
#endif
        PS_PRINT_INFO("readm %s\n",filename);

        fp = open_file_to_readm(filename);
        if (IS_ERR_OR_NULL(fp))
        {
            PS_PRINT_ERR("create file error,fp = 0x%p, filename is [%s]\n", fp, pst_mem_dump_info[i].file_name);
            break;
        }

        ret = sdio_read_device_mem(&pst_mem_dump_info[i], fp, pucDataBuf, sdio_transfer_limit);
        if (ret < 0)
        {
            filp_close(fp, NULL);
            break;
        }
        filp_close(fp, NULL);
        time_stop = ktime_get();
        trans_us = (oal_uint64)ktime_to_us(ktime_sub(time_stop, time_start));
        OAL_IO_PRINT("device get mem %s cost %llu us\n", filename, trans_us);
    }

    /*send cmd to oam_hisi to rotate file*/
    plat_send_rotate_cmd_2_app(CMD_READM_WIFI_SDIO);

    OS_MEM_KFREE(pucDataBuf);

    return ret;
}

int sdio_read_mem(unsigned char *Key, unsigned char *Value)
{
    int l_ret = -EFAIL;
    int size;
    unsigned char *flag;
    OS_KERNEL_FILE_STRU *fp;
    unsigned char *pucDataBuf = NULL;
    unsigned int sdio_transfer_limit = oal_sdio_func_max_req_size(oal_get_sdio_default_handler());

    flag = OS_STR_CHR(Value, ',');
    if (NULL == flag)
    {
        PS_PRINT_ERR("RECV LEN ERROR..\n");
        return -EFAIL;
    }
    flag++;
    PS_PRINT_DBG("recv len [%s]\n", flag);
    while(COMPART_KEYWORD == *flag)
    {
        flag++;
    }

    string_to_num(flag, &size);

    do
    {
        PS_PRINT_INFO("try to malloc sdio mem read buf len is [%d]\n", sdio_transfer_limit);
        pucDataBuf = (unsigned char *)OS_KMALLOC_GFP(sdio_transfer_limit);
        if (NULL == pucDataBuf)
        {
            PS_PRINT_WARNING("malloc mem len [%d] fail, continue to try in a smaller size\n", sdio_transfer_limit);
            sdio_transfer_limit = sdio_transfer_limit >> 1;
        }
    }while((NULL == pucDataBuf) && (sdio_transfer_limit >= MIN_FIRMWARE_FILE_TX_BUF_LEN));

    if (NULL == pucDataBuf)
    {
        PS_PRINT_ERR("pucDataBuf KMALLOC failed\n");
        return -EFAIL;
    }

    fp = open_file_to_readm(NULL);
    if (IS_ERR(fp))
    {
        PS_PRINT_ERR("create file error,fp = 0x%p\n", fp);
        OS_MEM_KFREE(pucDataBuf);
        return SUCC;
    }

    l_ret = number_type_cmd_send(Key, Value);
    if (0 > l_ret)
    {
        PS_PRINT_ERR("send %s,%s fail \n", Key, Value);
        filp_close(fp, NULL);
        OS_MEM_KFREE(pucDataBuf);
        return l_ret;
    }

    PS_PRINT_DBG("recv len [%d]\n", size);

    l_ret = recv_device_mem(fp, pucDataBuf, size);

    filp_close(fp, NULL);
    OS_MEM_KFREE(pucDataBuf);

    return l_ret;
}

int exec_number_type_cmd(unsigned char *Key, unsigned char *Value)
{
    int       l_ret = -EFAIL;
    BOARD_INFO* board_info = NULL;

    board_info = get_hi110x_board_info();
    if (NULL == board_info)
    {
        PS_PRINT_ERR("board_info is null!\n");
        return -EFAIL;
    }
    if (MODE_SDIO == board_info->wlan_download_channel)
    {
        if (!OS_MEM_CMP(Key, VER_CMD_KEYWORD, OS_STR_LEN(VER_CMD_KEYWORD)))
        {
            l_ret = check_version();
            if (0 > l_ret)
            {
                PS_PRINT_ERR("check version FAIL [%d]\n", l_ret);
                return -EFAIL;
            }
        }

        if (!OS_STR_CMP((char *)Key, WMEM_CMD_KEYWORD))
        {
            if (NULL != OS_STR_STR((char *)Value, (char *)STR_REG_NFC_EN_KEEP))
            {
                if(V100 == get_ec_version())
                {
                    PS_PRINT_INFO("hi110x V100\n");
                }
                else
                {
                    PS_PRINT_INFO("hi110x V120\n");
                    return SUCC;
                }
            }

            l_ret = number_type_cmd_send(Key, Value);
            if (0 > l_ret)
            {
                PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", Key, Value);
                return l_ret;
            }

            l_ret = recv_expect_result(MSG_FROM_DEV_WRITEM_OK);
            if (0 > l_ret)
            {
                PS_PRINT_ERR("recv expect result fail!\n");
                return l_ret;
            }

        }
        else if (!OS_STR_CMP((char *)Key, CALI_COUNT_CMD_KEYWORD))
        {
            l_ret = update_device_cali_count(Key, Value);
            if (0 > l_ret)
            {
                PS_PRINT_ERR("update device cali count fail\n");
                return l_ret;
            }
        }
        else if (!OS_STR_CMP((char *)Key, CALI_BFGX_DATA_CMD_KEYWORD))
        {
            l_ret = download_bfgx_cali_data(FILES_CMD_KEYWORD, Value);
            if (0 > l_ret)
            {
                PS_PRINT_ERR("download bfgx cali data fail\n");
                return l_ret;
            }
        }
        else if (!OS_STR_CMP((char *)Key, JUMP_CMD_KEYWORD))
        {
            g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_SUCC;
            l_ret = number_type_cmd_send(Key, Value);
            if (0 > l_ret)
            {
                PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", Key, Value);
                return l_ret;
            }

            /*100000ms timeout*/
            l_ret = recv_expect_result_timeout(MSG_FROM_DEV_JUMP_OK, READ_MEG_JUMP_TIMEOUT);
            if (l_ret >= 0)
            {
                PS_PRINT_INFO("JUMP success!\n");
                return l_ret;
            }
            else
            {
                PS_PRINT_ERR("CMD JUMP timeout! l_ret=%d\n", l_ret);
                g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_FAIL;
                return l_ret;
            }
        }
        else if (!OS_STR_CMP((char *)Key, SETPM_CMD_KEYWORD) || !OS_STR_CMP((char *)Key, SETBUCK_CMD_KEYWORD)
              || !OS_STR_CMP((char *)Key, SETSYSLDO_CMD_KEYWORD) || !OS_STR_CMP((char *)Key, SETNFCRETLDO_CMD_KEYWORD)
              || !OS_STR_CMP((char *)Key, SETPD_CMD_KEYWORD) || !OS_STR_CMP((char *)Key, SETNFCCRG_CMD_KEYWORD)
              || !OS_STR_CMP((char *)Key, SETABB_CMD_KEYWORD) || !OS_STR_CMP((char *)Key, SETTCXODIV_CMD_KEYWORD))
        {
            l_ret = number_type_cmd_send(Key, Value);
            if (0 > l_ret)
            {
                PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", Key, Value);
                return l_ret;
            }

            l_ret = recv_expect_result(MSG_FROM_DEV_SET_OK);
            if (0 > l_ret)
            {
                PS_PRINT_ERR("recv expect result fail!\n");
                return l_ret;
            }
        }
        else if (!OS_STR_CMP((char *)Key, RMEM_CMD_KEYWORD))
        {
            l_ret = sdio_read_mem(Key, Value);
        }
    }
    else if (MODE_PCIE == board_info->wlan_download_channel)
    {
        PS_PRINT_ERR("download_firmware_mode=%d is illegal\n", board_info->wlan_download_channel);
        return -EFAIL;
    }
    else
    {
        PS_PRINT_ERR("download_firmware_mode=%d is illegal\n", board_info->wlan_download_channel);
        return -EFAIL;
    }

    return l_ret;
}

int exec_quit_type_cmd(void)
{
    int   l_ret;
    int   l_len;
    unsigned char   buf[8];
    BOARD_INFO* board_info = NULL;

    board_info = get_hi110x_board_info();
    if (NULL == board_info)
    {
        PS_PRINT_ERR("board_info is null!\n");
        return -EFAIL;
    }

    OS_MEM_SET(buf, 0, 8);
    if (MODE_SDIO == board_info->wlan_download_channel)
    {
        OS_MEM_CPY(buf, (unsigned char *)QUIT_CMD_KEYWORD, OS_STR_LEN(QUIT_CMD_KEYWORD));
        l_len = OS_STR_LEN(QUIT_CMD_KEYWORD);

        buf[l_len] = COMPART_KEYWORD;
        l_len++;

        l_ret = msg_send_and_recv_except(buf, l_len, MSG_FROM_DEV_QUIT_OK);
    }
    else if (MODE_PCIE == board_info->wlan_download_channel)
    {
        l_ret = -EFAIL;
    }
    else
    {
        PS_PRINT_ERR("download_firmware_mode=%d is illegal\n", board_info->wlan_download_channel);
        return -EFAIL;
    }
    return l_ret;
}

int exec_file_type_cmd(unsigned char *Key, unsigned char *Value)
{
    ulong addr;
    ulong addr_send;
    char *path;
    int ret;
    unsigned int file_len;
    unsigned int transmit_limit;
    unsigned int per_send_len;
    unsigned int send_count;
    int rdlen;
    unsigned int i;
    unsigned int offset = 0;
    unsigned char buff_tx[SEND_BUF_LEN] = {0};
    OS_KERNEL_FILE_STRU *fp;
    BOARD_INFO* board_info = NULL;

    board_info = get_hi110x_board_info();
    if (NULL == board_info)
    {
        PS_PRINT_ERR("board_info is null!\n");
        return -EFAIL;
    }

    ret = parse_file_cmd(Value, &addr, &path);
    if (ret < 0)
    {
        PS_PRINT_ERR("parse file cmd fail!\n");
        return ret;
    }

    PS_PRINT_INFO("download firmware:%s\n", path);

    fp = filp_open(path, O_RDONLY, 0);
    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("filp_open [%s] fail!!, fp=%p\n", path, fp);
        fp = NULL;
        return -EFAIL;
    }

    file_len = vfs_llseek(fp, 0, SEEK_END);
    vfs_llseek(fp, 0, SEEK_SET);

    PS_PRINT_DBG("file len is [%d]\n", file_len);

    transmit_limit = g_ulDataBufLen;
    per_send_len = (transmit_limit > file_len) ? file_len : transmit_limit;
    send_count = (file_len + per_send_len - 1)/per_send_len;
    if (MODE_SDIO == board_info->wlan_download_channel)
    {
        for (i = 0; i < send_count; i++)
        {
            rdlen = kernel_read(fp, fp->f_pos, g_pucDataBuf, per_send_len);
            if (rdlen > 0)
            {
                PS_PRINT_DBG("len of kernel_read is [%d], i=%d\n", rdlen, i);
                fp->f_pos += rdlen;
            }
            else
            {
                PS_PRINT_ERR("len of kernel_read is error! ret=[%d], i=%d\n", rdlen, i);
                filp_close(fp, NULL);
                return -EFAIL;
            }

            addr_send = addr + offset;
            PS_PRINT_DBG("send addr is [0x%lx], i=%d\n", addr_send, i);
            snprintf(buff_tx, SEND_BUF_LEN, "%s%c%d%c0x%lx%c",
                                                FILES_CMD_KEYWORD,
                                                COMPART_KEYWORD,
                                                FILE_COUNT_PER_SEND,
                                                COMPART_KEYWORD,
                                                addr_send,
                                                COMPART_KEYWORD);

            PS_PRINT_DBG("send file addr cmd is [%s]\n", buff_tx);
            ret = msg_send_and_recv_except(buff_tx, OS_STR_LEN(buff_tx), MSG_FROM_DEV_READY_OK);
            if (0 > ret)
            {
                PS_PRINT_ERR("SEND [%s] error\n", buff_tx);
                filp_close(fp, NULL);
                return -EFAIL;
            }

            /* Wait at least 5 ms */
            usleep_range(FILE_CMD_WAIT_TIME_MIN, FILE_CMD_WAIT_TIME_MAX);

            ret = msg_send_and_recv_except(g_pucDataBuf, rdlen, MSG_FROM_DEV_FILES_OK);
            if(0 > ret)
            {
                PS_PRINT_ERR(" sdio send data fail\n");
                filp_close(fp, NULL);
                return -EFAIL;
            }
            offset += rdlen;
        }
    }
    else if (MODE_PCIE == board_info->wlan_download_channel)
    {
        /*download with PCI-E*/
        PS_PRINT_ERR("download_firmware_mode=%d is illegal\n", board_info->wlan_download_channel);
        filp_close(fp, NULL);
        return -EFAIL;
    }
    else
    {
        PS_PRINT_ERR(" download_firmware_mode=%d is illegal\n", board_info->wlan_download_channel);
        filp_close(fp, NULL);
        return -EFAIL;
    }
    filp_close(fp, NULL);

    if (offset != file_len)
    {
        PS_PRINT_ERR("file send len is err! send len is [%d], file len is [%d]\n", offset, file_len);
        return -EFAIL;
    }

    return SUCC;
}

int exec_shutdown_type_cmd(unsigned int which_cpu)
{
    int l_ret = -EFAIL;
    unsigned char Value_SHUTDOWN[SHUTDOWN_TX_CMD_LEN];

    if (DEV_WCPU == which_cpu)
    {
        snprintf(Value_SHUTDOWN, sizeof(Value_SHUTDOWN),"%d,%s,%d", 2, SOFT_WCPU_EN_ADDR, 0);

        l_ret = number_type_cmd_send(WMEM_CMD_KEYWORD, Value_SHUTDOWN);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", SHUTDOWN_WIFI_CMD_KEYWORD, Value_SHUTDOWN);
            return l_ret;
        }
    }
    else if (DEV_BCPU == which_cpu)
    {
        snprintf(Value_SHUTDOWN, sizeof(Value_SHUTDOWN),"%d,%s,%d", 2, SOFT_BCPU_EN_ADDR, 0);

        l_ret = number_type_cmd_send(WMEM_CMD_KEYWORD, Value_SHUTDOWN);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", SHUTDOWN_BFGX_CMD_KEYWORD, Value_SHUTDOWN);
            return l_ret;
        }

        l_ret = recv_expect_result(MSG_FROM_DEV_WRITEM_OK);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("recv expect result fail!\n");
            return l_ret;
        }

        snprintf(Value_SHUTDOWN, sizeof(Value_SHUTDOWN),"%d,%s,%d", 2, BCPU_DE_RESET_ADDR, 1);

        l_ret = number_type_cmd_send(WMEM_CMD_KEYWORD, Value_SHUTDOWN);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("send key=[%s],value=[%s] fail\n", SHUTDOWN_BFGX_CMD_KEYWORD, Value_SHUTDOWN);
            return l_ret;
        }

        l_ret = recv_expect_result(MSG_FROM_DEV_WRITEM_OK);
        if (0 > l_ret)
        {
            PS_PRINT_ERR("recv expect result fail!\n");
            return l_ret;
        }
    }
    else
    {
        PS_PRINT_ERR("para is error, which_cpu=[%d]\n", which_cpu);
        return  -EFAIL;
    }

    return SUCC;
}

int execute_download_cmd(int cmd_type, unsigned char *cmd_name, unsigned char *cmd_para)
{
    int l_ret;

    switch(cmd_type)
    {
         case FILE_TYPE_CMD:
            PS_PRINT_DBG(" command type FILE_TYPE_CMD\n");
            l_ret = exec_file_type_cmd(cmd_name, cmd_para);
            break;
         case NUM_TYPE_CMD:
            PS_PRINT_DBG(" command type NUM_TYPE_CMD\n");
            l_ret = exec_number_type_cmd(cmd_name, cmd_para);
            break;
         case QUIT_TYPE_CMD:
            PS_PRINT_DBG(" command type QUIT_TYPE_CMD\n");
            l_ret = exec_quit_type_cmd();
            break;
         case SHUTDOWN_WIFI_TYPE_CMD:
            PS_PRINT_DBG(" command type SHUTDOWN_WIFI_TYPE_CMD\n");
            l_ret = exec_shutdown_type_cmd(DEV_WCPU);
            break;
        case SHUTDOWN_BFGX_TYPE_CMD:
            PS_PRINT_DBG(" command type SHUTDOWN_BFGX_TYPE_CMD\n");
            l_ret = exec_shutdown_type_cmd(DEV_BCPU);
            break;

         default:
            PS_PRINT_ERR("command type error[%d]\n", cmd_type);
            l_ret = -EFAIL;
            break;
    }

    return l_ret;
}

int firmware_read_cfg(unsigned char *puc_CfgPatch, unsigned char *puc_read_buffer)
{
    OS_KERNEL_FILE_STRU    *fp;
    int                   l_ret;

    if ((NULL == puc_CfgPatch) || (NULL == puc_read_buffer))
    {
        PS_PRINT_ERR("para is NULL\n");
        return -EFAIL;
    }

    fp = filp_open(puc_CfgPatch, O_RDONLY, 0);
    if (IS_ERR_OR_NULL(fp))
    {
        PS_PRINT_ERR("open file %s fail, fp=%p\n", puc_CfgPatch, fp);
        fp = NULL;
        return -EFAIL;
    }

    OS_MEM_SET(puc_read_buffer, 0, READ_CFG_BUF_LEN);
    l_ret = kernel_read(fp, fp->f_pos, puc_read_buffer, READ_CFG_BUF_LEN);

    filp_close(fp, NULL);
    fp = NULL;

    return l_ret;
}

int firmware_parse_cmd(unsigned char *puc_cfg_buffer, unsigned char *puc_cmd_name, unsigned char *puc_cmd_para)
{
    int       l_ret;
    int       l_cmdlen;
    int       l_paralen;
    unsigned char      *begin;
    unsigned char      *end;
    unsigned char      *link;
    unsigned char      *handle;
    unsigned char      *handle_temp;

    begin = puc_cfg_buffer;
    if((NULL == puc_cfg_buffer) || (NULL == puc_cmd_name) || (NULL == puc_cmd_para))
    {
        PS_PRINT_ERR("para is NULL\n");
        return ERROR_TYPE_CMD;
    }

    if ('@' == puc_cfg_buffer[0])
    {
        return ERROR_TYPE_CMD;
    }

    link = OS_STR_CHR((char *)begin, '=');
    if (NULL == link)
    {
        if (NULL != OS_STR_STR((char *)puc_cfg_buffer, QUIT_CMD_KEYWORD))
        {
            return QUIT_TYPE_CMD;
        }
        else if (NULL != OS_STR_STR((char *)puc_cfg_buffer, SHUTDOWN_WIFI_CMD_KEYWORD))
        {
            return SHUTDOWN_WIFI_TYPE_CMD;
        }
        else if (NULL != OS_STR_STR((char *)puc_cfg_buffer, SHUTDOWN_BFGX_CMD_KEYWORD))
        {
            return SHUTDOWN_BFGX_TYPE_CMD;
        }

        return ERROR_TYPE_CMD;
    }

    end = OS_STR_CHR(link, ';');
    if (NULL == end)
    {
        return ERROR_TYPE_CMD;
    }

    l_cmdlen = link - begin;

    handle = delete_space((unsigned char *)begin, &l_cmdlen);
    if (NULL == handle)
    {
        return ERROR_TYPE_CMD;
    }

    if (!OS_MEM_CMP(handle, (unsigned char *)FILE_TYPE_CMD_KEY, OS_STR_LEN((unsigned char *)FILE_TYPE_CMD_KEY)))
    {
        handle_temp = OS_STR_STR(handle, (unsigned char *)FILE_TYPE_CMD_KEY);
        if (NULL == handle_temp)
        {
            PS_PRINT_ERR("'ADDR_FILE_'is not handle child string, handle=%s", handle);
            return ERROR_TYPE_CMD;
        }
        handle= handle_temp + OS_STR_LEN(FILE_TYPE_CMD_KEY);
        l_cmdlen = l_cmdlen - OS_STR_LEN(FILE_TYPE_CMD_KEY);
        l_ret = FILE_TYPE_CMD;
    }
    else if (!OS_MEM_CMP(handle, (unsigned char *)NUM_TYPE_CMD_KEY, OS_STR_LEN(NUM_TYPE_CMD_KEY)))
    {
        handle_temp = OS_STR_STR(handle, (unsigned char *)NUM_TYPE_CMD_KEY);
        if (NULL == handle_temp)
        {
            PS_PRINT_ERR("'PARA_' is not handle child string, handle=%s", handle);
            return ERROR_TYPE_CMD;
        }
        handle= handle_temp + OS_STR_LEN(NUM_TYPE_CMD_KEY);
        l_cmdlen = l_cmdlen - OS_STR_LEN(NUM_TYPE_CMD_KEY);
        l_ret = NUM_TYPE_CMD;
    }
    else
    {
        return ERROR_TYPE_CMD;
    }

    if (DOWNLOAD_CMD_LEN < l_cmdlen || 0 > l_cmdlen)
    {
        PS_PRINT_ERR("cmd len out of range!\n");
        return ERROR_TYPE_CMD;
    }
    OS_MEM_CPY(puc_cmd_name, handle, l_cmdlen);

    begin = link + 1;
    l_paralen = end - begin;
    if (DOWNLOAD_CMD_PARA_LEN < l_paralen || 0 > l_paralen)
    {
        PS_PRINT_ERR("para len out of range!\n");
        return ERROR_TYPE_CMD;
    }

    handle = delete_space((unsigned char *)begin, &l_paralen);
    if (NULL == handle)
    {
        return ERROR_TYPE_CMD;
    }
    OS_MEM_CPY(puc_cmd_para, handle, l_paralen);

    return l_ret;
}

int firmware_parse_cfg(unsigned char *puc_cfg_info_buf, int l_buf_len, unsigned int ul_index)
{
    int           i;
    int           l_len;
    unsigned char          *flag;
    unsigned char          *begin;
    unsigned char          *end;
    int           cmd_type;
    unsigned char           cmd_name[DOWNLOAD_CMD_LEN];
    unsigned char           cmd_para[DOWNLOAD_CMD_PARA_LEN];
    unsigned int          cmd_para_len = 0;
    if (NULL == puc_cfg_info_buf)
    {
        PS_PRINT_ERR("puc_cfg_info_buf is NULL!\n");
        return -EFAIL;
    }

    g_st_cfg_info.apst_cmd[ul_index] = (struct cmd_type_st *)malloc_cmd_buf(puc_cfg_info_buf, ul_index);
    if (NULL == g_st_cfg_info.apst_cmd[ul_index])
    {
        PS_PRINT_ERR(" malloc_cmd_buf fail!\n");
        return -EFAIL;
    }

    flag = puc_cfg_info_buf;
    l_len = l_buf_len;
    i = 0;
    while((i < g_st_cfg_info.al_count[ul_index]) && (flag < &puc_cfg_info_buf[l_len]))
    {
        begin = flag;
        end   = OS_STR_CHR(flag, '\n');
        if (NULL == end)
        {
            PS_PRINT_DBG("lost of new line!\n");
            end = &puc_cfg_info_buf[l_len];
        }
        else if (end == begin)
        {
            PS_PRINT_DBG("blank line\n");
            flag = end + 1;
            continue;
        }
        *end = '\0';

        PS_PRINT_DBG("operation string is [%s]\n", begin);

        OS_MEM_SET(cmd_name, 0, DOWNLOAD_CMD_LEN);
        OS_MEM_SET(cmd_para, 0, DOWNLOAD_CMD_PARA_LEN);

        cmd_type = firmware_parse_cmd(begin, cmd_name, cmd_para);

        PS_PRINT_DBG("cmd type=[%d],cmd_name=[%s],cmd_para=[%s]\n", cmd_type, cmd_name, cmd_para);

        if (ERROR_TYPE_CMD != cmd_type)
        {
            g_st_cfg_info.apst_cmd[ul_index][i].cmd_type = cmd_type;
            OS_MEM_CPY(g_st_cfg_info.apst_cmd[ul_index][i].cmd_name, cmd_name, DOWNLOAD_CMD_LEN);
            OS_MEM_CPY(g_st_cfg_info.apst_cmd[ul_index][i].cmd_para, cmd_para, DOWNLOAD_CMD_PARA_LEN);

            if (!OS_MEM_CMP(g_st_cfg_info.apst_cmd[ul_index][i].cmd_name,
                            VER_CMD_KEYWORD,
                            OS_STR_LEN(VER_CMD_KEYWORD)))
            {
                cmd_para_len = OS_STR_LEN(g_st_cfg_info.apst_cmd[ul_index][i].cmd_para);
                if (VERSION_LEN >= cmd_para_len)
                {
                    OS_MEM_CPY(g_st_cfg_info.auc_CfgVersion,
                        g_st_cfg_info.apst_cmd[ul_index][i].cmd_para,
                        cmd_para_len);
                }
                else
                {
                    PS_PRINT_DBG("cmd_para_len = %d over auc_CfgVersion length", cmd_para_len);
                    return -EFAIL;
                }
                PS_PRINT_DBG("g_CfgVersion = [%s].\n", g_st_cfg_info.auc_CfgVersion);
            }
            i++;
        }
        flag = end + 1;
    }

    g_st_cfg_info.al_count[ul_index] = i;
    PS_PRINT_INFO("effective cmd count: al_count[%d] = %d\n", ul_index, g_st_cfg_info.al_count[ul_index]);

    return SUCC;
}

int firmware_get_cfg(unsigned char *puc_CfgPatch, unsigned int ul_index)
{
    unsigned char   *puc_read_cfg_buf;
    int   l_readlen;
    int   l_ret;

    if (NULL == puc_CfgPatch)
    {
        PS_PRINT_ERR("cfg file path is null!\n");
        return -EFAIL;
    }

    puc_read_cfg_buf = OS_KMALLOC_GFP(READ_CFG_BUF_LEN);
    if (NULL == puc_read_cfg_buf)
    {
        PS_PRINT_ERR("kmalloc READ_CFG_BUF fail!\n");
        return -EFAIL;
    }

    l_readlen = firmware_read_cfg(puc_CfgPatch, puc_read_cfg_buf);
    if(0 > l_readlen)
    {
        PS_PRINT_ERR("read cfg error!\n");
        OS_MEM_KFREE(puc_read_cfg_buf);
        puc_read_cfg_buf = NULL;
        return -EFAIL;
    }

    else if (l_readlen > READ_CFG_BUF_LEN - 1)
    {
        PS_PRINT_ERR("cfg file [%s] larger than %d\n", puc_CfgPatch, READ_CFG_BUF_LEN);
        OS_MEM_KFREE(puc_read_cfg_buf);
        puc_read_cfg_buf = NULL;
        return -EFAIL;
    }
    else
    {
        PS_PRINT_DBG("read cfg file [%s] ok, size is [%d]\n", puc_CfgPatch, l_readlen);
    }

    l_ret = firmware_parse_cfg(puc_read_cfg_buf, l_readlen, ul_index);
    if(0 > l_ret)
    {
        PS_PRINT_ERR("parse cfg error!\n");
    }

    OS_MEM_KFREE(puc_read_cfg_buf);
    puc_read_cfg_buf = NULL;

    return l_ret;
}

int firmware_download(unsigned int ul_index)
{
    int l_ret;
    int i;
    int l_cmd_type;
    unsigned char *puc_cmd_name;
    unsigned char *puc_cmd_para;

    if (ul_index >= CFG_FILE_TOTAL)
    {
        PS_PRINT_ERR("ul_index [%d] is error!\n", ul_index);
        return -EFAIL;
    }

    store_efuse_info();

    PS_PRINT_INFO("start download firmware, ul_index = [%d]\n", ul_index);

    if (0 == g_st_cfg_info.al_count[ul_index])
    {
        PS_PRINT_ERR("firmware download cmd count is 0, ul_index = [%d]\n", ul_index);
        return -EFAIL;
    }

    g_ulDataBufLen = oal_sdio_func_max_req_size(oal_get_sdio_default_handler());
    PS_PRINT_INFO("sdio max transmit size is [%d]\n", g_ulDataBufLen);
    if (g_ulDataBufLen < HISDIO_BLOCK_SIZE)
    {
        PS_PRINT_ERR("sdio max transmit size [%d] is error!\n", g_ulDataBufLen);
        return -EFAIL;
    }

    do
    {
        PS_PRINT_INFO("try to malloc firmware download file buf len is [%d]\n", g_ulDataBufLen);
        g_pucDataBuf = (unsigned char *)OS_KMALLOC_GFP(g_ulDataBufLen);
        if (NULL == g_pucDataBuf)
        {
            PS_PRINT_WARNING("malloc mem len [%d] fail, continue to try in a smaller size\n", g_ulDataBufLen);
            g_ulDataBufLen = g_ulDataBufLen >> 1;
        }
    }while((NULL == g_pucDataBuf) && (g_ulDataBufLen >= MIN_FIRMWARE_FILE_TX_BUF_LEN));

    if (NULL == g_pucDataBuf)
    {
        PS_PRINT_ERR("g_pucDataBuf KMALLOC failed\n");
        return -EFAIL;
    }

    PS_PRINT_INFO("download firmware file buf len is [%d]\n", g_ulDataBufLen);

    for (i = 0; i < g_st_cfg_info.al_count[ul_index]; i++)
    {
        l_cmd_type   = g_st_cfg_info.apst_cmd[ul_index][i].cmd_type;
        puc_cmd_name = g_st_cfg_info.apst_cmd[ul_index][i].cmd_name;
        puc_cmd_para = g_st_cfg_info.apst_cmd[ul_index][i].cmd_para;

        PS_PRINT_DBG("cmd[%d]:type[%d], name[%s], para[%s]\n", i, l_cmd_type, puc_cmd_name, puc_cmd_para);

        PS_PRINT_DBG("firmware down start cmd[%d]:type[%d], name[%s]\n", i, l_cmd_type, puc_cmd_name);

        l_ret = execute_download_cmd(l_cmd_type, puc_cmd_name, puc_cmd_para);
        if (0 > l_ret)
        {
            if (RAM_REG_TEST_CFG == ul_index)
            {
                if ((!OS_MEM_CMP(puc_cmd_name, JUMP_CMD_KEYWORD, OS_STR_LEN(JUMP_CMD_KEYWORD))) && (CMD_JUMP_EXEC_RESULT_FAIL == g_ulJumpCmdResult))
                {
                    PS_PRINT_ERR("Device Mem Reg check result is fail\n");
                    continue;
                }
            }

            OS_MEM_KFREE(g_pucDataBuf);
            g_pucDataBuf = NULL;
            PS_PRINT_ERR("download firmware fail\n");

            return l_ret;
        }
        if (RAM_REG_TEST_CFG == ul_index)
        {
            if ((!OS_MEM_CMP(puc_cmd_name, RMEM_CMD_KEYWORD, OS_STR_LEN(RMEM_CMD_KEYWORD))) && (CMD_JUMP_EXEC_RESULT_FAIL == g_ulJumpCmdResult))
            {
                PS_PRINT_ERR("Device Mem Reg check WL_L2_RAM_BASEADDR fail\n");
                break;
            }
        }

        PS_PRINT_DBG("firmware down finish cmd[%d]:type[%d], name[%s]\n", i, l_cmd_type, puc_cmd_name);
    }

    OS_MEM_KFREE(g_pucDataBuf);
    g_pucDataBuf = NULL;

    PS_PRINT_INFO("finish download firmware\n");

    return SUCC;
}


int print_firmwrae_download_cmd(unsigned int ul_index)
{
    int i;
    int l_cmd_type;
    unsigned char *puc_cmd_name;
    unsigned char *puc_cmd_para;
    unsigned int count;

    count = g_st_cfg_info.al_count[ul_index];
    PS_PRINT_INFO("[%s] download cmd, total count is [%d]\n", g_auc_cfg_path[ul_index], count);

    for (i = 0; i < count; i++)
    {
        l_cmd_type   = g_st_cfg_info.apst_cmd[ul_index][i].cmd_type;
        puc_cmd_name = g_st_cfg_info.apst_cmd[ul_index][i].cmd_name;
        puc_cmd_para = g_st_cfg_info.apst_cmd[ul_index][i].cmd_para;

        PS_PRINT_INFO("cmd[%d]:type[%d], name[%s], para[%s]\n", i, l_cmd_type, puc_cmd_name, puc_cmd_para);
    }

    return 0;
}

int print_cfg_file_cmd(void)
{
    int i;

    for (i = 0; i < CFG_FILE_TOTAL; i++)
    {
        print_firmwrae_download_cmd(i);
    }

    return 0;
}

static int firmware_cfg_cmd_fill(unsigned int index, unsigned int cmd_count, unsigned char* cmd_str)
{
    unsigned int ul_size = 0;
    unsigned int ul_len  = 0;

    if ((NULL == cmd_str) || (cmd_count > g_st_cfg_info.al_count[index] + CFG_INFO_RESERVE_LEN - 1))
    {
        return -EFAIL;
    }

    g_st_cfg_info.apst_cmd[index][cmd_count].cmd_type = NUM_TYPE_CMD;

    ul_len  = OS_STR_LEN((unsigned char *)WMEM_CMD_KEYWORD) + 1;
    ul_size = (DOWNLOAD_CMD_LEN > ul_len) ? ul_len : DOWNLOAD_CMD_LEN;
    OS_MEM_CPY(g_st_cfg_info.apst_cmd[index][cmd_count].cmd_name, WMEM_CMD_KEYWORD, ul_size);

    ul_len  = OS_STR_LEN((unsigned char *)cmd_str) + 1;
    ul_size = (DOWNLOAD_CMD_PARA_LEN > ul_len) ? ul_len : DOWNLOAD_CMD_PARA_LEN;
    OS_MEM_CPY(g_st_cfg_info.apst_cmd[index][cmd_count].cmd_para, cmd_str, ul_size);

    return 0;
}

static int firmware_cfg_fill (unsigned int index, unsigned int cmd_count)
{
    int  result = 0;
    unsigned int count;

    if (CFG_FILE_TOTAL <= index || (0 == cmd_count))
    {
        return -EFAIL;
    }

    count = cmd_count;

    count -= 1;

    result  = firmware_cfg_cmd_fill(index, count++, "2,0x50002210,0x351C");
    result |= firmware_cfg_cmd_fill(index, count++, "2,0x50002214,0x301C");
    result |= firmware_cfg_cmd_fill(index, count++, "2,0x50002280,0x5413");
    result |= firmware_cfg_cmd_fill(index, count++, "2,0x50002284,0x2C00");

    if (count > g_st_cfg_info.al_count[index] + CFG_INFO_RESERVE_LEN - 1)
    {
        PS_PRINT_ERR("cfg space overflow, maxlen[0x%x] < reallen[0x%x]",(g_st_cfg_info.al_count[index] + CFG_INFO_RESERVE_LEN),count);
        return -EFAIL;
    }
    g_st_cfg_info.apst_cmd[index][count++].cmd_type = QUIT_TYPE_CMD;
    g_st_cfg_info.al_count[index] = count;

    return result;
}

int firmware_cfg_init_extra(void)
{
    oal_int32  result;
    oal_int32  wifi_5g_enable_info = WIFI_MODE_5G;
    unsigned int index = BFGX_AND_WIFI_CFG;
    unsigned int cmd_count = g_st_cfg_info.al_count[BFGX_AND_WIFI_CFG];

    result = get_cust_conf_int32(INI_MODU_WIFI, CHECK_5G_ENABLE, &wifi_5g_enable_info);
    if (0 > result)
    {
        PS_PRINT_WARNING("host get wifi 5g enable info fail\n");
        wifi_5g_enable_info = WIFI_MODE_5G;
    }

    if (WIFI_MODE_2_4G == wifi_5g_enable_info)
    {
        result = firmware_cfg_fill(index, cmd_count);
        if (SUCC != result)
        {
            PS_PRINT_ERR("cfg space overflow (err = 0x%x)\n",result);
        }
    }
    else
    {
        result = SUCC;
    }

    return result;
}

int firmware_cfg_init(void)
{
    int  l_ret;
    unsigned int i;

#ifdef _PRE_HI110X_FIRMWARE_NOT_BUILDIN
    int  firmware_in_boot = 1;

    l_ret = get_cust_conf_int32(INI_MODU_PLAT, "firmware_buildin", &firmware_in_boot);
    if (l_ret < 0)
    {
        PS_PRINT_INFO("not found firmware_buildin in ini file\n");
        firmware_in_boot = 1;
    }

    if (firmware_in_boot)
    {
        PS_PRINT_INFO("Hi110x firmware is buildin\n");
        g_auc_cfg_path = g_auc_cfg_in_boot_path;
    }
    else
    {
        PS_PRINT_INFO("Hi110x firmware is not buildin\n");
        g_auc_cfg_path = g_auc_cfg_in_system_path;
    }
#endif

    for (i = 0; i < CFG_FILE_TOTAL; i++)
    {
        l_ret = firmware_get_cfg(g_auc_cfg_path[i], i);
        if(0 > l_ret)
        {
            if (RAM_REG_TEST_CFG == i)
            {
                PS_PRINT_WARNING("ram_reg_test_cfg maybe not exist, please check\n");
                continue;
            }

            PS_PRINT_ERR("get cfg file [%s] fail\n", g_auc_cfg_path[i]);
            goto cfg_file_init_fail;
        }
    }

    l_ret = firmware_cfg_init_extra();
    if (SUCC != l_ret)
    {
        PS_PRINT_ERR("download cfg file fail (err = 0x%x)\n",l_ret);
        goto cfg_file_init_fail;
    }

    l_ret = cali_data_buf_malloc();
    if(0 > l_ret)
    {
        PS_PRINT_ERR("alloc cali data buf fail\n");
        goto alloc_cali_data_buf_fail;
    }

    return SUCC;

alloc_cali_data_buf_fail:

cfg_file_init_fail:
    firmware_cfg_clear();

    return -EFAIL;
}

int firmware_cfg_clear(void)
{
    int i;

    cali_data_buf_free();

    for (i = 0; i < CFG_FILE_TOTAL; i++)
    {
        g_st_cfg_info.al_count[i]= 0;
        if (NULL != g_st_cfg_info.apst_cmd[i])
        {
            OS_MEM_KFREE(g_st_cfg_info.apst_cmd[i]);
            g_st_cfg_info.apst_cmd[i] = NULL;
        }
    }

    return SUCC;
}

int nfc_buffer_data_recv(unsigned char *pucDataBuf, int len)
{
    unsigned int l_ret = 0;
    int lenbuf = 0;
    int retry = 3;

    if (NULL == pucDataBuf)
    {
        PS_PRINT_ERR("pucDataBuf is NULL\n");
        return -EFAIL;
    }

    while (len > lenbuf)
    {
        l_ret = read_msg(pucDataBuf + lenbuf, len - lenbuf);
        if (l_ret > 0)
        {
            lenbuf += l_ret;
        }
        else
        {
            retry--;
            lenbuf = 0;
            if (0 == retry)
            {
                PS_PRINT_ERR("time out\n");
                return -EFAIL;
            }
        }
    }
    return SUCC;
}

void save_nfc_lowpower_log_2_sdt(void)
{
    unsigned int cp_len = 0;
    unsigned int index = 0;
    unsigned char buf_tx[SEND_BUF_LEN];
    unsigned int total_len = 0;
    unsigned int buf_tx_len = 0;
    unsigned char retry;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }
    PS_PRINT_INFO("save nfc low-power log begin\n");
    total_len = nfc_buffer_data.size;
    oal_sdio_claim_host(pm_data->pst_wlan_pm_info->pst_sdio);

    g_pucNfcLog = kmalloc(NFC_SEND_LEN_LIMIT, GFP_ATOMIC);
    if (NULL == g_pucNfcLog)
    {
        PS_PRINT_ERR("nfc log buffer malloc fail!\n");
        return;
    }

    while (index < total_len)
    {
        cp_len = total_len - index;
        if (cp_len > NFC_SEND_LEN_LIMIT)
        {
            cp_len = NFC_SEND_LEN_LIMIT;
        }
        buf_tx_len = snprintf(buf_tx,sizeof(buf_tx),"%s%c0x%lx%c%d%c",
                                                RMEM_CMD_KEYWORD,
                                                COMPART_KEYWORD,
                                                nfc_buffer_data.mem_addr + index,
                                                COMPART_KEYWORD,
                                                cp_len,
                                                COMPART_KEYWORD);
        PS_PRINT_INFO("read nfc buffer cmd:[%s]\n", buf_tx);
        /*usleep_range(10000, 11000);*/
        send_msg(buf_tx, buf_tx_len);

        if(SUCC !=  nfc_buffer_data_recv(g_pucNfcLog, cp_len))
        {
            PS_PRINT_ERR("recv data error!\n");
            oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
            kfree(g_pucNfcLog);
            g_pucNfcLog = NULL;
            return;
        }
#if 0
        {
            unsigned int i =0;
            PS_PRINT_ERR("NFC_LOG_DATA: ");
            for(; i<29; i++)
            {
                PS_PRINT_ERR("%d\n", p_pucNfcLog[i]);
            }
        }
#endif
        retry = 3;
        while (!wifi_choose_bfgn_channel_send_log2sdt(g_pucNfcLog, cp_len))
        {
            retry--;
            if (0 == retry)
            {
                PS_PRINT_ERR("send log to bfgn log channels error\n");
                break;
            }
        }

        index += cp_len;
    }

    kfree(g_pucNfcLog);
    g_pucNfcLog = NULL;

    oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
    PS_PRINT_INFO("save nfc low-power log sucess\n");
}

