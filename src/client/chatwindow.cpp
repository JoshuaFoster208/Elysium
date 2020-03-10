#include "chatwindow.h"
#include "ui_chatwindow.h"

/*
 * Constructor:
 * Sets style of the ChatWindow up
 * while making a connection to the server
 */
ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->friendsDisplay->setReadOnly(1);
    ui->outputDisplay->setReadOnly(1);
    ui->inputDisplay->setPlaceholderText("Type here");
    ui->friendsDisplay->setPlaceholderText("Friends list");

    ui->outputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                     "color:white;");
    ui->inputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                    "color:white;"
                                    "border: 1px solid black;");
    ui->friendsDisplay->setStyleSheet("background: rgb(80,80,80);"
                                      "color:white;");
    ui->typingIndicator->setStyleSheet("color:green");

    socket = new SocketManager(this);
    connect(socket->getSocket(), &QTcpSocket::readyRead,this, &ChatWindow::display);
}

void ChatWindow::setUsername(QString u) {
    username = u;
    socket->setUsernameOnServer(username);
}

ChatWindow::~ChatWindow(){
    delete ui;
}
/*
 * Slot function:
 * After typing message in GUI and pressing enter this
 * function is emmited in which it sends the data
 * to the server
 */
void ChatWindow::on_inputDisplay_returnPressed(){
   socket->sendBasicChatMessage(ui->inputDisplay->text());
   ui->inputDisplay->clear();
}
/*
 * Slot function:
 * This slot is emmited when the user clicks on light mode
 * for the menubar of the GUI
 */
void ChatWindow::on_actionLight_mode_triggered(){
    ui->outputDisplay->setStyleSheet("background: white;"
                                     "color:black;");
    ui->inputDisplay->setStyleSheet("background: white;"
                                    "color:black;"
                                    "border: 1px solid black;");
    ui->friendsDisplay->setStyleSheet("background: white;"
                                      "color:black;");

}
/*
 * Slot function:
 * This slot is emmited when the user clicks on dark mode
 * from the menubar of the GUI
 */
void ChatWindow::on_actionDark_mode_triggered() {
    ui->outputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                     "color:white;");
    ui->inputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                    "color:white;"
                                    "border: 1px solid black;");
    ui->friendsDisplay->setStyleSheet("background: rgb(80,80,80);"
                                      "color:white;");
}
/*
 * Slot function:
 * This slot is emmited when there is data avaible to be
 * read from the server. It reads the data and then displays
 * it to the ChatWindow GUI
 */
void ChatWindow::display() {
    std::string holder;
    QString qInput,output;
    holder = socket->readServerData();
    output = QString::fromUtf8(holder.c_str());
    qDebug() << "Incoming message: " + output;
    if(holder == "TI "){
        ui->typingIndicator->setText("Someone's Typing ...");
    }
    else if(holder == "N T"){
        ui->typingIndicator->setText("");
    }
    else{
        qInput = QString::fromUtf8(holder.c_str());
        ui->outputDisplay->append(qInput);
        //ui->typingIndicator->setText("");

    }

}
/*
 * Slot function:
 * This slot is emited when someone is typing but hasn't hit
 * the return key. This sends a protocol to the server in which
 * can be broadcasted to all other clients indicating someone
 * is typing
 */
//void ChatWindow::on_inputDisplay_textChanged(const QString &arg1)
//{
//    qDebug() << "working" + arg1;
//    socket->sendTypingIndicator();

//}

/*
 * Slot function:
 * This slot is emited when someone stops editing or return key is pressed
 * I use hasfocus() to only send messages when someone has stopped typing
 * this will then send a signal to cancel typing indicator
 * hasfocus() returns true when in focused
 */
//void ChatWindow::on_inputDisplay_editingFinished()
//{
//    QString text = ui->inputDisplay->text();
//    text.contains("\n");
//    if(text.contains("\n")){
//       socket->sendBasicChatMessage(ui->inputDisplay->text());
//        ui->inputDisplay->clear();
//    }
//    else{
//        socket->sendNoTypingIndicator();

//    }

//}
/*
 * Slot function:
 * This slot is emited when someone changes cursor position
 * It is being used a notype indicator.
 * when cursorposition reaches 0 signal notype indicator
 */
//Its getting changed when enter key is pressed
void ChatWindow::on_inputDisplay_cursorPositionChanged(int arg1, int arg2)
{
//    if(arg2 == 0 && arg1 != 0){
//        qDebug() << "arg2 == ";
//        qDebug() << arg2;
//        socket->sendNoTypingIndicator();
//    }
     if(arg1 == 0){
        qDebug() << "arg1 == 0";
        socket->sendTypingIndicator();
    }
    qDebug() << arg1 << " " << arg2;

}
