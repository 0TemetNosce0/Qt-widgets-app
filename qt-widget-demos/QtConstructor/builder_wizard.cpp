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

#include "builder_wizard.h"
#include "ui_builder_wizard.h"

BuilderWizard::BuilderWizard(QWidget *parent)
    : QWidget(parent)
    , criar_coluna_automatico(true)
    , paranoia_mode(false)
    , ui(new Ui::builder_wizard)
{
    ui->setupUi(this);
    connect(ui->wizard_pages, SIGNAL(currentChanged(int)),
             this, SLOT(configure_page(int)));

    ui->wizard_pages->setCurrentIndex(PAGINA_DATABASE);
    ui->widget_btn_wizard->hide();
}

BuilderWizard::~BuilderWizard()
{
    delete ui;
}

void BuilderWizard::start(database *_db)
{
    startSettings();
    db = _db;
    configureDatabase(db);
}

void BuilderWizard::startSettings(){
    QFile file(INI_FILE);
    settings = new QSettings(INI_FILE, QSettings::IniFormat);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        send_info("Settings file not ReadWrite!", CSS_RED);
    } else {
        read_settings();
    }
    file.close();
}

void BuilderWizard::read_settings(){
    settings->beginGroup("Database");
    ui->db_host->setText(settings->value("db_host").toString());
    ui->db_user->setText(settings->value("db_user").toString());
    ui->db_paswd->setText(settings->value("db_paswd").toString());
    ui->db_port->setValue(settings->value("db_port").toInt());
    settings->endGroup();
}

void BuilderWizard::write_settings(){
    settings->beginGroup("Database");
    settings->setValue("db_host", ui->db_host->text().trimmed());
    settings->setValue("db_user", ui->db_user->text().trimmed());
    settings->setValue("db_paswd", ui->db_paswd->text().trimmed());
    settings->setValue("db_port", ui->db_port->value());
    settings->endGroup();

    settings->sync();
}

void BuilderWizard::configureDatabase(database * _database)
{
    _database->host = ui->db_host->text().trimmed();
    _database->user = ui->db_user->text().trimmed();
    _database->pass = ui->db_paswd->text().trimmed();
    _database->port = ui->db_port->value();
    _database->driver = ui->db_driver->currentText().trimmed();

    bool connection = _database->abrir_conexao();
    if(connection)
    {
        send_info("Connected", CSS_GREEN);

        ui->btn_connect->setStyleSheet("border: 1px solid green;\n");
        ui->btn_connect->setText("Connected!");
        ui->btn_connect->setDisabled(true);

        write_settings();

        start_mainwindow();
        configureBuilder();
    }
    else
    {
        send_info("Connection to the database failed!", CSS_RED);
        ui->btn_connect->setStyleSheet("border: 1px solid red;\nborder-radius: 3px;\n");
    }
}

void BuilderWizard::configureBuilder()
{
    ui->widget_btn_wizard->show();
    start_models();
    ui->component_sql->setEnabled(false);

    //ui->menu_nome->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]{1,20}"), this ));
    //ui->action_slot->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]{1,20}"), this ));
    //ui->componente_titulo->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]{1,20}"), this ));

    start_model_widgets();
    start_model_menus();
    start_model_tables();

    QS sql_get_actions = "CALL get_actions";
    actions = db->get_all(sql_get_actions);

    QS sql_get_types = "CALL get_component_type()";
    components_types = db->get_all(sql_get_types);

    QS sql_components = "CALL get_componentes()";
    components = db->get_all(sql_components);

    qsl icones = getResourceIcons(resource_path);
    getModelIcons(icones, model_icons);

    ui->widget_btn_wizard->hide();
    ui->wizard_pages->setCurrentIndex(PAGINA_INICIAL);

    start_root_model();
}

void BuilderWizard::show_error(QString str)
{
    QString text = returnLogger(str);
    ui->log->appendPlainText(text);
}

void BuilderWizard::start_models(){
    if(criar_coluna_automatico){
        ui->componente_db_tabelas->setEnabled(false);
        ui->componente_db_colunas->setEnabled(false);
    }

    ui->componente_widgets_tipo->setModel(& model_lista_widget_tipo);
    ui->componente_tipo_dados->setModel(& model_tipo_dados);
    ui->componente_db_tabelas->setModel(& model_banco_tabelas);
    ui->componente_db_colunas->setModel(& model_banco_coluna);
    ui->lista_actions->setModel(& model_lista_actions);

    ui->lista_menus->setModel(& model_lista_menus);
    ui->lista_menu_select->setModel(& model_lista_menus);

    ui->treeView->setModel(& model_root);

    ui->menu_lista_icones->setModel(& model_icons);
    ui->action_lista_icones->setModel(& model_icons);
    ui->componente_lista_icone->setModel(& model_icons);
}

void BuilderWizard::start_model_widgets(){
    componentes_widget = db->get_all("CALL get_widgets_type");
    CINT total_widgets = componentes_widget.count();
    for(int i = 0 ; i < total_widgets ; ++ i){
        PV r = componentes_widget.at(i);
        QS WIDGET_NAME = r.value("WIDGET_NAME").toString();
        QS WIDGET_ICON = r.value("WIDGET_ICON").toString();
        QS WIDGET_TOOLTIP = r.value("WIDGET_TOOLTIP").toString();

        QStandardItem *item = new QStandardItem(QIcon(WIDGET_ICON),WIDGET_NAME);
        item->setToolTip(WIDGET_TOOLTIP);
        item->setData(r);
        model_lista_widget_tipo.insertRow(i, item);
    }
}

