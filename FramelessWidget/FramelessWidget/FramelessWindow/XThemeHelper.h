#ifndef XTHEMEHELPER_H
#define XTHEMEHELPER_H

#include <QList>
#include "XWindow.h"
class XPicture;
class XColorLabel;
class XHslPalette;
class XSlider;
class XColorPicker;

#define gp_themeHelper XThemeHelper::instance()

class XThemeHelper : public XWindow
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(XThemeHelper)
    XThemeHelper(QWidget *parent = 0);

public:
    ~XThemeHelper();
    static XThemeHelper* instance();

signals:
    void themeColorChanged(QColor color);
    void themeAlphaChanged(int ntAlpha);
    void backgroundImageChanged(QPixmap pixmap);

public slots:
    void onPickColor();
    void onColorPickerFinished();

    void onColorLabelChanged(QColor color);
    void onPaletteChanged(QColor color);
    void onRgbChanged();

    void onColorPicked(QColor color);
    void setThemeAlpha(int ntAlpha);
    void setBackgroundImage(QPixmap pixmap);

private:
    void initOutook();
    void initMembers();
    void initContents();

private:
    XColorLabel *mp_colorPickLabel;
    XColorPicker *mp_colorPicker;
    XHslPalette *mp_hslPalette;
    XColorLabel *mp_colorDisplayer;
    XSlider *mp_sliderRed;
    XSlider *mp_sliderGreen;
    XSlider *mp_sliderBlue;
    XSlider *mp_sliderAlpha;

};



#endif // XTHEMEHELPER_H
