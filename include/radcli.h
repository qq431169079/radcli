/*
 * $Id: freeradius-client.h,v 1.18 2010/06/15 09:22:51 aland Exp $
 *
 * Copyright (C) 1995,1996,1997,1998 Lars Fenneberg
 *
 * Copyright 1992 Livingston Enterprises, Inc.
 *
 * Copyright 1992,1993, 1994,1995 The Regents of the University of Michigan
 * and Merit Network, Inc. All Rights Reserved
 *
 * See the file COPYRIGHT for the respective terms and conditions.
 * If the file is missing contact me at lf@elemental.net
 * and I'll send you a copy.
 *
 */

#ifndef RADCLI_H
#define RADCLI_H

#ifdef CP_DEBUG
#define		DEBUG(args, ...)	rc_log(## args)
#else
#define		DEBUG(args, ...)	;
#endif

#include	<sys/types.h>
/*
 * Include for C99 uintX_t defines is stdint.h on most systems.  Solaris uses
 * inttypes.h instead.  Comment out the stdint include if you get an error,
 * and uncomment the inttypes.h include.
 */
#include	<stdint.h>
/* #include	<inttypes.h> */
#include	<stdio.h>
#include	<time.h>


/* for struct addrinfo and sockaddr_storage */
#include <sys/socket.h>
#include <netdb.h>

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

#define AUTH_PASS_LEN		(3 * 16) /* multiple of 16 */
#define AUTH_ID_LEN		64
#define AUTH_STRING_LEN		253	 /* maximum of 253 */

#define BUFFER_LEN		8192

#define NAME_LENGTH		32

#define MAX_SECRET_LENGTH	(6 * 16) /* MUST be multiple of 16 */

#define VENDOR(x)		(((x) >> 16) & 0xffff)
#define ATTRID(x)		((x) & 0xffff)

#define PW_MAX_MSG_SIZE		4096

/* codes for radius_buildreq, radius_getport, etc. */
typedef enum rc_type {
	AUTH = 0,
	ACCT = 1
} rc_type;

/* defines for config.c */

#define SERVER_MAX 8

#define AUTH_LOCAL_FST	(1<<0)
#define AUTH_RADIUS_FST	(1<<1)
#define AUTH_LOCAL_SND	(1<<2)
#define AUTH_RADIUS_SND	(1<<3)

struct rc_conf;
typedef struct rc_conf rc_handle;

typedef struct server {
	int max;
	char *name[SERVER_MAX];
	uint16_t port[SERVER_MAX];
	char *secret[SERVER_MAX];
	double deadtime_ends[SERVER_MAX];
} SERVER;

#define AUTH_HDR_LEN			20
#define CHAP_VALUE_LENGTH		16

#define PW_AUTH_UDP_PORT		1645
#define PW_ACCT_UDP_PORT		1646

#define PW_TYPE_STRING			0
#define PW_TYPE_INTEGER			1
#define PW_TYPE_IPADDR			2
#define PW_TYPE_DATE			3
#define PW_TYPE_IPV6ADDR		4
#define PW_TYPE_IPV6PREFIX		5

/* standard RADIUS codes */

#define PW_ACCESS_REQUEST		1
#define PW_ACCESS_ACCEPT		2
#define PW_ACCESS_REJECT		3
#define PW_ACCOUNTING_REQUEST		4
#define PW_ACCOUNTING_RESPONSE		5
#define PW_ACCOUNTING_STATUS		6
#define PW_PASSWORD_REQUEST		7
#define PW_PASSWORD_ACK			8
#define PW_PASSWORD_REJECT		9
#define PW_ACCOUNTING_MESSAGE		10
#define PW_ACCESS_CHALLENGE		11
#define PW_STATUS_SERVER		12
#define PW_STATUS_CLIENT		13


/* standard RADIUS attribute-value pairs */