void BuilderWizard::start_model_menus(){
    QS sql_get_menus = "CALL get_menus()";
    menus = db->get_all( sql_get_menus );
    CINT total_menus = menus.count();

    for( int i = 0 ; i < total_menus ; ++ i ){
        pv r = menus.at(i);
        QS MENU_NAME = r.value("MENU_NAME").toString();
        QS MENU_ICON = r.value("MENU_ICON").toString();

        QStandardItem *item = new QStandardItem(QIcon(MENU_ICON),MENU_NAME);
        item->setData(r);
        model_lista_menus.insertRow(i, item);
    }
}

void BuilderWizard::start_root_model(){
    CINT total_menus = menus.count();
    CINT total_actions = actions.count();
    CINT total_components = components.count();

    model_root.setHorizontalHeaderItem(0, new QStandardItem( "Right click for options" ) );
    model_root.horizontalHeaderItem(0)->setTextAlignment(Qt::AlignHCenter);
    model_root.horizontalHeaderItem(0)->setIcon(getIcon("bug"));

    int MENU_ID = 0;
    int ACTION_MENU_ID = 0;
    int ACTION_ID = 0;

    for(int i = 0; i < total_menus; ++i){
        pv r = menus.at(i);
        QS MENU_NAME = r.value("MENU_NAME").toString();
        QS MENU_ICON = r.value("MENU_ICON").toString();
        MENU_ID = r.value("MENU_ID").toInt();

        int action_idx = 0;
        int componente_idx = 0;

        QStandardItem *menu_item = new QStandardItem(QIcon(MENU_ICON),MENU_NAME);
        menu_item->setData(r);
        model_root.insertRow(i, menu_item);


        for(int j = 0; j < total_actions; ++j){
            pv rs = actions.at(j);
            ACTION_MENU_ID = rs.value("MENU_ID").toInt();
            ACTION_ID = rs.value("ACTION_ID").toInt();
            QS ACTION_NAME = rs.value("ACTION_NAME").toString();
            QS ACTION_ICON = rs.value("ACTION_ICON").toString();

            if(MENU_ID == ACTION_MENU_ID){
                QStandardItem *action_item = new QStandardItem(QIcon(ACTION_ICON),ACTION_NAME);
                action_item->setData(rs);
                menu_item->setChild(action_idx++, action_item);

                if(MENU_ID == 1){
                    menu_item->setEnabled(false);
                    action_item->setEnabled(false);
                }

                for( int x = 0; x < total_components; ++x){
                    pv rx = components.at(x);
                    CINT _ACTION_ID = rx.value("ACTION_ID").toInt();
                    QS COMPONENT_NAME = rx.value("COMPONENT_NAME").toString();
                    QS COMPONENT_ICON = rx.value("COMPONENT_ICON").toString();

                    if(ACTION_ID == _ACTION_ID){
                        QStandardItem *component_item = new QStandardItem(QIcon(COMPONENT_ICON),COMPONENT_NAME);
                        component_item->setData(rx);
                        action_item->setChild(componente_idx++, component_item);
                    }
                }
            }
        }
    }
}

void BuilderWizard::start_model_tables(){
    tables_names = get_tables();

    CINT total_tables_name = tables_names.count();
    for( int i = 0; i < total_tables_name; ++i ){
        pv r = tables_names.at( i );
        QS NOME_TABELA = r.value("NOME_TABELA").toString();

        if(! criar_coluna_automatico){
            tables << NOME_TABELA;
        } else {
            if(! NOME_TABELA.startsWith("isql")){
                tables << NOME_TABELA;
                QStandardItem *item = new QStandardItem(NOME_TABELA);
                item->setData(r);
                model_banco_tabelas.insertRow(i, item);
            }
        }
    }
}

void BuilderWizard::configure_page(int index){
    switch ( index ) {
    case PAGINA_INICIAL:
        ui->label_titulo->setText("  Start Page");
        ui->widget_btn_wizard->hide();
        break;
    case PAGINA_MENU:
        ui->label_titulo->setText("  Add Menu");
        break;
    case PAGINA_ACTION:
        ui->label_titulo->setText("  Add Action");
        break;    
    case PAGINA_DATABASE:
        ui->label_titulo->setText("  Database Options");
        ui->btn_update->hide();
        ui->widget_btn_wizard->show();
        break;
    }

}

void BuilderWizard::update(pv r){
    send_info("Updating component...", CSS_GREEN);

    qs componente_title = r.value("COMPONENT_TITLE").toString();
    qs COMPONENT_NAME = r.value("COMPONENT_NAME").toString();
    qs componente_icone = r.value("COMPONENT_ICON").toString();
    int status = r.value("COMPONENT_STATUS").toInt();
    int ordem = r.value("COMPONENT_ORDER").toInt();
    qs componente_tooltip = r.value("COMPONENT_TOOLTIP").toString();
    int ACTION_ID = r.value("ACTION_ID").toInt();
    int WIDGET_ID = r.value("WIDGET_ID").toInt();
    int TYPE_ID = r.value("TYPE_ID").toInt();
    qs title_regex = r.value("COMPONENT_COLUMN").toString();
    qs key_var = r.value("COMPONENT_TABLE").toString();
    qs sql_component = r.value("COMPONENT_SQL").toString();

    if(sql_component.isEmpty()){
        sql_component = "";
    }

    qs sql = "UPDATE components SET "
                                    "component_title = " + escape(componente_title) +
                                    ",component_icon = " + escape(componente_icone) +
                                    ",component_status = " + QString::number(status) +
                                    ",component_order = " + QString::number(ordem) +
                                    ",component_tooltip = " + escape(componente_tooltip) +
                                    ",fk_action_id = " + QString::number(ACTION_ID) +
                                    ",fk_widget_type = " + QString::number(WIDGET_ID) +
                                    ",fk_data_type = " + QString::number(TYPE_ID) +
                                    ",component_column_on_table = " + escape(title_regex) +
                                    ",component_table = " + escape(key_var) +
                                    ",component_sql = " + escape(sql_component) +
                                    "WHERE component_title = " + escape(COMPONENT_NAME);


    bool insert = db->execRow(sql);
     if(insert){
            send_info("Component updated successfully!!", CSS_GREEN);
            ui->wizard_pages->setCurrentIndex(PAGINA_INICIAL);
            refresh_component();
            lineedit_clear();
        } else {
            send_info("Error: Could not update the component", CSS_RED);
            return;
        }
}

