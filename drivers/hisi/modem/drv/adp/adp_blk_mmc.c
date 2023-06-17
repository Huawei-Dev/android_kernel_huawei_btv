
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/statfs.h>
#include <adrv.h>
/*lint --e{585}*/
/*****************************************************************************
* ????  : bsp_blk_size
* ????  : ??????????????????
* ????  : part_name ????????
* ????  : size  ??????????????????size
* ????  : ????0??????????????0????
*****************************************************************************/
int bsp_blk_size(const char *part_name, u32 *size)
{
	mm_segment_t fs;
	long ret = 0;
	unsigned int fd = 0;
	loff_t isize = 0;

	char dev_name[128] = "";

	/* check param */
	if(!part_name || !size)
	{
		printk(KERN_ERR "%s:invalid param, part_name %s data_buf %p!\n",
				__func__, part_name, size);
		return -1;
	}
	ret = (long)flash_find_ptn(part_name, dev_name);
	if (ret < 0) {
		printk(KERN_ERR "%s not found from partition table!\n", part_name);
		return -1;
	}

	fs = get_fs();
	set_fs(KERNEL_DS);

	ret = sys_open(dev_name, O_RDONLY, 0600);
	if (ret < 0) {
		printk(KERN_ERR"fail to open file %s, ret %ld!\n", dev_name, ret);
		goto open_err;
	}

	fd = (unsigned long)ret;

	ret = sys_ioctl(fd, BLKGETSIZE64, (unsigned long)&isize);
	if (ret < 0) {
		printk(KERN_ERR "get %s size is failed, ret %ld!\n",
				dev_name, ret);
		goto ioctl_err;
	}
    ret = 0 ;
	*size = (u32)isize;

ioctl_err:
	if(sys_close(fd)) {
		ret = -1;
        printk(KERN_ERR "%s close failed??\n", dev_name);
	}

open_err:
	set_fs(fs);

	return ret;
}

/*****************************************************************************
* ????  : bsp_blk_read
* ????  : ????????????????????????
* ????  : part_name ????????
* ????  : part_offset ????????
* ????  : data_len  ??????????
* ????  : data_buf  ??????????????
* ????  : ????0??????????????0????
*****************************************************************************/
int bsp_blk_read(const char *part_name, loff_t part_offset, void *data_buf, size_t data_len, unsigned int *skip_len)
{
	mm_segment_t fs;
	long ret = 0, len = 0;
	unsigned int fd = 0;
	loff_t size = 0;

	char dev_name[128] = "";

	/* check param */
	if(!part_name || !data_buf)
	{
		printk(KERN_ERR "%s:invalid param, part_name %s data_buf %p!\n",
				__func__, part_name, data_buf);
		return -1;
	}

	ret = flash_find_ptn(part_name, dev_name);
	if (ret < 0) {
		printk(KERN_ERR "%s not found from partition table!\n", part_name);
		return -1;
	}
    if(skip_len)
    {
        *skip_len = 0;
    }
	fs = get_fs();
	set_fs(KERNEL_DS);

	ret = sys_open(dev_name, O_RDONLY, 0600);
	if (ret < 0) {
		printk(KERN_ERR"fail to open file %s, ret %ld!\n", dev_name, ret);
		goto open_err;
	}

	fd = (unsigned long)ret;

	ret = sys_ioctl(fd, BLKGETSIZE64, (unsigned long)&size);
	if (ret < 0) {
		printk(KERN_ERR "get %s size is failed, ret %ld!\n",
				dev_name, ret);
		goto ioctl_err;
	}

	if (part_offset > size || (part_offset + data_len > size)) {
		ret = -1;
		printk(KERN_ERR "%s invalid offset %lld data_len %zu size %lld!\n",
				dev_name, part_offset, data_len, size);
		goto ioctl_err;
	}

	ret = sys_lseek(fd, part_offset, SEEK_SET);
	if (ret < 0) {
		printk(KERN_ERR "%s lseek %lld failed, ret %ld!\n",
				dev_name, part_offset, ret);
		goto ioctl_err;
	}

	ret = 0;
	len = sys_read(fd, data_buf, data_len);
	if (len != data_len)
	{
		ret = -1;
		printk(KERN_ERR "%s read error, data_len %zu read_len %ld!\n",
				dev_name, data_len, len);
		goto ioctl_err;
	}

ioctl_err:
	if(sys_close(fd)) {
		ret = -1;
        printk(KERN_ERR "%s close failed??\n", dev_name);
	}

open_err:
	set_fs(fs);

	return ret;
}

