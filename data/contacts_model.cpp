#include "contacts_model.h"

using namespace model;

ContactsModel::ContactsModel(UserInfoPtrListPtr data, QObject* parent) :
    QAbstractListModel (parent)
{
    this->m_data = data;
}

int ContactsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data->size();
}

QVariant ContactsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case PhoneRole:
        return QVariant(m_data->at(index.row())->phone());
    case UserIdRole:
        return QVariant(m_data->at(index.row())->userId());
    case OnlineRole:
        return QVariant(m_data->at(index.row())->online());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ContactsModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[PhoneRole] = "phone";
    roles[UserIdRole] = "userId";
    roles[OnlineRole] = "online";

    return roles;
}

int ContactsModel::getUserIdByIndex(int index) const
{
    return m_data->at(index)->userId();
}

void ContactsModel::onNewUserStatus(int user_id, bool status)
{
    int i;
    bool found = false;
    for (i = 0; i < m_data->size(); i++)
    {
        UserInfoPtr tmpUserInfo = (*(m_data.data()))[i];
        if (tmpUserInfo->userId() == user_id)
        {
            found = true;
            tmpUserInfo->setOnline(status);
            break;
        }
    }

    if (found)
    {
        QModelIndex index = createIndex(i, 0, static_cast<void *>(0));
        emit dataChanged(index, index);
    }
    else
    {
        beginInsertRows(QModelIndex(), m_data->size(), m_data->size());
        m_data->prepend(UserInfoPtr(new UserInfo("", user_id, status)));
        endInsertRows();

       QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
       emit dataChanged(index, index);
    }
}
