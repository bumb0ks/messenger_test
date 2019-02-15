#ifndef REQUEST_CODE_COMMAND_H
#define REQUEST_CODE_COMMAND_H

#include "abstract_command_handler.h"


namespace model
{
    class RequestCodeCommandHandler : public AbstractCommandHandler
    {
    public:
        RequestCodeCommandHandler( QString phoneNumber );

        json initializeJson() override;

    private:
        QString m_phoneNumber;
    };
}

#endif // REQUEST_CODE_COMMAND_H
