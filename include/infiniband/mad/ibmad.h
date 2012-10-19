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
#ifndef _IBMAD_H_
#define _IBMAD_H_

#include <infiniband/ibmad_osd.h>
#include <infiniband/ibmad_util.h>
#include <infiniband/ibmad_base.h>
#include <infiniband/ibmad_sm.h>
#include <infiniband/ibmad_sa.h>
#include <infiniband/ibmad_perfmgt.h>
#include <infiniband/ibmad_bm.h>
#include <infiniband/ibmad_cm.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Management classes */
enum IBMAD_BASE_CLASS {
	IBMAD_CLASS_SUBN_LID_ROUTED	= 0x01,
	IBMAD_CLASS_SUBN_DIRECTED_ROUTE	= 0x81,
	IBMAD_CLASS_SUBN_ADM		= 0x03,
	IBMAD_CLASS_PERF_MGMT		= 0x04,
	IBMAD_CLASS_BM			= 0x05,
	IBMAD_CLASS_DEVICE_MGMT		= 0x06,
	IBMAD_CLASS_CM			= 0x07,
	IBMAD_CLASS_SNMP		= 0x08,
	IBMAD_CLASS_VENDOR_RANGE1_START	= 0x09,
	IBMAD_CLASS_VENDOR_RANGE1_END	= 0x0F,
	IBMAD_CLASS_DEVICE_ADM		= 0x10,
	IBMAD_CLASS_BOOT_MGMT		= 0x11,
	IBMAD_CLASS_BIS			= 0x12,
	IBMAD_CLASS_CONG_MGMT		= 0x21,
	IBMAD_CLASS_VENDOR_RANGE2_START	= 0x30,
	IBMAD_CLASS_VENDOR_RANGE2_END	= 0x4F
};

/* generic IBMAD defines */
enum {
	IBMAD_BASE_VERSION		= 1
};










/*
 * SA RMPP section
 */
enum RMPP_TYPE_ENUM {
	IB_RMPP_TYPE_NONE,
	IB_RMPP_TYPE_DATA,
	IB_RMPP_TYPE_ACK,
	IB_RMPP_TYPE_STOP,
	IB_RMPP_TYPE_ABORT,
};

enum RMPP_FLAGS_ENUM {
	IB_RMPP_FLAG_ACTIVE = 1 << 0,
	IB_RMPP_FLAG_FIRST  = 1 << 1,
	IB_RMPP_FLAG_LAST   = 1 << 2,
};

typedef struct {
	int type;
	int flags;
	int status;
	union {
		uint32_t u;
		uint32_t segnum;
	} d1;
	union {
		uint32_t u;
		uint32_t len;
		uint32_t newwin;
	} d2;
} ib_rmpp_hdr_t;

enum SA_SIZES_ENUM {
	SA_HEADER_SZ = 20,
};

typedef struct ib_sa_call {
	unsigned attrid;
	unsigned mod;
	uint64_t mask;
	unsigned method;

	uint64_t trid;		/* used for out mad if nonzero, return real val */
	unsigned recsz;		/* return field */
	ib_rmpp_hdr_t rmpp;
} ib_sa_call_t;

typedef struct ib_vendor_call {
	unsigned method;
	unsigned mgmt_class;
	unsigned attrid;
	unsigned mod;
	uint32_t oui;
	unsigned timeout;
	ib_rmpp_hdr_t rmpp;
} ib_vendor_call_t;

typedef struct ib_bm_call {
	unsigned method;
	unsigned attrid;
	unsigned mod;
	unsigned timeout;
	uint64_t bkey;
} ib_bm_call_t;

#define IB_MIN_UCAST_LID	1
#define IB_MAX_UCAST_LID	(0xc000-1)
#define IB_MIN_MCAST_LID	0xc000
#define IB_MAX_MCAST_LID	(0xffff-1)

