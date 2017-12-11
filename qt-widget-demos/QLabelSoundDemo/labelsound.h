#ifndef LABELSOUND_H
#define LABELSOUND_H

#include <QWidget>

namespace Ui {
class LabelSound;
}

class LabelSound : public QWidget
{
    Q_OBJECT

public:
    explicit LabelSound(QWidget *parent = 0);
    ~LabelSound();

private slots :
    void playSound();

private:
    Ui::LabelSound *ui;
};

#endif // LABELSOUND_H
