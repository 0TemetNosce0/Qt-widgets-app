#include <QGridLayout>
#include <QDebug>

#include "XThemeHelper.h"
#include "XBorderPanel.h"
#include "XClientPanel.h"
#include "XPicture.h"
#include "XColorLabel.h"
#include "XHslPalette.h"
#include "XColorPicker.h"
#include "XSlider.h"


XThemeHelper::XThemeHelper(QWidget *parent)
    : XWindow(parent)
{
//    setWindowFlag(Qt::Tool, true);
    setAttribute(Qt::WA_DeleteOnClose, false);
    setFixedSize(QSize(640, 450));

    initMembers();
    initOutook();
    initContents();
}


XThemeHelper::~XThemeHelper()
{
    if(mp_colorPicker != nullptr)
    {
        delete mp_colorPicker;
        mp_colorPicker = nullptr;
    }
}


XThemeHelper *XThemeHelper::instance()
{
    static XThemeHelper* inst = new XThemeHelper;
    return inst;
}

void XThemeHelper::onPickColor()
{
    mp_colorPickLabel->setEnabled(false);
    mp_colorPicker = new XColorPicker;
    connect(mp_colorPicker, SIGNAL(colorChanged(QColor)), this, SLOT(onColorPicked(QColor)));
    connect(mp_colorPicker, SIGNAL(colorFinished(QColor)), this, SLOT(onColorPicked(QColor)));
    connect(mp_colorPicker, SIGNAL(colorFinished(QColor)), this, SLOT(onColorPickerFinished()));
    mp_colorPicker->pickColor();
}

void XThemeHelper::onColorPickerFinished()
{
    mp_colorPickLabel->setEnabled(true);
}


void XThemeHelper::initOutook()
{
    setWindowTitle(tr("系统主题"));
    setTitleButtonHints(Xc::WindowMinMaxCloseButtonHint);

    borderFrame()->setBackgroundColor(Qt::green, Qt::green);
    borderFrame()->setBorderWidth(0);
    borderFrame()->setBorderColor(Qt::red, Qt::darkGray);

    titleBar()->setBackgroundColor(Qt::transparent, Qt::transparent);
    titleBar()->setBorderWidth(0);
    titleBar()->setBorderColor(Qt::transparent, Qt::blue);

    clientFrame()->setBackgroundColor(QColor(255,255,255,150), QColor(255,255,150));

    setRadius(0, 0);
}


void XThemeHelper::initMembers()
{
    mp_colorPickLabel = nullptr;
    mp_colorPicker = nullptr;
    mp_hslPalette = nullptr;
    mp_sliderRed = nullptr;
    mp_sliderGreen = nullptr;
    mp_sliderBlue = nullptr;
    mp_sliderAlpha = nullptr;
}


