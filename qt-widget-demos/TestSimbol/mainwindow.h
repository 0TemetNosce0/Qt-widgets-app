#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GLDTableView.h"
#include "GLDDefaultItemDelegate.h"
#include "GLDGlobal.h"
#include "GSPTableView.h"
#include "GTPGSPTableView.h"
#include "GLDFooterTableView.h"
#include "GSPCore.h"
#include "GSPDefaultItemDelegate.h"
#include "GSPGridDataSourceModel.h"
#include "GSPGridDataSource.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>

namespace Ui {
class MainWindow;
}

/**
 * @brief The GlodonSimbolBtn class 特殊字符Buttton类
 */
class GlodonSimbolBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit GlodonSimbolBtn(QWidget *parent = 0, const QString &simbol = "");

public slots:
    void onclicked();

signals:
    void showText(const QString &text);

private:
    QString m_simbol;
};

class GlodonSimbolRow : public QWidget
{
    Q_OBJECT
public:
    explicit GlodonSimbolRow(const QStringList &simbols, QWidget *parent = 0);
    void layoutSimbolRow();

signals:
    void showText(const QString &text);

private:
    QList<GlodonSimbolBtn *> m_simbolBtns;
    QHBoxLayout *m_rowLayout;
};

class GlodonSimbolTable : public QWidget
{
    Q_OBJECT
public:
    explicit GlodonSimbolTable(const QStringList &simbols, QWidget *parent = 0);
    void appendSimbolRow(const QStringList &simbols);
    void layoutSimbolTable();

signals:
    void showText(const QString &text);

private:
    QList<GlodonSimbolRow*> m_simbolRows;
    QVBoxLayout *m_simbolTableLayout;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void testGlodonSimbolRow();
    void testGlodonSimbolTable();

private slots:
    void showPopWidget();
    void displayOnLineEdit(const QString &text);

private:
    void loadDataToTableView();
    QWidget *loadTableView();
    QWidget *loadFilterTableView();
    QWidget *loadFooterTableView();
    QList<QStringList> loadSimbolText();
    void loadFont();
    void initWidget();

    void loadGSPTableView();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *m_model;
    GlodonTableView *m_pTableView;
    QWidget *m_showWidget;
    QWidget *m_simbolWidget;
    QPushButton *m_simbolBtn;
    QPushButton *m_row1Btn;
    QLineEdit *m_lineEdit1;
    QLineEdit *m_lineEdit2;

    GlodonSimbolBtn *m_simbolButton;
    GlodonSimbolRow *m_simbolRow;
    GlodonSimbolTable *m_simbolTable;

    QString m_simbolText;
    QList<QStringList> m_simbolList;

    QHBoxLayout *m_gsplayout;
    GSPModel m_gspModel;
    GSPGridDataSource *m_dataSource;
    GSPGridDataSourceModel *m_dataSourceModel;
    GSPTableView *m_gspTableView;
    GTPGSPTableView *m_gtpGspTableView;

    GlodonFooterTableView *m_footerTableView;
    GlodonFilterTableView *m_filterTableView;
};

class GlodonTableViewDelegate : public GlodonDefaultItemDelegate
{
    Q_OBJECT
public:
    explicit GlodonTableViewDelegate(QObject *parent = 0){G_UNUSED(parent)}
    GEditStyle editStyle(const QModelIndex &index, bool &readOnly) const;
    void initComboBox(QComboBox *comboBox, const QModelIndex &index) const;
};

class GSPTableViewDelegate : public GSPDefaultItemDelegate
{
public:
    GSPTableViewDelegate(QObject *parent = 0);
    GEditStyle editStyle(const QModelIndex &index, bool &readOnly) const;
};

#endif // MAINWINDOW_H
