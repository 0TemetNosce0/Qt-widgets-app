/********************************************************************************
** Form generated from reading UI file 'webcrawlerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBCRAWLERDIALOG_H
#define UI_WEBCRAWLERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>

QT_BEGIN_NAMESPACE

class Ui_WebCrawlerDialog
{
public:
    QGridLayout *gridLayout_2;
    QLabel *description;
    QSplitter *splitter;
    QLabel *label;
    QLineEdit *seedUrlEdit;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *maxLinksPerPageSpinBox;
    QLabel *label_4;
    QSpinBox *totalUrlsToCrawlSpinBox;
    QCheckBox *extLinksCheckBox;
    QCheckBox *intLinksCheckBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *WebCrawlerDialog)
    {
        if (WebCrawlerDialog->objectName().isEmpty())
            WebCrawlerDialog->setObjectName(QStringLiteral("WebCrawlerDialog"));
        WebCrawlerDialog->resize(639, 313);
        WebCrawlerDialog->setMinimumSize(QSize(14, 0));
        gridLayout_2 = new QGridLayout(WebCrawlerDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        description = new QLabel(WebCrawlerDialog);
        description->setObjectName(QStringLiteral("description"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(description->sizePolicy().hasHeightForWidth());
        description->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans"));
        font.setPointSize(11);
        description->setFont(font);
        description->setTextFormat(Qt::RichText);
        description->setWordWrap(true);

        gridLayout_2->addWidget(description, 0, 0, 1, 1);

        splitter = new QSplitter(WebCrawlerDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans"));
        label->setFont(font1);
        splitter->addWidget(label);
        seedUrlEdit = new QLineEdit(splitter);
        seedUrlEdit->setObjectName(QStringLiteral("seedUrlEdit"));
        seedUrlEdit->setMinimumSize(QSize(370, 32));
        seedUrlEdit->setMaximumSize(QSize(400, 32));
        seedUrlEdit->setFont(font1);
        splitter->addWidget(seedUrlEdit);

        gridLayout_2->addWidget(splitter, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        label_3 = new QLabel(WebCrawlerDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(201, 0));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        maxLinksPerPageSpinBox = new QSpinBox(WebCrawlerDialog);
        maxLinksPerPageSpinBox->setObjectName(QStringLiteral("maxLinksPerPageSpinBox"));
        maxLinksPerPageSpinBox->setMinimumSize(QSize(46, 0));
        maxLinksPerPageSpinBox->setMinimum(0);
        maxLinksPerPageSpinBox->setMaximum(500);
        maxLinksPerPageSpinBox->setValue(0);

        gridLayout->addWidget(maxLinksPerPageSpinBox, 1, 2, 1, 1);

        label_4 = new QLabel(WebCrawlerDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(230, 0));
        QFont font2;
        font2.setFamily(QStringLiteral("DejaVu Sans"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        label_4->setFont(font2);

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        totalUrlsToCrawlSpinBox = new QSpinBox(WebCrawlerDialog);
        totalUrlsToCrawlSpinBox->setObjectName(QStringLiteral("totalUrlsToCrawlSpinBox"));
        totalUrlsToCrawlSpinBox->setMinimumSize(QSize(46, 0));
        totalUrlsToCrawlSpinBox->setMinimum(0);
        totalUrlsToCrawlSpinBox->setMaximum(9999);
        totalUrlsToCrawlSpinBox->setValue(600);

        gridLayout->addWidget(totalUrlsToCrawlSpinBox, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 1);

        extLinksCheckBox = new QCheckBox(WebCrawlerDialog);
        extLinksCheckBox->setObjectName(QStringLiteral("extLinksCheckBox"));
        extLinksCheckBox->setMinimumSize(QSize(13, 0));
        extLinksCheckBox->setFont(font1);
        extLinksCheckBox->setFocusPolicy(Qt::TabFocus);
        extLinksCheckBox->setLayoutDirection(Qt::LeftToRight);
        extLinksCheckBox->setChecked(true);
        extLinksCheckBox->setTristate(false);

        gridLayout_2->addWidget(extLinksCheckBox, 3, 0, 1, 1);

        intLinksCheckBox = new QCheckBox(WebCrawlerDialog);
        intLinksCheckBox->setObjectName(QStringLiteral("intLinksCheckBox"));
        intLinksCheckBox->setFont(font1);
        intLinksCheckBox->setFocusPolicy(Qt::TabFocus);
        intLinksCheckBox->setLayoutDirection(Qt::LeftToRight);
        intLinksCheckBox->setChecked(true);

        gridLayout_2->addWidget(intLinksCheckBox, 4, 0, 1, 1);

        buttonBox = new QDialogButtonBox(WebCrawlerDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setFont(font1);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 5, 0, 1, 1);


        retranslateUi(WebCrawlerDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), WebCrawlerDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WebCrawlerDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(WebCrawlerDialog);
    } // setupUi

    void retranslateUi(QDialog *WebCrawlerDialog)
    {
        WebCrawlerDialog->setWindowTitle(QApplication::translate("WebCrawlerDialog", "Dialog", 0));
        description->setText(QApplication::translate("WebCrawlerDialog", "<html><head/><body><p><span style=\" font-family:'DejaVu Sans'; font-size:10pt;\">SocNetV includes a simple web crawler. It scans the HTML  code of a given initial URL  (i.e. a website) and maps all internal or external links to other pages found there. As new urls are discovered, the crawler follows them to scan their HTML code for links as well.  For more details, see the Manual.</span></p></body></html>", 0));
        label->setText(QApplication::translate("WebCrawlerDialog", "Enter the initial URL to start crawling:", 0));
#ifndef QT_NO_TOOLTIP
        seedUrlEdit->setToolTip(QApplication::translate("WebCrawlerDialog", "<html><head/><body><p>Enter the initial url/domain to start crawling from, i.e. http://www.iefimerida.gr  </p><p>You may omit http:// if you want. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("WebCrawlerDialog", "Set the max links inside a page to be followed and crawled by SocNetV.\n"
"\n"
" Set this to zero if you don't want to have this limit. \n"
"In this case SocNetV will follow and crawl each one link found in a page.", 0));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("WebCrawlerDialog", "Max links in each page to follow", 0));
#ifndef QT_NO_TOOLTIP
        maxLinksPerPageSpinBox->setToolTip(QApplication::translate("WebCrawlerDialog", "Set the max links inside a page to be followed and crawled by SocNetV.\n"
"\n"
" Set this to zero if you don't want to have this limit. \n"
"In this case SocNetV will follow and crawl each one link found in a page.", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_4->setToolTip(QApplication::translate("WebCrawlerDialog", "Set the total urls to be crawled - this is the total nodes the result network will have. \n"
"Set value to 0, if you don't want any limits...", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("WebCrawlerDialog", "Total urls  to crawl", 0));
#ifndef QT_NO_TOOLTIP
        totalUrlsToCrawlSpinBox->setToolTip(QApplication::translate("WebCrawlerDialog", "Set the total urls to be crawled - this is the total nodes the result network will have. \n"
"Set value to 0, if you don't want any limits...", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        totalUrlsToCrawlSpinBox->setWhatsThis(QApplication::translate("WebCrawlerDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Maximum Nodes to display</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">In this spinbox, you define the maximum nodes to be displayed by SocNetV when running in Web Crawler mode. Set value to 0, if you don't want any limits...</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        extLinksCheckBox->setToolTip(QApplication::translate("WebCrawlerDialog", "<html><head/><body><p>If enabled, the crawler will map <span style=\" font-weight:600;\">external links</span>. For instance, if you start crawling from www.iefimerida.gr and we find there a link to another domain, i.e. www.linuxinsider.gr, then we will go outside of iefimerida.gr and crawl linuxinsider.gr too. </p><p><br/></p><p>If you don't want to crawl external links, disable this option. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        extLinksCheckBox->setText(QApplication::translate("WebCrawlerDialog", "Crawl external links", 0));
#ifndef QT_NO_TOOLTIP
        intLinksCheckBox->setToolTip(QApplication::translate("WebCrawlerDialog", "<html><head/><body><p>If enabled the crawler will scan and map <span style=\" font-weight:600;\">internal links </span>as well (i.e. pages within the initial website).</p><p> If you do not want to crawl internal links disable this option. Default is not to crawl internal links.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        intLinksCheckBox->setText(QApplication::translate("WebCrawlerDialog", "Crawl internal links", 0));
    } // retranslateUi

};

namespace Ui {
    class WebCrawlerDialog: public Ui_WebCrawlerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBCRAWLERDIALOG_H
