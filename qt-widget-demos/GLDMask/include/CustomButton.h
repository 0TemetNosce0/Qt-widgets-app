#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include "GLDMask_Global.h"

#include <QPushButton>

class GLDMASKSHARED_EXPORT CustomButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CustomButton(QWidget* parent = nullptr);
    explicit CustomButton(const QString &iconPath, QWidget* parent = nullptr);

    void setPixmap(const QPixmap& pm);
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent* e);

private:
    QPixmap m_pixmap;
};

#endif // CUSTOMBUTTON_H
