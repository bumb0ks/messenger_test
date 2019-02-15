#include "main_screen_presenter.h"
#include "messenger_screen_presenter.h"
#include "registration_screen_presenter.h"

#include <QScopedPointer>
#include <QQmlProperty>
#include <QDebug>

namespace {
    bool isRegistered = false;
}

using namespace presentation;

using model::CommandServer;
using model::CommandServerPtr;

enum class MainScreenState {
    Registration,
    Messenger
};

class MainScreenPresenter::Impl
{
public:
    Impl()
    { }

    MainScreenState state = MainScreenState::Registration;

    QScopedPointer<MessengerScreenPresenter> messengerScreenPresenter;
    QScopedPointer<RegistrationScreenPresenter> registrationScreenPresenter;
    CommandServerPtr commandServer;
};

MainScreenPresenter::MainScreenPresenter(CommandServerPtr commandServer, QObject *parent) :
    AbstractPresenter (parent),
    d(new Impl)
{
    d->commandServer = commandServer;
    d->messengerScreenPresenter.reset(new MessengerScreenPresenter(d->commandServer, this));
    d->registrationScreenPresenter.reset(new RegistrationScreenPresenter(d->commandServer, this));
}

void MainScreenPresenter::connectView()
{
    connect(this->view(), SIGNAL(loadCompleted()), this, SLOT(onLoadCompleted()));

    if (this->isRegistered())
    {
        this->setProperty("loaderSource", QVariant::fromValue(QString("qrc:/MessengerScreen.qml")));
        d->state = MainScreenState::Messenger;
    }
    else
    {
        this->setProperty("loaderSource", QVariant::fromValue(QString("qrc:/RegistrationScreen.qml")));
        d->state = MainScreenState::Registration;
    }

}

void MainScreenPresenter::onLoadCompleted()
{
    disconnect(this->view(), SIGNAL(loadCompleted()), this, SLOT(onLoadCompleted()));


    QObject * loader = this->view()->findChild<QObject*>("screensLoader");

    switch (d->state)
    {
    case MainScreenState::Messenger:
    {
        d->messengerScreenPresenter->setView(qvariant_cast<QObject*>(QQmlProperty::read(loader, "item")));
        break;
    }
    case MainScreenState::Registration:
    {
        d->registrationScreenPresenter->setView(qvariant_cast<QObject*>(QQmlProperty::read(loader, "item")));

        connect(d->registrationScreenPresenter.data(), SIGNAL(registrationCompleted()),
                this, SLOT(onRegistered()));

        break;
    }
    }
}

void MainScreenPresenter::onRegistered()
{
    ::isRegistered = true;
    d->state = MainScreenState::Messenger;
    this->connectView();
}

bool MainScreenPresenter::isRegistered()
{
    // Проверяем, вдруг пользователь уже регистрировался на сервисе
    // и если да, то переходим на 'следующий экран мессенджера
    return ::isRegistered;
}

