/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Voltaire, Inc.  All rights reserved.
 * Copyright (c) 2006, 2010 Intel Corporation.  All rights reserved.
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
 *
 */
#ifndef _IBMAD_SA_H
#define _IBMAD_SA_H

#include <infiniband/ibmad_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Chapter 15 Subnet Administration Defines */

/* SA version */
enum {
	IBMAD_SA_CLASS_VERSION		= 2,	/* IB spec version 1.1/1.2 */
};

/* SA methods */
enum {
	IBMAD_SA_METHOD_GET		= IBMAD_METHOD_GET,
	IBMAD_SA_METHOD_GET_RESP	= IBMAD_METHOD_GET_RESP,
	IBMAD_SA_METHOD_SET		= IBMAD_METHOD_SET,
	IBMAD_SA_METHOD_REPORT		= IBMAD_METHOD_REPORT,
	IBMAD_SA_METHOD_REPORT_RESP	= IBMAD_METHOD_REPORT_RESP,
	IBMAD_SA_METHOD_GET_TABLE	= 0x12,
	IBMAD_SA_METHOD_GET_TABLE_RESP	= 0x92,

	/* Optional */
	IBMAD_SA_METHOD_GET_TRACE_TABLE	= 0x13
	IBMAD_SA_METHOD_GET_MULTI	= 0x14,
	IBMAD_SA_METHOD_GET_MULTI_RESP	= 0x94,

	/* Required */
	IBMAD_SA_METHOD_DELETE		= 0x15,
	IBMAD_SA_METHOD_DELETE_RESP	= 0x95,
};

/* SA attributes */
enum {
	IBMAD_SA_ATTR_CLASS_PORT_INFO		= IBMAD_ATTR_CLASS_PORT_INFO,
	IBMAD_SA_ATTR_NOTICE			= IBMAD_ATTR_NOTICE,
	IBMAD_SA_ATTR_INFORM_INFO		= IBMAD_ATTR_INFORM_INFO,
	IBMAD_SA_ATTR_NODE_REC			= 0x0011,
	IBMAD_SA_ATTR_PORT_INFO_REC		= 0x0012,
	IBMAD_SA_ATTR_SLVL_REC			= 0x0013,
	IBMAD_SA_ATTR_SWITCH_INFO_REC		= 0x0014,
	IBMAD_SA_ATTR_LINEAR_FT_REC		= 0x0015,
	IBMAD_SA_ATTR_RANDOM_FT_REC		= 0x0016,
	IBMAD_SA_ATTR_MCAST_FT_REC		= 0x0017,
	IBMAD_SA_ATTR_SM_INFO_REC		= 0x0018,
	IBMAD_SA_ATTR_LINK_SPEED_WIDTH_TBL_REC	= 0x0019,
	IBMAD_SA_ATTR_INFORM_INFO_REC		= 0x00F3,
	IBMAD_SA_ATTR_LINK_REC			= 0x0020,
	IBMAD_SA_ATTR_GUID_INFO_REC		= 0x0030,
	IBMAD_SA_ATTR_SERVICE_REC		= 0x0031,
	IBMAD_SA_ATTR_PKEY_TABLE_REC		= 0x0033,
	IBMAD_SA_ATTR_PATH_REC			= 0x0035,
	IBMAD_SA_ATTR_VL_ARB_REC		= 0x0036,
	IBMAD_SA_ATTR_MCMEMBER_REC		= 0x0038,
	IBMAD_SA_ATTR_TRACE_REC			= 0x0039,
	IBMAD_SA_ATTR_MULTI_PATH_REC		= 0x003A,
	IBMAD_SA_ATTR_SERVICE_ASSOC_REC		= 0x003B
};

enum {
	IBMAD_LEN_SA_DATA		= 200
};

/*
 *  sm_key is not aligned on an 8-byte boundary, so is defined as a byte array
 */
struct ibmad_sa_packet {
	struct ibumad_hdr	mad_hdr;
	struct ibumad_rmpp_hdr	rmpp_hdr;
	uint8_t			sm_key[8]; /* network-byte order */
	be16_t			attr_offset;
	be16_t			reserved;
	be64_t			comp_mask;
	uint8_t 		data[IBMAD_LEN_SA_DATA]; /* network-byte order */
};

struct ibmad_path_record {
	be64_t service_id;
	ib_gid_t dgid;
	ib_gid_t sgid;
	be16_t dlid;
	be16_t slid;
	be32_t hop_flow_raw;
	uint8_t tclass;
	uint8_t num_path;
	be16_t pkey;
	be16_t qos_class_sl;
	uint8_t mtu;
	uint8_t rate;
	uint8_t pkt_life;
	uint8_t preference;
	uint8_t resv2[6];
};

#ifdef __cplusplus
}
#endif

#endif				/* _IBMAD_SA_H */
