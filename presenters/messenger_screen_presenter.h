#ifndef MESSENGER_SCREEN_PRESENTER_H
#define MESSENGER_SCREEN_PRESENTER_H

#include "abstract_presenter.h"
#include "command_server/command_server.h"
#include "data/user_info.h"

using model::CommandServerPtr;
using model::UserInfoPtrListPtr;

namespace presentation
{
    class MessengerScreenPresenter : public AbstractPresenter
    {
        Q_OBJECT
    public:
        MessengerScreenPresenter(CommandServerPtr commandServer, QObject* parent);

        void connectView() override;

    private slots:
        void onNewContactList(UserInfoPtrListPtr contactList);
        void onSelectedContactChanged(int user_id);
        void onSendMessage(QString);

    private:
        class Impl;
        QScopedPointer<Impl> d;
    };
}

#endif // MESSENGER_SCREEN_PRESENTER_H
