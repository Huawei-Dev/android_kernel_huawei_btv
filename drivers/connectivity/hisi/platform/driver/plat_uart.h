#ifndef __PLAT_UART_H__
#define __PLAT_UART_H__
/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#include <linux/serial_core.h>
#include "plat_type.h"
/*****************************************************************************
  2 Define macro
*****************************************************************************/
typedef  enum {
    STATE_TTY_TX = 0,
    STATE_TTY_RX = 1,
    STATE_UART_TX = 2,
    STATE_UART_RX = 3,
}UART_STATE_INDEX;
/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/
struct ps_uart_state_s {
    unsigned int tty_tx_cnt;
    unsigned int tty_rx_cnt;
    unsigned int tty_stopped;
    unsigned int tty_hw_stopped;
    struct uart_icount uart_cnt;
};

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern int plat_uart_init(void);
extern int plat_uart_exit(void);
extern int open_tty_drv(void *pm_data);
extern int release_tty_drv(void *pm_data);
extern int ps_change_uart_baud_rate(long baud_rate, unsigned char enable_flowctl);
extern void ps_uart_tty_tx_add(unsigned int cnt);
extern void ps_uart_state_pre(struct tty_struct *tty);
extern void ps_uart_state_dump(struct tty_struct *tty);
extern unsigned int ps_uart_state_cur(unsigned int index);
#endif

