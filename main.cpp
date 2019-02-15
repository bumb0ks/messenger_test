#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickWindow>

#include "command_server/command_server.h"
#include "command_server/commands_traits.h"
#include "nlohmann/json.hpp"
#include "palette.h"

#include "presenters/main_screen_presenter.h"

using model::CommandServer;
using presentation::MainScreenPresenter;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext* context = new QQmlContext(engine.rootContext());

    context->setContextObject(new Palette());

    QQmlComponent component(&engine, "qrc:/main.qml");

    QQuickWindow* rootObject = qobject_cast<QQuickWindow*>(component.create(context));

    QSharedPointer<CommandServer> commandServer;
    commandServer.reset(new CommandServer());

    QObject *mainScreenView = rootObject->findChild<QObject*>("mainScreen");

    MainScreenPresenter* mainScreenPresenter = new MainScreenPresenter(commandServer, rootObject);
    mainScreenPresenter->setView(mainScreenView);

    rootObject->show();

    return app.exec();
}
