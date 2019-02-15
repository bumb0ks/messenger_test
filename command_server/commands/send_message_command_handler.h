#ifndef SEND_MESSAGE_COMMAND_H
#define SEND_MESSAGE_COMMAND_H

#include "abstract_command_handler.h"

namespace model
{
    class SendMessageCommandHandler : public AbstractCommandHandler
    {
    public:
        SendMessageCommandHandler(quint32 user_id, QString text);

        json initializeJson() override;

    private:
        quint32 m_user_id;
        QString m_text;
    };
}

#endif // SEND_MESSAGE_COMMAND_H