#define IB_LID_VALID(lid)	((lid) >= IB_MIN_UCAST_LID && lid <= IB_MAX_UCAST_LID)
#define IB_MLID_VALID(lid)	((lid) >= IB_MIN_MCAST_LID && lid <= IB_MAX_MCAST_LID)

#define MAD_DEF_RETRIES		3
#define MAD_DEF_TIMEOUT_MS	1000

enum MAD_DEST {
	IB_DEST_LID,
	IB_DEST_DRPATH,
	IB_DEST_GUID,
	IB_DEST_DRSLID,
	IB_DEST_GID
};

enum MAD_NODE_TYPE {
	IB_NODE_CA = 1,
	IB_NODE_SWITCH,
	IB_NODE_ROUTER,
	NODE_RNIC,

	IB_NODE_MAX = NODE_RNIC
};

/******************************************************************************/

/* portid.c */
MAD_EXPORT char *portid2str(ib_portid_t * portid);
MAD_EXPORT int portid2portnum(ib_portid_t * portid);
MAD_EXPORT int str2drpath(ib_dr_path_t * path, char *routepath, int drslid,
			  int drdlid);
MAD_EXPORT char *drpath2str(ib_dr_path_t * path, char *dstr, size_t dstr_size);

static inline int ib_portid_set(ib_portid_t * portid, int lid, int qp, int qkey)
{
	portid->lid = lid;
	portid->qp = qp;
	portid->qkey = qkey;
	portid->grh_present = 0;

	return 0;
}

/* fields.c */
MAD_EXPORT uint32_t mad_get_field(void *buf, int base_offs,
				  enum MAD_FIELDS field);
MAD_EXPORT void mad_set_field(void *buf, int base_offs, enum MAD_FIELDS field,
			      uint32_t val);
/* field must be byte aligned */
MAD_EXPORT uint64_t mad_get_field64(void *buf, int base_offs,
				    enum MAD_FIELDS field);
MAD_EXPORT void mad_set_field64(void *buf, int base_offs, enum MAD_FIELDS field,
				uint64_t val);
MAD_EXPORT void mad_set_array(void *buf, int base_offs, enum MAD_FIELDS field,
			      void *val);
MAD_EXPORT void mad_get_array(void *buf, int base_offs, enum MAD_FIELDS field,
			      void *val);
MAD_EXPORT char *mad_dump_field(enum MAD_FIELDS field, char *buf, int bufsz,
				void *val);
MAD_EXPORT char *mad_dump_val(enum MAD_FIELDS field, char *buf, int bufsz,
			      void *val);
MAD_EXPORT const char *mad_field_name(enum MAD_FIELDS field);

/* mad.c */
MAD_EXPORT void *mad_encode(void *buf, ib_rpc_t * rpc, ib_dr_path_t * drpath,
			    void *data);
MAD_EXPORT uint64_t mad_trid(void);
MAD_EXPORT int mad_build_pkt(void *umad, ib_rpc_t * rpc, ib_portid_t * dport,
			     ib_rmpp_hdr_t * rmpp, void *data);

/* New interface */
MAD_EXPORT void madrpc_show_errors(int set);
MAD_EXPORT struct ibmad_port *mad_rpc_open_port(char *dev_name, int dev_port,
						int *mgmt_classes,
						int num_classes);
MAD_EXPORT void mad_rpc_close_port(struct ibmad_port *srcport);

/* set timeouts */
MAD_EXPORT void mad_rpc_set_timeout(struct ibmad_port *port, int timeout);
MAD_EXPORT int mad_get_timeout(const struct ibmad_port *srcport,
			       int override_ms);
MAD_EXPORT void mad_rpc_set_retries(struct ibmad_port *port, int retries);
MAD_EXPORT int mad_get_retries(const struct ibmad_port *srcport);


/*
 * On redirection, the dport argument is updated with the redirection target,
 * so subsequent MADs will not go through the redirection process again but
 * reach the target directly.
 */
