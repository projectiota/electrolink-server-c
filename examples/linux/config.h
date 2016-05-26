/*   
   Copyright 2016 electrolink-server-c

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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
