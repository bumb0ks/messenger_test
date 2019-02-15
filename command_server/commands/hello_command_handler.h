#ifndef HELLOCOMMAND_H
#define HELLOCOMMAND_H

#include "abstract_command_handler.h"

namespace model
{
    class HelloCommandHandler : public AbstractCommandHandler
    {
    public:
        HelloCommandHandler();

        json initializeJson() override;
    };
}

#endif // HELLOCOMMAND_H
