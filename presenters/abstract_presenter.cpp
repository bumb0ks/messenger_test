#include "abstract_presenter.h"

using namespace presentation;

AbstractPresenter::AbstractPresenter(QObject *parent) : QObject(parent)
{

}

AbstractPresenter::~AbstractPresenter()
{
}

void AbstractPresenter::setView(QObject *view)
{
    this->m_view = view;
    this->connectView();
}

void AbstractPresenter::connectView()
{
}

void AbstractPresenter::setProperty(const char* property, QVariant value)
{
    this->view()->setProperty(property, value);
}

QVariant AbstractPresenter::getProperty(const char *property)
{
    return this->view()->property(property);
}

void AbstractPresenter::invokeViewMethod(const char* name)
{
    QMetaObject::invokeMethod(this->view(), name);
}

QObject *AbstractPresenter::view() const
{
    return this->m_view;
}
