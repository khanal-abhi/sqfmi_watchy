/**
 * SPDX-License-Identifier: Apache-2.0
 */
#define DT_DRV_COMPAT gooddisplay_gdey0154d67

#include "display_gdey0154D67.h"

#include <zephyr/dt-bindings/display/panel.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/byteorder.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(display_gdey0154d67, CONFIG_DISPLAY_LOG_LEVEL);

/* Display data struct */
struct gdey0154d67_data
{
	struct gpio_dt_spec dc;
	struct gpio_dt_spec reset;
	struct gpio_dt_spec busy;
};

struct gdey0154d67_config
{
	struct gpio_dt_spec dc;
	struct gpio_dt_spec reset;
	struct gpio_dt_spec busy;
};

/* Initialization command data struct  */
struct gdey0154d67_default_init_regs
{
	uint8_t cmd;
	uint8_t len;
	uint8_t data[GDEY0154D67_NUM_DEFAULT_INIT_REGS];
};

// /*
//  * Default initialization commands. There are a lot of undocumented commands
//  * within the manufacturer sample code, that are essential for proper operation of
//  * the display controller
//  */
// static const struct gc9x01x_default_init_regs default_init_regs[] = {
// 	{
// 		.cmd = 0xEBU,
// 		.len = 1U,
// 		.data = {0x14U},
// 	},
// 	{
// 		.cmd = 0x84U,
// 		.len = 1U,
// 		.data = {0x40U},
// 	},
// 	{
// 		.cmd = 0x85U,
// 		.len = 1U,
// 		.data = {0xFFU},
// 	},
// 	{
// 		.cmd = 0x86U,
// 		.len = 1U,
// 		.data = {0xFFU},
// 	},
// 	{
// 		.cmd = 0x87U,
// 		.len = 1U,
// 		.data = {0xFFU},
// 	},
// 	{
// 		.cmd = 0x88U,
// 		.len = 1U,
// 		.data = {0x0AU},
// 	},
// 	{
// 		.cmd = 0x89U,
// 		.len = 1U,
// 		.data = {0x21U},
// 	},
// 	{
// 		.cmd = 0x8AU,
// 		.len = 1U,
// 		.data = {0x00U},
// 	},
// 	{
// 		.cmd = 0x8BU,
// 		.len = 1U,
// 		.data = {0x80U},
// 	},
// 	{
// 		.cmd = 0x8CU,
// 		.len = 1U,
// 		.data = {0x01U},
// 	},
// 	{
// 		.cmd = 0x8DU,
// 		.len = 1U,
// 		.data = {0x01U},
// 	},
// 	{
// 		.cmd = 0x8EU,
// 		.len = 1U,
// 		.data = {0xFFU},
// 	},
// 	{
// 		.cmd = 0x8FU,
// 		.len = 1U,
// 		.data = {0xFFU},
// 	},
// 	{
// 		.cmd = 0xB6U,
// 		.len = 2U,
// 		.data = {0x00U, 0x20U},
// 	},
// 	{
// 		.cmd = 0x90U,
// 		.len = 4U,
// 		.data = {0x08U, 0x08U, 0x08U, 0x08U},
// 	},
// 	{
// 		.cmd = 0xBDU,
// 		.len = 1U,
// 		.data = {0x06U},
// 	},
// 	{
// 		.cmd = 0xBCU,
// 		.len = 1U,
// 		.data = {0x00U},
// 	},
// 	{
// 		.cmd = 0xFFU,
// 		.len = 3U,
// 		.data = {0x60U, 0x01U, 0x04U},
// 	},
// 	{
// 		.cmd = 0xBEU,
// 		.len = 1U,
// 		.data = {0x11U},
// 	},
// 	{
// 		.cmd = 0xE1U,
// 		.len = 2U,
// 		.data = {0x10U, 0x0EU},
// 	},
// 	{
// 		.cmd = 0xDFU,
// 		.len = 3U,
// 		.data = {0x21U, 0x0CU, 0x02U},
// 	},
// 	{
// 		.cmd = 0xEDU,
// 		.len = 2U,
// 		.data = {0x1BU, 0x0BU},
// 	},
// 	{
// 		.cmd = 0xAEU,
// 		.len = 1U,
// 		.data = {0x77U},
// 	},
// 	{
// 		.cmd = 0xCDU,
// 		.len = 1U,
// 		.data = {0x63U},
// 	},
// 	{
// 		.cmd = 0x70U,
// 		.len = 9U,
// 		.data = {0x07U, 0x07U, 0x04U, 0x0EU, 0x0FU, 0x09U, 0x07U, 0x08U, 0x03U},
// 	},
// 	{
// 		.cmd = 0x62U,
// 		.len = 12U,
// 		.data = {0x18U, 0x0DU, 0x71U, 0xEDU, 0x70U, 0x70U, 0x18U, 0x0FU, 0x71U, 0xEFU,
// 				 0x70U, 0x70U},
// 	},
// 	{
// 		.cmd = 0x63U,
// 		.len = 12U,
// 		.data = {0x18U, 0x11U, 0x71U, 0xF1U, 0x70U, 0x70U, 0x18U, 0x13U, 0x71U, 0xF3U,
// 				 0x70U, 0x70U},
// 	},
// 	{
// 		.cmd = 0x64U,
// 		.len = 7U,
// 		.data = {0x28U, 0x29U, 0xF1U, 0x01U, 0xF1U, 0x00U, 0x07U},
// 	},
// 	{
// 		.cmd = 0x66U,
// 		.len = 10U,
// 		.data = {0x3CU, 0x00U, 0xCDU, 0x67U, 0x45U, 0x45U, 0x10U, 0x00U, 0x00U, 0x00U},
// 	},
// 	{
// 		.cmd = 0x67U,
// 		.len = 10U,
// 		.data = {0x00U, 0x3CU, 0x00U, 0x00U, 0x00U, 0x01U, 0x54U, 0x10U, 0x32U, 0x98U},
// 	},
// 	{
// 		.cmd = 0x74U,
// 		.len = 7U,
// 		.data = {0x10U, 0x85U, 0x80U, 0x00U, 0x00U, 0x4EU, 0x00U},
// 	},
// 	{
// 		.cmd = 0x98U,
// 		.len = 2U,
// 		.data = {0x3EU, 0x07U},
// 	},
// };

