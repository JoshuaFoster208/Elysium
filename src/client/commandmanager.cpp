#include <QList>
#include "commandmanager.h"
#include "chatwindow.h"
#include "notificationmanager.h"
#include "soundmanager.h"


CommandManager::CommandManager(ChatWindow * cw, SocketManager * s, SoundManager * sm) {

    /* Set pointers back to the ChatWindow and SocketManager */
    chatWindow = cw;
    socket = s;
    soundManager = sm;
}


/**
 * Master function called when the Socket object emits a signal indicating
 * data has been received from the server. 
 *
 * Analyzes and trims the first byte of the incoming message branches
 * to an appropriate response function based on the Protocol enumeration
 * detected.
 */
void CommandManager::handleIncomingMessage() {
    std::string temp;
    QString qInput,userName;
    
    /* Read data received from server */
    temp = socket->readServerData();

    /* Get the first byte and use its value to index in to the Protocol enum */
    CoreSettings::Protocol response = static_cast<CoreSettings::Protocol>(temp[0]);

    /* Strip the Protocol enum from the receieved data */
    temp = temp.substr(1);
    
    /* Branch against the Protocol enum */
    switch (response){
        
        /* ServerBroadcastMessage enums indicate a regular chat message, display it to
         * the ChatWindow with a CommandManager wrapper around a ChatWindow function display() */
        case CoreSettings::Protocol::ServerBroadcastMessage:

            /* Scan the message for a '@' user mention */
            chatWindow->getNotificationManager()->detectUserMention(QString::fromUtf8(temp.c_str()));

            addIncomingMessageToChat(QString::fromUtf8(temp.c_str()));
            break;

        /* Both typing indicators get channeled through chatWindow->setUsersTyping() */
        case CoreSettings::Protocol::TypingIndicator:
        case CoreSettings::Protocol::NoTyping:
            chatWindow->setUsersTypingLabel(response, temp);
            break;

        /* Online status list received */
        case CoreSettings::Protocol::ClientReceiveOnlineStatus:
            updateOnlineUserlist(QString::fromUtf8(temp.c_str()));
            break;

        default:
            break;
    }
}


/** 
 * Wrapper around a ChatWindow function
 *
 * @param msg - Message to be displayed in the ChatWindow
 */
void CommandManager::addIncomingMessageToChat(QString msg) {
    soundManager->newMessage();
    chatWindow->display(msg);
}


/**
 * Gets the comma separated list of usernames received from
 * the server and explodes them into a QStringList. 
 *
 * If there are usernames in the list, ChatWindow updates
 * the UI with its contents
 */
void CommandManager::updateOnlineUserlist(QString userlistString) {
    QStringList userlist = userlistString.split(",");
    if (!userlist.empty()) {
        chatWindow->setOnlineUserList(userlist);
    }
}
/**
 * Updatest the sound settings for the user. Additional
 * options may be added for @ mentions and different sounds.
 */
void CommandManager::updateSoundSettings(bool onOff){
    soundManager->setSoundSetting(onOff);
}