#include "message_info.h"

 using namespace model;

MessageInfo::MessageInfo(int from_user_id, int to_user_id, QString message) :
    m_from_user_id(from_user_id),
    m_to_user_id(to_user_id),
    m_message(message)
{
}

int MessageInfo::fromUserId() const
{
    return m_from_user_id;
}

int MessageInfo::toUserId() const
{
    return m_to_user_id;
}

QString MessageInfo::message() const
{
    return m_message;
}