void BuilderWizard::save(){
    CINT current_page = ui->wizard_pages->currentIndex();
    qsl valores;

    switch (current_page) {
    case PAGINA_MENU:{
        ui->wizard_pages->setCurrentIndex(PAGINA_MENU);
        QString nome =  ui->menu_nome->text() ;
        bool status = ui->menu_status->isChecked();
        QString descricao = ui->menu_descricao->text();
        QString ordem = ui->menu_ordem->text();
        int acl = ui->menu_acl->value();

        QItemSelectionModel* selected_icon =
                ui->menu_lista_icones->selectionModel();
        QModelIndex nome_icone = selected_icon->currentIndex();
        if(! selected_icon->isSelected(nome_icone)){
            send_info("Please select one icon! " , CSS_RED);
            return;
        }

        QString icone = nome_icone.data().toString();
        valores << nome << descricao << ordem;

        CINT total_valores = valores.count();
        for(int i = 0; i < total_valores; ++i){
            if(valores.at( i ).isEmpty()){
                send_info("All fields are necessary. ", CSS_RED);
                return;
            }
        }

        qs sql = QString("INSERT INTO  menu ( menu_name, menu_status, menu_desc,"
                          " menu_icon, menu_order, menu_acl ) VALUES ( %1, %2, %3, %4, %5, %6 )")
                .arg(escape(nome), QString::number(status),  escape(descricao),
                      escape(icone), escape(ordem), QString::number(acl));

        bool insert = db->execRow(sql);
        if(insert){
            send_info("Menu successfully added!!", CSS_GREEN);
            foreach(QLineEdit* i, this->findChildren<QLineEdit*>()) {
                i->clear();
            }
            ui->wizard_pages->setCurrentIndex(PAGINA_INICIAL);
            add_menu();
            refresh_component();

        } else {
            send_info("Erro, please verify the menu table!!", CSS_RED);
        }
        break;
    }

    case PAGINA_ACTION:{
        ui->wizard_pages->setCurrentIndex(PAGINA_ACTION);

        QString nome =  ui->action_nome->text() ;
        QString descricao = ui->action_descricao->text();
        QString slot = ui->action_slot->text();
        QString tooltip = ui->action_tooltip->text();
        int status = ui->action_status->isChecked();

        QItemSelectionModel* selected_icon =
                ui->action_lista_icones->selectionModel();
        QModelIndex nome_icone = selected_icon->currentIndex();
        if(! selected_icon->isSelected(nome_icone)){
            send_info("Please select one icon! " , CSS_RED);
            return;
        }

        QString icone = nome_icone.data().toString();

        valores << nome << descricao << tooltip;

        CINT total_valores = valores.count();
        for( int i = 0; i < total_valores; ++i ){
            if( valores.at( i ).isEmpty() ){
                send_info("All fields are necessary. ", CSS_RED);
                return;
            }
        }

        QItemSelectionModel* selected = ui->lista_menus->selectionModel();
        QModelIndex index = selected->currentIndex();
        if(! selected->isSelected(index)){
            send_info("Please select one menu on the list! " , CSS_RED);
            return;
        }

        CINT row = index.row();
        CINT column = index.column();
        QStandardItem *item = model_lista_menus.item(row, column);

        PV r = item->data().toHash();
        CINT MENU_ID = r.value("MENU_ID").toInt();

        qs sql = QString("INSERT INTO  actions ( action_name, action_desc,"
                          " action_icon, action_slot, action_tooltip, action_status, fk_menu_id ) VALUES ( %1, %2, %3, %4, %5, %6 , %7 )")
                .arg( escape(nome), escape (descricao),  escape(icone), escape(slot),
                      escape(tooltip), QString::number(status), QString::number(MENU_ID));

    bool insert = db->execRow(sql);
        if (insert){
            send_info("Action added.", CSS_GREEN);
            ui->wizard_pages->setCurrentIndex(PAGINA_INICIAL);

            pv r_action;
            r_action.insert("ACTION_STATUS",status);
            r_action.insert("ACTION_NAME",nome);
            r_action.insert("ACTION_ICONE",icone);
            r_action.insert("ACTION_TOOLTIP",tooltip);
            r_action.insert("ACTION_SLOT",slot);
            add_qaction(r_action);

            refresh_component();
        } else {
            send_info("Error: Could not add action", CSS_RED);
            return;
        }
    }

        break;

    case PAGINA_COMPONENTES:{
        QString componente_titulo = ui->componente_titulo->text();        
        qsl valores;
        int status = ui->componente_status->isChecked();
        QString componente_tooltip = ui->componente_tooltip->text();
        int ordem = ui->componente_ordem->value();

        if(componente_titulo.isEmpty()){
            send_info("Component title is necessary! " , CSS_RED);
            return;
        } else if(componente_tooltip.isEmpty()){
            send_info("Component tooltip is necessary! " , CSS_RED);
            return;
        }
        valores << componente_titulo << componente_tooltip;

        QItemSelectionModel* selected_icon =
                ui->componente_lista_icone->selectionModel();
        QModelIndex nome_icone = selected_icon->currentIndex();
        if(! selected_icon->isSelected(nome_icone)){
            send_info("Please select one icon! " , CSS_RED);
            return;
        }

        QString componente_icone = nome_icone.data().toString();

        CINT total_valores = valores.count();
        for(int i = 0; i < total_valores; ++i){
            if( valores.at(i).isEmpty()){
                send_info("Please select one QAction!", CSS_RED);
                return;
            }
        }

        QItemSelectionModel* selected_action =
                ui->lista_actions->selectionModel();

        QModelIndex index_action = selected_action->currentIndex();
        if(! selected_action->isSelected(index_action)){
            send_info("Please select one QAction!", CSS_RED);
            return;
        }

        CINT row_action = index_action.row();
        QStandardItem *action_item = model_lista_actions.item(row_action);

        PV r_action = action_item->data().toHash();
        CINT ACTION_ID = r_action.value("ACTION_ID").toInt();
        QS ACTION_NAME = r_action.value("ACTION_NAME").toString();

        QItemSelectionModel* selected_widget_tipo =
                ui->componente_widgets_tipo->selectionModel();

        QModelIndex index_widget = selected_widget_tipo->currentIndex();
        if(! selected_widget_tipo->isSelected(index_widget)){
            send_info("Please select at least one component " , CSS_RED);
            return;
        }

        CINT row = index_widget.row();
        QStandardItem *componente_item = model_lista_widget_tipo.item(row);

        PV r_wdg = componente_item->data().toHash();
        CINT WIDGET_ID = r_wdg.value("WIDGET_ID").toInt();

        qs sql_component;
        if(WIDGET_ID == CAMPO_QCOMBOBOX){
            sql_component = ui->component_sql->text().trimmed();
        } else {          
        qs sql_component = "";
        if(WIDGET_ID == CAMPO_QCOMBOBOX){
            sql_component = ui->component_sql->text().trimmed();
        }

       QItemSelectionModel* selected_tipo_dados =
                ui->componente_tipo_dados->selectionModel();
        QModelIndex index_tipo = selected_tipo_dados->currentIndex();
        if(! selected_tipo_dados->isSelected(index_tipo)){
            send_info("Please select the data type" , CSS_RED);
            return;
        }

        CINT row_widget = index_tipo.row();
        QStandardItem *item_widget = model_tipo_dados.item(row_widget);

        PV r_tipo = item_widget->data().toHash();
        int TYPE_ID = r_tipo.value("TYPE_ID").toInt();

        qs tmp = ACTION_NAME;
        qs key_var = tmp.replace(QRegExp("[^a-zA-Z0-9_]"),"_");

        if(! criar_coluna_automatico){

            QItemSelectionModel* selected_table =
                    ui->componente_db_colunas->selectionModel();
            QModelIndex index_table = selected_table->currentIndex();
            if(! selected_table->isSelected(index_table)){
                send_info("Please select one table! " , CSS_RED);
                return;
            }

            QItemSelectionModel* selected_column =
                ui->componente_db_colunas->selectionModel();
            QModelIndex index_column = selected_column->currentIndex();

            if(! selected_column->isSelected( index_column)){
                send_info("Please select one column! " , CSS_RED);
                return;
            }
        } else {
            if(! tables.contains(key_var)){
                bool table_create = confirmation("Table not found!"," Table not found for this QAction, create the table?");
                if( table_create){
                    bool table_create = create_table(key_var);
                    if(! table_create){
                        send_info("Erro creating the component_table", CSS_RED);
                        return;
                    }
                } else {
                    send_info("Canceled by user", CSS_RED);
                    return;
                }
            }
        }

        qs title_regex = componente_titulo.replace(QRegExp("[^a-zA-Z0-9_]"),"_");
        qs componente_title = ui->componente_titulo->text();
        bool column_ok = create_column(key_var,title_regex,TYPE_ID);

        if(! column_ok){
           send_info("Error on create column!", CSS_RED);
           return;
        } else {
            send_info("Column successfully create!", CSS_GREEN);
        }

        qs sql = QString("INSERT INTO  components ( component_title, component_icon,"
                          " component_status, component_order, component_tooltip, fk_action_id, fk_widget_type,"
                          " fk_data_type, component_column_on_table, component_table, component_sql ) VALUES ( %1, %2, %3, %4, %5, %6 , %7, %8, %9, %10, %11 )")
                .arg(escape(componente_title)).arg (escape (componente_icone)).arg(QString::number(status)).arg(
                    QString::number(ordem)).arg(escape(componente_tooltip)).arg(QString::number(ACTION_ID)).arg(
                    QString::number(WIDGET_ID)).arg( QString::number(TYPE_ID)).arg(escape(title_regex)).arg(escape(key_var)).arg(escape(sql_component));

       ui->log->appendPlainText(returnLogger(sql));

      bool insert = db->execRow(sql);
            if(insert){
                send_info("Component added successfully!!", CSS_GREEN);
                ui->wizard_pages->setCurrentIndex(PAGINA_INICIAL);
                refresh_component();
                lineedit_clear();

                tables << key_var;

            } else {
                send_info("Error: Could not add the component", CSS_RED);
                return;
            }
      }
        break;
    }

    case PAGINA_DATABASE:{
        ui->wizard_pages->setCurrentIndex(PAGINA_INICIAL);
    }
        break;
 }
}

