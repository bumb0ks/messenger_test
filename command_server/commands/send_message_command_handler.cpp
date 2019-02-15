#include "send_message_command_handler.h"

using namespace model;

SendMessageCommandHandler::SendMessageCommandHandler(quint32 user_id, QString text) :
    AbstractCommandHandler(),
    m_user_id(user_id),
    m_text(text)
{

}

json SendMessageCommandHandler::initializeJson()
{    json outMessage = {
         { "command", "send_message" },
         { "payload",
           {
               { "message", m_text.toStdString() },
               { "user_id", m_user_id },
           }
         }
     };
     return outMessage;
}