#define PW_USER_NAME			1	//!< string.
#define PW_USER_PASSWORD		2	//!< string.
#define PW_CHAP_PASSWORD		3	//!< string.
#define PW_NAS_IP_ADDRESS		4	//!< ipaddr.
#define PW_NAS_PORT			5	//!< integer.
#define PW_SERVICE_TYPE			6	//!< integer.
#define PW_FRAMED_PROTOCOL		7	//!< integer.
#define PW_FRAMED_IP_ADDRESS		8	//!< ipaddr.
#define PW_FRAMED_IP_NETMASK		9	//!< ipaddr.
#define PW_FRAMED_ROUTING		10	//!< integer.
#define PW_FILTER_ID			11	//!< string.
#define PW_FRAMED_MTU			12	//!< integer.
#define PW_FRAMED_COMPRESSION		13	//!< integer.
#define PW_LOGIN_IP_HOST		14	//!< ipaddr.
#define PW_LOGIN_SERVICE		15	//!< integer.
#define PW_LOGIN_PORT			16	//!< integer.
#define PW_OLD_PASSWORD			17	//!< string */ /* deprecated.
#define PW_REPLY_MESSAGE		18	//!< string.
#define PW_LOGIN_CALLBACK_NUMBER	19	//!< string.
#define PW_FRAMED_CALLBACK_ID		20	//!< string.
#define PW_EXPIRATION			21	//!< date */ /* deprecated.
#define PW_FRAMED_ROUTE			22	//!< string.
#define PW_FRAMED_IPX_NETWORK		23	//!< integer.
#define PW_STATE			24	//!< string.
#define PW_CLASS			25	//!< string.
#define PW_VENDOR_SPECIFIC		26	//!< string.
#define PW_SESSION_TIMEOUT		27	//!< integer.
#define PW_IDLE_TIMEOUT			28	//!< integer.
#define PW_TERMINATION_ACTION		29	//!< integer.
#define PW_CALLED_STATION_ID		30	//!< string.
#define PW_CALLING_STATION_ID		31	//!< string.
#define PW_NAS_IDENTIFIER		32	//!< string.
#define PW_PROXY_STATE			33	//!< string.
#define PW_LOGIN_LAT_SERVICE		34	//!< string.
#define PW_LOGIN_LAT_NODE		35	//!< string.
#define PW_LOGIN_LAT_GROUP		36	//!< string.
#define PW_FRAMED_APPLETALK_LINK	37	//!< integer.
#define PW_FRAMED_APPLETALK_NETWORK	38	//!< integer.
#define PW_FRAMED_APPLETALK_ZONE	39	//!< string.
#define PW_ACCT_STATUS_TYPE		40	//!< integer.
#define PW_ACCT_DELAY_TIME		41	//!< integer.
#define PW_ACCT_INPUT_OCTETS		42	//!< integer.
#define PW_ACCT_OUTPUT_OCTETS		43	//!< integer.
#define PW_ACCT_SESSION_ID		44	//!< string.
#define PW_ACCT_AUTHENTIC		45	//!< integer.
#define PW_ACCT_SESSION_TIME		46	//!< integer.
#define PW_ACCT_INPUT_PACKETS		47	//!< integer.
#define PW_ACCT_OUTPUT_PACKETS		48	//!< integer.
#define PW_ACCT_TERMINATE_CAUSE		49	//!< integer.
#define PW_ACCT_MULTI_SESSION_ID	50	//!< string.
#define PW_ACCT_LINK_COUNT		51	//!< integer.
#define PW_ACCT_INPUT_GIGAWORDS		52	//!< integer.
#define PW_ACCT_OUTPUT_GIGAWORDS	53	//!< integer.
#define PW_EVENT_TIMESTAMP		55	//!< integer.
#define PW_EGRESS_VLANID		56	//!< string.
#define PW_INGRESS_FILTERS		57	//!< integer.
#define PW_EGRESS_VLAN_NAME		58	//!< string.
#define PW_USER_PRIORITY_TABLE		59	//!< string.
#define PW_CHAP_CHALLENGE		60	//!< string.
#define PW_NAS_PORT_TYPE		61	//!< integer.
#define PW_PORT_LIMIT			62	//!< integer.
#define PW_LOGIN_LAT_PORT		63	//!< string.
#define PW_TUNNEL_TYPE			64	//!< string.
#define PW_TUNNEL_MEDIUM_TYPE		65	//!< integer.
#define PW_TUNNEL_CLIENT_ENDPOINT	66	//!< string.
#define PW_TUNNEL_SERVER_ENDPOINT	67	//!< string.
#define PW_ACCT_TUNNEL_CONNECTION	68	//!< string.
#define PW_TUNNEL_PASSWORD		69	//!< string.
#define PW_ARAP_PASSWORD		70	//!< string.
#define PW_ARAP_FEATURES		71	//!< string.
#define PW_ARAP_ZONE_ACCESS		72	//!< integer.
#define PW_ARAP_SECURITY		73	//!< integer.
#define PW_ARAP_SECURITY_DATA		74	//!< string.
#define PW_PASSWORD_RETRY		75	//!< integer.
#define PW_PROMPT			76	//!< integer.
#define PW_CONNECT_INFO			77	//!< string.
#define PW_CONFIGURATION_TOKEN		78	//!< string.
#define PW_EAP_MESSAGE			79	//!< string.
#define PW_MESSAGE_AUTHENTICATOR	80	//!< string.
#define PW_TUNNEL_PRIVATE_GROUP_ID	81	//!< string.
#define PW_TUNNEL_ASSIGNMENT_ID		82	//!< string.
#define PW_TUNNEL_PREFERENCE		83	//!< string.
#define PW_ARAP_CHALLENGE_RESPONSE	84	//!< string.
#define PW_ACCT_INTERIM_INTERVAL	85	//!< integer.
#define PW_ACCT_TUNNEL_PACKETS_LOST	86	//!< integer.
#define PW_NAS_PORT_ID_STRING		87	//!< string.
#define PW_FRAMED_POOL			88	//!< string.
#define PW_CHARGEABLE_USER_IDENTITY	89	//!< string.
#define PW_CUI				89	//!< string.
#define PW_TUNNEL_CLIENT_AUTH_ID	90	//!< string.
#define PW_TUNNEL_SERVER_AUTH_ID	91	//!< string.
#define PW_NAS_FILTER_RULE		92	//!< string.
#define PW_ORIGINATING_LINE_INFO	94	//!< string.
#define PW_NAS_IPV6_ADDRESS		95	//!< string.
#define PW_FRAMED_INTERFACE_ID		96	//!< string.
#define PW_FRAMED_IPV6_PREFIX		97	//!< string.
#define PW_LOGIN_IPV6_HOST		98	//!< string.
#define PW_FRAMED_IPV6_ROUTE		99	//!< string.
#define PW_FRAMED_IPV6_POOL		100	//!< string.
#define PW_ERROR_CAUSE			101	//!< integer.
#define PW_EAP_KEY_NAME			102	//!< string.