void BuilderWizard::on_btn_save_clicked(){
    save();
}

bool BuilderWizard::create_table(QString table){
    qs sql = QString("CREATE TABLE %1 ( %2 INT(11) unsigned NOT NULL AUTO_INCREMENT, "
                     "PRIMARY KEY ( %3 )) Engine = InnoDB DEFAULT CHARSET = utf8").arg(table).arg(table+"_id").arg(table+"_id");

    bool creating_table = db->execRow(sql);
    if(! creating_table){
        send_info("Error: table not created", CSS_RED);
        return false;
    }

    send_info("Table create successfully!", CSS_RED);
    tables << table;
    tabela_selecionada = table;
    return true;
}

bool BuilderWizard::create_column(qs table, qs title, int type){
    send_info("Creating column.. please wait..!!", CSS_YELLOW);
    qs sql;   

    switch (type) {
    case TIPO_INT:
        sql = QString("ALTER TABLE %1 ADD %2 INT(11) NOT NULL").arg(table).arg(title);
        break;
    case TIPO_STRING:
        sql = QString("ALTER TABLE %1 ADD %2 VARCHAR(32)").arg(table).arg(title);
        break;
    case TIPO_DATE:
        sql = QString("ALTER TABLE %1 ADD %2 DATE()").arg(table).arg(title);
        break;
    case TIPO_DATETIMEEDIT:
        sql = QString("ALTER TABLE %1 ADD %2 DATETIME()").arg(table).arg(title);
        break;
    }

    _D << sql;
    bool query = db->execRow(sql);
    if(!query){
        send_info("Error: Could not add the column on table", CSS_RED);
        return false;
    }

    return true;
}

