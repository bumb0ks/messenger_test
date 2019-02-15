#include "presence_command_handler.h"

#include <QDebug>

using namespace model;

PresenceCommandHandler::PresenceCommandHandler(QString jwt) :
    AbstractCommandHandler (),
    m_jwt(jwt)
{

}

json PresenceCommandHandler::initializeJson()
{
    json outMessage = {
        { "command", "presence" },
        { "payload",
          {
              { "jwt", m_jwt.toStdString() }
          }
        }
    };
    return outMessage;
}
