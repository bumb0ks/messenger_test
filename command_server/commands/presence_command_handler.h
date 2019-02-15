#ifndef PRESENCE_COMMAND_H
#define PRESENCE_COMMAND_H

#include "abstract_command_handler.h"


namespace model
{
    class PresenceCommandHandler : public AbstractCommandHandler
    {
    public:
        PresenceCommandHandler(QString jwt);

        json initializeJson() override;

    private:
        QString m_jwt;
    };
}

#endif // PRESENCE_COMMAND_H
