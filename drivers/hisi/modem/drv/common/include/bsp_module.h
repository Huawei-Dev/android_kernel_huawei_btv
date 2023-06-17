#ifndef __BSP_MODULE_H
#define __BSP_MODULE_H

#if defined(__OS_RTOSCK__)

#include <sre_buildef.h>

#ifndef CONFIG_MODULE_MAX_NUM
#define CONFIG_MODULE_MAX_NUM      200
#endif

typedef enum _module_level
{
	mod_level_libc_init = 0,
	mod_level_dts,
	mod_level_HardBoot_end,

	mod_level_l2cache,
	mod_level_gic,
	mod_level_syslog_cb,
	mod_level_serial,
	mod_level_HardDrv_end,

	mod_level_dt_sysctrl,
	mod_level_share_mem,
	mod_level_timer,
	mod_level_fiq, 
	mod_level_dump_mem,
	mod_level_dmesg,
	mod_level_coresight,
	mod_level_pdlock,
	mod_level_dump,
	/* bsp_drivers */
	mod_level_console,
	mod_level_pm_om_dump,
	mod_level_clk,
	mod_level_systimer,
	mod_level_rsracc,
	mod_level_wakelock,
	mod_level_dpm,
	mod_level_watchpoint,
	mod_level_hardtimer,
	mod_level_vic,
	mod_level_ipc,
	mod_level_dump_phase2,
	mod_level_reset_node,
	mod_level_icc,
	mod_level_pdlock2,
	mod_level_vshell,
	mod_level_nvm,
	mod_level_amon,
	mod_level_rfile,
	mod_level_version_core,
	mod_level_hwspinlock,
	mod_level_hkadc,
	mod_level_version,
	mod_level_hwadp,
	mod_level_softtimer,
	mod_level_edma,
	mod_level_socp,
	mod_level_dual_modem,
	mod_level_dsp,
	mod_level_dsp_load,
	mod_level_bbp,
	mod_level_board_fpga,
	mod_level_gpio,
	mod_level_pmu,
	mod_level_regulator,
	mod_level_mipi,
	mod_level_cross_mipi,
	mod_level_pinctrl,
	mod_level_rffe,
	mod_level_watchdog,
	mod_level_i2c,
	mod_level_efuse,
	mod_level_tsensor,
	mod_level_led,
	mod_level_loadps_core,
	mod_level_cipher,
	mod_level_ipf,
	mod_level_psam,
	mod_level_mailbox,
	mod_level_xmailbox,
	mod_level_anten,
	mod_level_mem,
	mod_level_sci_cfg,
	mod_level_abb,
	mod_level_remote_clk,
	mod_level_onoff,
	mod_level_cpufreq,
	mod_level_pm,
	mod_level_reset,
	mod_level_modem_log,
	mod_level_pmomlog,
	mod_level_pm_wakeup_debug,
	mod_level_ddrtst_pm,
	mod_level_sysbus_core,
	mod_level_dsp_dvs,
	mod_level_dsp_dfs,
	mod_level_dload,
	mod_level_rsracc_late,

	mod_level_psroot,
	mod_level_dump_mem_debug,
	mod_level_regidle,
	mod_level_dump_init_tsk,
	mod_level_onoff_modem_ok,
	mod_level_App_end
} module_level;

typedef int (*modcall_t)(void);

struct module
{
	const char	name[32];
	modcall_t      init_fun;
	modcall_t      exit_fun;
	module_level  level;
	const char	init_func_name[64];
	const char	exit_func_name[64];
};

#define __init           __attribute__((section(".init.text")))
#define __exit          __attribute__((section(".exit.text")))
#define __used	    __attribute__((__used__))

#define module_init(name, initlevel, initcall,exitcall) \
	__used __attribute__((section(".mod.info"))) static struct module __mod_##initcall \
		= { name,  initcall, exitcall, initlevel,  #initcall ,#exitcall}

void bsp_module_init(module_level module_level_t);

struct module * bsp_module_get(const char *module_name);

int bsp_module_put(struct module *module);
#endif
#endif
