#ifndef HEBREWPANEL_H
#define HEBREWPANEL_H

#include <QDockWidget>
#include <QPushButton>


namespace Ui {
class HebrewPanel;
}

class HebrewPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit HebrewPanel(QWidget *parent = 0);
    ~HebrewPanel();


private slots:
    void sPressSymbol();

signals:
    void SIGNAL_SendSymbol(QString);

private:
    Ui::HebrewPanel *ui;

    QStringList m_capitalCase;

    void init();

    QVector <QPushButton *> m_buttons;
};

#endif // HEBREWPANEL_H
