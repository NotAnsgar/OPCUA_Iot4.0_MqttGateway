#include "mqtt.h"
#include <QDebug>
#include <QCoreApplication>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <QTimer>

Mqtt::Mqtt(QObject *parent) : QObject(parent)
{
    mosquitto_lib_init();
    mqtt_setup();
    mosquitto_subscribe(mosq, NULL, "/dev/", 0);
}

Mqtt::~Mqtt()
{
   mosquitto_lib_cleanup();
}


void Mqtt::mqtt_setup(){

    char *host = "localhost";
    int port = 1883;
    int keepalive = 60;
    bool clean_session = true;
    topic = "/testtopic";
    mosq = mosquitto_new(NULL, clean_session, NULL);
  if(!mosq){
        fprintf(stderr, "Error: Out of memory.\n");
        exit(1);
    }

  mosquitto_log_callback_set(mosq, mosq_log_callback);
  mosquitto_connect_callback_set(mosq, connect_callback);
  mosquitto_message_callback_set(mosq, message_callback);

  if(mosquitto_connect(mosq, host, port, keepalive)){
        fprintf(stderr, "Unable to connect.\n");
        exit(1);
    }
  int loop = mosquitto_loop_start(mosq);
  if(loop != MOSQ_ERR_SUCCESS){
    fprintf(stderr, "Unable to start loop: %i\n", loop);
    exit(1);
  }
}

void Mqtt::mqtt_thread()
{
//    int rc=0;
//    rc = mosquitto_loop(mosq, -1, 1);
//    if(rc){
//        printf("connection error!\n");
//        mosquitto_reconnect(mosq);
//    }

    QTimer::singleShot(100, this, SLOT(mqtt_thread()));
}

void Mqtt::message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    bool match = 0;
    printf("got message '%.*s' for topic '%s'\n", message->payloadlen, (char*) message->payload, message->topic);
}

void Mqtt::connect_callback(struct mosquitto *mosq, void *obj, int result)
{
    printf("connect callback, rc=%d\n", result);
}

void Mqtt::mosq_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
    /* Pring all log messages regardless of level. */

  switch(level){
    //case MOSQ_LOG_DEBUG:
    //case MOSQ_LOG_INFO:
    //case MOSQ_LOG_NOTICE:
    case MOSQ_LOG_WARNING:
    case MOSQ_LOG_ERR: {
      printf("%i:%s\n", level, str);
    }
  }


}

int Mqtt::mqtt_send(QString msg){
  return mosquitto_publish(mosq, NULL, topic, msg.toStdString().length(), (char*) msg.toStdString().c_str(), 0, 0);

}

int Mqtt::mqtt_send_topic(QString msg, QString topic){
  return mosquitto_publish(mosq, NULL, (char*) topic.toStdString().c_str(), msg.toStdString().length(), (char*) msg.toStdString().c_str(), 0, 0);
}
