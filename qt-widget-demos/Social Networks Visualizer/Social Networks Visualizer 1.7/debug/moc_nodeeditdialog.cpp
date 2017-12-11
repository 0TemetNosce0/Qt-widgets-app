/****************************************************************************
** Meta object code from reading C++ file 'nodeeditdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/nodeeditdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nodeeditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NodeEditDialog_t {
    QByteArrayData data[7];
    char stringdata[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_NodeEditDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_NodeEditDialog_t qt_meta_stringdata_NodeEditDialog = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 11),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 19),
QT_MOC_LITERAL(4, 48, 11),
QT_MOC_LITERAL(5, 60, 10),
QT_MOC_LITERAL(6, 71, 11)
    },
    "NodeEditDialog\0userChoices\0\0"
    "nodeEditDialogError\0checkErrors\0"
    "gatherData\0selectColor\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NodeEditDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   39,    2, 0x05,
       3,    1,   50,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    0,   53,    2, 0x0a,
       5,    0,   54,    2, 0x0a,
       6,    0,   55,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::QColor, QMetaType::QString,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NodeEditDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NodeEditDialog *_t = static_cast<NodeEditDialog *>(_o);
        switch (_id) {
        case 0: _t->userChoices((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QColor(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 1: _t->nodeEditDialogError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->checkErrors(); break;
        case 3: _t->gatherData(); break;
        case 4: _t->selectColor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NodeEditDialog::*_t)(const QString , const int , const QString , const QColor , const QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NodeEditDialog::userChoices)) {
                *result = 0;
            }
        }
        {
            typedef void (NodeEditDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NodeEditDialog::nodeEditDialogError)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject NodeEditDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NodeEditDialog.data,
      qt_meta_data_NodeEditDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *NodeEditDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NodeEditDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NodeEditDialog.stringdata))
        return static_cast<void*>(const_cast< NodeEditDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NodeEditDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void NodeEditDialog::userChoices(const QString _t1, const int _t2, const QString _t3, const QColor _t4, const QString _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NodeEditDialog::nodeEditDialogError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