void BuilderWizard::lineedit_clear(){
    foreach( QLineEdit* i, this->findChildren<QLineEdit*>()) {
        i->clear();
    }
}

void BuilderWizard::on_componente_db_tabelas_clicked(const QModelIndex &index){
    CINT total = model_banco_coluna.rowCount();
    if( total != 0 ){
        model_banco_coluna.clear();
    }

    CINT row = index.row();
    QStandardItem *item = model_banco_tabelas.item(row);
    PV r = item->data().toHash();

    tabela_selecionada = r.value("NOME_TABELA").toString();
    qs sql = QString("CALL get_columns_names(%1)").arg(escape (tabela_selecionada));
    lpv colunas = db->get_all(sql);

    CINT t = colunas.count();
    for(int i = 0 ; i < t ; ++ i){
        PV r = colunas.at(i);
        QS NOME_COLUNA = r.value("NOME_COLUNA").toString();
        QStandardItem *item = new QStandardItem(NOME_COLUNA);
        item->setData(r);
        model_banco_coluna.insertRow(i, item);
    }

}

void BuilderWizard::on_componente_db_colunas_clicked(const QModelIndex & index){
    CINT row = index.row();
    QStandardItem *item = model_banco_coluna.item(row);
    PV r = item->data().toHash();
    coluna_selecionada = r.value("NOME_COLUNA").toString();
}

void BuilderWizard::on_btn_cancel_clicked(){    
    CINT current_page = ui->wizard_pages->currentIndex();

    switch (current_page) {
    case PAGINA_MENU:
    case PAGINA_ACTION:
    case PAGINA_COMPONENTES:
    case PAGINA_DATABASE:
        ui->widget_btn_wizard->hide();
        ui->wizard_pages->setCurrentIndex(PAGINA_INICIAL);
        break;
    default:
        _D << current_page << "!!!!!";
        break;
    }
}

void BuilderWizard::on_btn_menu_clicked(){
    ui->btn_save->show();
    ui->btn_update->hide();
    ui->widget_btn_wizard->show();
    ui->wizard_pages->setCurrentIndex(PAGINA_MENU);
}

void BuilderWizard::on_btn_action_clicked(){
    ui->btn_save->show();
    ui->btn_update->hide();
    ui->widget_btn_wizard->show();
    ui->wizard_pages->setCurrentIndex(PAGINA_ACTION);
}

void BuilderWizard::on_btn_componente_clicked(){
    ui->btn_save->show();
    ui->btn_update->hide();
    ui->widget_btn_wizard->show();
    ui->wizard_pages->setCurrentIndex(PAGINA_COMPONENTES);
}

void BuilderWizard::on_ajuda_acl_clicked(){
    CINT idx = ui->wizard_pages->currentIndex();

    switch ( idx ) {
    case PAGINA_INICIAL:
    case PAGINA_MENU:
    case PAGINA_ACTION:
    case PAGINA_COMPONENTES:
        _D << idx;
        QMessageBox::information(this,"Ajuda","Em construção.");
        break;
    default:
        _D << idx;
        break;
    }
}

void BuilderWizard::on_lista_menu_select_clicked(const QModelIndex & index){
    CINT row = index.row();
    QStandardItem *item = model_lista_menus.item(row);
    PV r = item->data().toHash();
    int menu_selecionado = r.value("MENU_ID").toInt();
    show_actions_on_model(menu_selecionado);
}

void BuilderWizard::show_actions_on_model(const int menu_selecionado){
    QS sql_get_actions = QString("CALL get_action_by_menu_id(%1)").arg(menu_selecionado);
    actions = db->get_all(sql_get_actions);
    CINT total_actions = actions.count();

    model_lista_actions.clear();
    for(int i = 0 ; i < total_actions ; ++ i){
        pv r = actions.at( i );
        QS ACTION_NAME = r.value("ACTION_NAME").toString();
        QS ACTION_ICON = r.value("ACTION_ICON").toString();

        QStandardItem *item = new QStandardItem(QIcon(ACTION_ICON),
                                                 ACTION_NAME );
        item->setData(r);
        model_lista_actions.insertRow(i, item);
    }
}

void BuilderWizard::on_componente_db_colunas_customContextMenuRequested(const QPoint &pos){
    QMenu *menu = new QMenu(this);
    menu->addAction(new QAction("Action 1", this));
    menu->addAction(new QAction("Action 2", this));
    menu->addAction(new QAction("Action 3", this));
    menu->popup(ui->componente_db_colunas->viewport()->mapToGlobal(pos));
}

