/*
 * Copyright (c) 2011 Lawrence Livermore National Security.  All rights reserved.
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
#ifndef _IBMAD_TYPES_H
#define _IBMAD_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Chapter 13 "Base" Defines */

enum IBMAD_STATUS {
	IBMAD_STATUS_SUCCESS  = 0x0000,
	IBMAD_STATUS_BUSY     = 0x0001,
	IBMAD_STATUS_REDIRECT = 0x0002,

	/* Invalid fields, bits 2-4 */
	IBMAD_STATUS_BAD_VERSION          = (1 << 2),
	IBMAD_STATUS_METHOD_NOT_SUPPORTED = (2 << 2),
	IBMAD_STATUS_ATTR_NOT_SUPPORTED   = (3 << 2),
	IBMAD_STATUS_INVALID_ATTR_VALUE   = (7 << 2),

	IBMAD_STATUS_CLASS_MASK = 0xFF00
};

/* Management methods */
enum IBMAD_BASE_METHOD {
	IBMAD_METHOD_GET		= 0x01,
	IBMAD_METHOD_SET		= 0x02,
	IBMAD_METHOD_GET_RESP		= 0x81,
	IBMAD_METHOD_SEND		= 0x03,
	IBMAD_METHOD_TRAP		= 0x05,
	IBMAD_METHOD_REPORT		= 0x06,
	IBMAD_METHOD_REPORT_RESP	= 0x86,
	IBMAD_METHOD_TRAP_REPRESS	= 0x07,
	IBMAD_METHOD_RESP_MASK		= 0x80
};

/* Attributes common to multiple classes */
enum IBMAD_BASE_ATTR {
	IBMAD_ATTR_CLASS_PORT_INFO	= 0x0001,
	IBMAD_ATTR_NOTICE		= 0x0002,
	IBMAD_ATTR_INFORM_INFO		= 0x0003
};

/* RMPP information */
enum {
	IBMAD_RMPP_VERSION		= 1
};

enum {
	IBMAD_RMPP_TYPE_DATA		= 1,
	IBMAD_RMPP_TYPE_ACK		= 2,
	IBMAD_RMPP_TYPE_STOP		= 3,
	IBMAD_RMPP_TYPE_ABORT		= 4,

	IBMAD_RMPP_FLAG_MASK		= 0x07,
	IBMAD_RMPP_FLAG_ACTIVE		= 1,
	IBMAD_RMPP_FLAG_FIRST		= (1 << 1),
	IBMAD_RMPP_FLAG_LAST		= (1 << 2),

	IBMAD_RMPP_RESP_TIME_SHIFT	= 3,
	IBMAD_RMPP_NO_RESP_TIME		= 0x1F,

	IBMAD_RMPP_STATUS_SUCCESS	= 0,
	IBMAD_RMPP_STATUS_RESX		= 1,
	IBMAD_RMPP_STATUS_ABORT_MIN	= 118,
	IBMAD_RMPP_STATUS_T2L		= 118,
	IBMAD_RMPP_STATUS_BAD_LEN	= 119,
	IBMAD_RMPP_STATUS_BAD_SEG	= 120,
	IBMAD_RMPP_STATUS_BADT		= 121,
	IBMAD_RMPP_STATUS_W2S		= 122,
	IBMAD_RMPP_STATUS_S2B		= 123,
	IBMAD_RMPP_STATUS_BAD_STATUS	= 124,
	IBMAD_RMPP_STATUS_UNV		= 125,
	IBMAD_RMPP_STATUS_TMR		= 126,
	IBMAD_RMPP_STATUS_UNSPEC	= 127,
	IBMAD_RMPP_STATUS_ABORT_MAX	= 127
};


/* ClassPortInfo */
struct ibmad_class_port_info_hdr {
	uint8_t BaseVersion;
	uint8_t ClassVersion;
	be16_t CapabilityMask;
	be32_t CapabilityMask2_RespTimeValue; /* 27: CM2
						  5: RespTimeValue */
	ibv_gid_t RedirectGID;
	be32_t RedirectTC_SL_FL; /*  8: TC
				     4: SL
				    20: FL */
	be16_t RedirectLID;
	be16_t RedirectP_Key;
	be32_t res_RedirectQP; /*  8: reserved
				  24: RedirectQP */
	be32_t RedirectQ_Key;
	ibv_gid_t TrapGID;
	be32_t TrapTC_SL_FL; /*  8: TC
				 4: SL
				20: FL */
	be16_t TrapLID;
	be16_t TrapP_KEY;
	be32_t TrapHL_QP; /*  8: HL
			     24: QP */
	be32_t TrapQ_Key;
};

/* Notice */
struct ibmad_notice_hdr {
	be32_t IsGeneric_Type_ProducerType_VendorID; /*  1: IsGeneric
							 7: Type
							24: ProducerType OR VendorID */
	be16_t TrapNumber_DeviceID; /* TrapNumber OR DeviceID */
	be16_t IssuerLID;
	be16_t NoticeToggle_NoticeCount; /* 1: NoticeToggle
					   15: NoticeCount */
	uint8_t DataDetails[54]; /* see ibmad_notice_* structs */
	ibv_gid_t IssuerGID;
	uint8_t ClassTrapSpecificData[1];
};

#if 0 /* WTF */
struct ibmad_notice_details_259	// bkey violation
{
	be16_t lidaddr;
	uint8_t method;
	uint8_t reserved;
	be16_t attribute_id;
	be32_t attribute_modifier;
	be32_t qp;		// qp is low 24 bits
	be64_t bkey;
	ibv_gid_t gid;
};
#endif
struct ibmad_notice_details_cckey_0	// CC key violation
{
	be16_t SourceLID;     // source LID from offending packet LRH
	uint8_t Method;      // method, from common MAD header
	uint8_t res1;
	be16_t AttributeID; // Attribute ID, from common MAD header
	be16_t res2;
	be32_t AttributeModifier; // Attribute Modif, from common MAD header
	be32_t res_QP; /*  8: reserved
			  24: QP */
	be64_t CC_Key;   // CC key of the offending packet
	ibv_gid_t SourceGID; // GID from GRH of the offending packet
	uint8_t Padding[14]; // Padding - ignored on read
};

/* InformInfo */
struct ibmad_inform_info_hdr {
	ibv_gid_t GID;
	be16_t LIDRangeBegin;
	be16_t LIDRangeEnd;
	be16_t reserved;
	uint8_t IsGeneric;
	uint8_t Subscribe;
	be16_t Type;
	be16_t TrapNumber_DeviceID; // TrapNumber OR DeviceID
	be32_t QPN_res_RespTimeValue; /* 24: QPN
					  3: reserved
					  5: RespTimeValue */
	be32_t res_ProducerType_VendorID /* 8: reserved
					   24: ProducerType OR VendorID */
};

#ifdef __cplusplus
}
#endif

#endif				/* _IBMAD_TYPES_H */
