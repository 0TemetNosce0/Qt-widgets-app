#ifndef GREEKPANEL_H
#define GREEKPANEL_H

#include <QDockWidget>
#include <QPushButton>

namespace Ui {
class GreekPanel;
}

class GreekPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit GreekPanel(QWidget *parent = 0);
    ~GreekPanel();

private slots:
    void sPressSymbol();

signals:
    void SIGNAL_SendSymbol(QString);

private:
    Ui::GreekPanel *ui;

    QStringList m_capitalCase;
    QStringList m_lowerCase;

    void init();

    QVector <QPushButton *> m_buttons;
};

#endif // GREEKPANEL_H
