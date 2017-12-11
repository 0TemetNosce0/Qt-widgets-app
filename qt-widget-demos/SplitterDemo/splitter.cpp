#include "splitter.h"
#include "ui_splitter.h"
#include <QTextEdit>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>

splitter::splitter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::splitter)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout();

    QTextEdit *editor1 = new QTextEdit;
    QTextEdit *editor2 = new QTextEdit;
    QTextEdit *editor3 = new QTextEdit;

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(editor1);
    splitter->addWidget(editor2);
    splitter->addWidget(editor3);

    editor1->setPlainText("Mon enfant, ma soeur,\n"
                          "Songe  la douceur\n"
                          "D'aller l-bas vivre ensemble,\n"
                          "Aimer  loisir,\n"
                          "Aimer et mourir\n"
                          "Au pays qui te ressemble.");
    editor2->setPlainText("My child, my sister,\n"
                          "think of the sweetness\n"
                          "of going there to live together!\n"
                          "To love at leisure,\n"
                          "to love and to die\n"
                          "in a country that is the image of you!");
    editor3->setPlainText("Mein Kind, meine Schwester,\n"
                          "denke an den Traum\n"
                          "dort hin(unter) zu gehen um zusammen\n"
                          "zu leben und in aller Ruhe zu lieben,\n"
                          "Zu lieben und zu sterben\n"
                          "in dem Land, das dir gleicht.");

    layout->addWidget(splitter);
    ui->centralWidget->setLayout(layout);

}

splitter::~splitter()
{
    delete ui;
}
