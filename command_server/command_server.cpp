#include <QHostAddress>
#include <QTcpSocket>
#include <QDebug>

#include "commands/abstract_command_handler.h"

#include "command_server.h"
#include "packet_parser.h"
#include "payload_handler.h"
#include "data_emitter.h"
#include "data/session_data.h"

using json = nlohmann::json;

namespace
{
    const qint8 packetHeadSize = 4;
}

using namespace model;

// Енам с состояниями "получения" пакета (на случай если пакет придёт не целым)
enum class ReceivingPacketStateEnum
{
    WaitingNewPacket,
    WaitingLeftPacket
};

class CommandServer::Impl
{
public:
    QScopedPointer<QTcpSocket> socket;

    QSharedPointer<DataEmitter> dataEmmiter;
    QScopedPointer<SessionData> sessionData;

    QScopedPointer<PacketParser> packetParser;
    QScopedPointer<PayloadHandler> payloadHandler;

    ReceivingPacketStateEnum packetReadState = ReceivingPacketStateEnum::WaitingNewPacket;
    int bytesLeft = 0;
    QByteArray notFullPacket;

    const QHostAddress address = QHostAddress("192.168.0.114");
    const quint16 port = 6000;
};

CommandServer::CommandServer() :
    QObject(nullptr),
    d(new Impl)
{
    this->initialize();
}

CommandServer::CommandServer(QObject* parent):
    QObject(parent),
    d(new Impl)
{
    this->initialize();
}

CommandServer::~CommandServer()
{
    d->socket->close();
}

// Инициализация сервера и подключение сокета
void CommandServer::initialize()
{
    d->packetParser.reset(new PacketParser());
    d->dataEmmiter.reset(new DataEmitter(this));
    d->sessionData.reset(new SessionData());
    d->payloadHandler.reset(new PayloadHandler(d->dataEmmiter, d->sessionData.data()));


    d->socket.reset(new QTcpSocket(this));

    connect(d->socket.data(), &QTcpSocket::readyRead, this, &CommandServer::onReadyRead);
    connect(d->socket.data(), &QTcpSocket::stateChanged, this, &CommandServer::onStateChanged);

    d->socket->connectToHost(d->address, d->port);
}

// Выполнение команды
void CommandServer::execute(AbstractCommandHandler* cmd)
{
    QByteArray sendArray = d->packetParser->toPacket(cmd->initializeJson());

    d->socket->write(sendArray);
}

bool CommandServer::isOpen() const
{
    return d->socket->isOpen();
}

DataEmitter const * CommandServer::getDataEmitter() const
{
    return d->dataEmmiter.data();
}

const SessionData *CommandServer::getSessionData() const
{
    return d->sessionData.data();
}

// От сигнала readyRead сокета
void CommandServer::onReadyRead()
{
    QByteArray receivedArray;
    qint64 bytesCount = d->socket->bytesAvailable();

    if (bytesCount != 0)
    {
        receivedArray = d->socket->read(bytesCount);

        /* Обработка пакетов по размеру. Если пришел неполный пакет, то конец
        *  пакета будет ожидаться в следующей датаграмме.
        */
        switch (d->packetReadState)
        {
            case ReceivingPacketStateEnum::WaitingNewPacket:
            {
                while(bytesCount > 0 && d->packetReadState == ReceivingPacketStateEnum::WaitingNewPacket)
                {
                    int packetSizeLeft = receivedArray.left(::packetHeadSize).toInt();
                    receivedArray = receivedArray.right(bytesCount - ::packetHeadSize);

                    if ( (bytesCount - ::packetHeadSize) - packetSizeLeft >= 0)
                    {
                        bytesCount = (bytesCount - ::packetHeadSize) - packetSizeLeft;
                        QByteArray packetA = receivedArray.left(packetSizeLeft);
                        receivedArray = receivedArray.right(receivedArray.length() - packetSizeLeft);
                        d->payloadHandler->parsePayload( d->packetParser->fromPacket(packetA) );
                    }
                    else
                    {
                        d->packetReadState = ReceivingPacketStateEnum::WaitingLeftPacket;
                        d->bytesLeft = packetSizeLeft - (bytesCount - ::packetHeadSize);
                        d->notFullPacket = receivedArray;
                    }
                }
                break;
            }
            case ReceivingPacketStateEnum::WaitingLeftPacket:
            {
                if(receivedArray.size() == d->bytesLeft)
                {
                    d->notFullPacket += receivedArray;
                    d->bytesLeft = 0;
                    d->payloadHandler->parsePayload( d->packetParser->fromPacket(d->notFullPacket) );
                }
                else
                {
                    d->notFullPacket += receivedArray;
                    d->bytesLeft -= receivedArray.size();
                }
            }
        }
    }
}

// Реагирование на изменения состояния сокета
void CommandServer::onStateChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::SocketState::BoundState:
    {
        qDebug() << "[S] Bound state";
        break;
    }
    case QAbstractSocket::SocketState::ClosingState:
    {
        qDebug() << "[S] Closing state";
        break;
    }
    case QAbstractSocket::SocketState::ConnectedState:
    {
        qDebug() << "[S] Connected state";
        break;
    }
    case QAbstractSocket::SocketState::ConnectingState:
    {
        qDebug() << "[S] Connecting state";
        break;
    }
    case QAbstractSocket::SocketState::HostLookupState:
    {
        qDebug() << "[S] Host lookup state";
        break;
    }
    case QAbstractSocket::SocketState::ListeningState:
    {
        qDebug() << "[S] Listening state";
        break;
    }
    case QAbstractSocket::SocketState::UnconnectedState:
    {
        qDebug() << "[S] Unconnected state";
        break;
    }
    }
}
