/*
 * Copyright (c) 2011 Lawrence Livermore National Security. All rights reserved
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _IBMAD_BM_H
#define _IBMAD_BM_H

#include <infiniband/ibmad_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Baseboard management methods */
enum {
	IBMAD_BM_METHOD_GET		= IBMAD_METHOD_GET,
	IBMAD_BM_METHOD_SET		= IBMAD_METHOD_SET,
	IBMAD_BM_METHOD_GET_RESP	= IBMAD_METHOD_GET_RESP,
	IBMAD_BM_METHOD_SEND		= IBMAD_METHOD_SEND,
	IBMAD_BM_METHOD_TRAP		= IBMAD_METHOD_TRAP,
	IBMAD_BM_METHOD_TRAP_REPRESS	= IBMAD_METHOD_TRAP_REPRESS
	IBMAD_BM_METHOD_REPORT		= IBMAD_METHOD_REPORT,
	IBMAD_BM_METHOD_REPORT_RESP	= IBMAD_METHOD_REPORT_RESP,
};

/* Baseboard management attributes */
enum {
	IBMAD_BM_ATTR_CLASS_PORT_INFO		= IBMAD_ATTR_CLASS_PORT_INFO,
	IBMAD_BM_ATTR_NOTICE			= IBMAD_ATTR_NOTICE,
	IBMAD_BM_ATTR_BKEYINFO			= 0x0010,
	IBMAD_BM_ATTR_WRITE_VPD			= 0x0020,
	IBMAD_BM_ATTR_READ_VPD			= 0x0021,
	IBMAD_BM_ATTR_RESET_IBML		= 0x0022,
	IBMAD_BM_ATTR_SET_MODULE_PM_CONTROL	= 0x0023,
	IBMAD_BM_ATTR_GET_MODULE_PM_CONTROL	= 0x0024,
	IBMAD_BM_ATTR_SET_UNIT_PM_CONTROL	= 0x0025,
	IBMAD_BM_ATTR_GET_UNIT_PM_CONTROL	= 0x0026,
	IBMAD_BM_ATTR_SET_IOC_PM_CONTROL	= 0x0027,
	IBMAD_BM_ATTR_GET_IOC_PM_CONTROL	= 0x0028,
	IBMAD_BM_ATTR_SET_MODULE_STATE		= 0x0029,
	IBMAD_BM_ATTR_SET_MODULE_ATTENTION	= 0x002A,
	IBMAD_BM_ATTR_GET_MODULE_STATUS		= 0x002B,
	IBMAD_BM_ATTR_IB2IBML			= 0x002C,
	IBMAD_BM_ATTR_IB2CME			= 0x002D,
	IBMAD_BM_ATTR_IB2MME			= 0x002E,
	IBMAD_BM_ATTR_OEM			= 0x002F
};

enum {
	IBMAD_LEN_BM_DATA		= 192
};

/*
 *  b_key is not aligned on an 8-byte boundary, so is defined as a byte array
 */
struct ibmad_pm_packet {
	struct   ibumad_hdr	mad_hdr;
	uint8_t			b_key[8];
	uint8_t			reserved[32];
	uint8_t			data[IBMAD_LEN_BM_DATA]; /* network-byte order */
};

#ifdef __cplusplus
}
#endif

#endif				/* _IBMAD_BM_H */
