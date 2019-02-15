#include "request_jwt_command_handler.h"

using namespace model;

RequestJWTCommandHandler::RequestJWTCommandHandler(QString code, QString token) :
    AbstractCommandHandler(),
    m_code(code),
    m_token(token)
{
}

json RequestJWTCommandHandler::initializeJson()
{
    json outMessage = {
        { "command", "request_jwt" },
        { "payload",
          {
              { "type", "register" },
              { "code", m_code.toStdString() },
              { "reset_password", false },
              { "restore", false },
              { "token", m_token.toStdString() }
          }
        }
    };
    return outMessage;
}
