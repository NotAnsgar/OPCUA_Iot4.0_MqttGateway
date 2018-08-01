#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QQmlContext>

#include "Mqtt/mqtt.h"
#include "OPCUA/opcua.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

    void registerMetaTypes();
    void setContextProperty(QQmlContext context);
    void settingupOPCUA();
    void settingupMQTT();
    static void stopHandler(int sign);
signals:

public slots:

private:
    opcua* m_opcua;
    QThread* m_opcuaThread;
    Mqtt* m_mqtt;
    QThread* m_mqttThread;
};

#endif // CONTROLLER_H
