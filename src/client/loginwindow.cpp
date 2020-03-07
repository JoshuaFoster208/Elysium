#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "chatwindow.h"
#include <QMessageBox>
/*
 * Constructor:
 * Constructs the object for use
 */
LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}
/*
 * Destructor:
 * Delete the object
 */
LoginWindow::~LoginWindow(){
    delete ui;
}

/*
 * Slot function:
 * When the enter button is pressed on the
 * LoginWindow GUI it checks that username
 * and password match and then will open
 * ChatWindow upon success
 */
void LoginWindow::on_pushButton_clicked(){

    /* Need to enter a username to initiate connection to server */
    if (ui->lineEdit_username->text().length()) {
        chatGui = new ChatWindow(this);
        chatGui->setUsername(ui->lineEdit_username->text());
        chatGui->show();

        this->hide();
    }
    else {
        ui->lineEdit_username->setStyleSheet(ui->lineEdit_username->styleSheet()
                                             + "border: 1px solid red;");
        QMessageBox alert;
        alert.setText("Please set a username!");
        alert.exec();
    }
}
