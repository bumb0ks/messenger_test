#ifndef MESSAGE_INFO_H
#define MESSAGE_INFO_H

#include <QSharedPointer>
#include <QString>

/*
 * Информация о сообщении
 */

namespace model {

    class MessageInfo
    {
    public:
        MessageInfo(int from_user_id, int to_user_id, QString message);

        int fromUserId() const;
        int toUserId() const;
        QString message() const;

    private:
        int m_from_user_id;
        int m_to_user_id;
        QString m_message;
    };

    typedef QSharedPointer<MessageInfo> MessageInfoPtr;
    typedef QList<MessageInfoPtr> MessageInfoPtrList;
    typedef QSharedPointer<MessageInfoPtrList> MessageInfoPtrListPtr;

}

#endif // MESSAGE_INFO_H
