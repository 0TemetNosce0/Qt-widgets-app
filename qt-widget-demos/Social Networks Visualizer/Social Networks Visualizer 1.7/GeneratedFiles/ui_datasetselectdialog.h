/********************************************************************************
** Form generated from reading UI file 'datasetselectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATASETSELECTDIALOG_H
#define UI_DATASETSELECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DataSetSelectDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *description_image;
    QLabel *description;
    QLabel *selectLabel;
    QComboBox *selectBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DataSetSelectDialog)
    {
        if (DataSetSelectDialog->objectName().isEmpty())
            DataSetSelectDialog->setObjectName(QStringLiteral("DataSetSelectDialog"));
        DataSetSelectDialog->setEnabled(true);
        DataSetSelectDialog->resize(592, 195);
        DataSetSelectDialog->setMaximumSize(QSize(600, 195));
        gridLayout = new QGridLayout(DataSetSelectDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        description_image = new QLabel(DataSetSelectDialog);
        description_image->setObjectName(QStringLiteral("description_image"));
        description_image->setMinimumSize(QSize(60, 70));
        description_image->setMaximumSize(QSize(32, 110));
        description_image->setTextFormat(Qt::RichText);
        description_image->setWordWrap(true);

        gridLayout->addWidget(description_image, 0, 0, 1, 1);

        description = new QLabel(DataSetSelectDialog);
        description->setObjectName(QStringLiteral("description"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(description->sizePolicy().hasHeightForWidth());
        description->setSizePolicy(sizePolicy);
        description->setMinimumSize(QSize(450, 70));
        description->setMaximumSize(QSize(0, 110));
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans"));
        font.setPointSize(11);
        description->setFont(font);
        description->setTextFormat(Qt::RichText);
        description->setWordWrap(true);

        gridLayout->addWidget(description, 0, 1, 1, 1);

        selectLabel = new QLabel(DataSetSelectDialog);
        selectLabel->setObjectName(QStringLiteral("selectLabel"));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans"));
        font1.setPointSize(10);
        selectLabel->setFont(font1);

        gridLayout->addWidget(selectLabel, 1, 0, 1, 1);

        selectBox = new QComboBox(DataSetSelectDialog);
        selectBox->setObjectName(QStringLiteral("selectBox"));
        selectBox->setEnabled(true);
        selectBox->setMinimumSize(QSize(494, 20));
        QFont font2;
        font2.setFamily(QStringLiteral("Sans Serif"));
        font2.setPointSize(10);
        selectBox->setFont(font2);
        selectBox->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(selectBox, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(DataSetSelectDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        QFont font3;
        font3.setFamily(QStringLiteral("DejaVu Sans"));
        buttonBox->setFont(font3);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(DataSetSelectDialog);

        QMetaObject::connectSlotsByName(DataSetSelectDialog);
    } // setupUi

    void retranslateUi(QDialog *DataSetSelectDialog)
    {
        DataSetSelectDialog->setWindowTitle(QApplication::translate("DataSetSelectDialog", "Select Data Set", 0));
        description_image->setText(QApplication::translate("DataSetSelectDialog", "<html><head/><body><p><img src=\":/images/socnetv-32px.png\"/></p></body></html>", 0));
        description->setText(QApplication::translate("DataSetSelectDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'DejaVu Sans'; font-size:10pt;\">SocNetV is able to automatically create known data sets, such as </span><span style=\" font-family:'DejaVu Sans'; font-size:10pt; font-style:italic;\">Padgett</span><span style=\" font-family:'DejaVu Sans'; font-size:10pt;\">'s florentine families etc. </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'DejaVu Sans'; font-size:10pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margi"
                        "n-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'DejaVu Sans'; font-size:10pt;\">Select the data set you want to re-create from the list below: </span></p></body></html>", 0));
        selectLabel->setText(QApplication::translate("DataSetSelectDialog", "Select", 0));
#ifndef QT_NO_TOOLTIP
        selectBox->setToolTip(QApplication::translate("DataSetSelectDialog", "<html><head/><body><p>Click to select a data set</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class DataSetSelectDialog: public Ui_DataSetSelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATASETSELECTDIALOG_H
