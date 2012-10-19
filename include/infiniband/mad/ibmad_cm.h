/*
 * Copyright (c) 2010 Intel Corporation.  All rights reserved.
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

#ifndef _IBMAD_CM_H
#define _IBMAD_CM_H

#include <infiniband/ibmad_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CM management methods */
enum {
	IBMAD_CM_METHOD_GET		= IBMAD_METHOD_GET,
	IBMAD_CM_METHOD_SET		= IBMAD_METHOD_SET,
	IBMAD_CM_METHOD_GET_RESP	= IBMAD_METHOD_GET_RESP,
	IBMAD_CM_METHOD_SEND		= IBMAD_METHOD_SEND
};

/* Communication management attributes */
enum {
	IBMAD_CM_ATTR_CLASS_PORT_INFO	= IBMAD_ATTR_CLASS_PORT_INFO,
	IBMAD_CM_ATTR_REQ		= 0x0010, /* ConnectRequest */
	IBMAD_CM_ATTR_MRA		= 0x0011, /* MsgRcptAck */
	IBMAD_CM_ATTR_REJ		= 0x0012, /* ConnectReject */
	IBMAD_CM_ATTR_REP		= 0x0013, /* ConnectReply */
	IBMAD_CM_ATTR_RTU		= 0x0014, /* ReadyToUse */
	IBMAD_CM_ATTR_DREQ		= 0x0015, /* DisconnectRequest */
	IBMAD_CM_ATTR_DREP		= 0x0016, /* DisconnectReply */
	IBMAD_CM_ATTR_SIDR_REQ		= 0x0017, /* ServiceIDResReq */
	IBMAD_CM_ATTR_SIDR_REP		= 0x0018, /* ServiceIDResReqResp */
	IBMAD_CM_ATTR_LAP		= 0x0019, /* LoadAlternatePath */
	IBMAD_CM_ATTR_APR		= 0x001A, /* AlternatePathResponse */
};

/* for now cm packets are just mad packets */
typedef ibmad_packet ibmad_cm;

#ifdef __cplusplus
}
#endif

#endif				/* _IBMAD_CM_H */
