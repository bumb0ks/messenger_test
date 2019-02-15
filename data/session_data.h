#ifndef SESSION_DATA_H
#define SESSION_DATA_H

#include <QString>

/*
    SessionObject - хранит сессионую информацию - token jwt
    Понадобится при потерях связи и дальнейшем её восстановлении
*/


namespace model
{
    class SessionData
    {
    public:
        SessionData();

        void setToken(const QString& token);
        void setJwt(const QString& jwt);

        QString getToken() const;
        QString getJwt() const;

    private:
        QString m_token;
        QString m_jwt;
    };
}

#endif // SESSION_DATA_H
