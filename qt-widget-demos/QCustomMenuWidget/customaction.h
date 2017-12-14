#ifndef CUSTOMACTION_H
#define CUSTOMACTION_H

#include <QWidgetAction>

class CustomAction : public QWidgetAction
{
    Q_OBJECT

public:
    CustomAction(QObject* parent = NULL);

protected slots:
    void onButtonHovered();
    void onButtonClicked();

protected:
    virtual QWidget* createWidget(QWidget *parent);
};

#endif
