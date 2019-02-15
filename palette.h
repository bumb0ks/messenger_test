#ifndef PALETTE_H
#define PALETTE_H

#include <QObject>
#include <QColor>
#include <QFont>

/*
    Объект передаваемый в контекст qml. Содержит в себе необходимую палитру цветов
    и шрифты
*/

class Palette : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor lighterColor READ lighter NOTIFY lighterChanged)
    Q_PROPERTY(QColor lightColor READ light NOTIFY lightChanged)
    Q_PROPERTY(QColor middleColor READ middle NOTIFY middleChanged)
    Q_PROPERTY(QColor darkColor READ dark NOTIFY darkChanged)
    Q_PROPERTY(QColor darkerColor READ darker NOTIFY darkerChanged)
    Q_PROPERTY(QFont defaultFont READ defaultFont NOTIFY fontChanged)
    Q_PROPERTY(QFont smallFont READ smallFont NOTIFY smallFontChanged)

public:
    explicit Palette(QObject *parent = nullptr);

    QColor lighter();
    QColor light();
    QColor middle();
    QColor dark();
    QColor darker();

    QFont defaultFont();
    QFont smallFont();

signals:
    void lighterChanged();
    void lightChanged();
    void middleChanged();
    void darkChanged();
    void darkerChanged();
    void fontChanged();
    void smallFontChanged();

private:
    void makeFonts();

    const QColor lighterColor = "#98C5DB";
    const QColor lightColor = "#69A4C4";
    const QColor middleColor = "#3E6B8C";
    const QColor darkColor = "#1B3E5B";
    const QColor darkerColor = "#0C1824";

    QFont m_defaultFont;
    QFont m_smallFont;
};

#endif // PALETTE_H
