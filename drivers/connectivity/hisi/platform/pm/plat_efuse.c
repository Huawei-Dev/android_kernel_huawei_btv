#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "plat_efuse.h"

unsigned char g_uc_hi110x_ec_version = V100;

void read_efuse_ec_version(void)
{
    int ret = 0;
    unsigned char buff[EFUSE_REG_WIDTH] = {0x00};
    unsigned char uc_ec_version = V100;
    unsigned int i = 0;

    ret = number_type_cmd_send(RMEM_CMD_KEYWORD, GET_EFUSE_EC_VERSION);
    if (0 > ret)
    {
        PS_PRINT_WARNING("send cmd %s:%s fail,ret = %d\n", RMEM_CMD_KEYWORD, GET_EFUSE_EC_VERSION, ret);
        return;
    }

    ret = read_msg((unsigned char*)buff, sizeof(buff));
    if (0 > ret)
    {
        PS_PRINT_WARNING("read efuse ec version fail, read_len = %d, return = %d\n", (int)sizeof(buff), ret);
        return;
    }

    for (i = 0; i < sizeof(buff); i++)
    {
        PS_PRINT_DBG("ec version[%d]=0x%x\n", i , buff[i]);
    }

    uc_ec_version  = buff[1];
    uc_ec_version &= ((unsigned char)0x03);

    if (V100 == uc_ec_version)
    {
        PS_PRINT_INFO("hi110x read efuse V100[0x%x]\n", uc_ec_version);
        g_uc_hi110x_ec_version = V100;
    }
    else
    {
        PS_PRINT_INFO("hi110x read efuse V120[0x%x]\n", uc_ec_version);
        g_uc_hi110x_ec_version = V120;
    }

    return;
}

unsigned char get_ec_version(void)
{
    return g_uc_hi110x_ec_version;
}

static void mask_bits(unsigned int value[], int start_bits, int end_bits)
{
    int index = 0;
    int     i = 0;
    int     j = 0;

    if (NULL == value)
    {
        return;
    }

    for (index = start_bits; index <= end_bits; index++)
    {
        i = index / EFUSE_VALUE_WIDTH;
        j = index % EFUSE_VALUE_WIDTH;
        value[i] &= ~(1 << j);
    }
}

static int check_efuse_file_exist(void)
{
    struct file* fp = NULL;

    fp = filp_open(EFUSE_FILE_PATH, O_RDONLY, 0);
    if (IS_ERR(fp))
    {
        return -EFAIL;
    }

    filp_close(fp, NULL);

    return SUCC;
}

static int get_efuse_from_device(unsigned int* buff, int len)
{
    int ret = 0;

    if (NULL == buff)
    {
        PS_PRINT_ERR("efuse buff is NULL\n");
        return -EFAIL;
    }

    ret = number_type_cmd_send(RMEM_CMD_KEYWORD, GET_EFUSE_CMD);
    if (0 > ret)
    {
        PS_PRINT_WARNING("send cmd %s:%s fail,ret = %d\n", RMEM_CMD_KEYWORD, GET_EFUSE_CMD, ret);
        return -EFAIL;
    }

    ret = read_msg((unsigned char*)buff, len);
    if (0 > ret)
    {
        PS_PRINT_WARNING("read efuse fail, read_len = %d, return = %d\n", len, ret);
        return -EFAIL;
    }

    return SUCC;

}

static int store_efuse_into_file(unsigned int* buff)
{
    struct file *fp  = NULL;
    loff_t       pos = 0;
    int      index = 0;
    ssize_t      ret = 0;
    mm_segment_t fs;

    if (NULL == buff)
    {
        PS_PRINT_ERR("efuse buff is NULL\n");
        return -EFAIL;
    }

    mask_bits(buff, DIEID_BIT_4,  DIEID_BIT_21);
    mask_bits(buff, DIEID_BIT_45, DIEID_BIT_45);
    mask_bits(buff, DIEID_BIT_53, DIEID_BIT_53);
    mask_bits(buff, DIEID_BIT_79, DIEID_BIT_95);

    memset(&fs, 0x00, sizeof(fs));

    fp = filp_open(EFUSE_FILE_PATH, O_CREAT|O_RDWR, 0644);
    if (IS_ERR(fp))
    {
        PS_PRINT_ERR("open %s fail, errno = %ld\n", EFUSE_FILE_PATH, PTR_ERR(fp));
        return -EFAIL;
    }

    fs = get_fs();
    set_fs(KERNEL_DS);
    pos = 0;
    for (index = 0; index < EFUSE_REG_NUM; index++)
    {
        ret = vfs_write(fp, (unsigned char *)(&buff[index]), sizeof(unsigned short), &pos);
        if (ret < 0)
        {
            PS_PRINT_ERR("write %s fail, ret = %d\n", EFUSE_FILE_PATH, (int)ret);
            filp_close(fp, NULL);
            set_fs(fs);
            return -EFAIL;
        }
    }

    filp_close(fp, NULL);
    set_fs(fs);

    return SUCC;
}

void store_efuse_info(void)
{
    int  ret = 0;
    unsigned int buff[EFUSE_REG_NUM] = {0x00};
    static int retry_count = 0;

    if (retry_count >= EFUSE_RETRY)
    {
        return;
    }
    retry_count++;

    read_efuse_ec_version();

    ret = check_efuse_file_exist();
    if (ret == SUCC)
    {
        retry_count = EFUSE_RETRY;
        return;
    }

    ret = get_efuse_from_device(buff, sizeof(buff));
    if (SUCC != ret)
    {
        PS_PRINT_ERR("get efuse from device fail\n");
        return;
    }

    ret = store_efuse_into_file(buff);
    if (SUCC != ret)
    {
        PS_PRINT_ERR("store efuse into %s fail\n", EFUSE_FILE_PATH);
        return;
    }

    retry_count = EFUSE_RETRY;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

