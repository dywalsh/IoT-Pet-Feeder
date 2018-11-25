/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_MODULE_NAME net_tb_pubsub
#define NET_LOG_LEVEL LOG_LEVEL_DBG

#include "tb_pubsub.h"

#include <zephyr.h>
#include <net/mqtt.h>
#include <stdlib.h>

#include <misc/printk.h>
#include <string.h>
#include <stdio.h>
#include <bluetooth/bluetooth.h>

#include <json.h>

#include "config.h"
#include "time.h"
#include "servo.h"

#define MAX_PENDING_PUB_MSGS 8
#define PUBSUB_STACK_SIZE 1024
#define PUBSUB_PRIORITY 5

static const char *TB_ATTRIBUTES_TOPIC = "v1/devices/me/attributes";
static const char *TB_TELEMETRY_TOPIC = "v1/devices/me/telemetry";
static const char *TB_RPC_TOPIC[] = {"v1/devices/me/rpc/request/+"};
static const enum mqtt_qos TB_RPC_QOS[] = {MQTT_QoS0};

int const timeAdd = 10000;

/* For some reason thingsboard.io is very slow to respond to TX Connect
 * requests. We'll implement them using an alert to signal when
 * a connection is established. */
K_ALERT_DEFINE(tb_connack_alert, K_ALERT_DEFAULT, 1);

#define RC_STR(rc)	((rc) == 0 ? "OK" : "ERROR")
#define PRINT_RESULT(func, rc)	\
	printf("[%s:%d] %s: %d <%s>\n", __func__, __LINE__, \
	       (func), rc, RC_STR(rc))

/* Container for some structures used by the MQTT pubsub app. */
static struct pubsub_ctx {
	/**
	 * The connect message structure is only used during the connect
	 * stage. Developers must set some msg properties before calling the
	 * mqtt_tx_connect routine. See below.
	 */
	struct mqtt_connect_msg connect_msg;

	/**
	 * This is the MQTT application context variable.
	 */
	struct mqtt_ctx mqtt_ctx;
} pubsub_ctx;

/* MQTT publish message descriptor */
static struct pub_msg {
	struct k_mem_block mem_block;
	struct mqtt_publish_msg mqtt_publish_msg;
};

struct rpc_schedule {
	const char* method;
	struct rpc_schedule_params {
		int time;
		int s1;
		int s2;
		int s3;
	} params;
};


/* Message Queue and Memory Pool for publish message descriptors and
 * associated JSON payload */
K_MSGQ_DEFINE(msgq, sizeof(struct pub_msg), MAX_PENDING_PUB_MSGS, 4);
K_MEM_POOL_DEFINE(pub_pool, 16, 128, 8, 4);

void handle_fillUpFood(char *json, int json_len)
{
	printf("[%s:%d] parsing: %s\n",	__func__, __LINE__, json);
}

/* Handles receiving time broadcasts*/
void handle_setTime(char *json, int json_len)
{
	printf("[%s:%d] parsing: %s\n",	__func__, __LINE__, json);

		/* JSON RPC params for putLights */
	static const struct json_obj_descr rpc_descr_params[] = {
		JSON_OBJ_DESCR_PRIM(struct rpc_schedule_params, time, JSON_TOK_NUMBER),
		JSON_OBJ_DESCR_PRIM(struct rpc_schedule_params, s1, JSON_TOK_NUMBER),
		JSON_OBJ_DESCR_PRIM(struct rpc_schedule_params, s2, JSON_TOK_NUMBER),
		JSON_OBJ_DESCR_PRIM(struct rpc_schedule_params, s3, JSON_TOK_NUMBER),
	};


/* JSON generic thingsboard.iharacter string pointed to by buf to values which are stored in the tm structure pointed to by tm, using the format specified by format.o RPC */
	static const struct json_obj_descr rpc_descr[] = {
		JSON_OBJ_DESCR_PRIM(struct rpc_schedule, method, JSON_TOK_STRING),
		JSON_OBJ_DESCR_OBJECT(struct rpc_schedule, params, rpc_descr_params)
	};


	struct rpc_schedule rx_rpc={};
	json_obj_parse(json, json_len, rpc_descr, ARRAY_SIZE(rpc_descr), &rx_rpc);

		printf("[%s:%d] parsed method: %s, params: unixTime: %d  s1:%d  s2: %d  s3: %d",
		__func__, __LINE__, rx_rpc.method, rx_rpc.params.time, rx_rpc.params.s1, rx_rpc.params.s2, rx_rpc.params.s3);

		schedule1 = rx_rpc.params.s1;
		schedule2 = rx_rpc.params.s2;
		schedule3 = rx_rpc.params.s3;
	printf("schedule times: %d\n %d\n %d\n", schedule1,schedule2,schedule3);
	setTime(rx_rpc.params.time);
	set_schedules(schedule1, schedule2, schedule3);
}



