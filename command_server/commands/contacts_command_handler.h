#ifndef CONTACTS_COMMAND_H
#define CONTACTS_COMMAND_H

#include "abstract_command_handler.h"

namespace model
{
    class ContactsCommandHandler : public AbstractCommandHandler
    {
    public:
        ContactsCommandHandler();

        json initializeJson() override;
    };
}

#endif // CONTACTS_COMMAND_H
