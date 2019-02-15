#include "messenger_screen_presenter.h"
#include "command_server/commands_traits.h"

#include "data/contacts_model.h"
#include "data/messages_handler.h"

#include <QQuickView>

using namespace presentation;

using namespace model;

class MessengerScreenPresenter::Impl
{
public:
    CommandServerPtr commandServer;
    QScopedPointer<ContactsModel> contactsModel;
    QScopedPointer<MessagesHandler> messagesHandler;
};

MessengerScreenPresenter::MessengerScreenPresenter(model::CommandServerPtr commandServer, QObject *parent) :
    AbstractPresenter (parent),
    d(new Impl)
{
    d->commandServer = commandServer;

    d->messagesHandler.reset( new MessagesHandler(this) );
}

void MessengerScreenPresenter::connectView()
{
    connect(this->view(), SIGNAL(selectedContactChanged(int)),
            this, SLOT(onSelectedContactChanged(int)));
    connect(this->view(), SIGNAL(sendMessage(QString)),
            this, SLOT(onSendMessage(QString)));

    connect(d->commandServer->getDataEmitter(), SIGNAL(newContacts(UserInfoPtrListPtr)),
            this, SLOT(onNewContactList(UserInfoPtrListPtr)));
    connect(d->commandServer->getDataEmitter(), SIGNAL(newNewMessage(int, QString)),
            d->messagesHandler.data(), SLOT(onNewMessageReceive(int,QString)));

    d->commandServer->execute(new model::ContactsCommandHandler());
}

void MessengerScreenPresenter::onNewContactList(UserInfoPtrListPtr contactList)
{
    d->contactsModel.reset( new ContactsModel(contactList, this) );

    connect(d->commandServer->getDataEmitter(), SIGNAL(newUserStatus(int,bool)),
            d->contactsModel.data(), SLOT(onNewUserStatus(int,bool)));

    this->setProperty("contactsModel", QVariant::fromValue(d->contactsModel.data()));
}

void MessengerScreenPresenter::onSelectedContactChanged(int user_id)
{
    this->setProperty("messagesModel", QVariant::fromValue(d->messagesHandler->getModelForUser(user_id).data()));
}

void MessengerScreenPresenter::onSendMessage(QString message)
{
    int user_id = d->messagesHandler->messagingWith();
    if (user_id == -1)
        return;
    d->commandServer->execute(new SendMessageCommandHandler(user_id, message));
    d->messagesHandler->onNewMessageSend(message);
}