void handle_updateSchedule(char *json, int json_len)
{
	printf("[%s:%d] parsing: %s\n",	__func__, __LINE__, json);
	char payload[64];
	//ts = time schedule
    char ts1[4];
	char ts2[4];
    char ts3[4];
	for(int i = 0; i<4; i++) {
		ts1[i] = json[i+37];
	}

	for(int j = 0; j<4; j++) {
		ts2[j] = json[j+42];
	}

	for (int k = 0; k<4; k++) {
		ts3[k] = json[k+47];
	}

	set_schedules(atoi(ts1), atoi(ts2), atoi(ts3));

	snprintf(payload, sizeof(payload), "{\"st1\":\"%s\", \"st2\":\"%s\", \"st3\":\"%s\"}", ts1, ts2, ts3);
	printf("test: %d\n %d\n %d", schedule1,schedule2,schedule3);
	tb_publish_telemetry(payload);
}

//Disepnces food ignoring the current weight/schedule
void handle_dispenseFood(char *json, int json_len)
{
	printf("Dispensing quarter\n");
	dispense_quarter();
}

void send_weightTelemetry(int weight)
{
	char payload[32];
	snprintf(payload, sizeof(payload), "{\"weight\":\"%d\"}", weight);
	printf("weight: %d\n", weight);
	tb_publish_telemetry(payload);
}

/*
 * Process an RPC request received from the thingsboard instance
 */
void handle_rpc(char *json, int json_len)
{
	if ( strncmp(&json[11], "fillUpFood", strlen("fillUpFood")) == 0 ) {
		handle_fillUpFood(json, json_len);
	}
	else if ( strncmp(&json[11], "time", strlen("time")) == 0 ) {
		printf("test");
		handle_setTime(json, json_len);
	} 
	else if ( strncmp(&json[11], "updateSchedule", strlen("updateSchedule")) == 0 ) {
		handle_updateSchedule(json, json_len);
	}
	else if ( strncmp(&json[11], "dispenseFood", strlen("dispenseFood")) == 0 ) {
		handle_dispenseFood(json, json_len);
	} 
}

/* The signature of this routine must match the connect callback declared at
 * the mqtt.h header.
 */
static void connect_cb(struct mqtt_ctx *mqtt_ctx)
{
	printf("[%s:%d]\n", __func__, __LINE__);

	k_alert_send(&tb_connack_alert);
}

/* The signature of this routine must match the disconnect callback declared at
 * the mqtt.h header.
 */
static void disconnect_cb(struct mqtt_ctx *mqtt_ctx)
{
	printf("[%s:%d]\n", __func__, __LINE__);

}

/**
 * The signature of this routine must match the publish_tx callback declared at
 * the mqtt.h header.
 *
 * Applications must keep a "message database" with pkt_id's. So far, this is
 * not implemented here. For example, if we receive a PUBREC message with an
 * unknown pkt_id, this routine must return an error, for example -EINVAL or
 * any negative value.
 */
static int publish_tx_cb(struct mqtt_ctx *mqtt_ctx, u16_t pkt_id,
		      enum mqtt_packet type)
{
	const char *str;
	int rc = 0;

	switch (type) {
	case MQTT_PUBACK:
		str = "MQTT_PUBACK";
		break;
	case MQTT_PUBCOMP:
		str = "MQTT_PUBCOMP";
		break;
	case MQTT_PUBREC:
		str = "MQTT_PUBREC";
		break;
	default:
		rc = -EINVAL;
		str = "Invalid MQTT packet";
	}

	printf("[%s:%d] <%s> packet id: %u\n", __func__, __LINE__, str, pkt_id);

	return rc;
}


/**
 * The signature of this routine must match the publish_rx callback declared at
 * the mqtt.h header.
 */
static int publish_rx_cb(struct mqtt_ctx *ctx, struct mqtt_publish_msg *msg,
		  u16_t pkt_id, enum mqtt_packet type)
{
	const char *str;
	int rc = 0;

	/* Received a MQTT message published to a topic to which
	 * we have subscribed. In this case, this will mean an RPC
	 * request originated from our thingsboard instance. */

	switch (type) {
	case MQTT_PUBLISH:
		str = "MQTT_PUBLISH";
		break;
	default:
		rc = -EINVAL;
		str = "Invalid or unsupported MQTT packet";
	}

	msg->msg[msg->msg_len] = 0;

	printf("[%s:%d] <%s> packet id: %u\n    topic: %s\n    payload: %s\n",
		__func__, __LINE__, str, pkt_id, msg->topic, msg->msg);

	/* Pass on for RPC processing */
	handle_rpc(msg->msg, msg->msg_len);

	return rc;
}

