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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwindow_includes.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public stdfctl {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    // Builder - Create your menus and actions
    void startBuilder();

    // clear() all itens on form
    void cleanStatusForm();

    // Select the style of this app
    void setTheme(int type);

    // layout stuff
    void setLayoutTheme(QLayout *layout);

    // Start all the necessary methods on the main window
    void start();  

    // Some information about this app
    void about();

    // Form
    void createBtns(QWidget *wdg, const int type);
    void callActions(const int fk_menu_id);
    void addQaction(pv r);
    void getAction(QAction* action);
    void insertTab(int modulo_id);
    void call_menus();
    void addMenu(pv r);
    int getNewTab(int layout_type);
    void removeMenuAction(int type, qs name);
    QPushButton *getBtn(const int btn_id);
    void addInformationOnForm();
    void addInformationOnForm( const int action_id);
    void statusFormulario(const QString str, const int css);
    void saveForm();
    void btnClean();
    void help();
    void removeRow();
    void save_pdf();
    void saveHtml();
    void saveHtmlOk();
    void mount_form(lpv dados);
    void configureComboboxes(QComboBox *combobox_componente);

    QStringList formGetHeader();
    QStringList formGetText(int row);

    // Verify if slot exists
    bool callSlotsByName(const QString & slot_name);

    // Return componentes
    lpv get_components();
    lpv get_component_by_action_id(const int id);

    // Create the main widget
    void mainLayout(pv r);
    void widgetSetStuff(pv r);

    // Create a widget template
    void createTemplateMenus(pv r);

    //  Tableview stuff
    void createTableForm();
    void populateTableForm(pv r);
    void populateTable(pv r);
    void populateTable(const int action_id);
    void populateTableHeader(pv r);
    void search_table_clicked(QModelIndex index);
    void set_table_editable();
    QStandardItem *qvariantType(pv r);

    // Combobox stuff
    void createSearchForm();
    void populateSearchCombobox(pv r);
    void search();
    void refresh();

    // Printer
    bool setPrinter();
    void printer();

    // HTML
    void htmlSetTitle(qs str);
    void htmlSetHeaderTitles(qsl str);
    void htmlAppendRow(qsl str);
    void resetHtml();
    void makeHtml();
    qs htmlMount();

    // Default widget
    QWidget *defaultWidget(pv r);
    void enviarPorEmail();
    void cancel();

private slots:
    void on_tabWidget_tabCloseRequested(int index);
    void modelDataChanged(QStandardItem* item);

private:
    // Builder
    BuilderWizard *builder;

    // Widgets defaultsitem
    Ui::MainWindow *ui;          
    QWidget *wdg;
    QWidget *wdg_default;
    QStandardItemModel *model;
    QTableView *search_table;
    QComboBox *search_combobox;
    QLineEdit *search_lineedit;

    // TextEdit
    QTextEdit* edit;

    // Tableview
    bool is_editable;
    bool is_changed;

    // Widget add Form
    QGridLayout *add_form_layout;
    QLabel *label_componente;
    QLineEdit *lineedit_componente;
    QComboBox *combobox_componente;
    QDateTimeEdit *datetime_componente;
    QDateEdit *date_componente;
    QCheckBox *checkbox_componente;
    qs tabela;

    // status
    QLabel *info_status;

    // Keep information about the actions menus and the widgets
    lpv actions;   
    lpv botoes;
    QHash <QString , QHash<int,QVariant> > entradas;
    QHash <QString , QLabel * > entradas_qlabel;
    QHash <QString , QLineEdit * > entradas_lineedit;
    QHash <QString , QComboBox * > entradas_combobox;
    QHash <QString , QDateTimeEdit * > entradas_datetimeedit;
    QHash <QString , QDateEdit * > entradas_date;
    QHash <QString , QCheckBox * > entradas_checkbox;

    // Design stuff
    static const QString combobox_stylesheet;

    static const int STYLE_FUSION = 1;

    // Database
    database *db;

    // Menus
    lpv menus;
    QMenuBar *menubar;
    QMenu *mainmenu;

    // Erros
    static const int SUCESS = 0;
    static const int WDG_ERR = 1;

    // Widgets
    static const int WDG_PRINCIPAL = 0;
    static const int WDG_ADICIONAR = 1;
    static const int WDG_FINANCEIRO = 2;

    // Botoes
    static const int BTN_HELP = 9;
    static const int BTN_REFRESH = 10;

    // Button function type
    static const int TYPE_HTML = 0;
    static const int TYPE_PDF = 1;       
};

#endif // MAINWINDOW_H
