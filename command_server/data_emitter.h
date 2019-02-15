#ifndef DATA_EMITTER_H
#define DATA_EMITTER_H

#include <QObject>

#include "data/user_info.h"

/*
    DataEmmiter - хранится указателем в CommandServer, содержит набор
        сигналов и получении новых пакетов/данных.
*/

namespace model
{
    class DataEmitter : public QObject
    {
        Q_OBJECT
    public:
        DataEmitter(QObject* parent);

    signals:
        void newHello();
        void newRequestCode(QString token);
        void newRequestJwt(QString jwt);
        void newPresence();
        void newUserStatus(int user_id, bool online);
        void newContacts(UserInfoPtrListPtr contactList);
        void newSendMessage();
        void newNewMessage(int user_id, QString message);
    };
}

#endif // DATA_EMITTER_H
