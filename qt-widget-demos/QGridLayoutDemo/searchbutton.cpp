#include "SearchButton.h"

#include <QLineEdit>
#include <QHBoxLayout>

SearchButton::SearchButton(const QString &text, QLineEdit *edit)
    : QPushButton(text, edit)
{
    QSize size = QSize(40, edit->sizeHint().height());
    setMinimumSize(size);
    setMaximumSize(size);           // 设置按钮的大小为图片的大小
    setFocusPolicy(Qt::NoFocus);    // 得到焦点时，不显示虚线框
    setFlat(true);
    setText(text);
    setCursor(QCursor(Qt::PointingHandCursor));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->addStretch();
    buttonLayout->addWidget(this);
    edit->setLayout(buttonLayout);

    // 设置输入框中文件输入区，不让输入的文字在被隐藏在按钮下
    edit->setTextMargins(0, 1, size.width(), 1);

    // 为了方便起见, 把 style sheet 写到代码里, 实际工作中应该放到专用的style sheet里, 方便修改
    QString qss = QString(".SearchButton {background: #E3E3E3; color: black; border: 1 solid gray; min-width: 40px;}")
            + QString(".SearchButton:hover {background: #B4B4B4; color: black; border: 1 solid black;}")
            + QString(".SearchButton:pressed {background: #B4B4B4; color: black;}");
    setStyleSheet(qss);
}

