#include "switchbutton.h"

/* ˵��:�Զ��忪�ذ�ť�ؼ�ʵ���ļ�
 * ����:�������������ļ��Ŀ�������
 * ����:������  QQ:517216493
 * ʱ��:2013-12-19  ���:2014-1-10
 */
SwitchButton::SwitchButton(QWidget *parent): QPushButton(parent)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    isCheck = false;
    styleOn = "background-image: url(:/image/btncheckon.png); border: 0px;";
    styleOff = "background-image: url(:/image/btncheckoff.png); border: 0px;";

    setFocusPolicy(Qt::NoFocus);
    setFixedSize(87, 28); //������仯��С
    setStyleSheet(styleOff);//���õ�ǰ��ʽ
    connect(this, SIGNAL(clicked()), this, SLOT(ChangeOnOff()));
}

void SwitchButton::ChangeOnOff()
{
    if (isCheck)
    {
        setStyleSheet(styleOff);
        isCheck = false;
    }
    else
    {
        setStyleSheet(styleOn);
        isCheck = true;
    }
}

//���õ�ǰѡ��״̬
void SwitchButton::SetCheck(bool isCheck)
{
    if (this->isCheck != isCheck)
    {
        this->isCheck = !isCheck;
        ChangeOnOff();
    }
}