void XThemeHelper::initContents()
{
    QGridLayout *pLayoutImage = new QGridLayout;
    pLayoutImage->setSizeConstraint(QLayout::SetMinimumSize);
    pLayoutImage->setMargin(5);
    pLayoutImage->setHorizontalSpacing(5);
    pLayoutImage->setVerticalSpacing(5);
    pLayoutImage->setColumnStretch(0,1);
    pLayoutImage->setColumnStretch(1,1);
    pLayoutImage->setRowStretch(0,1);
    pLayoutImage->setRowStretch(1,1);
    pLayoutImage->setRowStretch(2,1);
    pLayoutImage->setRowStretch(3,1);

    XPicture *pPictureA = new XPicture(QPixmap(":/pic1.jpg"));
    XPicture *pPictureB = new XPicture(QPixmap(":/pic2.jpg"));
    XPicture *pPictureC = new XPicture(QPixmap(":/pic3.jpg"));
    XPicture *pPictureD = new XPicture(QPixmap(":/pic4.jpg"));
    XPicture *pPictureE = new XPicture(QPixmap(":/pic5.jpg"));
    XPicture *pPictureF = new XPicture(QPixmap(":/pic6.jpg"));
    XPicture *pPictureG = new XPicture(QPixmap(":/pic7.jpg"));
    XPicture *pPictureH = new XPicture(QPixmap(":/pic8.jpg"));

    pLayoutImage->addWidget(pPictureA, 0, 0);
    pLayoutImage->addWidget(pPictureB, 0, 1);
    pLayoutImage->addWidget(pPictureC, 1, 0);
    pLayoutImage->addWidget(pPictureD, 1, 1);
    pLayoutImage->addWidget(pPictureE, 2, 0);
    pLayoutImage->addWidget(pPictureF, 2, 1);
    pLayoutImage->addWidget(pPictureG, 3, 0);
    pLayoutImage->addWidget(pPictureH, 3, 1);

    XColorLabel *pColorLabelA = new XColorLabel(QColor("black"));
    XColorLabel *pColorLabelB = new XColorLabel(QColor("red"));
    XColorLabel *pColorLabelC = new XColorLabel(QColor("green"));
    XColorLabel *pColorLabelD = new XColorLabel(QColor("blue"));
    XColorLabel *pColorLabelE = new XColorLabel(QColor("orange"));
    XColorLabel *pColorLabelF = new XColorLabel(QColor("purple"));
    XColorLabel *pColorLabelG = new XColorLabel(QColor("yellow"));
    XColorLabel *pColorLabelH = new XColorLabel(QColor("deepskyblue"));
    XColorLabel *pColorLabelI = new XColorLabel(QColor("deeppink"));
    mp_colorPickLabel = new XColorLabel(QColor("powderblue"));
    mp_colorPickLabel->setText("⌫");
    mp_colorPickLabel->setAlignment(Qt::AlignCenter);

    QGridLayout *pLayoutColorLabel = new QGridLayout;
    pLayoutColorLabel->setSizeConstraint(QLayout::SetMinimumSize);
    pLayoutColorLabel->setMargin(5);
    pLayoutColorLabel->setHorizontalSpacing(5);
    pLayoutColorLabel->setVerticalSpacing(5);

    pLayoutColorLabel->addWidget(pColorLabelA, 0, 0);
    pLayoutColorLabel->addWidget(pColorLabelB, 0, 1);
    pLayoutColorLabel->addWidget(pColorLabelC, 0, 2);
    pLayoutColorLabel->addWidget(pColorLabelD, 0, 3);
    pLayoutColorLabel->addWidget(pColorLabelE, 0, 4);
    pLayoutColorLabel->addWidget(pColorLabelF, 1, 0);
    pLayoutColorLabel->addWidget(pColorLabelG, 1, 1);
    pLayoutColorLabel->addWidget(pColorLabelH, 1, 2);
    pLayoutColorLabel->addWidget(pColorLabelI, 1, 3);
    pLayoutColorLabel->addWidget(mp_colorPickLabel, 1, 4);

    mp_hslPalette = new XHslPalette;
    mp_colorDisplayer = new XColorLabel(Qt::black);

    mp_sliderRed = new XSlider;
    mp_sliderRed->setOrientation(Qt::Horizontal);
    mp_sliderRed->setRange(0,255);  
    mp_sliderRed->setSingleStep(5);
    mp_sliderRed->setValue(0);
    mp_sliderRed->setOutlook("$grooveNormalColor: darkgray; "
                         "$grooveHoverColor: red; "
                         "$headleNormalColor: red; "
                         "$headleHoverColor: red;"
                         "$grooveDiameter: 20;"
                         "$headleBorderWidth: 10;");

    mp_sliderGreen = new XSlider;
    mp_sliderGreen->setOrientation(Qt::Horizontal);
    mp_sliderGreen->setRange(0,255);
    mp_sliderGreen->setSingleStep(5);
    mp_sliderGreen->setValue(0);
    mp_sliderGreen->setOutlook("$grooveNormalColor: darkgray; "
                         "$grooveHoverColor: green; "
                         "$headleNormalColor: green; "
                         "$headleHoverColor: green;"
                         "$grooveDiameter: 20;"
                         "$headleBorderWidth: 10;");

    mp_sliderBlue = new XSlider;
    mp_sliderBlue->setOrientation(Qt::Horizontal);
    mp_sliderBlue->setRange(0,255);
    mp_sliderBlue->setSingleStep(5);
    mp_sliderBlue->setValue(0);
    mp_sliderBlue->setOutlook("$grooveNormalColor: darkgray; "
                         "$grooveHoverColor: blue; "
                         "$headleNormalColor: blue; "
                         "$headleHoverColor: blue;"
                         "$grooveDiameter: 20;"
                         "$headleBorderWidth: 10;");

    mp_sliderAlpha = new XSlider;
    mp_sliderAlpha->setOrientation(Qt::Horizontal);
    mp_sliderAlpha->setRange(0,255);
    mp_sliderAlpha->setSingleStep(5);
    mp_sliderAlpha->setValue(0);
    mp_sliderAlpha->setOutlook("$grooveNormalColor: darkgray; "
                         "$grooveHoverColor: black; "
                         "$headleNormalColor: black; "
                         "$headleHoverColor: black;"
                         "$grooveDiameter: 20;"
                         "$headleBorderWidth: 10;");

    QVBoxLayout *pLayoutRgbSlider = new QVBoxLayout;   
    pLayoutRgbSlider->addWidget(mp_sliderRed);
    pLayoutRgbSlider->addWidget(mp_sliderGreen);
    pLayoutRgbSlider->addWidget(mp_sliderBlue);
    pLayoutRgbSlider->addWidget(mp_sliderAlpha);


    QHBoxLayout *pLayoutRgb = new QHBoxLayout;
    pLayoutRgb->addWidget(mp_colorDisplayer);
    pLayoutRgb->addLayout(pLayoutRgbSlider);


    QVBoxLayout *pLayoutColor = new QVBoxLayout;
    pLayoutColor->setSizeConstraint(QLayout::SetMinimumSize);
    pLayoutColor->setMargin(5);
    pLayoutColor->setSpacing(5);
    pLayoutColor->addLayout(pLayoutColorLabel);
    pLayoutColor->addWidget(mp_hslPalette);
    pLayoutColor->addLayout(pLayoutRgb);
    pLayoutColor->addStretch();

    QHBoxLayout *pLayoutMain = new QHBoxLayout;
    pLayoutMain->setSizeConstraint(QLayout::SetMinimumSize);
    pLayoutMain->setContentsMargins(5,5,5,5);
    pLayoutMain->setSpacing(5);
    pLayoutMain->addLayout(pLayoutImage,4);
    pLayoutMain->addLayout(pLayoutColor,3);

    setLayout(pLayoutMain);

    connect(pPictureA, SIGNAL(clicked(QPixmap)), this, SLOT(setBackgroundImage(QPixmap)));
    connect(pPictureB, SIGNAL(clicked(QPixmap)), this, SLOT(setBackgroundImage(QPixmap)));
    connect(pPictureC, SIGNAL(clicked(QPixmap)), this, SLOT(setBackgroundImage(QPixmap)));
    connect(pPictureD, SIGNAL(clicked(QPixmap)), this, SLOT(setBackgroundImage(QPixmap)));
    connect(pPictureE, SIGNAL(clicked(QPixmap)), this, SLOT(setBackgroundImage(QPixmap)));
    connect(pPictureF, SIGNAL(clicked(QPixmap)), this, SLOT(setBackgroundImage(QPixmap)));
    connect(pPictureG, SIGNAL(clicked(QPixmap)), this, SLOT(setBackgroundImage(QPixmap)));
    connect(pPictureH, SIGNAL(clicked(QPixmap)), this, SLOT(setBackgroundImage(QPixmap)));


    connect(pColorLabelA, SIGNAL(clicked(QColor)), this, SLOT(onColorLabelChanged(QColor)));
    connect(pColorLabelB, SIGNAL(clicked(QColor)), this, SLOT(onColorLabelChanged(QColor)));
    connect(pColorLabelC, SIGNAL(clicked(QColor)), this, SLOT(onColorLabelChanged(QColor)));
    connect(pColorLabelD, SIGNAL(clicked(QColor)), this, SLOT(onColorLabelChanged(QColor)));
    connect(pColorLabelE, SIGNAL(clicked(QColor)), this, SLOT(onColorLabelChanged(QColor)));
    connect(pColorLabelF, SIGNAL(clicked(QColor)), this, SLOT(onColorLabelChanged(QColor)));
    connect(pColorLabelG, SIGNAL(clicked(QColor)), this, SLOT(onColorLabelChanged(QColor)));
    connect(pColorLabelH, SIGNAL(clicked(QColor)), this, SLOT(onColorLabelChanged(QColor)));
    connect(pColorLabelI, SIGNAL(clicked(QColor)), this, SLOT(onColorLabelChanged(QColor)));

    connect(mp_colorPickLabel, SIGNAL(clicked(QColor)), this, SLOT(onPickColor()));

    connect(mp_hslPalette, SIGNAL(colorChanged(QColor)), this, SLOT(onPaletteChanged(QColor)));

    connect(mp_sliderRed, SIGNAL(valueChanged(int)), this, SLOT(onRgbChanged()));
    connect(mp_sliderGreen, SIGNAL(valueChanged(int)), this, SLOT(onRgbChanged()));
    connect(mp_sliderBlue, SIGNAL(valueChanged(int)), this, SLOT(onRgbChanged()));
    connect(mp_sliderAlpha, SIGNAL(valueChanged(int)), this, SLOT(setThemeAlpha(int)));
}


