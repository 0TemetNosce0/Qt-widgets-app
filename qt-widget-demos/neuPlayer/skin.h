#ifndef SKIN_H
#define SKIN_H

#include <QObject>
#include <QStyle>
#include <QApplication>
#include <QSettings>

class Skin : public QObject
{
    Q_OBJECT

public:
    explicit Skin(QObject *parent = 0);
    Skin (int skinId, QObject *parent);
    ~Skin();

    void setSkin(int id)
    {
        a_idSkin = id;
    }

    void load(); //Used when loaded (For both startup and runtime)
    //Use update(); on your objects or a container to apply the changes if loaded at runtime

private:
    void initSkinPalettes();
    //Attributes
    int a_idSkin;
    QPalette a_darkPalette;
    QString a_darkPaletteCSS;
    QPalette a_lightPalette;
    QString a_lightPaletteCSS;

};

#endif // SKIN_H
