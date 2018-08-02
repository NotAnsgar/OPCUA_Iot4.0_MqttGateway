#include <iostream>
#include "open62541.h"

using namespace std;

int main(int argc, char *argv[])
{
    /* create a client and connect */
    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return retval;
    }
    UA_Variant input;
    UA_String argString = UA_STRING("Hello Server");
    UA_Variant_init(&input);
    UA_Variant_setScalarCopy(&input, &argString, &UA_TYPES[UA_TYPES_STRING]);
    size_t outputSize;
    UA_Variant *output;
    retval = UA_Client_call(client, UA_NODEID_STRING(1, "UARM"), UA_NODEID_STRING(1, "car2"), 1, &input, &outputSize, &output);
    UA_Variant_deleteMembers(&input);
}
