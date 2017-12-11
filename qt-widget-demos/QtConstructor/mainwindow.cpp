// This file is part of QtConstructor.
// Copyright (c) 2015, Diego Queiroz dos Santos, drift@linuxmail.com
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//
// * Neither the name of its contributors may be used to endorse or promote
// products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString MainWindow::combobox_stylesheet  = "min-width: 10em; padding: 1px 18px 1px 3px; ";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , is_editable(false)
    , is_changed(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new database();
    setTheme(STYLE_FUSION);
    start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTheme(int type)
{
    QPalette p = qApp->palette();
    switch (type)
    {
    case STYLE_FUSION:
        qApp->setStyle(QStyleFactory::create("Fusion"));
        p.setColor(QPalette::Window, QColor(53,53,53));
        p.setColor(QPalette::Button, QColor(53,53,53));
        p.setColor(QPalette::Highlight, QColor(142,45,197));
        p.setColor(QPalette::ButtonText, QColor(255,255,255));
        p.setColor(QPalette::WindowText, QColor(255,255,255));
        break;
    default:
        _D << "Theme not found!!!";
        break;
    }
    qApp->setPalette(p);
}

void MainWindow::setLayoutTheme(QLayout *layout)
{
    layout->setSpacing(10);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
}

void MainWindow::start()
{
    info_status = new QLabel();
    ui->centralWidget->layout()->addWidget(info_status);

    startBuilder();
}

void MainWindow::startBuilder()
{
    builder = new BuilderWizard();
    builder->start(db);

    CINT idx = ui->tabWidget->addTab(builder, "Builder");
    ui->tabWidget->setTabIcon(idx, getIcon("wrench"));
    ui->tabWidget->setCurrentIndex(idx);

    connect(builder, SIGNAL(start_mainwindow()), this, SLOT(call_menus()));

    connect(builder, SIGNAL(send_info(const QString, const int)),
            this, SLOT(statusFormulario(const QString, const int)));

    connect(builder, SIGNAL(addQaction(pv)), this, SLOT(addQaction(pv)));
    connect(builder, SIGNAL(addMenu()), this, SLOT(call_menus()));
    connect(builder, SIGNAL(removeMenuAction(int, qs)), this, SLOT(removeMenuAction(int, qs)));
}

void MainWindow::call_menus()
{
    menuBar()->clear();

    QString sql_get_menus = "CALL get_menus()";
    menus = db->get_all(sql_get_menus);
    CINT t = menus.count();

    for( int i = 0 ; i < t ; ++ i )
    {
        pv menu_list = menus.at(i);
        addMenu(menu_list);
    }
}

void MainWindow::addMenu(pv r)
{
    CINT MENU_ID = r.value("MENU_ID").toInt();
    QS MENU_NAME = r.value("MENU_NAME").toString();
    CINT MENU_STATUS = r.value("MENU_STATUS").toInt();

    if(MENU_STATUS == 1)
    {
        mainmenu = new QMenu(MENU_NAME, this);
        menuBar()->addMenu(mainmenu);
        callActions(MENU_ID);

        connect(mainmenu, SIGNAL(triggered(QAction*)), this, SLOT(getAction(QAction*)));
    }
}

void MainWindow::getAction(QAction* action)
{
    PV r = action->data().toHash();
    QS ACTION_SLOT = "1" + r.value("ACTION_SLOT").toString();

    if(!callSlotsByName(ACTION_SLOT.mid(1)))
    {
        mainLayout(r);
    }
}

void MainWindow::callActions(const int fk_menu_id)
{
    qs sql = QString("CALL get_action_by_menu_id(%1)").arg(fk_menu_id);
    actions = db->get_all(sql);
    CINT t = actions.count();

    for(int i = 0 ; i < t ; ++ i)
    {
        PV r = actions.at(i);
        addQaction(r);
    }
}

void MainWindow::addQaction(pv r)
{
    CINT ACTION_STATUS = r.value("ACTION_STATUS").toInt();
    QS ACTION_NOME = r.value ("ACTION_NAME").toString();
    QS ACTION_ICONE = r.value("ACTION_ICONE").toString();
    QS ACTION_TOOLTIP = r.value("ACTION_TOOLTIP").toString();
    QS ACTION_SLOT = "1" + r.value("ACTION_SLOT").toString();

    if(ACTION_STATUS == 1)
    {
        QAction * act_btn = new QAction(ACTION_NOME, this);
        act_btn->setToolTip(ACTION_TOOLTIP);
        act_btn->setIcon(QIcon(ACTION_ICONE));
        act_btn->setData(r);

        if(callSlotsByName(ACTION_SLOT.mid(1)))
        {
            connect(act_btn, SIGNAL( triggered()) ,this, ACTION_SLOT.toUtf8().constData(), Qt::UniqueConnection);
        }
        mainmenu->addAction(act_btn);
    }
}

void MainWindow::removeMenuAction(int type, qs name)
{
    QList<QAction*> act = mainmenu->actions();
    CINT total = act.count();
    for(int i =0; i < total; ++i)
    {
        qs action = act.at(i)->text();
        if(action == name)
        {
            if(type == MENU)
            {
                call_menus();
            }
            else if(type == ACTION)
            {
                mainmenu->removeAction(act.at(i));
            }
        }
    }
}

bool MainWindow::callSlotsByName(const QString & slot_name)
{
    const QMetaObject *o = metaObject();
    const int slot_index = o->indexOfSlot(slot_name.toUtf8().constData());

    if(slot_index != -1)
    {
        QMetaMethod method = o->method(slot_index);
        const bool status = method.isValid();

        if(!status)
        {
            return false;
        }

    }
    else
    {
        _D << QString("Slot not implemented: %1. Its a default slot?" ).arg(slot_name);
        return false;
    }
    return true;
}

void MainWindow::createBtns(QWidget *wdg, const int type)
{
    qs sql = "CALL get_buttons()" ;
    botoes = db->get_all(sql);

    QGroupBox *h_groupbox = new QGroupBox();
    QHBoxLayout *h_layout = new QHBoxLayout();

    h_groupbox->setLayout(h_layout);
    wdg->layout()->addWidget(h_groupbox);

    CINT t = botoes.count();
    for(int i = 0 ; i < t ; ++ i)
    {
        PV r = botoes.at(i);
        QS BUTTON_NAME = r.value("BUTTON_NAME").toString();
        CINT BUTTON_STATUS = r.value("BUTTON_STATUS").toInt();
        CINT BUTTON_WIDGET = r.value("BUTTON_WIDGET").toInt();
        QS BUTTON_STYLESHEET = r.value("BUTTON_STYLESHEET").toString();
        QS BUTTON_ICON = r.value("BUTTON_ICON").toString();
        QS BUTTON_TOOLTIP = r.value("BUTTON_TOOLTIP").toString();
        QS BUTTON_SLOT = "1" + r.value("BUTTON_SLOT").toString();

        if(BUTTON_STATUS == 0)
        {
            continue;
        }

        if(BUTTON_WIDGET != type)
        {
            continue;
        }

        QPushButton * btn = new QPushButton(QIcon(BUTTON_ICON), BUTTON_NAME);
        btn->setFlat(true);
        btn->setToolTip(BUTTON_TOOLTIP);
        btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        btn->setStyleSheet(BUTTON_STYLESHEET);
        h_layout->addWidget(btn, Qt::AlignRight);

        if(BUTTON_STATUS == 1)
        {
            if(callSlotsByName(BUTTON_SLOT.mid(1)))
            {
                connect(btn, SIGNAL(clicked()) ,this, BUTTON_SLOT.toUtf8().constData());
            }
        }
    }
}

QPushButton* MainWindow::getBtn(const int btn_id)
{
    qs sql = QString("CALL get_btn_by_id(%1)").arg(btn_id) ;
    lpv botoes_ = db->get_all(sql);

    CINT t = botoes_.count();
    for(int i = 0 ; i < t ; ++ i)
    {
        PV r = botoes_.at(i);
        QS BUTTON_NAME = r.value("BUTTON_NAME").toString();
        CINT BUTTON_STATUS = r.value("BUTTON_STATUS").toInt();
        QS BUTTON_STYLESHEET = r.value("BUTTON_STYLESHEET").toString();
        QS BUTTON_ICON = r.value("BUTTON_ICON").toString();
        QS BUTTON_TOOLTIP = r.value("BUTTON_TOOLTIP").toString();
        QS BUTTON_SLOT = "1" + r.value("BUTTON_SLOT").toString();

        QPushButton* btn = new QPushButton(QIcon(BUTTON_ICON), BUTTON_NAME);
        btn->setToolTip(BUTTON_TOOLTIP);
        btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        btn->setStyleSheet(BUTTON_STYLESHEET);

        if(BUTTON_STATUS == 1)
        {
            if(callSlotsByName(BUTTON_SLOT.mid(1)))
            {
                connect( btn, SIGNAL( clicked() ) ,this, BUTTON_SLOT.toUtf8().constData());
            }
        }

        return btn;
    }

    return new QPushButton();
}

void MainWindow::mainLayout(pv r)
{
    CINT idx = getNewTab(LAYOUT_VERTICAL);
    r.insert("CURRENT_INDEX", idx);
    widgetSetStuff(r);
}

void MainWindow::widgetSetStuff(pv r)
{
    QS ACTION_NAME = r.value("ACTION_NAME").toString();
    QS ACTION_ICON =  r.value("ACTION_ICON").toString();
    QS ACTION_TOOLTIP = r.value("ACTION_TOOLTIP").toString();
    CINT CURRENT_INDEX = r.value("CURRENT_INDEX").toInt();

    ui->tabWidget->setTabIcon(CURRENT_INDEX, QIcon(ACTION_ICON));
    ui->tabWidget->setTabText(CURRENT_INDEX, ACTION_NAME);
    ui->tabWidget->setTabToolTip(CURRENT_INDEX, ACTION_TOOLTIP);

    createTemplateMenus(r);

}

void MainWindow::createTemplateMenus(pv r)
{
    CINT CURRENT_INDEX = r.value("CURRENT_INDEX").toInt() ;
    createBtns(ui->tabWidget->widget(CURRENT_INDEX), WDG_PRINCIPAL);

    createSearchForm();
    createTableForm();
    populateSearchCombobox(r);
    populateTableForm(r);
}

void MainWindow::populateTableForm(pv r)
{
    CINT idx = r.value("ACTION_ID").toInt();
    ui->tabWidget->currentWidget()->setProperty("ACTION_ID", idx);
    populateTableHeader(r);
    populateTable(idx);
}

void MainWindow::createSearchForm()
{
    QGroupBox *combo_groupbox = new QGroupBox();
    search_combobox = new QComboBox();
    search_lineedit = new QLineEdit();
    search_lineedit->setPlaceholderText(tr("Search the filter and press ENTER"));
    QGridLayout *combo_layout = new QGridLayout();
    combo_groupbox->setLayout( combo_layout );

    qs combobox_stylesheet = "QComboBox {\n     "
            "border: 1px solid gray;\n"
            "border-radius: 3px;\n"
            "padding: 1px 18px 1px 3px;\n"
            "min-width: 10em;\n }\n\n"
            " QComboBox:editable {\n     "
            "background: white;\n }\n\n "
            "QComboBox:!editable, "
            "QComboBox::drop-down:editable {\n      "
            "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
            "stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n "
            "stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n "
            "}\n\n\n "
            "QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n     "
            "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n                                 "
            "stop: 0 #D3D3D3, stop: 0.4 #D8D8D8,\n                                 "
            "stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);\n }\n\n "
            "QComboBox:on { /* shift the text when the popup opens */\n     "
            "padding-top: 3px;\n     padding-left: 4px;\n }\n\n QComboBox::drop-down {\n     "
            "subcontrol-origin: padding;\n     subcontrol-position: top right;\n     "
            "width: 15px;\n\n     border-left-width: 1px;\n     "
            "border-left-color: darkgray;\n     "
            "border-left-style: solid;\n     "
            "border-top-right-radius: 3px; \n     "
            "border-bottom-right-radius: 3px;\n }\n\n ";

    search_combobox->setStyleSheet(combobox_stylesheet);

    QPushButton *refresh = getBtn(BTN_REFRESH);
    refresh->setText("");

    combo_layout->addWidget(search_combobox ,0, 0);
    combo_layout->addWidget(search_lineedit ,0, 1);
    combo_layout->addWidget(refresh ,0, 2 );

    wdg->layout()->addWidget(combo_groupbox);
}

void MainWindow::createTableForm()
{
    search_table = new QTableView( );
    model = new QStandardItemModel();

    connect( search_table, SIGNAL( clicked( QModelIndex )),
             this, SLOT(search_table_clicked( QModelIndex )), Qt::UniqueConnection );

    //connect( model, SIGNAL(itemChanged( QStandardItem *)),
    // this, SLOT(model_data_changed( QStandardItem* )));

    search_table->setModel(model);
    search_table->setSortingEnabled(true);
    search_table->sortByColumn(0);
    search_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    search_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    search_table->setAutoScroll(true);

    wdg->layout()->addWidget(search_table);
}

void MainWindow::modelDataChanged(QStandardItem *item)
{
    CINT row =  item->row();
    CINT column =  item->column();

    CINT total_column = model->columnCount();

    QString data = model->index(row, column).data().toString();

    lpv componentes = get_components();
    for( int i = 0; i < total_column; ++i )
    {
        pv r = componentes.at( i );
        QS COMPONENT_NAME = r.value("COMPONENT_NAME").toString();
        CINT COMPONENT_ORDER = r.value("COMPONENT_ORDER").toInt();

        _D << COMPONENT_NAME << model->index(COMPONENT_ORDER,i).data().toString();
    }
}

void MainWindow::populateTableHeader(pv r)
{
    CINT idx = r.value("ACTION_ID").toInt();
    lpv componentes = get_component_by_action_id(idx);
    CINT total = componentes.count();

    for( int i = 0; i < total; ++i )
    {
        PV valores = componentes.at( i );
        QS COMPONENT_NAME = valores.value("COMPONENT_NAME").toString();
        QS COMPONENTE_ICONE = valores.value("COMPONENT_ICON").toString();
        QS COMPONENT_TOOLTIP = valores.value("COMPONENT_TOOLTIP").toString();
        CINT COMPONENT_ORDER = valores.value("COMPONENT_ORDER").toInt();
        CINT COMPONENT_STATUS = valores.value("COMPONENT_STATUS").toInt();


        QStandardItem *item = new QStandardItem(QIcon(COMPONENTE_ICONE), COMPONENT_NAME);
        item->setData(valores);
        item->setToolTip(COMPONENT_TOOLTIP);
        model->setHorizontalHeaderItem(COMPONENT_ORDER , item);

        if(COMPONENT_STATUS == 0)
        {
            search_table->setColumnHidden(COMPONENT_ORDER, true);
        }
    }
    search_table->horizontalHeader()->setStretchLastSection(true);
    search_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::populateTable(const int action_id)
{
    lpv componentes = get_component_by_action_id(action_id);

    CINT t = componentes.count();
    for(int i = 0 ; i < t ; ++ i)
    {
        PV r = componentes.at(i);
        populateTable(r);
    }

    is_changed = false;
}

void MainWindow::populateTable(pv r)
{
    QS COMPONENT_COLUMN = r.value("COMPONENT_COLUMN").toString();
    QS COMPONENT_TABLE = r.value("COMPONENT_TABLE").toString();

    CINT COMPONENT_ORDER = r.value("COMPONENT_ORDER").toInt();
    CINT COMPONENT_STATUS = r.value("COMPONENT_STATUS").toInt();

    qs sql = QString("SELECT %1 FROM %2").arg(COMPONENT_COLUMN).arg(COMPONENT_TABLE) ;
    lpv resultado = db->get_all(sql);
    CINT t = resultado.count();

    for(int i = 0; i < t; ++i)
    {
        QS v = resultado.at(i).value(COMPONENT_COLUMN).toString();
        r.insert("VALOR_ITEM", v);
        QStandardItem *item = qvariantType(r);
        model->setItem(i, COMPONENT_ORDER, item);
        item->setData(Qt::AlignCenter, Qt::TextAlignmentRole);

        if(COMPONENT_STATUS == 0)
        {
            search_table->setColumnHidden(COMPONENT_ORDER, true);
        }
    }
}

QStandardItem* MainWindow::qvariantType(pv r)
{
    CINT COMPONENT_TYPE = r.value("COMPONENT_TYPE").toInt();

    switch (COMPONENT_TYPE)
    {
    case TIPO_INT:
    {
        int campo = r.value("VALOR_ITEM").toInt();
        return new QStandardItem( campo );
        break;
    }
    case TIPO_STRING:
    {
        QString campo = r.value("VALOR_ITEM").toString();
        return new QStandardItem(campo);
        break;
    }
    case TIPO_DATE:
    {
        QString campo = r.value("VALOR_ITEM").toDate().toString("dd.MM.yy");
        return new QStandardItem(campo);
        break;
    }
    case TIPO_DATETIMEEDIT:
    {
        QString campo = r.value("VALOR_ITEM").toString();
        return new QStandardItem(campo);
        break;
    }
    case TIPO_BOOL:
    {
        bool tipo = r.value("VALOR_ITEM").toBool();
        if(tipo)
        {
            return new QStandardItem(getIcon("tick.png"),"Positivo");
        }
        else
        {
            return new QStandardItem(getIcon("cancel.png"),"Negativo");
        }
        break;
    }
    default:
        QString campo = r.value("VALOR_ITEM").toDate().toString("dd-MM-yy");
        return new QStandardItem(campo);
        break;
    }
}

void MainWindow::populateSearchCombobox(pv r)
{
    CINT idx = r.value("ACTION_ID").toInt();

    lpv componentes = get_component_by_action_id(idx);

    CINT t = componentes.count();
    for( int i = 0 ; i < t ; ++ i )
    {
        PV r = componentes.at(i);

        QS COMPONENTE_ICONE =  r.value("COMPONENT_ICON").toString();
        QS COMPONENT_NAME = r.value("COMPONENT_NAME").toString();
        CINT COMPONENT_STATUS = r.value("COMPONENT_STATUS").toInt();

        if(COMPONENT_STATUS == 1)
        {
            search_combobox->addItem(QIcon(COMPONENTE_ICONE), COMPONENT_NAME, r);
        }
    }

    connect(search_lineedit, SIGNAL(returnPressed()), this, SLOT(search()), Qt::UniqueConnection);
}

void MainWindow::search()
{
    if(is_changed)
    {
        refresh();
    }

    qs str = search_lineedit->text().trimmed();
    pv r = search_combobox->itemData(search_combobox->currentIndex()).toHash();

    QS COMPONENT_COLUMN = r.value("COMPONENT_COLUMN").toString();
    QS COMPONENT_TABLE = r.value("COMPONENT_TABLE").toString();
    CINT COMPONENT_ORDER = r.value("COMPONENT_ORDER").toInt();

    qs sql;
    if(str.isEmpty())
    {
        statusFormulario("Please insert some word ! " , CSS_RED);
        refresh();
        return;
    }
    else
    {
        sql = QString("SELECT * FROM %1 WHERE %2 LIKE '\%\%3\%'")
                .arg(COMPONENT_TABLE)
                .arg(COMPONENT_COLUMN).arg(str) ;
    }

    lpv resultado = db->get_all(sql);
    DUMP(resultado);

    if(resultado.isEmpty())
    {
        statusFormulario("No results! " , CSS_RED);
        return;
    }

    CINT t = resultado.count();

    for(int i = 0; i < t; ++i)
    {
        QS v = resultado.at(i).value(COMPONENT_COLUMN).toString();
        r.insert("VALOR_ITEM", v);
        QStandardItem *item = qvariantType(r);
        model->setItem(i, COMPONENT_ORDER, item);
        item->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    is_changed = true;
}

void MainWindow::addInformationOnForm()
{
    CINT action_id = ui->tabWidget->currentWidget()->property("ACTION_ID").toInt();
    addInformationOnForm(action_id);
}

int MainWindow::getNewTab(int layout_type)
{
    wdg = new QWidget();

    switch (layout_type)
    {
    case LAYOUT_VERTICAL:
    {
        QVBoxLayout *main_layout = new QVBoxLayout();
        wdg->setLayout(main_layout);
        break;
    }
    case LAYOUT_HORIZONTAL:
    {
        QHBoxLayout *main_layout = new QHBoxLayout();
        wdg->setLayout(main_layout);
        break;
    }
    case LAYOUT_FORM:
    {
        QFormLayout *main_layout = new QFormLayout();
        wdg->setLayout(main_layout);
        break;
    }
    default:
        qFatal("Segfault prevention. No layout specified.");
        break;
    }
    CINT idx = ui->tabWidget->addTab(wdg, "");
    ui->tabWidget->setCurrentIndex(idx);

    return idx;
}

void MainWindow::insertTab(int modulo_id)
{
    _D << modulo_id;
    qs sql = QString("CALL get_componentes_externos(%1)").arg(modulo_id);
    lpv callback = db->get_all(sql);

    PV r = callback.at(0);
    QS MODULO_NOME = r.value("MODULO_NOME").toString();

    CINT idx = getNewTab(LAYOUT_FORM);
    ui->tabWidget->setCurrentIndex(idx);

    createBtns(ui->tabWidget->currentWidget(), WDG_FINANCEIRO);

    QGroupBox *add_form_groupbox = new QGroupBox();
    add_form_layout = new QGridLayout();
    add_form_groupbox->setLayout(add_form_layout);
    wdg->layout()->addWidget(add_form_groupbox);

    ui->tabWidget->setTabIcon(idx, QIcon( resource_path + "add"));
    ui->tabWidget->setTabText(idx, QString("Adicionar informação: %1").arg(MODULO_NOME));

    mount_form(callback);
}

void MainWindow::mount_form(lpv dados)
{
    CINT idx = ui->tabWidget->currentIndex();
    CINT t = dados.count();

    for( int i = 0 ; i < t ; ++ i )
    {
        PV r = dados.at( i );
        QS COMPONENT_NAME = r.value("COMPONENT_NAME").toString();
        QS COMPONENT_COLUMN = r.value("COMPONENT_COLUMN").toString();
        QS COMPONENT_TOOLTIP = r.value("COMPONENT_TOOLTIP").toString();
        QS COMPONENT_TABLE = r.value("COMPONENT_TABLE").toString();
        CINT COMPONENT_STATUS = r.value("COMPONENT_STATUS").toInt();
        CINT WIDGET_TYPE = r.value("WIDGET_TYPE").toInt();
        CINT COMPONENT_TYPE = r.value( "COMPONENT_TYPE").toInt();
        CINT COMPONENT_ID = r.value("COMPONENT_ID").toInt();
        CINT COMPONENT_ORDER = r.value("COMPONENT_ORDER").toInt();

        if(COMPONENT_STATUS == 0)
        {
            continue;
        }

        ui->tabWidget->widget(idx)->setWindowTitle(COMPONENT_NAME);

        QPushButton *help = getBtn(BTN_HELP);
        help->setText("");
        help->setProperty("COMPONENT_ID", COMPONENT_ID);

        QLabel *COMPONENT_NAME_ = new QLabel(COMPONENT_NAME);
        add_form_layout->addWidget(COMPONENT_NAME_ , COMPONENT_ORDER, 0);
        add_form_layout->addWidget(help , COMPONENT_ORDER, 2);

        switch (WIDGET_TYPE)
        {
        case CAMPO_QLABEL:
        {
            label_componente = new QLabel();
            label_componente->setProperty("COMPONENT_COLUMN", COMPONENT_COLUMN);
            label_componente->setProperty("COMPONENT_NAME", COMPONENT_NAME);
            label_componente->setProperty("COMPONENT_ID", COMPONENT_ID);
            label_componente->setProperty("COMPONENT_TABLE", COMPONENT_TABLE);
            add_form_layout->addWidget(label_componente , COMPONENT_ORDER, 1);

            entradas_qlabel.insert(COMPONENT_COLUMN, label_componente);
        }
            break;
        case CAMPO_QLINEEDIT:
        {
            lineedit_componente = new QLineEdit();
            lineedit_componente->setProperty("COMPONENT_COLUMN", COMPONENT_COLUMN);
            lineedit_componente->setProperty("COMPONENT_NAME", COMPONENT_NAME);
            lineedit_componente->setProperty("COMPONENT_ID", COMPONENT_ID);
            lineedit_componente->setProperty("COMPONENT_TABLE", COMPONENT_TABLE);
            lineedit_componente->setPlaceholderText(COMPONENT_NAME_->text());
            lineedit_componente->setToolTip(COMPONENT_TOOLTIP);
            add_form_layout->addWidget(lineedit_componente ,COMPONENT_ORDER, 1);

            switch (COMPONENT_TYPE)
            {
            case TIPO_INT:
            {
                _D << "TIPO_INT";
                lineedit_componente->setValidator(new QIntValidator(lineedit_componente));
            }
                break;
            case TIPO_STRING:
            {
                // _D << "TIPO_STRING";
                // QRegExp regex("[_a-zA-Z][_a-zA-Z0-9]+" );
                //QRegExpValidator *v = new QRegExpValidator( regex );
                // lineedit_componente->setValidator( v );
                lineedit_componente->setValidator(0);
            }
                break;
            case TIPO_DATE:
                _D << "TIPO_DATE";
                break;
            case TIPO_DATETIMEEDIT:
                _D << "TIPO_DATETIMEEDIT";
                break;
            case TIPO_BOOL:
                _D << "TIPO_BOOL";
                break;
            default:
                _D << "DEFAULT";
                lineedit_componente->setValidator(0);
                break;
            }

            entradas_lineedit.insert(COMPONENT_COLUMN, lineedit_componente);
        }

            break;
        case CAMPO_QCOMBOBOX:
        {
            QS COMPONENT_SQL = r.value("COMPONENT_SQL").toString();
            combobox_componente = new QComboBox();
            combobox_componente->setProperty("COMPONENT_COLUMN", COMPONENT_COLUMN);
            combobox_componente->setProperty("COMPONENT_NAME", COMPONENT_NAME);
            combobox_componente->setProperty("COMPONENT_ID", COMPONENT_ID);
            combobox_componente->setProperty("COMPONENT_SQL", COMPONENT_SQL);
            combobox_componente->setProperty("COMPONENT_TABLE", COMPONENT_TABLE);
            combobox_componente->setCurrentText(COMPONENT_NAME);
            combobox_componente->setToolTip(COMPONENT_TOOLTIP);
            add_form_layout->addWidget(combobox_componente , COMPONENT_ORDER, 1);

            entradas_combobox.insert(COMPONENT_COLUMN, combobox_componente);
            configureComboboxes(combobox_componente);
        }

            break;
        case TIPO_DATETIMEEDIT:
        {
            datetime_componente = new QDateTimeEdit();
            datetime_componente->setProperty("COMPONENT_COLUMN", COMPONENT_COLUMN);
            datetime_componente->setProperty("COMPONENT_NAME", COMPONENT_NAME);
            datetime_componente->setProperty("COMPONENT_ID", COMPONENT_ID);
            datetime_componente->setProperty("COMPONENT_TABLE", COMPONENT_TABLE);
            datetime_componente->setDateTime(QDateTime::currentDateTime());
            datetime_componente->setCalendarPopup(true);
            datetime_componente->setToolTip(COMPONENT_TOOLTIP);
            add_form_layout->addWidget(datetime_componente , COMPONENT_ORDER, 1);

            entradas_datetimeedit.insert(COMPONENT_COLUMN, datetime_componente);
        }
            break;
        case CAMPO_QDATEEDIT:
        {
            date_componente = new QDateEdit();
            date_componente->setProperty("COMPONENT_COLUMN", COMPONENT_COLUMN);
            date_componente->setProperty("COMPONENT_NAME", COMPONENT_NAME);
            date_componente->setProperty("COMPONENT_ID", COMPONENT_ID);
            date_componente->setProperty("COMPONENT_TABLE", COMPONENT_TABLE);
            date_componente->setDateTime(QDateTime::currentDateTime());
            date_componente->setToolTip(COMPONENT_TOOLTIP);
            add_form_layout->addWidget(date_componente , COMPONENT_ORDER, 1);

            entradas_date.insert(COMPONENT_COLUMN, date_componente);
        }
            break;
        case CAMPO_QCHECKBOX:
        {
            checkbox_componente = new QCheckBox();
            checkbox_componente->setProperty("COMPONENT_COLUMN", COMPONENT_COLUMN);
            checkbox_componente->setProperty("COMPONENT_NAME", COMPONENT_NAME);
            checkbox_componente->setProperty("COMPONENT_ID", COMPONENT_ID);
            checkbox_componente->setProperty("COMPONENT_TABLE", COMPONENT_TABLE);
            checkbox_componente->setToolTip(COMPONENT_TOOLTIP);
            checkbox_componente->setChecked(true);
            add_form_layout->addWidget(checkbox_componente , COMPONENT_ORDER, 1);

            entradas_checkbox.insert(COMPONENT_COLUMN, checkbox_componente);
        }
            break;
        default:
            _D << "!!!!!!" << WIDGET_TYPE; ;
            break;
        }

        connect(help, SIGNAL( clicked()), this, SLOT(help()));

    }
}

void MainWindow::configureComboboxes(QComboBox *combobox_componente)
{
    QS sql = combobox_componente->property("COMPONENT_SQL").toString();
    lpv dados = db->get_all(sql);
    CINT total = dados.count();

    for(int i = 0; i < total; ++i)
    {
        QList<QVariant> lista = dados.at(i).values();
        CINT total_lista = lista.count();
        for(int j = 0; j < total_lista; ++j)
        {
            QS item = lista.at(j).toString();
            combobox_componente->addItem(item);
        }
    }
}

void MainWindow::addInformationOnForm(const int action_id)
{
    CINT idx = getNewTab(LAYOUT_FORM);
    ui->tabWidget->setCurrentIndex(idx);

    createBtns(ui->tabWidget->currentWidget(), WDG_ADICIONAR);

    QGroupBox *add_form_groupbox = new QGroupBox();
    add_form_layout = new QGridLayout();
    add_form_groupbox->setLayout(add_form_layout);
    wdg->layout()->addWidget(add_form_groupbox);

    ui->tabWidget->setTabIcon(idx, QIcon( resource_path + "add"));
    ui->tabWidget->setTabText(idx, "Add information");

    lpv componentes = get_component_by_action_id(action_id);
    mount_form(componentes);
}

void MainWindow::help()
{

}

void MainWindow::saveForm()
{
    qsl colunas;
    qsl valores;
    qs tabela;

    if(! entradas_lineedit.isEmpty())
    {
        QHashIterator< QString, QLineEdit * >
                lineedits( entradas_lineedit);
        while(lineedits.hasNext())
        {
            lineedits.next();
            QS entrada =  lineedits.value()->text();
            if(! entrada.isEmpty())
            {
                valores << escape( lineedits.value()->text());
                colunas << lineedits.value()->property("COMPONENT_COLUMN").toString() ;
                tabela = lineedits.value()->property("COMPONENT_TABLE").toString() ;
            }
            else
            {
                statusFormulario(QString(tr("All fields are necessary! ")) , CSS_RED);
                return;
            }
        }
    }

    if(! entradas_combobox.isEmpty())
    {
        QHashIterator< QString, QComboBox* >
                comboboxes(entradas_combobox);
        while(comboboxes.hasNext())
        {
            comboboxes.next();
            valores << escape(comboboxes.value()->currentText());
            colunas << comboboxes.value()->property("COMPONENT_COLUMN").toString();
            tabela = comboboxes.value()->property("COMPONENT_TABLE").toString() ;
        }
    }

    if(! entradas_datetimeedit.isEmpty())
    {
        QHashIterator< QString, QDateTimeEdit* >
                datetimeedits( entradas_datetimeedit );
        while(datetimeedits.hasNext())
        {
            datetimeedits.next();
            valores << escape( datetimeedits.value()->date().toString("dd.MM.yyyy")) ;
            colunas << datetimeedits.value()->property("COMPONENT_COLUMN").toString();
            tabela = datetimeedits.value()->property("COMPONENT_TABLE").toString() ;
        }
    }

    if(! entradas_date.isEmpty())
    {
        QHashIterator< QString, QDateEdit* >
                datetime( entradas_date );
        while(datetime.hasNext())
        {
            datetime.next();
            valores << escape( datetime.value()->date().toString("dd.MM.yyyy")) ;
            colunas << datetime.value()->property("COMPONENT_COLUMN").toString();
            tabela = datetime.value()->property("COMPONENT_TABLE").toString();
        }
    }

    if(! entradas_checkbox.isEmpty())
    {
        QHashIterator< QString, QCheckBox * >
                checkboxes( entradas_checkbox );
        while(checkboxes.hasNext())
        {
            checkboxes.next();
            if(checkboxes.value()->isChecked())
            {
                valores <<  "True";
            }
            else
            {
                valores << "False";
            }
            colunas << checkboxes.value()->property("COMPONENT_COLUMN").toString();
            tabela = checkboxes.value()->property("COMPONENT_TABLE").toString();
        }
    }

    _D << colunas;
    _D << valores;

    qs sql = QString("INSERT INTO %1 (%2) VALUES(%3)").arg(tabela).
            arg(colunas.join(",")).arg(valores.join(","));

    _D << sql;

    bool sql_ok = db->execRow(sql);
    if(!sql_ok)
    {
        statusFormulario(QString(tr("Save failed ")) , CSS_RED);
        return;
    }
    else
    {
        statusFormulario(QString(tr("Save successfully ")) , CSS_GREEN);
        btnClean();
    }
}

void MainWindow::btnClean()
{
    QHashIterator< QString, QLineEdit * > lineedits(entradas_lineedit);
    while( lineedits.hasNext())
    {
        lineedits.next();
        lineedits.value()->clear();
    }

    QHashIterator< QString, QComboBox* > comboboxes(entradas_combobox);
    while(comboboxes.hasNext())
    {
        comboboxes.next();
        comboboxes.value()->clear();
    }

    QHashIterator< QString, QDateTimeEdit * > datetimeedits(entradas_datetimeedit);
    while(datetimeedits.hasNext())
    {
        datetimeedits.next();
        datetimeedits.value()->setDateTime(QDateTime::currentDateTime());
    }
}

void MainWindow::refresh()
{
    CINT action_id = ui->tabWidget->currentWidget()->property("ACTION_ID").toInt();
    lpv componentes = get_component_by_action_id(action_id);

    CINT total_componentes = componentes.count();

    for(int i = 0 ; i < total_componentes; ++ i)
    {
        PV r = componentes.at(i);
        populateTable(r);
    }

    is_changed = false;
}

void MainWindow::statusFormulario(const QString str, const int css)
{
    info_status->setText(str);

    switch (css) {
    case CSS_RED:
        info_status->setStyleSheet(bg_red+ ";border-radius:2;padding:2px;margin:2px;");
        break;
    case CSS_YELLOW:
        info_status->setStyleSheet(bg_yellow+ ";border-radius:2;padding:2px;margin:2px;");
        break;
    case CSS_BLUE:
        info_status->setStyleSheet(bg_blue+ ";border-radius:2;padding:2px;margin:2px;");
        break;
    case CSS_GREEN:
        info_status->setStyleSheet(bg_green+ ";border-radius:2;padding:2px;margin:2px;");
        break;
    case CSS_GRAY:
        info_status->setStyleSheet(bg_gray + ";border-radius:2;padding:2px;margin:2px;");
        break;
    default:
        info_status->setStyleSheet(bg_red+ ";border-radius:2;padding:2px;margin:2px;");
        break;
    }

    info_status->setVisible(str.size() > 0);

    QTimer::singleShot(INFO_TIME,  this ,SLOT (cleanStatusForm())) ;
}

void MainWindow::cleanStatusForm()
{
    info_status->setText("");
    info_status->setStyleSheet("border-radius:2;padding:2px;margin:2px;");
    info_status->setVisible(true);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->widget( index )->deleteLater();
}

void MainWindow::about()
{
    QMessageBox::about(this,"About","Shaman Easy Builder.");
}

lpv MainWindow::get_components()
{
    qs sql = "CALL get_components()";
    lpv componentes = db->get_all(sql);

    return componentes;
}

lpv MainWindow::get_component_by_action_id(const int id)
{
    qs sql = QString("CALL get_componente_by_action_id(%1)").arg(id) ;
    lpv componentes = db->get_all(sql);
    return componentes;
}

void MainWindow::search_table_clicked(QModelIndex index)
{
    CINT row =  index.row();
    CINT columns = model->columnCount() ;

    qsl valores;

    for(int i = 0; i < columns; ++i)
    {
        valores << index.sibling(row , i).data().toString();
    }
}

void MainWindow::set_table_editable()
{
    if(is_editable)
    {
        is_editable = false;
        search_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        statusFormulario(QString(tr("Table edit disabled !")) , CSS_RED);
    }
    else
    {
        is_editable = true;
        search_table->setEditTriggers(QAbstractItemView::DoubleClicked);
        statusFormulario(QString(tr("Table edit enabled !")) , CSS_GREEN);
    }
}

void MainWindow::removeRow()
{
    if(! is_editable)
    {
        statusFormulario(QString(tr("Please enable the edit mode !")) , CSS_RED);
        return;
    }

    bool confirma_delete = confirmation(tr("Delete"), tr("Are you sure?"));
    if(! confirma_delete)
    {
        statusFormulario(tr("Canceled!") , CSS_RED);
        return;
    }

    QItemSelectionModel* selected = search_table->selectionModel();

    CINT total_rows = model->rowCount();
    if(total_rows == 0)
    {
        statusFormulario(tr("empty table!") , CSS_RED);
        return;
    }

    QModelIndex index = selected->currentIndex();
    if(! selected->isSelected(index))
    {
        statusFormulario(tr("Please select one row! ") , CSS_RED);
        return;
    }

    CINT row =  index.row();

    qsl valores;
    qsl colunas;
    qs tabela;

    CINT action_id = ui->tabWidget->currentWidget()->property("ACTION_ID").toInt();
    lpv componentes = get_component_by_action_id(action_id);
    CINT t = componentes.count();
    for(int i = 0 ; i < t ; ++ i)
    {
        valores <<  escape(index.sibling(row , i).data().toString());
        PV r = componentes.at(i);
        QS COMPONENT_COLUMN = r.value("COMPONENT_COLUMN").toString();
        QS COMPONENT_TABLE = r.value("COMPONENT_TABLE").toString();
        CINT COMPONENT_ORDER = r.value("COMPONENT_ORDER").toInt();
        colunas.insert(COMPONENT_ORDER, COMPONENT_COLUMN);

        tabela = COMPONENT_TABLE;
    }

    qs sql = QString("DELETE FROM %1  WHERE  %2 = %3 ").arg(tabela).
            arg(colunas.at(0)).arg( valores.at(0));

    bool sql_ok = db->execRow(sql);
    if(!sql_ok)
    {
        statusFormulario(tr("Delete fail ! ") , CSS_RED);
        return;
    }
    else
    {
        statusFormulario(tr("Delete successfully ! ") , CSS_GREEN);
        model->removeRow(row);
    }
}

QStringList MainWindow::formGetText(int row)
{
    CINT total_colunas = model->columnCount();
    qsl valores;

    for(int i = 0; i < total_colunas; ++i)
    {
        qs valor = model->item(row , i)->text();
        valores << valor;
    }
    return valores;

}

QStringList MainWindow::formGetHeader()
{
    CINT action_id = ui->tabWidget->currentWidget()->property("ACTION_ID").toInt();
    lpv componentes = get_component_by_action_id(action_id);
    qsl titulos;

    CINT total_colunas = model->columnCount();

    for(int i = 0 ; i < total_colunas ; ++ i)
    {
        PV r = componentes.at(i);

        QS COMPONENT_NAME = r.value("COMPONENT_NAME").toString();
        CINT COMPONENT_ORDER = r.value("COMPONENT_ORDER").toInt();
        titulos.insert(COMPONENT_ORDER, COMPONENT_NAME);
    }

    return titulos;
}

void MainWindow::htmlSetTitle(qs str)
{
    title = table_html_begin + row_begin + header_cell_style +
            str + header_cell_end + row_end;

}

void MainWindow::htmlSetHeaderTitles(qsl str)
{
    CINT total = str.count();
    qs tmp;

    for(int i = 0; i < total; ++i)
    {
        tmp.append(cell_begin + str.at(i) + cell_end);
    }

    header_titles = table_html_begin + row_begin +
            tmp + header_cell_end + row_end;

}

void  MainWindow::htmlAppendRow(qsl str)
{
    CINT total = str.count();
    qs tmp;

    for( int i = 0; i < total; ++ i )
    {
        tmp.append( cell_begin + str.at(i) + cell_end );
    }

    rows.append(row_begin  + tmp + row_end);
}


qs MainWindow::htmlMount()
{
    html_final = html_style + table_html_begin +
            title + header_titles + rows.join("");
    return html_final;
}

void MainWindow::makeHtml()
{
    QStringList header = formGetHeader();

    htmlSetTitle( QString("Relatório - %1 ").arg(QDateTime::currentDateTime().toString()));
    htmlSetHeaderTitles(header);

    QItemSelectionModel* selected = search_table->selectionModel();
    CINT total_rows = model->rowCount();

    if(total_rows == 0)
    {
        statusFormulario(tr("Empty table! ") , CSS_RED);
        return;
    }

    QModelIndex index = selected->currentIndex();

    if(! selected->isSelected(index))
    {
        for(int i = 0; i < total_rows; ++i)
        {
            qsl rows = formGetText(i);
            htmlAppendRow(rows);
        }
    }
    else
    {
        QModelIndexList rows_selected = selected->selectedRows();
        CINT total_indexes = rows_selected.count();
        for(int i = 0; i < total_indexes; ++i)
        {
            qsl rows = formGetText(rows_selected.at(i).row());
            htmlAppendRow(rows);
        }
    }

    html_form = htmlMount();
}

void MainWindow::saveHtml()
{
    pv r;
    QString texto_botao = "Click to export";
    r.insert("TEXTO_BOTAO", texto_botao);
    r.insert("ICONE", "html_valid");

    QWidget *wdg_form = defaultWidget(r);
    QPushButton *btn_ok = wdg_form->findChild<QPushButton *>(texto_botao);

    wdg_form->show();

    connect(btn_ok, SIGNAL(clicked()), this, SLOT(saveHtmlOk()));
}

void MainWindow::saveHtmlOk()
{
    QString texto = edit->document()->toHtml();

    QFile file;
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Salvar arquivo"), "/home/diego/" , tr("HTML Files (*.html)"));

    file.setFileName(filename);

    if(file.open(QIODevice::WriteOnly  | QIODevice::Text))
    {
        QTextStream out (& file);
        out << texto;
        statusFormulario(tr("Saved!"), CSS_GREEN);
        file.close();
    }
    else
    {
        statusFormulario(tr("Error saving the file"), CSS_RED);
        return;
    }

    wdg_default->close();
}

QWidget* MainWindow::defaultWidget(pv r)
{
    qs texto_botao = r.value("TEXTO_BOTAO").toString();
    qs icone_botao = r.value("ICONE").toString();

    wdg_default  = new QWidget();
    QHBoxLayout *h_layout = new QHBoxLayout();
    QVBoxLayout *v_layout = new QVBoxLayout();

    QPushButton *ok = new QPushButton(QIcon(icone_botao), texto_botao);
    ok->setObjectName(texto_botao);
    QPushButton *cancel = new QPushButton(getIcon("cancel") ,"cancel");

    connect(cancel, SIGNAL(clicked()), this, SLOT(cancel()));

    h_layout->addWidget(ok);
    h_layout->addWidget(cancel);

    edit = new QTextEdit();
    QFont* font = new QFont("Times");
    font->setPixelSize(12);
    edit->setFont(*font);

    edit->setFixedSize(500, 300);
    edit->setWindowTitle("Relatory");
    edit->setReadOnly(true);

    makeHtml();
    edit->setHtml(html_form);

    v_layout->addWidget(edit);
    v_layout->addLayout(h_layout);
    wdg_default->setLayout(v_layout);

    resetHtml();

    return wdg_default;
}

void MainWindow::enviarPorEmail()
{
    _D << "TODO";
}

void MainWindow::cancel()
{
    statusFormulario(tr("Canceled by user. "), CSS_RED);
    return;
}

void MainWindow::resetHtml()
{
    title.clear();
    header_titles.clear();
    rows.clear();
    html_final.clear();
}

void MainWindow::save_pdf()
{
    _D << "TODO";
}

bool MainWindow::setPrinter()
{
#ifndef QT_NO_PRINTER
    QPrinter *printer = new QPrinter();
    edit = new QTextEdit();

    QPrintDialog *dialog = new QPrintDialog(printer, this);
    dialog->setWindowTitle(tr("Select printer."));

    if (edit->textCursor().hasSelection())
    {
        dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }

    if (dialog->exec() != QDialog::Accepted)
    {
        return false;
    }

    return true;
#endif
}

void MainWindow::printer()
{
    bool printer_ok = setPrinter();
    if(!printer_ok)
    {
        statusFormulario(tr("Canceled by user. ") , CSS_RED);
        return;
    }
}
