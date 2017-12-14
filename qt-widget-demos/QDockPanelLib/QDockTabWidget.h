#ifndef QDOCKTABWIDGET_H
#define QDOCKTABWIDGET_H

#include <QTabWidget>

class QDockTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    QDockTabWidget(QWidget* parent);
    ~QDockTabWidget();

signals:
    void setBasePanelTitle(const QString &);

private slots:
    void onDragTabOut(int index);
    void onCurrenChanged(int index);

protected:
    virtual void tabRemoved(int);
};

#endif // QDOCKTABWIDGET_H
