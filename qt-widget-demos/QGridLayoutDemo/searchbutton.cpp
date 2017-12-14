#include "SearchButton.h"

#include <QLineEdit>
#include <QHBoxLayout>

SearchButton::SearchButton(const QString &text, QLineEdit *edit)
    : QPushButton(text, edit)
{
    QSize size = QSize(40, edit->sizeHint().height());
    setMinimumSize(size);
    setMaximumSize(size);           // ���ð�ť�Ĵ�СΪͼƬ�Ĵ�С
    setFocusPolicy(Qt::NoFocus);    // �õ�����ʱ������ʾ���߿�
    setFlat(true);
    setText(text);
    setCursor(QCursor(Qt::PointingHandCursor));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->addStretch();
    buttonLayout->addWidget(this);
    edit->setLayout(buttonLayout);

    // ������������ļ�����������������������ڱ������ڰ�ť��
    edit->setTextMargins(0, 1, size.width(), 1);

    // Ϊ�˷������, �� style sheet д��������, ʵ�ʹ�����Ӧ�÷ŵ�ר�õ�style sheet��, �����޸�
    QString qss = QString(".SearchButton {background: #E3E3E3; color: black; border: 1 solid gray; min-width: 40px;}")
            + QString(".SearchButton:hover {background: #B4B4B4; color: black; border: 1 solid black;}")
            + QString(".SearchButton:pressed {background: #B4B4B4; color: black;}");
    setStyleSheet(qss);
}

