/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2021 A. Karas, SomLabs
 * Copyright (C) 2015-2016 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the SoMlabs VisionSOM 6UL/6ULL board.
 */
#ifndef __STARSOM_6ULL_H
#define __STARSOM_6ULL_H

#include <asm/arch/imx-regs.h>
#include <linux/sizes.h>
#include "mx6_common.h"
#include <asm/mach-imx/gpio.h>
#include "imx_env.h"

/* SPL options */
#include "imx6_spl.h"

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

/* for version with fastboot we set bootdelay to 0 */
#ifdef CONFIG_FSL_FASTBOOT
#define CONFIG_MFG_ENV_SETTINGS \
	CONFIG_MFG_ENV_SETTINGS_DEFAULT \
	"initrd_addr=0x86800000\0" \
	"initrd_high=0xffffffff\0" \
	"emmc_dev=1\0"\
	"emmc_ack=1\0"\
	"sd_dev=1\0"
#else
#define CONFIG_MFG_ENV_SETTINGS
#endif

#define CONFIG_EXTRA_ENV_SETTINGS \
	CONFIG_MFG_ENV_SETTINGS \
	"console=ttymxc3\0" \
	"initrd_addr=0x86800000\0" \
	"fdt_addr=0x83000000\0" \
	"script=boot.scr\0" \
	"image=zImage\0" \
	"splashimage=0x80000000\0" \
	"splashfile=splash.bmp\0" \
	"mmcdev=1\0" \
	"mmcpart=1\0" \
	"mmcroot=/dev/mmcblk1p2 rootwait rw\0" \
	"setrootmmc=setenv rootspec root=${mmcroot}\0" \
	"loadbootscript=load mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
	"loadimage=load mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image};\0" \
	"loadfdt=load mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file};\0" \
	"extrabootargs=earlyprintk\0" \
	"setbootargs=setenv bootargs console=${console},${baudrate} ${extrabootargs} " \
		"${bootarg_cmasize} ${rootspec}\0" \
	"execbootscript=echo Running bootscript...; source\0" \
	"fdt_file=\0" \

#define CONFIG_BOOTCOMMAND \
	"run setrootmmc;" \
	"run loadfdt;" \
	"if run loadbootscript; then " \
		"run bootscript; " \
	"else " \
		"if run loadimage; then " \
			"run setbootargs; " \
			"bootz ${loadaddr} - ${fdt_addr}; " \
		"fi; " \
	"fi"

/* Miscellaneous configurable options */

#define CONFIG_SYS_HZ			1000

#define CONFIG_SERIAL_TAG

/* Physical Memory Map */
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

//#define CONFIG_ENV_SIZE			SZ_8K

/* USB Configs */
#ifdef CONFIG_CMD_USB
#define CONFIG_MXC_USB_PORTSC  (PORT_PTS_UTMI | PORT_PTS_PTW)
#endif

#ifndef CONFIG_SPL_BUILD
#ifdef CONFIG_DM_VIDEO
#define CONFIG_VIDEO_MXS
#define CONFIG_VIDEO_LOGO
#define CONFIG_SPLASH_SOURCE
#define CONFIG_BMP_16BPP
#define CONFIG_BMP_24BPP
#define CONFIG_BMP_32BPP
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_VIDEO_BMP_GZIP
#define CONFIG_SYS_VIDEO_LOGO_MAX_SIZE  (2 << 20)
#define CONFIG_HIDE_LOGO_VERSION
#endif

#endif

#endif /* __STARSOM_6ULL_H */