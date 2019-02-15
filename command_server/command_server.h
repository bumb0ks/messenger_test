#ifndef COMMANDSERVER_H
#define COMMANDSERVER_H

#include <QAbstractSocket>
#include <QObject>
#include <nlohmann/json.hpp>

/*
    Класс команд сервер содержит себе сокет для передачи/получения информации, набор необходимых
    объектов для распространения и набор для обработки входных пакетов и выходных.
*/

class QTcpSocket;

namespace model
{
    class AbstractCommandHandler;
    class DataEmitter;
    class SessionData;

    class CommandServer :public QObject
    {
        Q_OBJECT
    public:
        CommandServer();
        CommandServer(QObject* parent);
        ~CommandServer();

        void execute(AbstractCommandHandler* cmd);
        bool isOpen() const;
        DataEmitter const *  getDataEmitter() const;
        SessionData const * getSessionData() const;

    private slots:
        void onReadyRead();
        void onStateChanged(QAbstractSocket::SocketState state);

    private:
        void initialize();
        void resolveJson(nlohmann::json incomeJson);

        class Impl;
        QScopedPointer<Impl> d;
    };

    typedef QSharedPointer<CommandServer> CommandServerPtr;
}

#endif // COMMANDSERVER_H
