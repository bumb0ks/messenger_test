#include <QStringList>
#include <QDebug>
#include <algorithm>

#include "payload_handler.h"
#include "data_emitter.h"
#include "data/user_info.h"
#include "data/session_data.h"


using namespace model;

namespace
{
    const int successCode = 200;
}

/*
    Обработка пэйлодов пакетов и эмит сигналов
*/

class PayloadHandler::Impl
{
public:
    Impl()
    {
        // перечисление "названий" возможных входящих команд
        commandNames << "hello"
                     << "request_code"
                     << "request_jwt"
                     << "presence"
                     << "user_online"
                     << "user_offline"
                     << "contacts"
                     << "send_message"
                     << "new_message";
    }

    QSharedPointer<DataEmitter> dataEmmiter = nullptr;
    SessionData* sessionData = nullptr;
    QStringList commandNames;
};


PayloadHandler::PayloadHandler(QSharedPointer<DataEmitter> dataEmmiter, SessionData *sessionData) :
    d(new Impl)
{
    d->dataEmmiter = dataEmmiter;
    d->sessionData = sessionData;
}

PayloadHandler::~PayloadHandler()
{
}

// Разпарсивание сигналов
void PayloadHandler::parsePayload(json jsonPacket) const
{
    QString commandName = QString::fromStdString(jsonPacket["command"].get<std::string>());
    json payload;

    if (this->isError(jsonPacket))
        return;

    if (jsonPacket.find("payload") != jsonPacket.end())
        payload = jsonPacket["payload"].get<json>();


    switch (d->commandNames.indexOf(commandName))
    {
    case 0: // "hello":
    {

        QString message = QString::fromStdString(payload["message"].get<std::string>());

        emit d->dataEmmiter->newHello();

        break;
    }
    case 1: // "request_code":
    {
        QString token = QString::fromStdString(payload["token"].get<std::string>());

        d->sessionData->setToken(token);

        emit d->dataEmmiter->newRequestCode(token);

        break;
    }
    case 2: //"request_jwt":
    {
        QString jwt = QString::fromStdString(payload["jwt"].get<std::string>());

        d->sessionData->setJwt(jwt);

        emit d->dataEmmiter->newRequestJwt(jwt);

        break;
    }
    case 3: //"presence":
    {
        emit d->dataEmmiter->newPresence();
        break;
    }
    case 4: //"user_online":
    {
        int user_id = QString::fromStdString(payload["user_id"].get<std::string>()).toInt();

        emit d->dataEmmiter->newUserStatus(user_id, true);

        break;
    }
    case 5: //"user_offline":
    {
        int user_id = QString::fromStdString(payload["user_id"].get<std::string>()).toInt();

        emit d->dataEmmiter->newUserStatus(user_id, false);

        break;
    }
    case 6: //"contacts":
    {
        std::vector<json> users = payload["users"].get<std::vector<json>>();

        UserInfoPtrListPtr userInfoList = UserInfoPtrListPtr( new UserInfoPtrList() );

        for(std::vector<json>::iterator it = users.begin(); it != users.end(); ++it)
        {
            userInfoList->append( UserInfoPtr( new UserInfo(QString::fromStdString((*it)["phone"].get<std::string>()),
                                                                    (*it)["user_id"].get<int>(),
                                                                    (*it)["online"].get<bool>())));
        }

        emit d->dataEmmiter->newContacts(userInfoList);

        break;
    }
    case 7: //"send_message":
    {
        emit d->dataEmmiter->newSendMessage();

        break;
    }
    case 8: //"new_message":
    {
        int sender_user_id = QString::fromStdString(payload["sender_user_id"].get<std::string>()).toInt();
        QString message = QString::fromStdString(payload["message"].get<std::string>());

        emit d->dataEmmiter->newNewMessage(sender_user_id, message);

        break;
    }
    }
}

bool PayloadHandler::isError(json packet) const
{
    int code = ::successCode;
    if(packet.find("code") != packet.end())
        code = packet["code"].get<int>();

    if (code != ::successCode)
    {
        qDebug() << "[!] Code is not 200";
        return true;
    }
    return false;
}
