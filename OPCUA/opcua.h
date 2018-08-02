#ifndef OPCUA_H
#define OPCUA_H

#include <QObject>
#include "open62541.h"
#include <QTimer>

class opcua : public QObject
{
    Q_OBJECT
public:
    static opcua &shared_instance() {static opcua OPCUA; return OPCUA;}


    void stopHandler(int sign);
    static void addUarmObject(UA_Server *server);
    static void addUarmMethod(UA_Server *server);
    static UA_StatusCode car2Callback(UA_Server *server, const UA_NodeId *sessionId, void *sessionHandle, const UA_NodeId *methodId, void *methodContext, const UA_NodeId *objectId, void *objectContext, size_t inputSize, const UA_Variant *input, size_t outputSize, UA_Variant *output);
    static UA_StatusCode car1Callback(UA_Server *server, const UA_NodeId *sessionId, void *sessionHandle, const UA_NodeId *methodId, void *methodContext, const UA_NodeId *objectId, void *objectContext, size_t inputSize, const UA_Variant *input, size_t outputSize, UA_Variant *output);
    UA_Boolean m_running = true;
signals:
     void publish(QString);
     void publishTopic(QString,QString);
public slots:
    void opcua_thread();
private:
    explicit opcua(QObject *parent = 0);
     ~opcua();
    UA_ServerConfig *config;
    UA_Server *server;


};

#endif // OPCUA_H