static int subscribe_cb(struct mqtt_ctx *ctx, u16_t pkt_id,
		 u8_t items, enum mqtt_qos qos[])
{
	/* Successful subscription to MQTT topic */

	printf("[%s:%d] <%s> packet id: %u\n", __func__, __LINE__, "MQTT_SUBACK", pkt_id);
	return 0;
}


static int unsubscribe_cb(struct mqtt_ctx *ctx, u16_t pkt_id)
{
	printf("[%s:%d] <%s> packet id: %u\n", __func__, __LINE__, "MQTT_UNSUBACK", pkt_id);
	return 0;
}

/**
 * The signature of this routine must match the malformed callback declared at
 * the mqtt.h header.
 */
static void malformed_cb(struct mqtt_ctx *mqtt_ctx, u16_t pkt_type)
{
	printf("[%s:%d] pkt_type: %u\n", __func__, __LINE__, pkt_type);
}

K_THREAD_STACK_DEFINE(pubsub_stack_area, PUBSUB_STACK_SIZE);
struct k_thread pubsub_thread_desc;

/**
 * Thread to manage thingsboard.io communication
 */
void pubsub_thread(void * unused1, void * unused2, void * unused3)
{
	ARG_UNUSED(unused1);
	ARG_UNUSED(unused2);
	ARG_UNUSED(unused3);

	int i, rc;
	char token[BT_ADDR_STR_LEN];
	struct bt_le_oob oob;
	struct pub_msg pub_msg;

	/* Set everything to 0 and later just assign the required fields. */
	memset(&pubsub_ctx, 0x00, sizeof(pubsub_ctx));

	/* connect, disconnect and malformed may be set to NULL */
	pubsub_ctx.mqtt_ctx.connect = connect_cb;

	pubsub_ctx.mqtt_ctx.disconnect = disconnect_cb;
	pubsub_ctx.mqtt_ctx.malformed = malformed_cb;
	pubsub_ctx.mqtt_ctx.publish_tx = publish_tx_cb;
	pubsub_ctx.mqtt_ctx.publish_rx = publish_rx_cb;
	pubsub_ctx.mqtt_ctx.subscribe = subscribe_cb;

	pubsub_ctx.mqtt_ctx.net_init_timeout = APP_NET_INIT_TIMEOUT;
	pubsub_ctx.mqtt_ctx.net_timeout = APP_TX_RX_TIMEOUT;

	pubsub_ctx.mqtt_ctx.peer_addr_str = SERVER_ADDR;
	pubsub_ctx.mqtt_ctx.peer_port = SERVER_PORT;

	/* IMPORTANT: Using the Bluetooth address as the thingsboard.io
	 * ACCESS TOKEN. You MUST configure the ACCESS TOKEN in your
	 * thingsboard.io instance. */
	bt_le_oob_get_local(BT_ID_DEFAULT, &oob);
	bt_addr_to_str(&oob.addr.a, token, sizeof(token));
	pubsub_ctx.connect_msg.user_name = token;

	printf("Connecting with thingsboard.io token: %s\n", token);

	pubsub_ctx.connect_msg.user_name_len = strlen(pubsub_ctx.connect_msg.user_name);

	pubsub_ctx.connect_msg.client_id = MQTT_CLIENTID;
	pubsub_ctx.connect_msg.client_id_len = strlen(MQTT_CLIENTID);

	/* Must be 1 - 0 not yet supported by Zephyr */
	pubsub_ctx.connect_msg.clean_session = 1;

	/* We are both a MQTT APP PUBLISHER and a MQTT APP SUBSCRIBER!! */
	rc = mqtt_init(&pubsub_ctx.mqtt_ctx, MQTT_APP_PUBLISHER_SUBSCRIBER);
	PRINT_RESULT("mqtt_init", rc);

	if (rc != 0) {
		goto exit_pub;
	}

	// To allow us to start wireshark!!!
	k_sleep(10000);

	/* Open a TCP connection to the thingsboard.io instance */
	i = 0;
	do {
		k_sleep(APP_TX_RX_TIMEOUT);
		rc = mqtt_connect(&pubsub_ctx.mqtt_ctx);
		PRINT_RESULT("mqtt_connect", rc);
	} while (rc != 0 && i++ < APP_CONN_TRIES);

	if (rc != 0) {
		goto exit_pub;
	}

	/* Open an MQTT session to the thingsboard.io instance */
	i = 0;
	do {
		rc = mqtt_tx_connect(&pubsub_ctx.mqtt_ctx, &pubsub_ctx.connect_msg);
		PRINT_RESULT("mqtt_tx_connect", rc);
		k_alert_recv(&tb_connack_alert, APP_TX_CONN_TIMEOUT);
	} while (rc == 0 && i++ < APP_TX_CONN_TRIES && !pubsub_ctx.mqtt_ctx.connected);

	if (!pubsub_ctx.mqtt_ctx.connected) {
		mqtt_close(&pubsub_ctx.mqtt_ctx);
		goto exit_pub;
	}

	/* Subscribe to RPC messages (e.g. for LED control). When they arrive, the
	 * RPC requests will appear first in publish_rx_cb(...) and will be passed on
	 * to  handle_rpc(...), which you should customize for your own
	  application requirments. */
	rc = mqtt_tx_subscribe(&pubsub_ctx.mqtt_ctx, sys_rand32_get(), 1,
		TB_RPC_TOPIC, TB_RPC_QOS);

	PRINT_RESULT("mqtt_tx_subscribe", rc);


	/* From here we enter an infinite loop, blocking until we receive a
	 * pub_msg descriptor from another part of the application. Note that
	 * after sending a publish message, we must free the allocated
	 * Zephyr memory pool block. */
	while ((rc = k_msgq_get(&msgq, &pub_msg, K_FOREVER)) == 0) {
		rc = mqtt_tx_publish(&pubsub_ctx.mqtt_ctx, &pub_msg.mqtt_publish_msg);
		k_mem_pool_free(&pub_msg.mem_block);
		PRINT_RESULT("mqtt_tx_publish", rc);
	}

	/* Something has failed if we get to here!!! */

	/* Disconnect */
	rc = mqtt_tx_disconnect(&pubsub_ctx.mqtt_ctx);
	PRINT_RESULT("mqtt_tx_disconnect", rc);

	k_sleep(APP_TX_RX_TIMEOUT);

	/* Close TCP connection */
	rc = mqtt_close(&pubsub_ctx.mqtt_ctx);
	PRINT_RESULT("mqtt_close", rc);

exit_pub:
	printf("\nPublisher terminated!!\n");
}