void BuilderWizard::on_criar_coluna_automatico_clicked(){
    if(ui->criar_coluna_automatico->isChecked()){
        criar_coluna_automatico = true;
        ui->componente_db_colunas->setEnabled(false);
        ui->componente_db_tabelas->setEnabled(false);
        send_info("Automatic database ON", CSS_RED);
    } else {
        criar_coluna_automatico = false;
        ui->componente_db_colunas->setEnabled(true);
        ui->componente_db_tabelas->setEnabled(true);

        send_info("Automatic database OFF", CSS_GREEN);
    }
}

lpv BuilderWizard::get_tables(){
    QS sql_tables_name = "CALL get_tables_names";
    lpv tables_names = db->get_all(sql_tables_name);
    return tables_names;
}

void BuilderWizard::on_componente_widgets_tipo_clicked(const QModelIndex &index){
    CINT row = index.row();
    QStandardItem *item = model_lista_widget_tipo.item(row);
    PV r = item->data().toHash();

    CINT WIDGET_STATUS = r.value("WIDGET_STATUS").toInt();
    CINT WIDGET_ID = r.value("WIDGET_ID").toInt();
    if(WIDGET_STATUS != 0){
            populate_data_type(WIDGET_ID);
    }

    if(WIDGET_ID == CAMPO_QCOMBOBOX){
        ui->component_sql->setEnabled(true);
    } else {
        ui->component_sql->setEnabled(false);
    }
}

void BuilderWizard::populate_data_type(const int idx){
    model_tipo_dados.clear();
    CINT t = components_types.count();
    for( int i = 0 ; i < t ; ++ i ){
        PV r = components_types.at(i);
        CINT TYPE_ID = r.value("TYPE_ID").toInt();
        QS TYPE_NAME = r.value("TYPE_NAME").toString();
        int j = 0;

        switch (idx) {
        case CAMPO_QLABEL:
        case CAMPO_QLINEEDIT:
            if(TYPE_ID == TIPO_INT){
                QStandardItem *item = new QStandardItem(TYPE_NAME);
                item->setData(r);
                model_tipo_dados.insertRow(j++, item);
            } else if (TYPE_ID == TIPO_STRING){
                QStandardItem *item = new QStandardItem(TYPE_NAME);
                item->setData(r);
                model_tipo_dados.insertRow(j++, item);
            }
            break;
        case CAMPO_QCOMBOBOX:
            if(TYPE_ID == TIPO_INT){
                QStandardItem *item = new QStandardItem(TYPE_NAME);
                item->setData(r);
                model_tipo_dados.insertRow(j++, item);
            } else if (TYPE_ID == TIPO_STRING){
                QStandardItem *item = new QStandardItem(TYPE_NAME);
                item->setData(r);
                model_tipo_dados.insertRow(j++, item);
            } else if (TYPE_ID == TIPO_DATE){
                QStandardItem *item = new QStandardItem(TYPE_NAME);
                item->setData(r);
                model_tipo_dados.insertRow(j++, item);
            } else if (TYPE_ID == TIPO_DATETIMEEDIT){
                QStandardItem *item = new QStandardItem(TYPE_NAME);
                item->setData(r);
                model_tipo_dados.insertRow(j++, item);
            }

            break;
        case CAMPO_QDATETIMEEDIT:
            if (TYPE_ID == TIPO_DATE){
                QStandardItem *item = new QStandardItem(TYPE_NAME);
                item->setData(r);
                model_tipo_dados.insertRow(j++, item);
            } else if (TYPE_ID == TIPO_DATETIMEEDIT){
                QStandardItem *item = new QStandardItem(TYPE_NAME);
                item->setData(r);
                model_tipo_dados.insertRow(j++, item);
            }
            break;
        case CAMPO_QDATEEDIT:
            if(TYPE_ID == TIPO_DATE){
                QStandardItem *item = new QStandardItem(TYPE_NAME);
                item->setData(r);
                model_tipo_dados.insertRow(j++, item);
            }
            break;
        }
    }
}


void BuilderWizard::on_treeView_customContextMenuRequested(const QPoint &pos){
    QMenu *menu = new QMenu(this);
    menu->addAction(edit = new QAction(QIcon(getIcon("folder_edit")),"Edit", this));
    menu->addAction(remove = new QAction(QIcon(getIcon("folder_delete")),"Remove", this));
    menu->addAction(refresh = new QAction(QIcon(getIcon("folder_go")),"Refresh", this));

    menu->popup(ui->treeView->viewport()->mapToGlobal(pos));

    connect(edit, SIGNAL(triggered()), this, SLOT(edit_()));
    connect(remove, SIGNAL(triggered()), this, SLOT(remove_component()));
    connect(refresh, SIGNAL(triggered()), this, SLOT(refresh_component()));
}

void BuilderWizard::edit_(){
    int idx = treeview_component_type();
    switch (idx) {
    case MENU:
        _D << "MENU";
        break;
    case ACTION:
        _D << "ACTION";
        break;
    case COMPONENT:
        edit_component();
        break;
    }
}

