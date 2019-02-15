#include "palette.h"

Palette::Palette(QObject *parent) : QObject(parent)
{
    this->makeFonts();
}

QColor Palette::lighter()
{
    return this->lighterColor;
}

QColor Palette::light()
{
    return this->lightColor;
}

QColor Palette::middle()
{
    return this->middleColor;
}

QColor Palette::dark()
{
    return this->darkColor;
}

QColor Palette::darker()
{
    return this->darkerColor;
}

QFont Palette::defaultFont()
{
    return this->m_defaultFont;
}

QFont Palette::smallFont()
{
    return this->m_smallFont;
}

void Palette::makeFonts()
{
    this->m_defaultFont = QFont("Berlin Sans FB", 25);
    this->m_smallFont = QFont("Berlin Sans FB", 18);
}
