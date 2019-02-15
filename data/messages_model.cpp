#include "messages_model.h"
#include "message_info.h"

#include <QDebug>

using namespace model;

namespace
{
    const int self_user_id = -1;
}

MessagesModel::MessagesModel(int messaging_with_id, MessageInfoPtrListPtr messages, QObject *parent) :
    QAbstractListModel (parent),
    m_messagingWithUserId (messaging_with_id)
{
    if (messages.isNull())
        this->m_data.reset(new MessageInfoPtrList());
    else
        this->m_data = messages;
}

int MessagesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data->size();
}

QVariant MessagesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case MessageRole:
        return QVariant(m_data->at(index.row())->message());
    case ToMeRole:
        return QVariant(m_data->at(index.row())->toUserId() == ::self_user_id);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MessagesModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[MessageRole] = "message";
    roles[ToMeRole] = "toMe";

    return roles;
}

void MessagesModel::add(MessageInfoPtr messageInfo)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_data->prepend(messageInfo);
    endInsertRows();

   QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
   emit dataChanged(index, index);
}

int MessagesModel::messagingWith() const
{
    return m_messagingWithUserId;
}
