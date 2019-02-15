#ifndef MESSAGES_HANDLER_H
#define MESSAGES_HANDLER_H

#include <QObject>
#include <QAbstractListModel>
#include "message_info.h"
#include "messages_model.h"

/*
 * Обработчик который будет прнинимать и хранить в себе все сообщения
 * По требованию выдавать историю сообщений с определенным пользователем
 */

namespace model
{
    class MessagesHandler : public QObject
    {
        Q_OBJECT
    public:
        explicit MessagesHandler(QObject *parent = nullptr);

        QSharedPointer<MessagesModel> getModelForUser(int user_id);

    public:
        int messagingWith() const;

    public slots:
        void onNewMessageReceive(int from_user_id, QString message);
        void onNewMessageSend(QString message);

    private:
        class Impl;
        QScopedPointer<Impl> d;
    };
}

#endif // MESSAGES_HANDLER_H
