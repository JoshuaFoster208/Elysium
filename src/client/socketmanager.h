#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H
#include <QTcpSocket>

class ChatWindow;
class SocketManager
{
public:
    SocketManager(ChatWindow * cw);
    std::string readServerData();
    void sendBasicChatMessage(QString msg);
    QTcpSocket *getSocket();

private:
    QTcpSocket tcpSocket;
    ChatWindow * chatWindow;
    void writeToServer(QString data);
};

#endif // SOCKETMANAGER_H
