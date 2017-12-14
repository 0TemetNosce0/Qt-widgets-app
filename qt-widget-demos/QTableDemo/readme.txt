QTable is table wrapper for table models (and for any models in general case).
The purpose of this class is to simplify work with tables for novices in Qt.

Use this class to simply create and manipulate table with ability to link to various viewers (for example, to QTableView).


Example of usage:

// Making
static QTable table;
ui->tableView->setModel( table.model() );
// Cofiguring
table.setColumnCount(3);
table.setColumnHeaders( QTableLine( "Name", "Product", "Cost" ) );
// Add data
table.appendRow( QTableLine( "V. Pupkin", "Car", "22000" ) );
table.appendRow( QTableLine( "I. Ivanov", "T-Shirt", "15" ) );
// Manipulate data
int sum = table.value(0,2).toInt() + table.value(1,2).toInt();
table.set( 0,2, 22500 );


By default QTable makes instance of QTableModel - the model-class of editable QVariant table. You can access to this model using model() member of QTable instance.


Also QTable can be used with external model:

QStringListModel listModel;
listModel.setStringList( QStringList() << "one" << "two" << "three" );
QTable table( &listModel );
qDebug() << table.column(0).cells();
table.set( 0, 0, "new one" );
qDebug() << table.column(0).cells();


You can copy rows or columns:

// Copy row 0 to row 1
table.setRow( 1, table.row(0) );
// Copy column 2 to column 0
table.setColumn( 1, table.column(0) );


You can work with headers of table:
// writing
table.setColumnHeaders( QTableLine( "Column 1", "Column 2", "Column 3" ) );
table.setRowHeaders( QTableLine( "Row1", "Row2" ) );
// by-element writing
table.setRowHeader( 0, "row 1" );
table.setColumnHeader( 0, "column 1" );
// reading
QString rowHdr1 = table.rowHeader(0).toString();
QString columnHdr1 = table.columnHeader(0).toString;


Also you can change root of table (useful for tree models):
table.setParent( model.index(1,0) );

