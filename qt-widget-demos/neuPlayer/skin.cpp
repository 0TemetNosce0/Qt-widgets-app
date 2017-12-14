#include "skin.h"

Skin::Skin(QObject *parent) :
    QObject(parent)
{
    initSkinPalettes();
}
Skin::Skin(int skinId, QObject *parent) :
    QObject(parent), a_idSkin(skinId)
{
    initSkinPalettes();
}

void Skin::initSkinPalettes()
{
    //Dark Palette
    a_darkPalette.setColor(QPalette::Window, QColor(45,45,45));
    a_darkPalette.setColor(QPalette::WindowText, Qt::white);
    a_darkPalette.setColor(QPalette::Base, QColor(30,30,30));
    a_darkPalette.setColor(QPalette::AlternateBase, QColor(45,45,45));
    a_darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    a_darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    a_darkPalette.setColor(QPalette::Button, QColor(45,45,45));
    a_darkPalette.setColor(QPalette::ButtonText, Qt::white);
    a_darkPalette.setColor(QPalette::BrightText, Qt::red);
    a_darkPalette.setColor(QPalette::Text, Qt::white);
    a_darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    a_darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    a_darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    a_darkPaletteCSS = "QToolTip { color: #ffffff; background-color: #353535; border: 1px solid #53a0ed; }";

    //Light palette
    a_lightPalette.setColor(QPalette::Base, QColor(220,220,220));
    a_lightPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    a_lightPalette.setColor(QPalette::Window, QColor(220,220,220));
    a_lightPalette.setColor(QPalette::WindowText, Qt::black);
    a_lightPalette.setColor(QPalette::AlternateBase, QColor(30,30,30));
    a_lightPalette.setColor(QPalette::ToolTipBase, Qt::black);
    a_lightPalette.setColor(QPalette::ToolTipText, Qt::black);
    a_lightPalette.setColor(QPalette::Button, QColor(220,220,220));
    a_lightPalette.setColor(QPalette::ButtonText, Qt::black);
    a_lightPalette.setColor(QPalette::BrightText, Qt::red);
    a_lightPalette.setColor(QPalette::Text, Qt::black);

    a_lightPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    a_lightPalette.setColor(QPalette::HighlightedText, Qt::white);
    a_lightPaletteCSS = "QToolTip { border: 1px solid #53a0ed; background-color: #f0f0f0}";
}

void Skin::load()
{
    if(a_idSkin == 0 || a_idSkin == 2)
    {
        qApp->setPalette(a_lightPalette);
        qApp->setStyleSheet(a_lightPaletteCSS);
    }
    else if(a_idSkin == 1  || a_idSkin == 3)
    {
        qApp->setPalette(a_darkPalette);
        qApp->setStyleSheet(a_darkPaletteCSS);
    }
}
Skin::~Skin()
{}
