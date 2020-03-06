#include "CommandManager.h"

#include <utility>
#include "Server.h"

CommandManager::CommandManager(Server * s) {
    server = s;
}


/**
 * This function should handle all incoming messages from the client and
 * determine the correct response to send back.
 */
void CommandManager::handleMessageAndResponse(std::string msg) {

    /* Store the incoming client message to class member variable */
    incomingMessage = std::move(msg);

    /* Analyze the message to determine the correct server response */
    CoreSettings::Protocol response = determineServerResponse();

    /* Use this switch to form and send the correct server response */
    switch (response) {
        case CoreSettings::Protocol::ServerBroadcastMessage:
            sendNormalMessageToAllClients();
        case CoreSettings::Protocol::NoOperation:
        default:
            break;
    }
}

CoreSettings::Protocol CommandManager::determineServerResponse() {

    /* Pluck the first character of the message and use the byte value
     * to index into the CoreSettings::Protocol enumeration to determine
     * the intended effect of the message */
    return static_cast<CoreSettings::Protocol>(incomingMessage[0]);
}


void CommandManager::sendNormalMessageToAllClients() {
    server->broadcastMessage(incomingMessage);
}

