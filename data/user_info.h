#ifndef USER_INFO_H
#define USER_INFO_H

#include <QSharedPointer>
#include <QString>

/*
 * Информация о контакте
 */

namespace model
{
    class UserInfo
    {
    public:
        UserInfo(QString phone, int user_id, bool online);

        QString phone() const;
        int userId() const;
        bool online() const;

        void setOnline(bool status);

    private:
        QString m_phone;
        int m_user_id;
        bool m_online;
    };

    typedef QSharedPointer<UserInfo> UserInfoPtr;
    typedef QList<UserInfoPtr> UserInfoPtrList;
    typedef QSharedPointer<UserInfoPtrList> UserInfoPtrListPtr;
}

#endif // USER_INFO_H
