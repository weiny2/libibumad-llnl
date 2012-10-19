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
 */

#ifndef _IBMAD_SM_H
#define _IBMAD_SM_H

#include <infiniband/ibmad_types.h>

#ifdef __cplusplus
extern "C" {
#endif





/* Chapter 14 Subnet Management Defines */

enum {
	IBMAD_SMP_DIRECTION		= 0x8000,
};

/* Subnet management methods */
enum {
	IBMAD_SMP_METHOD_GET		= IBMAD_METHOD_GET,
	IBMAD_SMP_METHOD_SET		= IBMAD_METHOD_SET,
	IBMAD_SMP_METHOD_GET_RESP	= IBMAD_METHOD_GET_RESP,
	IBMAD_SMP_METHOD_TRAP		= IBMAD_METHOD_TRAP,
	IBMAD_SMP_METHOD_TRAP_REPRESS	= IBMAD_METHOD_TRAP_REPRESS
};

/* Subnet management attributes */
enum {
	IBMAD_SMP_ATTR_NOTICE			= IBMAD_ATTR_NOTICE,
	IBMAD_SMP_ATTR_NODE_DESC		= 0x0010,
	IBMAD_SMP_ATTR_NODE_INFO		= 0x0011,
	IBMAD_SMP_ATTR_SWITCH_INFO		= 0x0012,
	IBMAD_SMP_ATTR_GUID_INFO		= 0x0014,
	IBMAD_SMP_ATTR_PORT_INFO		= 0x0015,
	IBMAD_SMP_ATTR_PKEY_TABLE		= 0x0016,
	IBMAD_SMP_ATTR_SLVL_TABLE		= 0x0017,
	IBMAD_SMP_ATTR_VL_ARB_TABLE		= 0x0018,
	IBMAD_SMP_ATTR_LINEAR_FT		= 0x0019,
	IBMAD_SMP_ATTR_RANDOM_FT		= 0x001A,
	IBMAD_SMP_ATTR_MCAST_FT			= 0x001B,
	IBMAD_SMP_ATTR_LINK_SPEED_WIDTH_TBL	= 0x001C,
	IBMAD_SMP_ATTR_VENDORMADSTBL		= 0x001D, /* This is not in the spec??? */
	IBMAD_SMP_ATTR_SM_INFO			= 0x0020,
	IBMAD_SMP_ATTR_VENDOR_DIAG		= 0x0030,
	IBMAD_SMP_ATTR_LED_INFO			= 0x0031,
	IBMAD_SMP_ATTR_VENDOR_MASK		= 0xFF00
};

enum {
	IBMAD_LEN_SMP_DATA		= 64,
	IBMAD_SMP_MAX_HOPS		= 64
};

struct ibmad_smp {
	struct ibmad_hdr mad_hdr;
	be64_t           mkey;
	uint8_t          reserved[4];
	uint8_t          data[IBMAD_LEN_SMP_DATA];
	uint8_t          reserved[128];
};

struct ibmad_smp_dr {
	/* "Common MAD Header 1" (byte 0-3 of ibmad_hdr) */
	uint8_t	 base_version;
	uint8_t	 mgmt_class;
	uint8_t	 class_version;
	uint8_t	 method;

	be16_t   d_status; /* 1bit direction/15bit status */
	uint8_t  hop_ptr;
	uint8_t  hop_cnt;

	/* "Common MAD Header 2" (byte 8-23 of ibmad_hdr) */
	be64_t   tid;
	be16_t   attr_id;
	be16_t   resv;
	be32_t   attr_mod;

	be64_t   mkey;
	be16_t   dr_slid;
	be16_t   dr_dlid;
	uint8_t  reserved[28];
	uint8_t  data[IBMAD_LEN_SMP_DATA];
	uint8_t  initial_path[IBMAD_SMP_MAX_HOPS];
	uint8_t  return_path[IBMAD_SMP_MAX_HOPS];
};

/* ibmad_notice_* */
struct ibmad_notice_details_64_65_66_67 {
	uint8_t res[6];
	ibv_gid_t GIDADDR;	// the Node or Multicast Group that came in/out
	uint8_t Padding[32];
};
struct ibmad_notice_details_128 {
	be16_t LIDADDR;	// the sw lid of which link state changed
	uint8_t Padding[52];
};
struct ibmad_notice_details_129_130_131 {
	be16_t res;
	be16_t LIDADDR;	// lid and port number of the violation
	uint8_t PORTNO;
	uint8_t Padding[49];
};
struct ibmad_notice_details_144 {
	be16_t res;
	be16_t LIDADDR;             // lid where change occured
	be16_t res_OtherLocalChanges; /* 7: reserved
					 1: OtherLocalChanges */
	be32_t CAPABILITYMASK;
	be16_t change_flgs; /* 13: reserved
				1: LinkSpeedEnabledChange
				1: LinkWidthEnabledChange
				1: NodeDescriptionChange */
	uint8_t Padding[42];
};
struct ibmad_notice_details_145 {
	be16_t res;
	be16_t LIDADDR;	// lid where sys guid changed
	be16_t res2;
	be64_t SYSTEMIMAGEGUID;	// new system image guid
	uint8_t Padding[40];
};
struct ibmad_notice_details_256 {
	be16_t res;
	be16_t LIDADDR;
	be16_t DRSLID;
	uint8_t METHOD;
	uint8_t res2;
	be16_t ATTRIBUTEID;
	be32_t ATTRIBUTEMODIFIER;
	be64_t MKEY;
	uint8_t res3;
	uint8_t DRNotice_DRPathTruncated_DRHopCount; /* 1: DRNotice
							1: DRPathTruncated
							6: DRHopCount */
	uint8_t DRNoticeReturnPath[30];
};
struct ibmad_notice_details_257_258	// violation of p/q_key // 49
{
	be16_t res;
	be16_t LIDADDR1;
	be16_t LIDADDR2;
	be32_t KEY;
	be32_t SL_QP1; /*  4: SL
			   4: reserved
			  24: QP1 */
	be32_t QP2; /*  8: reserved
		       24: QP2 */
	ibv_gid_t GIDADDR1;
	ibv_gid_t GIDADDR2;
	uint8_t Padding[4];
};
struct ibmad_notice_details_259	// pkey violation from switch 51
{
	be16_t DataValid;
	be16_t LIDADDR1;
	be16_t LIDADDR2;
	be16_t PKEY;
	be32_t SL_QP1; /*  4: SL
			   4: reserved
			  24: QP1 */
	be32_t QP2; /*  8: reserved
		       24: QP2 */
	ibv_gid_t GIDADDR1;
	ibv_gid_t GIDADDR2;
	be16_t SWLIDADDR;
	uint8_t PORTNO;
	uint8_t Padding[3];
};

/* NodeDescription */
struct ibmad_node_description {
	uint8_t NodeString[64];
};

/* NodeInfo */
struct ibmad_node_info {
	uint8_t BaseVersion;
	uint8_t ClassVersion;
	uint8_t NodeType;
	uint8_t NumPorts;
	be64_t SystemImageGUID;
	be64_t NodeGUID;
	be64_t PortGUID;
	be16_t PartitionCap;
	be16_t DeviceID;
	be32_t Revision;
	be32_t LocalPortNum_VendorID; /*  8: LocalPortNum
					 24: VendorID */
};

/* SwitchInfo */
struct ibmad_switch_info {
	ib_net16_t LinearFDBCap;
	ib_net16_t RandomFDBCap;
	ib_net16_t MulticastFDBCap;
	ib_net16_t LinearFDBTop;
	uint8_t DefaultPort;
	uint8_t DefaultMulticastPrimaryPort;
	uint8_t DefaultMulticastNotPrimaryPort;
	uint8_t LifeTimeValue_PortStateChange_OptimizedSLtoVLMappingProgramming;
		/* 5: LifeTimeValue
		   1: PortStateChange
		   2: OptimizedSLtoVLMappingProgramming */
	ib_net16_t LIDsPerPort;
	ib_net16_t PartitionEnforcementCap;
	uint8_t flags;
		/* 1: InboundEnvorcementCap
		   1: OutboundEnforcementCap
		   1: FilterRawInboundCap
		   1: FilterRawOutboundCap
		   1: EnhancedPort0
		   3: Reserved */
	uint8_t resvd;
	ib_net16_t mcast_top;
};

/* PortInfo */
struct ibmad_port_info {

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

#endif				/* _IBMAD_SM_H */
