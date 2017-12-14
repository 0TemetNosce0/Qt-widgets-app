/****************************************************************************
**
** Copyright (C) 2010 Richard Steffen and/or its subsidiary(-ies).
** All rights reserved.
** Contact: rsteffen@messbild.de, rsteffen@uni-bonn.de
**
** Observe the License Information
**
****************************************************************************/

#ifndef __MULTIBOXCOMBO_H__
#define __MULTIBOXCOMBO_H__

#include <iostream>
using namespace std;

#include <QComboBox>
#include <QListWidget>
#include <QVBoxLayout>
#include <QStylePainter>

class QMultiComboBox : public QComboBox
{
    Q_OBJECT

public:

    /// Constructor
    QMultiComboBox(QWidget *widget = 0);

    virtual ~QMultiComboBox();

    /// the main display text
    void setDisplayText(QString text);

    /// get the main display text
    QString getDisplayText() const;

    /// add a item to the list
    void addItem(const QString& text, const QVariant& userData = QVariant());

    /// custom paint
    virtual void paintEvent(QPaintEvent *e);

    /// set the height of the popup
    void setPopupHeight(int h);

    /// replace standard QComboBox Popup
    void showPopup();
    void hidePopup();

    /// replace neccessary data access
    int count();
    void setCurrentIndex(int index);
    QString currentText();
    QString itemText(int row);
    QVariant itemData(int row);

signals:
    /// item changed
    void itemChanged();

public slots:

    /// react on changes of the item checkbox
    void scanItemSelect(QListWidgetItem* item);

    /// the init style
    void initStyleOption(QStyleOptionComboBox *option) const;

protected:

    /// the height of the popup
    int popheight;

    /// lower/upper screen bound
    int screenbound;

    /// hold the main display text
    QString m_displayText;

    /// popup frame
    QFrame* popframe;

    /// multi selection list in the popup frame
    QListWidget* listWidget;

};

#endif
