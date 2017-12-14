#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>

/* ˵��:�Զ��忪�ذ�ť�ؼ�ͷ�ļ�
 * ����:�������������ļ��Ŀ�������
 * ����:������  QQ:517216493
 * ʱ��:2013-12-19  ���:2014-1-10
 */
class SwitchButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = 0);

    //��ȡ��ǰѡ��״̬
    bool GetCheck() const
    {
        return isCheck;
    }

    //���õ�ǰѡ��״̬
    void SetCheck(bool isCheck);

private:
    bool isCheck;
    QString styleOn;
    QString styleOff;

signals:

private slots:
    void ChangeOnOff();

};

#endif //SWITCHBUTTON_H
