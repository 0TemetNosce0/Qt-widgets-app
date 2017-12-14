/********************************************************************************
** Form generated from reading UI file 'nodeeditdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEEDITDIALOG_H
#define UI_NODEEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_NodeEditDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *labelEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *valueEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QRadioButton *boxRadio;
    QRadioButton *circleRadio;
    QRadioButton *diamondRadio;
    QRadioButton *ellipseRadio;
    QRadioButton *triangleRadio;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *colorButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QSpinBox *sizeSpin;

    void setupUi(QDialog *NodeEditDialog)
    {
        if (NodeEditDialog->objectName().isEmpty())
            NodeEditDialog->setObjectName(QStringLiteral("NodeEditDialog"));
        NodeEditDialog->resize(520, 335);
        NodeEditDialog->setMinimumSize(QSize(500, 300));
        gridLayout = new QGridLayout(NodeEditDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(NodeEditDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        labelEdit = new QLineEdit(NodeEditDialog);
        labelEdit->setObjectName(QStringLiteral("labelEdit"));

        horizontalLayout->addWidget(labelEdit);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(NodeEditDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(false);

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        valueEdit = new QLineEdit(NodeEditDialog);
        valueEdit->setObjectName(QStringLiteral("valueEdit"));
        valueEdit->setEnabled(false);

        horizontalLayout_3->addWidget(valueEdit);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(NodeEditDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        boxRadio = new QRadioButton(NodeEditDialog);
        boxRadio->setObjectName(QStringLiteral("boxRadio"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/box.png"), QSize(), QIcon::Normal, QIcon::Off);
        boxRadio->setIcon(icon);

        horizontalLayout_5->addWidget(boxRadio);

        circleRadio = new QRadioButton(NodeEditDialog);
        circleRadio->setObjectName(QStringLiteral("circleRadio"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        circleRadio->setIcon(icon1);

        horizontalLayout_5->addWidget(circleRadio);

        diamondRadio = new QRadioButton(NodeEditDialog);
        diamondRadio->setObjectName(QStringLiteral("diamondRadio"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/diamond.png"), QSize(), QIcon::Normal, QIcon::Off);
        diamondRadio->setIcon(icon2);

        horizontalLayout_5->addWidget(diamondRadio);

        ellipseRadio = new QRadioButton(NodeEditDialog);
        ellipseRadio->setObjectName(QStringLiteral("ellipseRadio"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/ellipse.png"), QSize(), QIcon::Normal, QIcon::Off);
        ellipseRadio->setIcon(icon3);

        horizontalLayout_5->addWidget(ellipseRadio);

        triangleRadio = new QRadioButton(NodeEditDialog);
        triangleRadio->setObjectName(QStringLiteral("triangleRadio"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/triangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        triangleRadio->setIcon(icon4);

        horizontalLayout_5->addWidget(triangleRadio);


        gridLayout->addLayout(horizontalLayout_5, 4, 0, 1, 2);

        buttonBox = new QDialogButtonBox(NodeEditDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 5, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(NodeEditDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        colorButton = new QToolButton(NodeEditDialog);
        colorButton->setObjectName(QStringLiteral("colorButton"));
        colorButton->setMinimumSize(QSize(60, 25));
        colorButton->setIconSize(QSize(60, 20));

        horizontalLayout_4->addWidget(colorButton);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(NodeEditDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        sizeSpin = new QSpinBox(NodeEditDialog);
        sizeSpin->setObjectName(QStringLiteral("sizeSpin"));
        sizeSpin->setValue(8);

        horizontalLayout_2->addWidget(sizeSpin);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 2);


        retranslateUi(NodeEditDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NodeEditDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NodeEditDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NodeEditDialog);
    } // setupUi

    void retranslateUi(QDialog *NodeEditDialog)
    {
        NodeEditDialog->setWindowTitle(QApplication::translate("NodeEditDialog", "Node Properties", 0));
        label->setText(QApplication::translate("NodeEditDialog", "Enter node label ", 0));
        label_3->setText(QApplication::translate("NodeEditDialog", "Enter node value (disabled)", 0));
        label_5->setText(QApplication::translate("NodeEditDialog", "Select node shape", 0));
        boxRadio->setText(QString());
        circleRadio->setText(QString());
        diamondRadio->setText(QString());
        ellipseRadio->setText(QString());
        triangleRadio->setText(QString());
        label_4->setText(QApplication::translate("NodeEditDialog", "Select the node color (click the button)", 0));
        colorButton->setText(QApplication::translate("NodeEditDialog", "...", 0));
        label_2->setText(QApplication::translate("NodeEditDialog", "Select the node size (default 8)", 0));
    } // retranslateUi

};

namespace Ui {
    class NodeEditDialog: public Ui_NodeEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEEDITDIALOG_H
