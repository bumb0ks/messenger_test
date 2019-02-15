#ifndef CONTACTS_MODEL_H
#define CONTACTS_MODEL_H

#include <QAbstractListModel>
#include "user_info.h"

/*
 * Модель для контактов
 */

namespace model
{
    class ContactsModel : public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum Roles {
            PhoneRole = Qt::UserRole + 1,
            UserIdRole,
            OnlineRole
        };

        ContactsModel(UserInfoPtrListPtr data, QObject* parent = nullptr);

        virtual int rowCount(const QModelIndex &parent) const;
        virtual QVariant data(const QModelIndex &index, int role) const;
        virtual QHash<int, QByteArray> roleNames() const;

        int getUserIdByIndex(int index) const;

    public slots:
        void onNewUserStatus(int user_id, bool status);

    private:
        UserInfoPtrListPtr m_data;
    };

}

#endif // CONTACTS_MODEL_H
