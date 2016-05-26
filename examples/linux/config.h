#ifndef _CONFIG_H_
#define _CONFIG_H_

/* General configuration */
#define DEBUG

/* MQTT Configuration */
#define MQTT_TOPIC      "electrolink"
#define MQTT_CLIENT_ID  "electrolink-server-c"
#define MQTT_QOS        2
#define MQTT_USERNAME   NULL
#define MQTT_PASSWORD   NULL
#define MQTT_HOST       "test.mosquitto.org"
#define MQTT_PORT       1883

#endif // _CONFIG_H_
