#include "hebrewpanel.h"
#include "ui_hebrewpanel.h"

#define ROWS_COUNT          6
#define COLUMNS_COUNT       4
#define CELL_SIZE           40
#define TOP_SPACE           80

HebrewPanel::HebrewPanel(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::HebrewPanel)
{
    ui->setupUi(this);

    init();
}
//------------------------------------------------------------------------------
HebrewPanel::~HebrewPanel()
{
    for (int i = 0; i < m_buttons.size(); i++)
    {
        delete m_buttons.at(i);
    }
    delete ui;
}
//------------------------------------------------------------------------------
void HebrewPanel::init()
{

    m_capitalCase
            << "?"
            << "?"
            << "?"
            << "?"
            << "?"
            << "?"
            << "?"
            << "?"
            << "?"
            << "?"
            << "??"
            << "?"
            << "?"
            << "??"
            << "?"
            << "?"
            << "?"
            << "?"
            << "?"
            << "?"
            << "?"
            << "?";


    this -> setFixedWidth(CELL_SIZE * COLUMNS_COUNT);
    this -> setFixedHeight(TOP_SPACE + CELL_SIZE * ROWS_COUNT);

    int t_int = 0;
    for(int i = 0; i < ROWS_COUNT; i++)
    {
        for(int j = 0; j < COLUMNS_COUNT; j++)
        {
            if (t_int < 22)
            {
                QPushButton * d = new QPushButton(this);
                d -> setAutoExclusive(true);
                d -> setText(m_capitalCase.at(t_int));
                t_int++;
                d -> setGeometry(j * CELL_SIZE + 20, i * CELL_SIZE + TOP_SPACE, CELL_SIZE, CELL_SIZE);
                d -> show();
                connect(d, SIGNAL(clicked()), SLOT(sPressSymbol()));

                m_buttons.push_back(d);
            }

        }
    }
}
//------------------------------------------------------------------------------
void HebrewPanel::sPressSymbol()
{
    QPushButton *button = (QPushButton *)sender();
    emit SIGNAL_SendSymbol(button->text());
}
//------------------------------------------------------------------------------
