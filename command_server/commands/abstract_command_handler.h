#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace model
{
    class AbstractCommandHandler : QObject
    {
        Q_OBJECT
    public:
        AbstractCommandHandler();

        virtual json initializeJson() = 0;

    };
}

#endif // COMMAND_H
