#include "request_code_command_handler.h"

using namespace model;

RequestCodeCommandHandler::RequestCodeCommandHandler( QString phoneNumber ) :
    AbstractCommandHandler (),
    m_phoneNumber(phoneNumber)
{

}

json RequestCodeCommandHandler::initializeJson()
{
    json outMessage = {
        { "command", "request_code" },
        { "payload",
          {
              { "phone", m_phoneNumber.toStdString() },
              { "type", "register" }
          }
        }
    };
    return outMessage;
}