void BuilderWizard::edit_component(){
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();

    QString name = index.data().toString();
    qs sql = QString("CALL get_component_by_name(%1)").arg(escape(name));

    lpv callback = db->get_all(sql);
    CINT t = callback.count(); // t=1
    for( int i = 0 ; i < t ; ++ i ){
        PV r = callback.at(i);
        update_dados = r;

        QS COMPONENT_NAME = r.value("COMPONENT_NAME").toString();
        CINT COMPONENT_STATUS = r.value("COMPONENT_STATUS").toInt();
        QS COMPONENT_TOOLTIP = r.value("COMPONENT_TOOLTIP").toString();
        CINT COMPONENT_ORDER = r.value("COMPONENT_ORDER").toInt();
        QS MENU_NAME = r.value("MENU_NAME").toString();
        CINT MENU_ID = r.value("MENU_ID").toInt();
        QS ACTION_NAME = r.value("ACTION_NAME").toString();
        QS COMPONENT_ICON = r.value("COMPONENT_ICON").toString();
        CINT WIDGET_ID = r.value("WIDGET_ID").toInt();        
        QS WIDGET_NAME = r.value("WIDGET_NAME").toString();
        QS TYPE_NAME = r.value("TYPE_NAME").toString();

        ui->componente_titulo->setText(COMPONENT_NAME);

        if(COMPONENT_STATUS == 1){
            ui->componente_status->setChecked(true);
        } else {
            ui->componente_status->setChecked(false);
        }

        ui->componente_tooltip->setText(COMPONENT_TOOLTIP);
        ui->componente_ordem->setValue(COMPONENT_ORDER);        

        QModelIndexList icones = get_item_match(COMPONENT_ICON, model_icons);
        QItemSelectionModel *selection_icone = ui->componente_lista_icone->selectionModel();
        select_item(icones,selection_icone, model_icons);

        QModelIndexList menus_list = get_item_match(MENU_NAME, model_lista_menus);
        QItemSelectionModel *selection_menu = ui->lista_menu_select->selectionModel();
        select_item(menus_list,selection_menu, model_lista_menus);

        CINT t = menus.count(); // t=2
        for( int i = 0 ; i < t ; ++ i ){
            PV r = menus.at(i);
            CINT _MENU_ID = r.value("MENU_ID").toInt(); // uint: 1
            if(MENU_ID == _MENU_ID){
                show_actions_on_model(MENU_ID);
            }

        }

        QModelIndexList actions = get_item_match(ACTION_NAME, model_lista_actions);
        QItemSelectionModel *selection_action= ui->lista_actions->selectionModel();
        select_item(actions,selection_action, model_lista_actions);

        QModelIndexList widget_type = get_item_match(WIDGET_NAME, model_lista_widget_tipo);
        QItemSelectionModel *selection_wdg = ui->componente_widgets_tipo->selectionModel();
        select_item(widget_type,selection_wdg, model_lista_widget_tipo);

        populate_data_type(WIDGET_ID);

        QModelIndexList data_type = get_item_match(TYPE_NAME, model_tipo_dados);
        QItemSelectionModel *selection_data = ui->componente_tipo_dados->selectionModel();
        select_item(data_type,selection_data, model_tipo_dados);
    }        

    ui->btn_save->hide();
    ui->btn_update->show();
    ui->widget_btn_wizard->show();

    ui->wizard_pages->setCurrentIndex(PAGINA_COMPONENTES);      
}

QModelIndexList BuilderWizard::get_item_match(QString str, ModelTemplate& model){
    QModelIndexList lista = model.match( model.index(0, 0),
        Qt::DisplayRole, QVariant::fromValue(str),
        1,  Qt::MatchFixedString);

    return lista;
}

void BuilderWizard::select_item(QModelIndexList list, QItemSelectionModel *selection, ModelTemplate& model){
    CINT total = list.count();
    for(int i = 0; i < total; ++i){
        CINT row = list.at(i).row();
        QModelIndex index = model.index(row, model.columnCount() -1);
        //selection->select(index, QItemSelectionModel::Select);
        selection->setCurrentIndex(index,QItemSelectionModel::Select);
    }
}

void BuilderWizard::remove_component(){
    if(paranoia_mode){
        send_info("Not possible delete with Paranoia mode ON", CSS_RED);
        return;
    }

    int idx = treeview_component_type();
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();

    qs name = index.data().toString();
    qs sql;

    switch (idx) {
    case MENU:{
        sql = QString("DELETE FROM %1  WHERE  %2 = %3 ").arg( "menu")
                .arg("menu_name").arg(escape(name));      
    }
        break;
    case ACTION:{
        sql = QString("DELETE FROM %1  WHERE  %2 = %3 ").arg( "actions")
                .arg("action_name").arg(escape(name));
    }
        break;
    case COMPONENT:{
        sql = QString("DELETE FROM %1  WHERE  %2 = %3 ").arg( "components")
                .arg("component_title").arg(escape(name));
    }
        break;
    }

    bool del_confirmation = confirmation("Warning", "Are you sure?");
    if(! del_confirmation){
        send_info("Canceled", CSS_RED);
        return;
    }

    bool remove = db->execRow(sql);
    if(remove){
        send_info("Successfully deleted", CSS_GREEN);
        remove_menu_action(idx,name);
        switch (idx) {
        case MENU:
            model_lista_menus.removeRow(index.row());
            break;
        case ACTION:
            model_lista_actions.removeRow(index.row());
            break;
        case COMPONENT:
            //model_root.removeRow(index.row());
            _D << 1;
            break;
        }
    } else {
        send_info("Not deleted", CSS_RED);
        return;
    }

    refresh_component();
}

void BuilderWizard::refresh_component(){
    model_root.clear();

    QS sql_get_menus = "CALL get_menus()";
    menus = db->get_all(sql_get_menus);

    QS sql_get_actions = "CALL get_actions";
    actions = db->get_all(sql_get_actions);

    QS sql_components = "CALL get_componentes()";
    components = db->get_all(sql_components);

    start_root_model();
}

void BuilderWizard::refresh_models(){

}

int BuilderWizard::treeview_component_type(){
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    int type =1;
    QModelIndex seek = index;

    while(seek.parent() != QModelIndex()){
      seek = seek.parent();
      type++;
    }

    return type;
}

