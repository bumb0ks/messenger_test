
#include "packet_parser.h"

#include <QString>
#include <QDebug>

using namespace model;

namespace
{
    const quint8 packetHeadSize = 4;
}

PacketParser::PacketParser()
{
}

// Функция для преобразования json в ByteArray
QByteArray PacketParser::toPacket(json jsonOut)
{
    std::vector<uint8_t> packedMessage = json::to_msgpack(jsonOut);
    QByteArray resultArray = QByteArray(reinterpret_cast<const char*>(packedMessage.data()), packedMessage.size());

    QString packetHead = QString("%1").arg(resultArray.size(), ::packetHeadSize, 10, QChar('0'));
    resultArray = QByteArray::fromStdString(packetHead.toStdString()) + resultArray;

    return resultArray;
}

// Функция для преобразования ByteArray в json
json PacketParser::fromPacket(QByteArray data)
{
    std::vector<uint8_t> receivedVector(data.begin(), data.end());

    json jsonOut = json::from_msgpack(receivedVector);

    return jsonOut;
}
