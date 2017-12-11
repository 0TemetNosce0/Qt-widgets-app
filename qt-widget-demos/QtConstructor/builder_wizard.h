// This file is part of QtConstructor.
// Copyright (c) 2015, Diego Queiroz dos Santos, drift@linuxmail.com
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

#ifndef BUILDER_WIZARD_H
#define BUILDER_WIZARD_H

#include <QWidget>
#include <QStandardItemModel>
#include <QDirIterator>
#include <QMenu>
#include <QItemSelection>
#include <QSettings>
#include "database.h"
#include "stdfctl.h"

namespace Ui {
class builder_wizard;
    class QFileDialog;
}

class BuilderWizard : public QWidget, public stdfctl
{
    Q_OBJECT

public:
    explicit BuilderWizard(QWidget *parent = 0);

    void start(database *_db);
    ~BuilderWizard();

signals:
    void start_mainwindow();
    void send_info( const QString, const int );
    void add_qaction(pv);
    void add_menu();
    void remove_menu_action(int,qs);

private slots:
    void configureBuilder();
    void startSettings();
    void read_settings();
    void write_settings();
    void start_models();
    void start_model_widgets();
    void start_model_menus();
    void start_model_tables();
    void on_btn_save_clicked();
    void save();
    void update(pv r);
    void on_btn_cancel_clicked();
    void on_btn_menu_clicked();
    void on_btn_action_clicked();
    void configure_page( int index );
    void on_btn_componente_clicked();        
    void on_componente_db_colunas_clicked( const QModelIndex &index );
    void on_componente_db_tabelas_clicked( const QModelIndex &index );    
    void on_ajuda_acl_clicked();
    void on_lista_menu_select_clicked(const QModelIndex &index);
    void lineedit_clear();
    bool create_column(qs table, qs title, int type);
    void on_componente_db_colunas_customContextMenuRequested(const QPoint &pos);
    void on_criar_coluna_automatico_clicked();
    bool create_table(QString table);
    lpv get_tables();
    void on_componente_widgets_tipo_clicked(const QModelIndex &index);
    void populate_data_type(const int idx);
    void start_root_model();
    void on_treeView_customContextMenuRequested(const QPoint &pos);
    void edit_();
    void edit_component();
    void remove_component();
    void refresh_component();
    void refresh_models();
    int treeview_component_type();
    bool has_child();
    void on_paranoia_mode_clicked();
    void show_error(QString str);    
    QModelIndexList get_item_match(QString str, ModelTemplate &model);
    void select_item(QModelIndexList list, QItemSelectionModel *selection, ModelTemplate& model);
    void show_actions_on_model(const int menu_selecionado);
    void on_btn_update_clicked();

    // DATABASE
    void on_btn_database_clicked();
    void on_btn_create_database_clicked();
    void create_tables();
    void create_sps();
    void create_database();
    void on_btn_dump_db_clicked();
    void configureDatabase(database *_database);
    void on_btn_connect_clicked();

private:
    Ui::builder_wizard *ui;
    ModelTemplate model_lista_widget_tipo;
    ModelTemplate model_lista_menus;
    ModelTemplate model_lista_actions;
    ModelTemplate model_tipo_dados;
    ModelTemplate model_banco_tabelas;
    ModelTemplate model_banco_coluna;
    ModelTemplate model_icons;
    ModelTemplate model_root;

    database *db;

    lpv menus;
    lpv actions;
    lpv componentes_widget;
    lpv components_types;
    lpv components;
    lpv tables_names;

    pv update_dados;

    qs coluna_selecionada;
    qs tabela_selecionada;
    qsl tables;

    bool criar_coluna_automatico;
    bool paranoia_mode;

    QAction *edit;
    QAction *remove;
    QAction *refresh;

    QSettings *settings;

    static const int PAGINA_INICIAL = 0;
    static const int PAGINA_MENU = 1;
    static const int PAGINA_ACTION = 2;
    static const int PAGINA_COMPONENTES = 3;  
    static const int PAGINA_DATABASE = 4;

};

#endif // BUILDER_WIZARD_H
