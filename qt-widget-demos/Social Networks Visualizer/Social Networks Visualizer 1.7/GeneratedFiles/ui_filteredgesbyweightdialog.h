/********************************************************************************
** Form generated from reading UI file 'filteredgesbyweightdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTEREDGESBYWEIGHTDIALOG_H
#define UI_FILTEREDGESBYWEIGHTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilterEdgesByWeightDialog
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *weightThreshold;
    QSplitter *splitter;
    QRadioButton *overThresholdBt;
    QRadioButton *belowThresholdBt;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FilterEdgesByWeightDialog)
    {
        if (FilterEdgesByWeightDialog->objectName().isEmpty())
            FilterEdgesByWeightDialog->setObjectName(QStringLiteral("FilterEdgesByWeightDialog"));
        FilterEdgesByWeightDialog->resize(368, 191);
        gridLayout = new QGridLayout(FilterEdgesByWeightDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_2 = new QSplitter(FilterEdgesByWeightDialog);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        label_2 = new QLabel(splitter_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setTextFormat(Qt::RichText);
        label_2->setWordWrap(true);
        splitter_2->addWidget(label_2);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        weightThreshold = new QDoubleSpinBox(layoutWidget);
        weightThreshold->setObjectName(QStringLiteral("weightThreshold"));
        weightThreshold->setDecimals(1);
        weightThreshold->setMinimum(-100);

        horizontalLayout->addWidget(weightThreshold);

        splitter_2->addWidget(layoutWidget);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        overThresholdBt = new QRadioButton(splitter);
        overThresholdBt->setObjectName(QStringLiteral("overThresholdBt"));
        splitter->addWidget(overThresholdBt);
        belowThresholdBt = new QRadioButton(splitter);
        belowThresholdBt->setObjectName(QStringLiteral("belowThresholdBt"));
        splitter->addWidget(belowThresholdBt);
        splitter_2->addWidget(splitter);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(FilterEdgesByWeightDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(FilterEdgesByWeightDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FilterEdgesByWeightDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FilterEdgesByWeightDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FilterEdgesByWeightDialog);
    } // setupUi

    void retranslateUi(QDialog *FilterEdgesByWeightDialog)
    {
        FilterEdgesByWeightDialog->setWindowTitle(QApplication::translate("FilterEdgesByWeightDialog", "Dialog", 0));
        label_2->setText(QApplication::translate("FilterEdgesByWeightDialog", "With this temporary action, you will make invisible some links according to their weight. Select a threshold then click on the desired radiobox below:", 0));
        label->setText(QApplication::translate("FilterEdgesByWeightDialog", "Weight Threshold", 0));
        overThresholdBt->setText(QApplication::translate("FilterEdgesByWeightDialog", "Filter edges with weight over threshold", 0));
        belowThresholdBt->setText(QApplication::translate("FilterEdgesByWeightDialog", "Filter edges with weight below threshold", 0));
    } // retranslateUi

};

namespace Ui {
    class FilterEdgesByWeightDialog: public Ui_FilterEdgesByWeightDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTEREDGESBYWEIGHTDIALOG_H
