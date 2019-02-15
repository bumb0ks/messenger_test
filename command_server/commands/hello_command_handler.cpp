#include "hello_command_handler.h"

using namespace model;

HelloCommandHandler::HelloCommandHandler() :
    AbstractCommandHandler()
{
}

json HelloCommandHandler::initializeJson()
{
    json outMessage = {
        { "command", "hello" }
    };
    return outMessage;
}
