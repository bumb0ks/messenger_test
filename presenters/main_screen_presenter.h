#ifndef MAIN_SCREEN_PRESENTER_H
#define MAIN_SCREEN_PRESENTER_H

#include "presenters/abstract_presenter.h"
#include "command_server/command_server.h"

using namespace model;

/*
    Главный презентер. Проводит пользователя по регистрации или через логин.
    Меняет активность дочерних презентеров.
*/

namespace presentation
{
    class MainScreenPresenter : public AbstractPresenter
    {
        Q_OBJECT
    public:
        MainScreenPresenter(CommandServerPtr commandServer, QObject* parent);

        void connectView() override;

    private slots:
        void onLoadCompleted();
        void onRegistered();

    private:
        bool isRegistered();

        class Impl;
        QScopedPointer<Impl> d;
    };
}

#endif // MAIN_SCREEN_PRESENTER_H
