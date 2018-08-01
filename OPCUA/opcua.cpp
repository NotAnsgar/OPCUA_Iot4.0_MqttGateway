#include "opcua.h"


opcua::opcua(QObject *parent) : QObject(parent)
{

    config = UA_ServerConfig_new_default();
    server = UA_Server_new(config);

    addUarmObject(server);

}

opcua::~opcua()
{
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
}

void opcua::opcua_thread()
{
    UA_StatusCode retval = UA_Server_run(server, &m_running);

    QTimer::singleShot(100, this, SLOT(opcua_thread()));
}

/*----------------------------OPCUA---------------------------------------*/
UA_StatusCode opcua::car1Callback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {

    UA_String tmp = UA_STRING_ALLOC("mode1");

    /*add UARM communication*/
    //system("mosquitto_pub -h localhost -m 1 -t /production/order");
    //client.publish("/production/order","1", sizeof("1"));

    UA_Variant_setScalarCopy(output, &tmp, &UA_TYPES[UA_TYPES_STRING]);
    UA_String_deleteMembers(&tmp);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "car 1 in production");
    //emit publishTopic("1","UARM");
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
opcua::car2Callback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {
    UA_String tmp = UA_STRING_ALLOC("mode2");

    /*add UARM communication*/
    //system("mosquitto_pub -h localhost -m 2 -t /production/order");
    //client.publish("/production/order","2", sizeof("2"));

    UA_Variant_setScalarCopy(output, &tmp, &UA_TYPES[UA_TYPES_STRING]);
    UA_String_deleteMembers(&tmp);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "car 2 in production");
    //emit publishTopic("2","UARM");
    return UA_STATUSCODE_GOOD;
}

void opcua::addUarmMethod(UA_Server *server) {

    // Input Arguments
    UA_Argument inputArguments;
    UA_Argument_init(&inputArguments);
    inputArguments.arrayDimensionsSize = 0;
    inputArguments.arrayDimensions = NULL;
    inputArguments.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    inputArguments.description = UA_LOCALIZEDTEXT("en_US", "A String");
    inputArguments.name = UA_STRING("MyInput");
    inputArguments.valueRank = -1;

    // Output Arguments
    UA_Argument outputArguments;
    UA_Argument_init(&outputArguments);
    outputArguments.arrayDimensionsSize = 0;
    outputArguments.arrayDimensions = NULL;
    outputArguments.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    outputArguments.description = UA_LOCALIZEDTEXT("en_US", "A String");
    outputArguments.name = UA_STRING("MyOutput");
    outputArguments.valueRank = -1;

    // Attributes
    UA_MethodAttributes incAttr;
    UA_MethodAttributes_init(&incAttr);
    incAttr.description = UA_LOCALIZEDTEXT("en_US", "Move UARM");
    incAttr.displayName = UA_LOCALIZEDTEXT("en_US", "Move UARM");
    incAttr.executable = true;
    incAttr.userExecutable = true;

    // Add MethodNode to UARM object
    UA_Server_addMethodNode(server, UA_NODEID_STRING(1, "car1"),
                            UA_NODEID_STRING(1, "UARM"),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                            UA_QUALIFIEDNAME(1, "car1"),
                            incAttr, &car1Callback,
                            1, &inputArguments, 1, &outputArguments, NULL, NULL);

    // Add MethodNode to UARM object
    UA_Server_addMethodNode(server, UA_NODEID_STRING(1, "car2"),
                            UA_NODEID_STRING(1, "UARM"),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                            UA_QUALIFIEDNAME(1, "car2"),
                            incAttr, &car2Callback,
                            1, &inputArguments, 1, &outputArguments, NULL, NULL);
}

void opcua::addUarmObject(UA_Server *server) {
    const UA_NodeId uarmNodeId =  UA_NODEID_STRING(1, "UARM");
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "UARM");
    UA_Server_addObjectNode(server, uarmNodeId,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "UARM"),UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, NULL);
    addUarmMethod(server);
}