int prepare_msg(struct pub_msg *pub_msg, const char *topic, const char *payload)
{
	/* allocate a buffer (block) for the message */
	if (k_mem_pool_alloc(&pub_pool, &pub_msg->mem_block, strlen(payload), K_NO_WAIT) == 0)
	{
		/* copy the payload to the allocated buffer */
		strcpy(pub_msg->mem_block.data, payload);

		/* prepare the remainder of the message descriptor */
		pub_msg->mqtt_publish_msg.msg = pub_msg->mem_block.data;
		pub_msg->mqtt_publish_msg.msg_len = strlen(pub_msg->mqtt_publish_msg.msg);
		pub_msg->mqtt_publish_msg.qos = MQTT_QoS0;
		pub_msg->mqtt_publish_msg.topic = topic;
		pub_msg->mqtt_publish_msg.topic_len = strlen(pub_msg->mqtt_publish_msg.topic);
		pub_msg->mqtt_publish_msg.pkt_id = sys_rand32_get();

		return 0;
	} else {
		return -ENOMEM;
	}
}

void tb_publish_attributes(const char * attr_payload)
{
	struct pub_msg pub_msg;
	int rc;

	/* Prepare the pub_msg descriptor for telemetry */
	rc = prepare_msg(&pub_msg, TB_ATTRIBUTES_TOPIC, attr_payload);

	if (rc != 0) {
		PRINT_RESULT("prepare_msg", rc);
		return;
	}

	printf("tb_publish_attributes: %s\n", attr_payload);

	/* Send it to the publish message queue */
	rc = k_msgq_put(&msgq, &pub_msg, K_NO_WAIT);

	/* If we couldn't send it to the message queue, we need to free memory
	 * that was allocated for the JSON payload */

	if (rc != 0) {
		k_mem_pool_free(&pub_msg.mem_block);
		PRINT_RESULT("k_msgq_put", rc);
	}
}

void tb_publish_telemetry(const char * tlmtry_payload)
{
	struct pub_msg pub_msg;
	int rc;

	/* Prepare the pub_msg descriptor for telemetry */
	rc = prepare_msg(&pub_msg, TB_TELEMETRY_TOPIC, tlmtry_payload);

	if (rc != 0) {
		PRINT_RESULT("prepare_msg", rc);
	}

	printf("tb_publish_telemetry: %s\n", pub_msg.mqtt_publish_msg.msg);

	/* Send it to the publish message queue */
	rc = k_msgq_put(&msgq, &pub_msg, K_NO_WAIT);

	/* If we couldn't send it to the message queue, we need to free memory
	 * that was allocated for the JSON payload */
	if (rc != 0) {
		k_mem_pool_free(&pub_msg.mem_block);
		PRINT_RESULT("k_msgq_put", rc);
	}
}

void tb_pubsub_start()
{
	k_tid_t tt_tid = k_thread_create(&pubsub_thread_desc, pubsub_stack_area,
                                 K_THREAD_STACK_SIZEOF(pubsub_stack_area),
                                 pubsub_thread,
                                 NULL, NULL, NULL,
                                 PUBSUB_PRIORITY, 0, K_NO_WAIT);
}
