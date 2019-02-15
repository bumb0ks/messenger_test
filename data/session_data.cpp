#include "session_data.h"

#include <QDebug>

using namespace model;

SessionData::SessionData()
{

}

void SessionData::setToken(const QString &token)
{
    this->m_token = token;
}

void SessionData::setJwt(const QString &jwt)
{
    this->m_jwt = jwt;
}

QString SessionData::getToken() const
{
    return this->m_token;
}

QString SessionData::getJwt() const
{
    return this->m_jwt;
}
