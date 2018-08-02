#include "controller.h"
#include <signal.h>

Controller::Controller(QObject *parent) : QObject(parent)
{
settingupOPCUA();
settingupMQTT();
signal(SIGINT, stopHandler);
signal(SIGTERM, stopHandler);
}

void Controller::registerMetaTypes()
{

}

void Controller::setContextProperty(QQmlContext context)
{

}

void Controller::settingupOPCUA()
{
    m_opcuaThread = new QThread;
    m_opcua = &opcua::shared_instance();
    m_opcua->moveToThread(m_opcuaThread);

   connect(m_opcuaThread, SIGNAL(started()), m_opcua, SLOT(opcua_thread()));
//    connect(m_opcua, SIGNAL(finished()), m_opcuaThread, SLOT(quit()));
//    connect(m_opcua, SIGNAL(finished()), m_opcua, SLOT(deleteLater()));
    connect(m_opcuaThread, SIGNAL(finished()), m_opcuaThread, SLOT(deleteLater()));
    m_opcuaThread->start();

}

void Controller::settingupMQTT()
{
    m_mqttThread = new QThread;
    m_mqtt = new Mqtt();
    m_mqtt->moveToThread(m_mqttThread);

    connect(m_mqttThread, SIGNAL(started()), m_mqtt, SLOT(mqtt_thread()));
    connect(m_opcua, SIGNAL(publish(QString)), m_mqtt, SLOT(mqtt_send(QString)));
    connect(m_opcua, SIGNAL(publishTopic(QString,QString)), m_mqtt, SLOT(mqtt_send_topic(QString, QString)));
    connect(m_mqttThread, SIGNAL(finished()), m_mqttThread, SLOT(deleteLater()));

    m_mqttThread->start();

}

void Controller::stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    //m_opcua->m_running = false;
}
