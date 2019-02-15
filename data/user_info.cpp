#include "user_info.h"

using namespace model;

UserInfo::UserInfo(QString phone, int user_id, bool online) :
    m_phone(phone),
    m_user_id(user_id),
    m_online(online)
{
}

QString UserInfo::phone() const
{
    return m_phone;
}

int UserInfo::userId() const
{
    return m_user_id;
}

bool UserInfo::online() const
{
    return m_online;
}

void UserInfo::setOnline(bool status)
{
    if (m_online != status)
        m_online = status;
}
