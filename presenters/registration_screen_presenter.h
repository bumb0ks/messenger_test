#ifndef REGISTRATION_SCREEN_PRESENTER_H
#define REGISTRATION_SCREEN_PRESENTER_H

#include "abstract_presenter.h"
#include "command_server/command_server.h"

using model::CommandServerPtr;

namespace presentation
{
    class RegistrationScreenPresenter : public AbstractPresenter
    {
        Q_OBJECT
    public:
        RegistrationScreenPresenter(CommandServerPtr commandServer, QObject* parent);

        void connectView() override;

    signals:
        void registrationCompleted();

    private slots:
        void onRegisterButtonClicked();
        void onNewRequestCode(QString token);
        void onNewRequestJwt(QString jwt);
        void onPresenceIncome();
        void onLginButtonClicked(QString);

    private:
        QString formatPhoneNumber(QString phone);

        class Impl;
        QScopedPointer<Impl> d;
    };
}

#endif // REGISTRATION_SCREEN_PRESENTER_H