// static int gc9x01x_transmit(const struct device *dev, uint8_t cmd, const void *tx_data,
// 							size_t tx_len)
// {
// 	const struct gc9x01x_config *config = dev->config;

// 	return mipi_dbi_command_write(config->mipi_dev, &config->dbi_config,
// 								  cmd, tx_data, tx_len);
// }

// static int gc9x01x_regs_init(const struct device *dev)
// {
// 	const struct gc9x01x_config *config = dev->config;
// 	const struct gc9x01x_regs *regs = config->regs;
// 	int ret;

// 	if (!device_is_ready(config->mipi_dev))
// 	{
// 		return -ENODEV;
// 	}

// 	/* Enable inter-command mode */
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_INREGEN1, NULL, 0);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_INREGEN2, NULL, 0);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}

// 	/* Apply default init sequence */
// 	for (int i = 0; (i < ARRAY_SIZE(default_init_regs)) && (ret == 0); i++)
// 	{
// 		ret = gc9x01x_transmit(dev, default_init_regs[i].cmd, default_init_regs[i].data,
// 							   default_init_regs[i].len);
// 		if (ret < 0)
// 		{
// 			return ret;
// 		}
// 	}

// 	/* Apply generic configuration */
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_PWRCTRL2, regs->pwrctrl2, sizeof(regs->pwrctrl2));
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_PWRCTRL3, regs->pwrctrl3, sizeof(regs->pwrctrl3));
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_PWRCTRL4, regs->pwrctrl4, sizeof(regs->pwrctrl4));
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_GAMMA1, regs->gamma1, sizeof(regs->gamma1));
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_GAMMA2, regs->gamma2, sizeof(regs->gamma2));
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_GAMMA3, regs->gamma3, sizeof(regs->gamma3));
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_GAMMA4, regs->gamma4, sizeof(regs->gamma4));
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_FRAMERATE, regs->framerate,
// 						   sizeof(regs->framerate));
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}

// 	/* Enable Tearing line */
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_TEON, NULL, 0);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}

// 	return 0;
// }

// static int gc9x01x_exit_sleep(const struct device *dev)
// {
// 	int ret;

// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_SLPOUT, NULL, 0);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}

// 	/*
// 	 * Exit sleepmode and enable display. 30ms on top of the sleepout time to account for
// 	 * any manufacturing defects.
// 	 * This is to allow time for the supply voltages and clock circuits stabilize
// 	 */
// 	k_msleep(GC9X01X_SLEEP_IN_OUT_DURATION_MS + 30);

// 	return 0;
// }

// #ifdef CONFIG_PM_DEVICE
// static int gc9x01x_enter_sleep(const struct device *dev)
// {
// 	int ret;

// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_SLPIN, NULL, 0);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}

// 	/*
// 	 * Exit sleepmode and enable display. 30ms on top of the sleepout time to account for
// 	 * any manufacturing defects.
// 	 */
// 	k_msleep(GC9X01X_SLEEP_IN_OUT_DURATION_MS + 30);

// 	return 0;
// }
// #endif

// static int gc9x01x_hw_reset(const struct device *dev)
// {
// 	const struct gc9x01x_config *config = dev->config;
// 	int ret;

// 	ret = mipi_dbi_reset(config->mipi_dev, 100);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}
// 	k_msleep(10);

// 	return ret;
// }