void XThemeHelper::onColorPicked(QColor color)
{
    XWindow::setThemeColor(color);
    emit themeColorChanged(color);

    mp_hslPalette->setColor(color);
    mp_colorPickLabel->setColor(color);
    mp_colorDisplayer->setColor(color);
    mp_sliderRed->setValue(color.red());
    mp_sliderGreen->setValue(color.green());
    mp_sliderBlue->setValue(color.blue());
}


void XThemeHelper::onColorLabelChanged(QColor color)
{
    XWindow::setThemeColor(color);
    emit themeColorChanged(color);

    mp_hslPalette->setColor(color);
    mp_colorPickLabel->setColor(color);
    mp_colorDisplayer->setColor(color);
    mp_sliderRed->setValue(color.red());
    mp_sliderGreen->setValue(color.green());
    mp_sliderBlue->setValue(color.blue());
}


void XThemeHelper::onPaletteChanged(QColor color)
{
    XWindow::setThemeColor(color);
    emit themeColorChanged(color);

    mp_colorPickLabel->setColor(color);
    mp_colorDisplayer->setColor(color);
    mp_sliderRed->setValue(color.red());
    mp_sliderGreen->setValue(color.green());
    mp_sliderBlue->setValue(color.blue());
}


void XThemeHelper::onRgbChanged()
{
    QColor color(mp_sliderRed->value(), mp_sliderGreen->value(), mp_sliderBlue->value());
    XWindow::setThemeColor(color);
    emit themeColorChanged(color);

    mp_hslPalette->setColor(color);
    mp_colorPickLabel->setColor(color);
    mp_colorDisplayer->setColor(color);
}


void XThemeHelper::setThemeAlpha(int ntAlpha)
{
    XWindow::setThemeAlpha(ntAlpha);
    emit themeAlphaChanged(ntAlpha);
}


void XThemeHelper::setBackgroundImage(QPixmap pixmap)
{
    XWindow::setBackgroundImage(pixmap);
    emit backgroundImageChanged(pixmap);
}

