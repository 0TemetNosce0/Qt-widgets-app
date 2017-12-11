#ifndef IRREGULARFORM_H
#define IRREGULARFORM_H

#include "GLDMask_Global.h"

#include <QWidget>
#include <QPushButton>

class CustomButton;

class GLDMASKSHARED_EXPORT IrregularForm : public QWidget
{
    Q_OBJECT

public:
    explicit IrregularForm(QWidget *parent = 0);
    explicit IrregularForm(const QString & irregularImgPath, const QString & btnImgPath, QWidget *parent = 0);

    void setFlagAndAttribute();

    ~IrregularForm();

    QSize sizeHint() const;

    void loadPixmap(const QString & pixmapPath);
    void setPixmap(const QPixmap & pm);

Q_SIGNALS:
    void irregularFormClicked();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    CustomButton* m_pCustomBtn;
    QPixmap m_irregularFormPm;
};

#endif // IRREGULARFORM_H