#define PW_FRAMED_IPV6_ADDRESS		168	//!< ipaddr6.
#define PW_DNS_SERVER_IPV6_ADDRESS	169	//!< ipaddr6.
#define PW_ROUTE_IPV6_INFORMATION	170	//!< ipv6prefix.

/* Experimental SIP-specific attributes (draft-sterman-aaa-sip-00.txt etc) */

#define PW_DIGEST_RESPONSE		206	//!< string.
#define PW_DIGEST_ATTRIBUTES		207	//!< string.
#define PW_DIGEST_REALM			1063	//!< string.
#define PW_DIGEST_NONCE			1064	//!< string.
#define PW_DIGEST_METHOD		1065	//!< string.
#define PW_DIGEST_URI			1066	//!< string.
#define PW_DIGEST_QOP			1067	//!< string.
#define PW_DIGEST_ALGORITHM		1068	//!< string.
#define PW_DIGEST_BODY_DIGEST		1069	//!< string.
#define PW_DIGEST_CNONCE		1070	//!< string.
#define PW_DIGEST_NONCE_COUNT		1071	//!< string.
#define PW_DIGEST_USER_NAME		1072	//!< string.

/* Merit Experimental Extensions */

#define PW_USER_ID			222	//!< string.
#define PW_USER_REALM			223	//!< string.

