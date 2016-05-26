OBJ_DIR = ./obj

PAHO_CORE = ../../src/paho.mqtt.embedded-c/MQTTPacket/src/
PAHO_CLIENT = ../../src/paho.mqtt.embedded-c/MQTTClient-C/src/
PAHO_PORT = ./mqtt/

JSMN_CORE = ../../src/jsmn/
RM := rm -rf

TARGET = electrolink-server
CFLAGS =  -pipe -std=gnu99 -Wall -O2 

# Includes
INCLUDE_DIRS = -I"./" -I"$(PAHO_CORE)" -I"$(PAHO_PORT)" -I"$(JSMN_CORE)"


.PHONY: all
# All Target
make:
	-if [ ! -d "$(OBJ_DIR)" ]; then mkdir "$(OBJ_DIR)"; fi
	-sed -e 's/""/"MQTTLinux.h"/g' $(PAHO_CLIENT)/MQTTClient.h > $(PAHO_PORT)/MQTTClient.h
	-cp $(PAHO_CLIENT)/MQTTClient.c $(PAHO_PORT)/MQTTClient.c
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) ./electrolink.c -o $(OBJ_DIR)/electrolink.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_PORT)/MQTTClient.c -o $(OBJ_DIR)/MQTTClient.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_PORT)/MQTTLinux.c -o $(OBJ_DIR)/MQTTLinux.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_CORE)/MQTTFormat.c -o $(OBJ_DIR)/MQTTFormat.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_CORE)/MQTTPacket.c -o $(OBJ_DIR)/MQTTPacket.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_CORE)/MQTTDeserializePublish.c -o $(OBJ_DIR)/MQTTDeserializePublish.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_CORE)/MQTTConnectClient.c -o $(OBJ_DIR)/MQTTConnectClient.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_CORE)/MQTTSubscribeClient.c -o $(OBJ_DIR)/MQTTSubscribeClient.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_CORE)/MQTTSerializePublish.c -o $(OBJ_DIR)/MQTTSerializePublish.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_CORE)/MQTTConnectServer.c -o $(OBJ_DIR)/MQTTConnectServer.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_CORE)/MQTTSubscribeServer.c -o $(OBJ_DIR)/MQTTSubscribeServer.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_CORE)/MQTTUnsubscribeServer.c -o $(OBJ_DIR)/MQTTUnsubscribeServer.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(PAHO_CORE)/MQTTUnsubscribeClient.c -o $(OBJ_DIR)/MQTTUnsubscribeClient.o
	$(CC) -c $(INCLUDE_DIRS) $(CFLAGS) $(JSMN_CORE)/jsmn.c -o $(OBJ_DIR)/jsmn.o
	$(CC) -o $(TARGET) $(OBJ_DIR)/*.o 

# Other Targets
clean:
	-$(RM) $(OBJS) $(TARGET) $(OBJ_DIR)
	-$(RM) $(PAHO_PORT)/MQTTClient.*
	-@echo ' '
