#include <netinet/in.h>
#include <sys/socket.h>

#include "ClientConnection.h"
#include "Logger.h"
#include "Server.h"
#include "SignalManager.h"

/**
 * This class should represent client connections. Each object should
 * contain identifying data for that client and it's relationship to the server.
 */

ClientConnection::ClientConnection(int socketFd, Server *s) {
    socketFileDescriptor = socketFd;
    server = s;

    setClientConnectionConfiguration();
}


// TODO: Make buffer size configurable
void ClientConnection::setClientConnectionConfiguration() {
}

/**
 * The main send/receive loop between the connected client and server
 */
void ClientConnection::mainClientServerLoop() {

    char buffer[C_BUFFER_SIZE] = {'\0'};

    // TODO: This is where the main conversation between client and server should happen
    // Need to implement functions to respond to client messages
    while (recv(socketFileDescriptor, buffer, sizeof(buffer), 0) != -1
        && !server->getSignalManager()->trappedSignal(SIGPIPE)) {

        send(socketFileDescriptor, "hi", sizeof("hi"), 0 );
    }
    Logger::warn("Client connection failed on recv.. Thread is about to die");
}