/* Integer Translations */

/* SERVICE TYPES */

#define PW_LOGIN			1
#define PW_FRAMED			2
#define PW_CALLBACK_LOGIN		3
#define PW_CALLBACK_FRAMED		4
#define PW_OUTBOUND			5
#define PW_ADMINISTRATIVE		6
#define PW_NAS_PROMPT			7
#define PW_AUTHENTICATE_ONLY		8
#define PW_CALLBACK_NAS_PROMPT		9

/* FRAMED PROTOCOLS */

#define PW_PPP				1
#define PW_SLIP				2
#define PW_ARA				3
#define PW_GANDALF			4
#define PW_XYLOGICS			5

/* FRAMED ROUTING VALUES */

#define PW_NONE				0
#define PW_BROADCAST			1
#define PW_LISTEN			2
#define PW_BROADCAST_LISTEN		3

/* FRAMED COMPRESSION TYPES */

#define PW_VAN_JACOBSON_TCP_IP		1
#define PW_IPX_HEADER_COMPRESSION	2

/* LOGIN SERVICES */

#define PW_TELNET			0
#define PW_RLOGIN			1
#define PW_TCP_CLEAR			2
#define PW_PORTMASTER			3
#define PW_LAT				4
#define PW_X25_PAD			5
#define PW_X25_T3POS			6

/* TERMINATION ACTIONS */

#define PW_DEFAULT			0
#define PW_RADIUS_REQUEST		1

/* PROHIBIT PROTOCOL */

#define PW_DUMB			0	//!< 1 and 2 are defined in FRAMED PROTOCOLS.
#define PW_AUTH_ONLY		3
#define PW_ALL			255

/* ACCOUNTING STATUS TYPES */

#define PW_STATUS_START		1
#define PW_STATUS_STOP		2
#define PW_STATUS_ALIVE		3
#define PW_STATUS_MODEM_START	4
#define PW_STATUS_MODEM_STOP	5
#define PW_STATUS_CANCEL	6
#define PW_ACCOUNTING_ON	7
#define PW_ACCOUNTING_OFF	8

/* ACCOUNTING TERMINATION CAUSES */

#define PW_USER_REQUEST		1
#define PW_LOST_CARRIER		2
#define PW_LOST_SERVICE		3
#define PW_ACCT_IDLE_TIMEOUT	4
#define PW_ACCT_SESSION_TIMEOUT	5
#define PW_ADMIN_RESET		6
#define PW_ADMIN_REBOOT		7
#define PW_PORT_ERROR		8
#define PW_NAS_ERROR		9
#define PW_NAS_REQUEST		10
#define PW_NAS_REBOOT		11
#define PW_PORT_UNNEEDED	12
#define PW_PORT_PREEMPTED	13
#define PW_PORT_SUSPENDED	14
#define PW_SERVICE_UNAVAILABLE	15
#define PW_CALLBACK		16
#define PW_USER_ERROR		17
#define PW_HOST_REQUEST		18

/* NAS PORT TYPES */

#define PW_ASYNC		0
#define PW_SYNC			1
#define PW_ISDN_SYNC		2
#define PW_ISDN_SYNC_V120	3
#define PW_ISDN_SYNC_V110	4
#define PW_VIRTUAL		5

/* AUTHENTIC TYPES */

#define PW_RADIUS	1
#define PW_LOCAL	2
#define PW_REMOTE	3

/* Server data structures */

