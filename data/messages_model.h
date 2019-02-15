#ifndef MESSAGES_MODEL_H
#define MESSAGES_MODEL_H

#include <QAbstractListModel>
#include "message_info.h"

/*
 * Модель сообений
 */

namespace model
{
    class MessagesModel : public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum Roles {
            MessageRole = Qt::UserRole + 1,
            ToMeRole
        };

        MessagesModel(int messaging_with_id, MessageInfoPtrListPtr messages, QObject* parent);

        virtual int rowCount(const QModelIndex &parent) const;
        virtual QVariant data(const QModelIndex &index, int role) const;
        virtual QHash<int, QByteArray> roleNames() const;

        void add(MessageInfoPtr messageInfo);

        int messagingWith() const;

    private:
        int m_messagingWithUserId;
        MessageInfoPtrListPtr m_data;
    };
}

#endif // MESSAGES_MODEL_H