/*****************************************************************************
* ????  : bsp_blk_write
* ????  : ????????????????????????
* ????  : part_name ????????
* ????  : part_offset ????????
* ????  : data_len  ??????????
* ????  : data_buf  ??????????????
* ????  : ????0??????????????0????
*****************************************************************************/
int bsp_blk_write(const char *part_name, loff_t part_offset, void *data_buf, size_t data_len)
{
	mm_segment_t fs;
	long ret = 0, len = 0;
	unsigned int fd = 0;
	loff_t size = 0;

	char dev_name[128] = "";

	/* check param */
	if(!part_name || !data_buf)
	{
		printk(KERN_ERR "%s:invalid param, part_name %s data_buf %p!\n",
				__func__, part_name, data_buf);
		return -1;
	}

	ret = flash_find_ptn(part_name, dev_name);
	if (ret < 0) {
		printk(KERN_ERR "%s not found from partition table!\n", part_name);
		return -1;
	}

	fs = get_fs();
	set_fs(KERNEL_DS);

	ret = sys_open(dev_name, O_WRONLY | O_DSYNC, 0600);
	if (ret < 0) {
		printk(KERN_ERR"fail to open file %s, ret %ld!\n", dev_name, ret);
		goto open_err;
	}

	fd = (unsigned long)ret;

	ret = sys_ioctl(fd, BLKGETSIZE64, (unsigned long)&size);
	if (ret < 0) {
		printk(KERN_ERR "get %s size is failed, ret %ld!\n",
				dev_name, ret);
		goto ioctl_err;
	}

	if (part_offset > size || (part_offset + data_len > size)) {
		ret = -1;
		printk(KERN_ERR "%s invalid offset %lld data_len %zu size %lld!\n",
				dev_name, part_offset, data_len, size);
		goto ioctl_err;
	}

	ret = sys_lseek(fd, part_offset, SEEK_SET);
	if (ret < 0) {
		printk(KERN_ERR "%s lseek %lld failed, ret %ld!\n",
				dev_name, part_offset, ret);
		goto ioctl_err;
	}

	len = sys_write(fd, data_buf, data_len);
	if (len != data_len)
	{
		ret = -1;
		printk(KERN_ERR "%s read error, data_len %zu read_len %ld!\n",
				dev_name, data_len, len);
		goto ioctl_err;
	}

	ret = sys_fsync(fd);
	if (ret < 0) {
		printk(KERN_ERR "%s fsync failed, ret %ld!\n",
				dev_name, ret);
		goto ioctl_err;
	}
    ret = 0;
ioctl_err:
	if(sys_close(fd)) {
		ret = -1;
        printk(KERN_ERR "%s close failed??\n", dev_name);
	}

open_err:
	set_fs(fs);

	return ret;

}

int bsp_blk_isbad(const char *partition_name, loff_t partition_offset)
{
	return 0;
}

int bsp_blk_erase(const char *partition_name, loff_t partition_offset)
{
	return 0;
}
EXPORT_SYMBOL(bsp_blk_size);
EXPORT_SYMBOL(bsp_blk_read);
EXPORT_SYMBOL(bsp_blk_write);
EXPORT_SYMBOL(bsp_blk_isbad);
EXPORT_SYMBOL(bsp_blk_erase);

