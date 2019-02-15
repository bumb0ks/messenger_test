#ifndef ABSTRACT_PRESENTER_H
#define ABSTRACT_PRESENTER_H

#include <QObject>
#include <QVariant>

namespace presentation
{
    class AbstractPresenter : public QObject
    {
        Q_OBJECT
    public:
        explicit AbstractPresenter(QObject *parent = nullptr);

        ~AbstractPresenter();

        void setView(QObject* view);
        virtual void connectView();

        void setProperty(const char* property, QVariant value);

        QVariant getProperty(const char* property);

        void invokeViewMethod(const char* name);

        QObject* view() const;

    private:
        QObject* m_view;
    };
}

#endif // ABSTRACT_PRESENTER_H
