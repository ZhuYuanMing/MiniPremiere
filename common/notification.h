#ifndef NOTIFICATION_H
#define NOTIFICATION_H

class Notification
{
public:
    Notification(){};
    virtual void Exec() = 0;
};

#endif //NOTIFICATION_H