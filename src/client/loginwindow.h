#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "chatwindow.h"

namespace Ui {
class LoginWindow;
}

class CoreSettings;
class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
    ChatWindow *chatGui;
    CoreSettings * coreSettings;
void demoConnectToServer();

};

#endif // LOGINWINDOW_H