MAD_EXPORT void *mad_rpc(const struct ibmad_port *srcport, ib_rpc_t * rpc,
			 ib_portid_t * dport, void *payload, void *rcvdata);

MAD_EXPORT void *mad_rpc_rmpp(const struct ibmad_port *srcport, ib_rpc_t * rpc,
			      ib_portid_t * dport, ib_rmpp_hdr_t * rmpp,
			      void *data);
MAD_EXPORT int mad_rpc_portid(struct ibmad_port *srcport);
MAD_EXPORT int mad_rpc_class_agent(struct ibmad_port *srcport, int cls);

/* register.c new interface */
MAD_EXPORT int mad_register_client(int mgmt, uint8_t rmpp_version,
				       struct ibmad_port *srcport);
MAD_EXPORT int mad_register_server(int mgmt, uint8_t rmpp_version,
				       long method_mask[16 / sizeof(long)],
				       uint32_t class_oui,
				       struct ibmad_port *srcport);
MAD_EXPORT int mad_class_agent(int mgmt) DEPRECATED;

/* serv.c new interface */
MAD_EXPORT int mad_send(ib_rpc_t * rpc, ib_portid_t * dport,
			    ib_rmpp_hdr_t * rmpp, void *data,
			    struct ibmad_port *srcport);
MAD_EXPORT void *mad_receive(void *umad, int timeout,
				 struct ibmad_port *srcport);
MAD_EXPORT int mad_respond(void *umad, ib_portid_t * portid,
			       uint32_t rstatus, struct ibmad_port *srcport);
MAD_EXPORT void *mad_alloc(void);
MAD_EXPORT void mad_free(void *umad);

/* vendor.c */
MAD_EXPORT uint8_t *ib_vendor_call(void *data, ib_portid_t * portid,
				   ib_vendor_call_t * call) DEPRECATED;

/* vendor.c new interface */
MAD_EXPORT uint8_t *ib_vendor_call(void *data, ib_portid_t * portid,
				       ib_vendor_call_t * call,
				       struct ibmad_port *srcport);

static inline int mad_is_vendor_range1(int mgmt)
{
	return mgmt >= 0x9 && mgmt <= 0xf;
}

static inline int mad_is_vendor_range2(int mgmt)
{
	return mgmt >= 0x30 && mgmt <= 0x4f;
}

/* smp.c new interface */
MAD_EXPORT uint8_t *smp_query(void *buf, ib_portid_t * id, unsigned attrid,
				  unsigned mod, unsigned timeout,
				  const struct ibmad_port *srcport);
MAD_EXPORT uint8_t *smp_set(void *buf, ib_portid_t * id, unsigned attrid,
				unsigned mod, unsigned timeout,
				const struct ibmad_port *srcport);
MAD_EXPORT uint8_t *smp_query_status(void *rcvbuf, ib_portid_t * portid,
					 unsigned attrid, unsigned mod,
					 unsigned timeout, int *rstatus,
					 const struct ibmad_port *srcport);
MAD_EXPORT uint8_t *smp_set_status(void *data, ib_portid_t * portid,
				       unsigned attrid, unsigned mod,
				       unsigned timeout, int *rstatus,
				       const struct ibmad_port *srcport);

/* sa.c new interface */
MAD_EXPORT uint8_t *sa_rpc_call(const struct ibmad_port *srcport, void *rcvbuf,
				ib_portid_t * portid, ib_sa_call_t * sa,
				unsigned timeout);
MAD_EXPORT int ib_path_query(const struct ibmad_port *srcport,
				 ibmad_gid_t srcgid, ibmad_gid_t destgid,
				 ib_portid_t * sm_id, void *buf);
	/* returns lid */

/* resolve.c new interface */
MAD_EXPORT int ib_resolve_smlid(ib_portid_t * sm_id, int timeout,
				    const struct ibmad_port *srcport);
