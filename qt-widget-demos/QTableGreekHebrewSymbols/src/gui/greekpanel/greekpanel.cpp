#include "greekpanel.h"
#include "ui_greekpanel.h"

#include "debughelper.h"

#include <QPushButton>

#define ROWS_COUNT          6
#define COLUMNS_COUNT       4
#define CELL_SIZE           40
#define TOP_SPACE           80

GreekPanel::GreekPanel(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::GreekPanel)
{
    ui->setupUi(this);

    init();
}
//------------------------------------------------------------------------------
GreekPanel::~GreekPanel()
{
    for (int i = 0; i < m_buttons.size(); i++)
    {
        delete m_buttons.at(i);
    }
    delete ui;
}
//------------------------------------------------------------------------------
void GreekPanel::init()
{

    m_lowerCase
            << "α"
            << "β"
            << "γ"
            << "δ"
            << "ε"
            << "ζ"
            << "η"
            << "θ"
            << "ι"
            << "κ"
            << "λ"
            << "μ"
            << "ν"
            << "ξ"
            << "ο"
            << "π"
            << "ρ"
            << "σ"
            << "τ"
            << "υ"
            << "φ"
            << "χ"
            << "ψ"
            << "ω";

    m_capitalCase
            << "Α"
            << "Β"
            << "Γ"
            << "Δ"
            << "Ε"
            << "Ζ"
            << "Η"
            << "Θ"
            << "Ι"
            << "Κ"
            << "Λ"
            << "Μ"
            << "Ν"
            << "Ξ"
            << "Ο"
            << "Π"
            << "Ρ"
            << "Σ"
            << "Τ"
            << "Υ"
            << "Φ"
            << "Χ"
            << "Ψ"
            << "Ω";

    this -> setFixedWidth(CELL_SIZE * COLUMNS_COUNT);
    this -> setFixedHeight(TOP_SPACE + CELL_SIZE * ROWS_COUNT);

    int t_int = 0;
    for(int i = 0; i < ROWS_COUNT; i++)
    {
        for(int j = 0; j < COLUMNS_COUNT; j++)
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


    //    char lowerCase[COUNT_SYMBOLS_GREEK] = { "α","β","γ","δ","ε","ζ"
    //                                           , "η","θ","ι","κ","λ","μ"
    //                                           , "ν","ξ","ο","π","ρ","σ"
    //                                           , "τ","υ","φ","χ","ψ","ω"};

    //    char capitalCase[COUNT_SYMBOLS_GREEK] = { "Α","Β","Γ","Δ","Ε","Ζ"
    //                                           , "Η","Θ","Ι","Κ","Λ","Μ"
    //                                           , "Ν","Ξ","Ο","Π","Ρ","Σ"
    //                                           , "Τ","Υ","Φ","Χ","Ψ","Ω"};
}
//------------------------------------------------------------------------------
void GreekPanel::sPressSymbol()
{
    QPushButton *button = (QPushButton *)sender();
    if (ui->checkBUpper->isChecked())
    {
        emit SIGNAL_SendSymbol(button->text());
    }
    else
    {
        int t_int = 0;
        do
        {
            t_int++;
        } while (m_capitalCase.at(t_int) != button->text());

        emit SIGNAL_SendSymbol(m_lowerCase.at(t_int));
    }
}
//------------------------------------------------------------------------------
