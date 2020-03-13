#ifndef CHATWINDOW_H
#define CHATWINDOW_H
#include <QMainWindow>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTimer>
#include "socketmanager.h"
#include "../core/CoreSettings.h"



namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);

    QString getUsername() {return username;}
    void setUsername(QString u);

    ~ChatWindow();
private slots:
    void on_inputDisplay_returnPressed();
    void on_actionLight_mode_triggered();
    void on_actionDark_mode_triggered();
    void display();
    void on_inputDisplay_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::ChatWindow *ui;
    SocketManager * socket;
    QString username;
    QVector<QString> usersTyping;
    QString updateUsersTyping(CoreSettings::Protocol,std::string);


};

#endif // CHATWINDOW_H
