#include "UpdateViewNotification.h"
#include "../MainWindow.h"

UpdateViewNotification::UpdateViewNotification(MainWindow *mainwindow):
    Notification()
{
    this->mainwindow = mainwindow;
}

void UpdateViewNotification::Exec()
{
    mainwindow->UpdateQImage();
}