static int gdey0154d67_display_blanking_off(const struct device *dev)
{
	LOG_DBG("Turning display blanking off");
	return 0;
}

static int gdey0154d67_display_blanking_on(const struct device *dev)
{
	LOG_DBG("Turning display blanking on");
	return 0;
}

static int gdey0154d67_set_pixel_format(const struct device *dev,
										const enum display_pixel_format pixel_format)
{
	return 0;
}

static int gdey0154d67_set_orientation(const struct device *dev,
									   const enum display_orientation orientation)
{
	return 0;
}

// static int gc9x01x_configure(const struct device *dev)
// {
// 	const struct gc9x01x_config *config = dev->config;
// 	int ret;

// 	/* Set all the required registers. */
// 	ret = gc9x01x_regs_init(dev);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}

// 	/* Pixel format */
// 	ret = gc9x01x_set_pixel_format(dev, config->pixel_format);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}

// 	/* Orientation */
// 	ret = gc9x01x_set_orientation(dev, config->orientation);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}

// 	/* Display inversion mode. */
// 	if (config->inversion)
// 	{
// 		ret = gc9x01x_transmit(dev, GC9X01X_CMD_INVON, NULL, 0);
// 		if (ret < 0)
// 		{
// 			return ret;
// 		}
// 	}

// 	return 0;
// }

static int gdey0154d67_init(const struct device *dev)
{
	LOG_INF("Display init called");
	return 0;
}

// static int gc9x01x_set_mem_area(const struct device *dev, const uint16_t x, const uint16_t y,
// 								const uint16_t w, const uint16_t h)
// {
// 	int ret;
// 	uint16_t spi_data[2];

// 	spi_data[0] = sys_cpu_to_be16(x);
// 	spi_data[1] = sys_cpu_to_be16(x + w - 1U);
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_COLSET, &spi_data[0], 4U);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}

// 	spi_data[0] = sys_cpu_to_be16(y);
// 	spi_data[1] = sys_cpu_to_be16(y + h - 1U);
// 	ret = gc9x01x_transmit(dev, GC9X01X_CMD_ROWSET, &spi_data[0], 4U);
// 	if (ret < 0)
// 	{
// 		return ret;
// 	}

// 	return 0;
// }

static int gdey0154d67_write(const struct device *dev, const uint16_t x, const uint16_t y,
							 const struct display_buffer_descriptor *desc, const void *buf)
{
	return 0;
}

static void gdey0154d67_get_capabilities(const struct device *dev,
										 struct display_capabilities *capabilities)
{
}

#ifdef CONFIG_PM_DEVICE
static int gdey0154d67_pm_action(const struct device *dev, enum pm_device_action action)
{
	int ret;

	switch (action)
	{
	case PM_DEVICE_ACTION_RESUME:
		ret = gdey0154d67_exit_sleep(dev);
		break;
	case PM_DEVICE_ACTION_SUSPEND:
		ret = gdey0154d67_enter_sleep(dev);
		break;
	default:
		ret = -ENOTSUP;
		break;
	}

	return ret;
}
#endif /* CONFIG_PM_DEVICE */

/* Device driver API*/
static DEVICE_API(display, gdey0154d67_api) = {
	.blanking_on = gdey0154d67_display_blanking_on,
	.blanking_off = gdey0154d67_display_blanking_off,
	.write = gdey0154d67_write,
	.get_capabilities = gdey0154d67_get_capabilities,
	.set_pixel_format = gdey0154d67_set_pixel_format,
	.set_orientation = gdey0154d67_set_orientation,
};

#define GDEY0154D67_INIT(inst)                                                               \
	static const struct gdey0154d67_config gdey0154d67_config_##inst = {                     \
		.dc = DT_INST_PROP(inst, dc_gpios),                                                  \
		.reset = DT_INST_PROP(inst, reset_gpios),                                            \
		.busy = DT_INST_PROP(inst, busy_gpios),                                              \
	};                                                                                       \
	static struct gdey0154d67_data gdey0154d67_data_##inst;                                  \
	DEVICE_DT_INST_DEFINE(inst, &gdey0154d67_init, NULL,                                     \
						  &gdey0154d67_data_##inst, &gdey0154d67_config_##inst, POST_KERNEL, \
						  CONFIG_DISPLAY_INIT_PRIORITY, &gdey0154d67_api);

DT_INST_FOREACH_STATUS_OKAY(GDEY0154D67_INIT)

#ifdef CONFIG_GDEY0154D67_SHELL
#include <zephyr/shell/shell.h>
static int watchy_display_cmd_handler(const struct shell *shell, size_t argc, char **argv)
{
	shell_print(shell, "Hello, Zephyr Shell!");
	return 0;
}

SHELL_CMD_REGISTER(watchy_display, NULL, "Prints 'Hello, Zephyr Shell!'", watchy_display_cmd_handler);
#endif