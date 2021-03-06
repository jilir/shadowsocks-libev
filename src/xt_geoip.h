/* ipt_geoip.h header file for libipt_geoip.c and ipt_geoip.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Copyright (c) 2004, 2005, 2006, 2007, 2008
 *
 * Samuel Jean
 * Nicolas Bouliane
 */
#ifndef _LINUX_NETFILTER_XT_GEOIP_H
#define _LINUX_NETFILTER_XT_GEOIP_H 1
#define aligned_u64 __u64 __attribute__((aligned(8)))

#include <linux/ip.h>
#include <linux/ipv6.h>

#include "list.h"



#include <asm/atomic.h>
#include <asm/uaccess.h>
enum {
	XT_GEOIP_SRC = 1 << 0,	/* Perform check on Source IP */
	XT_GEOIP_DST = 1 << 1,	/* Perform check on Destination IP */
	XT_GEOIP_INV = 1 << 2,	/* Negate the condition */

	XT_GEOIP_MAX = 15,	/* Maximum of countries */
};

/* Yup, an address range will be passed in with host-order */
struct geoip_subnet4 {
	__u32 begin;
	__u32 end;
};

struct geoip_subnet6 {
	struct in6_addr begin, end;
};

struct geoip_country_user {
	aligned_u64 subnets;
	__u32 count;
	__u16 cc;
};

struct geoip_country_kernel;

union geoip_country_group {
	aligned_u64 user; /* struct geoip_country_user * */
	struct geoip_country_kernel *kernel;
};

struct xt_geoip_match_info {
	__u8 flags;
	__u8 count;
	__u16 cc[XT_GEOIP_MAX];

	/* Used internally by the kernel */
	union geoip_country_group mem[XT_GEOIP_MAX];
};
#define GEOIP_DB_DIR "/data/xt_geoip"
#define COUNTRY(cc) ((cc) >> 8), ((cc) & 0x00FF)

enum geoip_proto {
	GEOIPROTO_IPV6,
	GEOIPROTO_IPV4,
	__GEOIPROTO_MAX,
};

/**
 * @list:	anchor point for geoip_head
 * @subnets:	packed ordered list of ranges (either v6 or v4)
 * @count:	number of ranges
 * @cc:		country code
 */
 /*
struct geoip_country_kernel {
	struct list_head list;
	void *subnets;
	atomic_t ref;
	unsigned int count;
	unsigned short cc;
};
*/
#endif /* _LINUX_NETFILTER_XT_GEOIP_H */
