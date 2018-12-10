
#ifndef __ds18b20_h__
#define __ds18b20_h__

#include "gpio.h"
#include "ds18b20.h"
#include "crc1w.h"
#include "timer.h"
#include "math.h"
#include <stdint.h>

#define Tslot		60	// minimum
#define Trec		1	// minimum
#define Tlow0		60	// minimum
#define Tlow1		1	// minimum
#define Trdv		15	// maximum
#define Trsth		480	// minimum
#define Trstl		480	// minimum
#define Tpdh		15	// minimum
#define Tpdl		60	// minimum
#define Tread		1	// minimum
#define Trstwait	65	// typical
#define Twr		10000	// maximum

/* mask and size values */
#define DS_RES_2	0x1f
#define DS_RES_4	0x3f
#define DS_RES_8	0x5f
#define DS_RES_16	0x7f
#define SCRATCHPAD_SIZE	9
#define MAX_GPIO	28

/* temperature range in multiples of 1/16C so that error codes can be detected */
#define TEMP_MIN	-880	// -55C
#define TEMP_MAX	2000	// 125C

/* error codes */
#define EBADR		53	/* invalid port or pin */

/* these error values are returned by read_temperature() */
/* so they need to be outside the range 16*[-55:125] */
#define ENOTPRESENT	10404	/* DS18B20 device is not connected */
#define ENAVAIL		10119	/* temperature reading not available */
#define EBADCRC		10120	/* CRC error */


typedef uint8_t u_int8_t;

typedef struct ds18b20
{
    uint8_t    present;

    uint8_t   pin;

    uint8_t    tempint;
    uint8_t    tempfrac;
    uint8_t    temphigh;
    uint8_t    templow;
    uint8_t    configvalid;
    uint8_t   resolution;

    uint8_t   scratchpad[SCRATCHPAD_SIZE];
} ds18b20_t;

/* use lookup table for Tconv */
const int Tconv[4] = {93750, 187500, 375000, 750000};

uint8_t ds18b20_init(ds18b20_t*);
uint16_t ds18b20_read_temperature(ds18b20_t*);
uint8_t _read_byte(ds18b20_t *p);
uint8_t _write_byte(ds18b20_t *p, uint8_t data);
uint8_t _reset(ds18b20_t *p);

#endif