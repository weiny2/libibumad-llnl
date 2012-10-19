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

#ifndef _IBMAD_PERFMGT_H
#define _IBMAD_PERFMGT_H

#include <infiniband/ibmad_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PerfMgt management methods */
enum {
	IBMAD_PERFMGT_METHOD_GET	= IBMAD_METHOD_GET,
	IBMAD_PERFMGT_METHOD_GET_RESP	= IBMAD_METHOD_GET_RESP,
	IBMAD_PERFMGT_METHOD_SET	= IBMAD_METHOD_SET,
};

/* Performance management attributes */
enum {
	IBMAD_PERFMGT_PORT_SAMPLES_CONTROL		= 0x0010,
	IBMAD_PERFMGT_PORT_SAMPLES_RESULT		= 0x0011,
	IBMAD_PERFMGT_PORT_COUNTERS			= 0x0012,

	/* Optional Attributes */
	IBMAD_PERFMGT_PORT_RCV_ERROR_DETAILS		= 0x0015,
	IBMAD_PERFMGT_PORT_XMIT_DISCARD_DETAILS		= 0x0016,
	IBMAD_PERFMGT_PORT_OP_RCV_COUNTERS		= 0x0017,
	IBMAD_PERFMGT_PORT_FLOW_CTL_COUNTERS		= 0x0018,
	IBMAD_PERFMGT_PORT_VL_OP_PACKETS		= 0x0019,
	IBMAD_PERFMGT_PORT_VL_OP_DATA			= 0x001A,
	IBMAD_PERFMGT_PORT_VL_XMIT_FLOW_CTL_UPDATE_ERRS	= 0x001B,
	IBMAD_PERFMGT_PORT_VL_XMIT_WAIT_COUNTERS	= 0x001C,
	IBMAD_PERFMGT_PORT_COUNTERS_EXT			= 0x001D,
	IBMAD_PERFMGT_PORT_SAMPLES_RESULT_EXTENDED	= 0x001E,
	IBMAD_PERFMGT_SW_PORT_VL_CONGESTION		= 0x0030,

	/* A10.5.3 */
	IBMAD_PERFMGT_PORT_RCV_CON_CTL			= 0x0031,
	IBMAD_PERFMGT_PORT_SL_RCV_FECN			= 0x0032,
	IBMAD_PERFMGT_PORT_SL_RCV_BECN			= 0x0033,
	IBMAD_PERFMGT_PORT_XMIT_CON_CTL			= 0x0034,
	IBMAD_PERFMGT_PORT_VL_XMIT_TIME_CONG		= 0x0035,

	/* A13.6.4 */
	IBMAD_PERFMGT_PORT_XMIT_DATA_SL			= 0x0036,
	IBMAD_PERFMGT_PORT_RCV_DATA_SL			= 0x0037
};

enum {
	IBMAD_LEN_PERFMGT_DATA		= 192
};

struct ibmad_pm_packet {
	struct ibumad_hdr	mad_hdr;
	uint8_t			reserved[40];
	uint8_t 		data[IBMAD_LEN_PERFMGT_DATA]; /* network-byte order */
};

#ifdef __cplusplus
}
#endif

#endif				/* _IBMAD_PERFMGT_H */