bool BuilderWizard::has_child(){
    // ARRUMAR ISSO AQ
    const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    if(index.parent() != QModelIndex()){
       return false;
    }
    return true;
}

void BuilderWizard::on_paranoia_mode_clicked(){
    if(ui->paranoia_mode->isChecked()){
        send_info("Paranoia mode ON", CSS_RED);
        paranoia_mode = true;
    } else {
        send_info("Paranoia mode OFF", CSS_GREEN);
        paranoia_mode = false;
    }
}

void BuilderWizard::on_btn_update_clicked(){
    QItemSelectionModel* selected_icon =
            ui->componente_lista_icone->selectionModel();
    QModelIndex nome_icone = selected_icon->currentIndex();
    QString componente_icone = nome_icone.data().toString();

    QItemSelectionModel* selected_action =
            ui->lista_actions->selectionModel();
    QModelIndex index_action = selected_action->currentIndex();
    CINT row_action = index_action.row();
    QStandardItem *action_item = model_lista_actions.item(row_action);
    PV r_action = action_item->data().toHash();
    CINT ACTION_ID = r_action.value("ACTION_ID").toInt();

    QItemSelectionModel* selected_widget_tipo =
            ui->componente_widgets_tipo->selectionModel();

    QModelIndex index_widget = selected_widget_tipo->currentIndex();
    CINT row = index_widget.row();
    QStandardItem *componente_item = model_lista_widget_tipo.item(row);

    PV r_wdg = componente_item->data().toHash();
    CINT WIDGET_ID = r_wdg.value("WIDGET_ID").toInt();

    qs sql_component;
    if(WIDGET_ID == CAMPO_QCOMBOBOX){
        sql_component = ui->component_sql->text().trimmed();
    } else {
        sql_component = " ";
    }

    QItemSelectionModel* selected_tipo_dados =
            ui->componente_tipo_dados->selectionModel();
    QModelIndex index_tipo = selected_tipo_dados->currentIndex();
    CINT row_widget = index_tipo.row();
    QStandardItem *item_widget = model_tipo_dados.item(row_widget);

    PV r_tipo = item_widget->data().toHash();
    int TYPE_ID = r_tipo.value("TYPE_ID").toInt();

    QS COMPONENT_TABLE = update_dados.value("COMPONENT_TABLE").toString();
    QS COMPONENT_COLUMN = update_dados.value("COMPONENT_COLUMN").toString();
    QS COMPONENT_NAME = update_dados.value("COMPONENT_NAME").toString();

    pv r;
    r.insert("COMPONENT_TITLE", ui->componente_titulo->text());
    r.insert("COMPONENT_STATUS", ui->componente_status->isChecked());
    r.insert("COMPONENT_TOOLTIP", ui->componente_tooltip->text());
    r.insert("COMPONENT_ORDER", ui->componente_ordem->value());
    r.insert("COMPONENT_ICON",componente_icone);
    r.insert("ACTION_ID", ACTION_ID);
    r.insert("WIDGET_ID", WIDGET_ID);
    r.insert("TYPE_ID", TYPE_ID);
    r.insert("COMPONENT_COLUMN", COMPONENT_TABLE);
    r.insert("COMPONENT_TABLE", COMPONENT_COLUMN);
    r.insert("COMPONENT_SQL", sql_component);
    r.insert("COMPONENT_NAME", COMPONENT_NAME);

    update(r);
}

// DATABASE

void BuilderWizard::on_btn_database_clicked(){
    ui->wizard_pages->setCurrentIndex(PAGINA_DATABASE);
}

void BuilderWizard::create_tables(){
    #ifdef linux
    cmd(QStringList() << "mysql" << "-u" << "root" << "QtConstructor"
        << "<" << SQL_PATH);
    #endif

    #ifdef _WIN32
    QString filename = SQL_PATH;
    QFile file(filename);
    QString sql;
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        sql = in.readAll();
    } else {
        send_info("Read fail", CSS_RED);
        return;
    }

    file.close();
    bool install_database = db->execRow(sql);
    if(install_database){
        send_info("Database created successfully!", CSS_GREEN);
    } else {
        send_info("Database creation failed!", CSS_RED);
        return;
    }
    #endif
}

void BuilderWizard::create_sps(){
  #ifdef linux
      cmd(QStringList() << "mysql" << "-u" << "root" << "QtConstructor"
          << "<" << SQL_SP_PATH);
  #elif _WIN32
    QString filename = SQL_SP_PATH;
    QFile file(filename);
    QString sql;

    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        sql = in.readAll();
    } else {
        send_info("Read fail", CSS_RED);
        return;
    }

    file.close();
    bool install_database = db->execRow(sql);
    if(install_database){
        send_info("SPs created successfully!", CSS_GREEN);
    } else {
        send_info("SPs creation failed!", CSS_RED);
        return;
    }
  #else
        send_info("Not implemented  !", CSS_RED);
  #endif
}

void BuilderWizard::create_database(){
    bool ok = confirmation("WARNING","Are you sure? All data will be lost!");
    if(! ok){
        return;
    }

    send_info("Creating tables!", CSS_YELLOW);
    create_tables();

    send_info("Creating SPs!", CSS_YELLOW);
    create_sps();
}

void BuilderWizard::on_btn_create_database_clicked(){
    create_database();
}

void BuilderWizard::on_btn_dump_db_clicked(){
    #ifdef linux
        cmd(QStringList() << "mysqldump" << "-u" << "root" << "--routines"
            << "QtConstructor" << ">" << "QtConstructor.sql");
    #else
        send_info("Not implemented on this OS!!", CSS_RED);
    #endif
}

void BuilderWizard::on_btn_connect_clicked(){
    configureDatabase(db);
}
