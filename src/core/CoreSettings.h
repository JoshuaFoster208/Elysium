#ifndef ELYSIUM_SERVER_CORESETTINGS_H
#define ELYSIUM_SERVER_CORESETTINGS_H


#include "../server/Server.h"

class CoreSettings {
public:

    CoreSettings(Server *s);

    enum ConfigEnvironment {
        DanielDev, ErickDev, JoshDev, NickDev, SebastianDev, Production
    };

    /* This enumeration can contain a maximum of 256 possible 
     * flags/indicators to use in communicating special operations to/from
     * the server
     */
    enum Protocol {
        NoOperation,
        ServerBroadcastMessage,
        ClientNormalMessage,
        ServerSetUsername,
        TypingIndicator,
        NoTyping,
        ServerRequestOnlineStatus,
        ClientReceiveOnlineStatus,
        ServerRequestAuthentication,
        ClientAcceptAuthentication,
        ClientRejectAuthentication
    };

    std::string getHostName();
    int getPortNumber();

private:
    Server * server;
    ConfigEnvironment env;

    void setConfigEnvironment();
};


#endif //ELYSIUM_SERVER_CORESETTINGS_H
