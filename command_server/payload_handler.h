#ifndef PAYLOAD_PARSER_H
#define PAYLOAD_PARSER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/*
    PayloadParser - принимает в себя объект-эммитер о новых данных.
        Распарсивает пэйлод и эмитит сигналы черех эммитер
*/

namespace model
{
    class DataEmitter;
    class SessionData;

    class PayloadHandler
    {
    public:
        PayloadHandler(QSharedPointer<DataEmitter> dataEmmiter, SessionData* sessionData);
        ~PayloadHandler();

        void parsePayload(json jsonPacket) const;

    private:
        bool isError(json packet) const;

        class Impl;
        QScopedPointer<Impl> d;
    };
}
#endif // PAYLOAD_PARSER_H
