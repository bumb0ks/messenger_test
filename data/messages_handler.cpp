#include "messages_handler.h"
#include "messages_model.h"

using namespace model;

namespace
{
    const int self_user_id = -1;
}

class MessagesHandler::Impl
{
public:
    int current_user_id = -1;
    MessageInfoPtrListPtr messages;
    QSharedPointer<MessagesModel> currentModel;
};

MessagesHandler::MessagesHandler(QObject *parent) :
    QObject(parent),
    d(new Impl)
{
    d->messages.reset(new MessageInfoPtrList());
}

QSharedPointer<MessagesModel> model::MessagesHandler::getModelForUser(int user_id)
{
    d->current_user_id = user_id;

    MessageInfoPtrListPtr newMessages(new MessageInfoPtrList());

    foreach(MessageInfoPtr messageInfo, *(d->messages.data()))
    {
        if (messageInfo->fromUserId() == user_id || messageInfo->toUserId() == user_id)
            newMessages->append(messageInfo);
    }

    QSharedPointer<MessagesModel> messageModel(new MessagesModel(user_id, newMessages, this));

    d->currentModel = messageModel;

    return messageModel;
}

int MessagesHandler::messagingWith() const
{
    return d->current_user_id;
}

void model::MessagesHandler::onNewMessageReceive(int from_user_id, QString message)
{
    MessageInfoPtr messageInfo(new MessageInfo(from_user_id, ::self_user_id, message));
    d->messages->prepend( messageInfo );
    if (!d->currentModel.isNull() &&
            d->currentModel->messagingWith() == from_user_id)
    {
        d->currentModel->add(messageInfo);
    }
}

void model::MessagesHandler::onNewMessageSend(QString message)
{
    if (d->currentModel.isNull())
        return;

    int to_user_id = d->currentModel->messagingWith();

    MessageInfoPtr messageInfo(new MessageInfo(::self_user_id, to_user_id, message));
    d->messages->prepend( messageInfo );

    if (!d->currentModel.isNull() &&
            d->currentModel->messagingWith() == to_user_id)
    {
        d->currentModel->add(messageInfo);
    }
}
