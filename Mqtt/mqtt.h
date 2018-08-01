#ifndef MQTT_H
#define MQTT_H

#include <QObject>
#include <QString>
#include <mosquitto.h>
#include <mosquittopp.h>

class Mqtt : public QObject
{
    Q_OBJECT
public:
    explicit Mqtt(QObject *parent = 0);
    ~Mqtt();


    void mqtt_setup();
    static void mosq_log_callback(mosquitto *mosq, void *userdata, int level, const char *str);
    static void connect_callback(mosquitto *mosq, void *obj, int result);
    static void message_callback(mosquitto *mosq, void *obj, const mosquitto_message *message);
signals:

public slots:
    void mqtt_thread();
    int mqtt_send_topic(QString msg, QString topic);
    int mqtt_send(QString msg);

private:
    struct mosquitto *mosq = NULL;
    char *topic = NULL;

};

#endif // MQTT_H
