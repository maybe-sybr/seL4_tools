/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */

#include <elfloader_common.h>
#include <platform.h>


#define UART_WFIFO  0x0
#define UART_STATUS 0xC
#define UART_TX_FULL        BIT(21)
#define UART_REG(x) ((volatile uint32_t *)(UART_PPTR + (x)))

int plat_console_putchar(unsigned int c)
{
    /* Wait to be able to transmit. */
    while ((*UART_REG(UART_STATUS) & UART_TX_FULL));

    /* Transmit. */
    *UART_REG(UART_WFIFO) = c;

    return 0;
}
