/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_sci_uart.h"
#include "r_uart_api.h"
#include "r_sci_i2c.h"
#include "r_i2c_api.h"
#include "r_elc.h"
#include "r_elc_api.h"
#include "r_cgc.h"
#include "r_cgc_api.h"
#include "r_ioport.h"
#include "r_ioport_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer0;
#ifdef NULL
#define TIMER_ON_GPT_CALLBACK_USED_g_timer0 (0)
#else
#define TIMER_ON_GPT_CALLBACK_USED_g_timer0 (1)
#endif
#if TIMER_ON_GPT_CALLBACK_USED_g_timer0
void NULL(timer_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t g_uart3;
#ifdef NULL
#else
extern void NULL(uint32_t channel, uint32_t level);
#endif
#ifdef UartCallback
#define UART_ON_SCI_UART_CALLBACK_USED_g_uart3 (0)
#else
#define UART_ON_SCI_UART_CALLBACK_USED_g_uart3 (1)
#endif
#if UART_ON_SCI_UART_CALLBACK_USED_g_uart3
void UartCallback(uart_callback_args_t * p_args);
#endif
extern const i2c_cfg_t g_i2c0_cfg;
/** I2C on SCI Instance. */
extern const i2c_master_instance_t g_i2c0;
#ifdef NULL
#define I2C_ON_SCI_CALLBACK_USED_g_i2c0 (0)
#else
#define I2C_ON_SCI_CALLBACK_USED_g_i2c0 (1)
#endif
#if I2C_ON_SCI_CALLBACK_USED_g_i2c0
void NULL(i2c_callback_args_t * p_args);
#endif
/** ELC Instance */
extern const elc_instance_t g_elc;
/** CGC Instance */
extern const cgc_instance_t g_cgc;
/** IOPORT Instance */
extern const ioport_instance_t g_ioport;
void hal_entry(void);
void g_hal_init(void);
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* HAL_DATA_H_ */
