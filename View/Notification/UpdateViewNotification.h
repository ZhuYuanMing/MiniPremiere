#ifndef MINIPREMIERE_UPDATEVIEWNOTIFICATION_H
#define MINIPREMIERE_UPDATEVIEWNOTIFICATION_H

#include <iostream>
#include <memory>
#include "../../common/notification.h"

class MainWindow;

class UpdateViewNotification : public Notification
{
private:
    MainWindow *mainwindow;
public:
    UpdateViewNotification(MainWindow *mainwindow);
    virtual void Exec();
};


#endif //MINIPREMIERE_UPDATEVIEWNOTIFICATION_H
