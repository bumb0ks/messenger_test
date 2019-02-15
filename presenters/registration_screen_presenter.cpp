#include "registration_screen_presenter.h"

#include "command_server/commands_traits.h"

#include <QDebug>

using namespace presentation;
using namespace model;

enum class RegistrationStage
{
    First,
    Second
};

class RegistrationScreenPresenter::Impl
{
public:
    RegistrationStage registrationStage = RegistrationStage::First;
    CommandServerPtr commandServer;
    QString token;
};

RegistrationScreenPresenter::RegistrationScreenPresenter(model::CommandServerPtr commandServer, QObject *parent) :
    AbstractPresenter (parent),
    d(new Impl)
{
    d->commandServer = commandServer;
}

void RegistrationScreenPresenter::connectView()
{
    connect(this->view(), SIGNAL(registrationButtonClicked()),
            this, SLOT(onRegisterButtonClicked()));
    connect(this->view(), SIGNAL(loginButtonClicked(QString)),
            this, SLOT(onLginButtonClicked(QString)));

    connect(d->commandServer->getDataEmitter(), SIGNAL(newRequestCode(QString)),
            this, SLOT(onNewRequestCode(QString)));
    connect(d->commandServer->getDataEmitter(), SIGNAL(newRequestJwt(QString)),
            this, SLOT(onNewRequestJwt(QString)));
    connect(d->commandServer->getDataEmitter(), SIGNAL(newPresence()),
            this, SLOT(onPresenceIncome()));
}

void RegistrationScreenPresenter::onRegisterButtonClicked()
{
    switch (d->registrationStage) {
        case RegistrationStage::First:
        {
            QString phone = this->formatPhoneNumber( this->getProperty("phoneNumber").toString() );
            this->invokeViewMethod("disablePhoneEdit");
            d->commandServer->execute(new RequestCodeCommandHandler(phone));

            break;
        }
        case RegistrationStage::Second:
        {
            QString code = this->getProperty("code").toString();
            this->invokeViewMethod("disableCodeEdit");
            d->commandServer->execute(new RequestJWTCommandHandler(code, d->token));

            break;
        }
    }
}

void RegistrationScreenPresenter::onNewRequestCode(QString token)
{
    d->token = token;
    this->invokeViewMethod("enableCodeEdit");
    d->registrationStage = RegistrationStage::Second;
}

void RegistrationScreenPresenter::onNewRequestJwt(QString jwt)
{
    d->commandServer->execute(new PresenceCommandHandler(jwt));
}

void RegistrationScreenPresenter::onPresenceIncome()
{
    emit this->registrationCompleted();
}

void RegistrationScreenPresenter::onLginButtonClicked(QString jwt)
{
    d->commandServer->execute(new PresenceCommandHandler(jwt));
}

QString RegistrationScreenPresenter::formatPhoneNumber(QString phone)
{
    return phone.remove('(').remove(')').remove('-');
}
