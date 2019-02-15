#ifndef PACKETPARSER_H
#define PACKETPARSER_H

#include <QByteArray>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/*
 *  Класс для преобразования объектов
 */

namespace model
{
    class PacketParser
    {
    public:
        PacketParser();

        QByteArray toPacket(json jsonOut);
        json fromPacket(QByteArray data);
    };
}

#endif // PACKETPARSER_H
