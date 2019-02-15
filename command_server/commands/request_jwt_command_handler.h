#ifndef REQUEST_JWT_COMMAND_H
#define REQUEST_JWT_COMMAND_H

#include "abstract_command_handler.h"


namespace model
{
    class RequestJWTCommandHandler : public AbstractCommandHandler
    {
    public:
        RequestJWTCommandHandler(QString code, QString token);

        json initializeJson() override;

    private:
        QString m_code;
        QString m_token;
    };
}

#endif // REQUEST_JWT_COMMAND_H
