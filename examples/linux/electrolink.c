#include <stdio.h>
#include <signal.h>
#include <memory.h>
#include <sys/time.h>

#include "config.h"
#include "MQTTClient.h"
#include "jsmn.h"

volatile int toStop = 0;

void cfinish(int sig)
{
    signal(SIGINT, NULL);
    toStop = 1;
}

// Should be defined in a config file somewhere.
struct opts_struct
{
    char* clientid;
    int nodelimiter;
    char* delimiter;
    enum QoS qos;
    char* username;
    char* password;
    char* host;
    int port;
} opts =
{
    (char*)MQTT_CLIENT_ID, 0, (char*)"\n", MQTT_QOS, MQTT_USERNAME, MQTT_PASSWORD,
    (char*)MQTT_HOST, MQTT_PORT
};
// TODO need an interface to jsnm
static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
    if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
            strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
    return -1;
}

// TODO need an interface to the low level function
void pinMode(void) {
    printf("This is the pinMode function");
}

// TODO -> move to the jsmn interface. fName to reconsider
int parse_frame(char* str, uint8_t len) {
    int r;
    int i;
    jsmn_parser p;
    jsmntok_t t[16];

    char key[30];

    jsmn_init(&p);
    r = jsmn_parse(&p, str, len, t, sizeof(t)/sizeof(t[0]));
#ifdef DEBUG
    printf("Json object size : %d\n", r);
#endif

    if (r < 1 || t[0].type != JSMN_OBJECT) {
#ifdef DEBUG
        printf("Object expected\n");
#endif
        return 1;
    }

    for (i = 1; i < r; i++) {
        if (jsoneq(str, &t[i], "jsonrpc") == 0) {
#ifdef DEBUG
            printf("JSON-RPC: %.*s\n", t[i+1].end-t[i+1].start,
                    str + t[i+1].start);
#endif
            i++;
        } else if (jsoneq(str, &t[i], "method") == 0) {
#ifdef DEBUG
            printf("Method: %.*s\n", t[i+1].end-t[i+1].start,
                    str + t[i+1].start);
#endif
            strncpy(key, str + t[i+1].start, t[i+1].end-t[i+1].start);
#ifdef DEBUG
            printf("Key : %s\n", key);
#endif
            i++;
        } else if (jsoneq(str, &t[i], "params") == 0) {
            int j;
#ifdef DEBUG
            printf("- Parameters :\n");
#endif
            if (t[i+1].type != JSMN_ARRAY) {
                continue; 
            }
            for (j = 0; j < t[i+1].size; j++) {
                // XXX Assign these values
                jsmntok_t *g = &t[i+j+2];
                // TODO Need to find something better than atoi().
                // Why primitive type return a string ? Need to check
#ifdef DEBUG
                printf(" %d\n", atoi(str + g->start));
#endif
            }
            i += t[i+1].size + 1;
        } else {
#ifdef DEBUG
            printf("Unexpected key: %.*s\n", t[i].end-t[i].start,
                    str + t[i].start);
#endif
        }
    }
    return 0;
}

void messageArrived(MessageData* md)
{
    MQTTMessage* message = md->message;
    uint8_t plen = (uint8_t)message->payloadlen;
    char* pdata = message->payload;
#ifdef DEBUG
    printf("Received frame :\n %s\n", pdata);
#endif
    parse_frame(pdata, plen);
}


int main(int argc, char** argv)
{
	int rc = 0;
	unsigned char buf[100];
	unsigned char readbuf[100];
	
#ifdef MQTT_TOPIC
	char* topic = MQTT_TOPIC;
#else
#error "MQTT_TOPIC must be defined in config.h"
#endif
        //argv[1];
        // XXX DEBUG
	printf("topic is %s\n", topic);

	Network n;
	Client c;

        // XXX
	signal(SIGINT, cfinish);
	signal(SIGTERM, cfinish);

	NewNetwork(&n);
	ConnectNetwork(&n, opts.host, opts.port);
	MQTTClient(&c, &n, 1000, buf, 100, readbuf, 100);
 
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;       
	data.willFlag = 0;
	data.MQTTVersion = 3;
	data.clientID.cstring = opts.clientid;
	data.username.cstring = opts.username;
	data.password.cstring = opts.password;

	data.keepAliveInterval = 10;
	data.cleansession = 1;
        // XXX DEBUG
	printf("Connecting to %s %d\n", opts.host, opts.port);
	
	rc = MQTTConnect(&c, &data);
        // XXX DEBUG
	printf("Connected %d\n", rc);
        printf("Subscribing to %s\n", topic);
	rc = MQTTSubscribe(&c, topic, opts.qos, messageArrived);
        // XXX DEBUG
	printf("Subscribed %d\n", rc);

	while (!toStop)
	{
		MQTTYield(&c, 1000);	
	}
	// XXX DEBUG
	printf("Stopping\n");

	MQTTDisconnect(&c);
	n.disconnect(&n);

	return 0;
}


