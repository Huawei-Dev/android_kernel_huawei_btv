#ifndef __NET_DST_METADATA_H
#define __NET_DST_METADATA_H 1

#include <linux/skbuff.h>
#include <net/ip_tunnels.h>
#include <net/dst.h>

struct metadata_dst {
	struct dst_entry		dst;
	size_t				opts_len;
	union {
		struct ip_tunnel_info	tun_info;
	} u;
};

static inline struct metadata_dst *skb_metadata_dst(struct sk_buff *skb)
{
	struct metadata_dst *md_dst = (struct metadata_dst *) skb_dst(skb);

	if (md_dst && md_dst->dst.flags & DST_METADATA)
		return md_dst;

	return NULL;
}

static inline struct ip_tunnel_info *skb_tunnel_info(struct sk_buff *skb)
{
	struct metadata_dst *md_dst = skb_metadata_dst(skb);
	struct dst_entry *dst;

	if (md_dst)
		return &md_dst->u.tun_info;

	dst = skb_dst(skb);
	if (dst && dst->lwtstate)
		return lwt_tun_info(dst->lwtstate);

	return NULL;
}

static inline bool skb_valid_dst(const struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);

	return dst && !(dst->flags & DST_METADATA);
}

struct metadata_dst *metadata_dst_alloc(u8 optslen, gfp_t flags);
struct metadata_dst __percpu *metadata_dst_alloc_percpu(u8 optslen, gfp_t flags);

static inline struct metadata_dst *tun_rx_dst(__be16 flags,
					      __be64 tunnel_id, int md_size)
{
	struct metadata_dst *tun_dst;
	struct ip_tunnel_info *info;

	tun_dst = metadata_dst_alloc(md_size, GFP_ATOMIC);
	if (!tun_dst)
		return NULL;

	info = &tun_dst->u.tun_info;
	info->key.tun_flags = flags;
	info->key.tun_id = tunnel_id;
	info->key.tp_src = 0;
	info->key.tp_dst = 0;
	return tun_dst;
}

static inline struct metadata_dst *ip_tun_rx_dst(struct sk_buff *skb,
						 __be16 flags,
						 __be64 tunnel_id,
						 int md_size)
{
	const struct iphdr *iph = ip_hdr(skb);
	struct metadata_dst *tun_dst;
	struct ip_tunnel_info *info;

	tun_dst = tun_rx_dst(flags, tunnel_id, md_size);
	if (!tun_dst)
		return NULL;

	info = &tun_dst->u.tun_info;
	info->key.u.ipv4.src = iph->saddr;
	info->key.u.ipv4.dst = iph->daddr;
	info->key.tos = iph->tos;
	info->key.ttl = iph->ttl;
	return tun_dst;
}

static inline struct metadata_dst *ipv6_tun_rx_dst(struct sk_buff *skb,
						 __be16 flags,
						 __be64 tunnel_id,
						 int md_size)
{
	const struct ipv6hdr *ip6h = ipv6_hdr(skb);
	struct metadata_dst *tun_dst;
	struct ip_tunnel_info *info;

	tun_dst = tun_rx_dst(flags, tunnel_id, md_size);
	if (!tun_dst)
		return NULL;

	info = &tun_dst->u.tun_info;
	info->key.u.ipv6.src = ip6h->saddr;
	info->key.u.ipv6.dst = ip6h->daddr;
	info->key.tos = ipv6_get_dsfield(ip6h);
	info->key.ttl = ip6h->hop_limit;
	info->mode = IP_TUNNEL_INFO_IPV6;
	return tun_dst;
}

#endif /* __NET_DST_METADATA_H */