MAD_EXPORT int ib_resolve_guid(ib_portid_t * portid, uint64_t * guid,
				   ib_portid_t * sm_id, int timeout,
				   const struct ibmad_port *srcport);
MAD_EXPORT int ib_resolve_gid(ib_portid_t * portid, ibmad_gid_t gid,
				  ib_portid_t * sm_id, int timeout,
				  const struct ibmad_port *srcport);
MAD_EXPORT int ib_resolve_portid_str(ib_portid_t * portid, char *addr_str,
					 enum MAD_DEST dest,
					 ib_portid_t * sm_id,
					 const struct ibmad_port *srcport);
MAD_EXPORT int ib_resolve_self(ib_portid_t * portid, int *portnum,
				   ibmad_gid_t * gid,
				   const struct ibmad_port *srcport);

/* gs.c new interface */
MAD_EXPORT uint8_t *pma_query(void *rcvbuf, ib_portid_t * dest, int port,
				  unsigned timeout, unsigned id,
				  const struct ibmad_port *srcport);
MAD_EXPORT uint8_t *performance_reset(void *rcvbuf, ib_portid_t * dest,
					  int port, unsigned mask,
					  unsigned timeout, unsigned id,
					  const struct ibmad_port *srcport);

/* bm.c */
MAD_EXPORT uint8_t *bm_call(void *data, ib_portid_t * portid,
				ib_bm_call_t * call,
				struct ibmad_port *srcport);

/* dump.c */
MAD_EXPORT ib_mad_dump_fn
    mad_dump_int, mad_dump_uint, mad_dump_hex, mad_dump_rhex,
    mad_dump_bitfield, mad_dump_array, mad_dump_string,
    mad_dump_linkwidth, mad_dump_linkwidthsup, mad_dump_linkwidthen,
    mad_dump_linkdowndefstate,
    mad_dump_linkspeed, mad_dump_linkspeedsup, mad_dump_linkspeeden,
    mad_dump_portstate, mad_dump_portstates,
    mad_dump_physportstate, mad_dump_portcapmask,
    mad_dump_mtu, mad_dump_vlcap, mad_dump_opervls,
    mad_dump_node_type, mad_dump_sltovl, mad_dump_vlarbitration,
    mad_dump_nodedesc, mad_dump_nodeinfo, mad_dump_portinfo,
    mad_dump_switchinfo, mad_dump_perfcounters, mad_dump_perfcounters_ext,
    mad_dump_perfcounters_xmt_sl, mad_dump_perfcounters_rcv_sl,
    mad_dump_perfcounters_xmt_disc, mad_dump_perfcounters_rcv_err,
    mad_dump_portsamples_control;

MAD_EXPORT void mad_dump_fields(char *buf, int bufsz, void *val, int valsz,
				int start, int end);

extern MAD_EXPORT int ibdebug;

/* Misc. macros: */
/** align value \a l to \a size (ceil) */
#define ALIGN(l, size) (((l) + ((size) - 1)) / (size) * (size))

/** printf style warning MACRO, includes name of function and pid */
#define IBWARN(fmt, ...) fprintf(stderr, "ibwarn: [%d] %s: " fmt "\n", getpid(), __func__, ## __VA_ARGS__)

#define IBDEBUG(fmt, ...) fprintf(stdout, "ibdebug: [%d] %s: " fmt "\n", getpid(), __func__, ## __VA_ARGS__)

#define IBVERBOSE(fmt, ...) fprintf(stdout, "[%d] %s: " fmt "\n", getpid(), __func__, ## __VA_ARGS__)

#define IBPANIC(fmt, ...) do { \
	fprintf(stderr, "ibpanic: [%d] %s: " fmt ": %m\n", getpid(), __func__, ## __VA_ARGS__); \
	exit(-1); \
} while(0)

MAD_EXPORT void xdump(FILE * file, char *msg, void *p, int size);

#ifdef __cplusplus
}
#endif

#endif				/* _IBMAD_H_ */