typedef struct dict_attr
{
	char              name[NAME_LENGTH + 1];	//!< attribute name.
	int               value;			//!< attribute index.
	int               type;				//!< string, int, etc..
	struct dict_attr *next;
} DICT_ATTR;

typedef struct dict_value
{
	char               attrname[NAME_LENGTH +1];
	char               name[NAME_LENGTH + 1];
	int                value;
	struct dict_value *next;
} DICT_VALUE;

typedef struct dict_vendor
{
	char               vendorname[NAME_LENGTH +1];
	int                vendorpec;
	struct dict_vendor *next;
} DICT_VENDOR;

typedef struct value_pair
{
	char               name[NAME_LENGTH + 1];
	int                attribute;
	int                type;
	uint32_t           lvalue;
	char               strvalue[AUTH_STRING_LEN + 1];
	struct value_pair *next;
} VALUE_PAIR;

/* don't change this, as it has to be the same as in the Merit radiusd code */
#define MGMT_POLL_SECRET	"Hardlyasecret"

/* Define return codes from "SendServer" utility */

#define BADRESPID_RC	-3
#define BADRESP_RC	-2
#define ERROR_RC	-1
#define OK_RC		0
#define TIMEOUT_RC	1
#define REJECT_RC	2

typedef struct send_data /* Used to pass information to sendserver() function */
{
	uint8_t        code;		//!< RADIUS packet code.
	uint8_t        seq_nbr;		//!< Packet sequence number.
	char           *server;		//!< Name/addrress of RADIUS server.
	int            svc_port;	//!< RADIUS protocol destination port.
	char           *secret;		//!< Shared secret of RADIUS server.
	int            timeout;		//!< Session timeout in seconds.
	int            retries;
	VALUE_PAIR     *send_pairs;     //!< More a/v pairs to send.
	VALUE_PAIR     *receive_pairs;  //!< Where to place received a/v pairs.
} SEND_DATA;

#ifndef MIN
#define MIN(a, b)     ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)     ((a) > (b) ? (a) : (b))
#endif

#ifndef PATH_MAX
#define PATH_MAX	1024
#endif

#define ENV_SIZE	128

__BEGIN_DECLS

/*!\mainpage
 * \section Introduction
 *
 * RADIUS stands for Remote Authentication Dial In User Service
 * and is a protocol for carrying authentication, authorization,
 * and configuration information between a Network Access Server
 * (NAS) which desires to authenticate its links and a shared
 * Authentication Server.  The protocol originally was designed
 * by the terminal server manufacturer Livingston for use with
 * their Portmaster series of terminal servers.  Since then it
 * has been implemented by a lot of other vendors and it is also
 * on it's way to become a Internet Standard.
 *
 * This library implements the needed standards for the client side
 * of the protocol, in a way the minimum configuration and modification
 * is needed for the clients. The approach is to rely on a small
 * external radius configuration file, read using rc_read_config2(),
 * and then using rc_auth() or rc_acct() to communicate with the server.
 * Check radexample.c for a functional example.
 *
 */

/** \example radexample.c
 * This is an example of how to use the radcli API.
 */

/* avpair.c */

VALUE_PAIR *rc_avpair_add (rc_handle const *rh, VALUE_PAIR **list, int attrid, void const *pval, int len, int vendorpec);
int rc_avpair_assign (VALUE_PAIR *vp, void const *pval, int len);
VALUE_PAIR *rc_avpair_new (rc_handle const *rh, int attrid, void const *pval, int len, int vendorpec);
VALUE_PAIR *rc_avpair_gen(rc_handle const *rh, VALUE_PAIR *pair, unsigned char const *ptr,
			  int length, int vendorpec);
