#include "contacts_command_handler.h"

using namespace model;

ContactsCommandHandler::ContactsCommandHandler() :
    AbstractCommandHandler ()
{
}

json ContactsCommandHandler::initializeJson()
{
    json outMessage = {
        { "command", "contacts" }
    };
    return outMessage;
}