VALUE_PAIR *rc_avpair_get (VALUE_PAIR *vp, int attrid, int vendorpec);
void rc_avpair_insert(VALUE_PAIR **a, VALUE_PAIR *p, VALUE_PAIR *b);
void rc_avpair_free (VALUE_PAIR *pair);
int rc_avpair_parse (rc_handle const *rh, char const *buffer, VALUE_PAIR **first_pair);
int rc_avpair_tostr (rc_handle const *rh, VALUE_PAIR *pair, char *name, int ln, char *value, int lv);
char *rc_avpair_log(rc_handle const *rh, VALUE_PAIR *pair, char *buf, size_t buf_len);
VALUE_PAIR *rc_avpair_readin(rc_handle const *rh, FILE *input);

/* buildreq.c */

void rc_buildreq(rc_handle const *rh, SEND_DATA *data, int code, char *server, unsigned short port,
		 char *secret, int timeout, int retries);
int rc_auth(rc_handle *rh, uint32_t client_port, VALUE_PAIR *send, VALUE_PAIR **received, char *msg);
int rc_auth_proxy(rc_handle *rh, VALUE_PAIR *send, VALUE_PAIR **received, char *msg);
int rc_acct(rc_handle *rh, uint32_t client_port, VALUE_PAIR *send);
int rc_acct_proxy(rc_handle *rh, VALUE_PAIR *send);
int rc_check(rc_handle *rh, char *host, char *secret, unsigned short port, char *msg);

int rc_aaa(rc_handle *rh, uint32_t client_port, VALUE_PAIR *send, VALUE_PAIR **received,
	   char *msg, int add_nas_port, int request_type);

/* config.c */

int rc_add_config(rc_handle *rh, char const *option_name, char const *option_val, char const *source, int line);
rc_handle *rc_config_init(rc_handle *rh);
rc_handle *rc_read_config(char const *filename);

#define RC_CONFIG_LOAD_ALL 1 //!< Load any other configuration files, such as dictionary, when needed
rc_handle *rc_read_config2(char const *filename, unsigned flags);
char *rc_conf_str(rc_handle const *rh, char const *optname);
int rc_conf_int(rc_handle const *rh, char const *optname);
SERVER *rc_conf_srv(rc_handle const *rh, char const *optname);
int rc_test_config(rc_handle *rh, char const *filename);
int rc_find_server_addr (rc_handle const *rh, char const *server_name,
                         struct addrinfo** info, char *secret, rc_type type);
void rc_config_free(rc_handle *rh);
rc_handle *rc_new(void);
void rc_destroy(rc_handle *rh);

#define test_config rc_test_config

/* dict.c */

int rc_read_dictionary (rc_handle *rh, char const *filename);
DICT_ATTR *rc_dict_getattr(rc_handle const *rh, int attribute);
DICT_ATTR *rc_dict_findattr(rc_handle const *rh, char const *attrname);
DICT_VALUE *rc_dict_findval(rc_handle const *rh, char const *valname);
DICT_VENDOR *rc_dict_findvend(rc_handle const *rh, char const *vendorname);
DICT_VENDOR *rc_dict_getvend (rc_handle const *rh, int vendorpec);
DICT_VALUE *rc_dict_getval(rc_handle const *rh, uint32_t value, char const *attrname);
void rc_dict_free(rc_handle *rh);

/*	tls.c			*/

int rc_tls_fd(rc_handle * rh);
int rc_check_tls(rc_handle * rh);
void rc_deinit_tls(rc_handle * rh);
#define SEC_FLAG_DTLS 1
int rc_init_tls(rc_handle * rh, unsigned flags);

/* ip_util.c */

unsigned short rc_getport(int type);
int rc_own_hostname(char *hostname, int len);
struct sockaddr;
int rc_get_srcaddr(struct sockaddr *lia, const struct sockaddr *ria);

/* log.c */

void rc_openlog(char const *ident);
void rc_log(int prio, char const *format, ...);

/* sendserver.c */

int rc_send_server (rc_handle *rh, SEND_DATA *data, char *msg,
                    unsigned type);

/* util.c */

void rc_str2tm (char const *valstr, struct tm *tm);

__END_DECLS

#endif /* RADCLI_H */
