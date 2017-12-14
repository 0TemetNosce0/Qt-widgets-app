/****************************************************************************
** Meta object code from reading C++ file 'webcrawler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/webcrawler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'webcrawler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WebCrawler_Parser_t {
    QByteArrayData data[16];
    char stringdata[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_WebCrawler_Parser_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_WebCrawler_Parser_t qt_meta_stringdata_WebCrawler_Parser = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 16),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 3),
QT_MOC_LITERAL(4, 40, 2),
QT_MOC_LITERAL(5, 43, 16),
QT_MOC_LITERAL(6, 60, 6),
QT_MOC_LITERAL(7, 67, 6),
QT_MOC_LITERAL(8, 74, 11),
QT_MOC_LITERAL(9, 86, 8),
QT_MOC_LITERAL(10, 95, 5),
QT_MOC_LITERAL(11, 101, 14),
QT_MOC_LITERAL(12, 116, 5),
QT_MOC_LITERAL(13, 122, 7),
QT_MOC_LITERAL(14, 130, 1),
QT_MOC_LITERAL(15, 132, 19)
    },
    "WebCrawler_Parser\0signalCreateNode\0\0"
    "url\0no\0signalCreateEdge\0source\0target\0"
    "startSpider\0finished\0parse\0QNetworkReply*\0"
    "reply\0newLink\0s\0enqueue_to_frontier\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebCrawler_Parser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x05,
       5,    2,   49,    2, 0x05,
       8,    0,   54,    2, 0x05,
       9,    1,   55,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      10,    1,   58,    2, 0x0a,
      13,    3,   61,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::QUrl, QMetaType::Bool,   14,    7,   15,

       0        // eod
};

void WebCrawler_Parser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WebCrawler_Parser *_t = static_cast<WebCrawler_Parser *>(_o);
        switch (_id) {
        case 0: _t->signalCreateNode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->signalCreateEdge((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->startSpider(); break;
        case 3: _t->finished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->parse((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->newLink((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QUrl(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WebCrawler_Parser::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebCrawler_Parser::signalCreateNode)) {
                *result = 0;
            }
        }
        {
            typedef void (WebCrawler_Parser::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebCrawler_Parser::signalCreateEdge)) {
                *result = 1;
            }
        }
        {
            typedef void (WebCrawler_Parser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebCrawler_Parser::startSpider)) {
                *result = 2;
            }
        }
        {
            typedef void (WebCrawler_Parser::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebCrawler_Parser::finished)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject WebCrawler_Parser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WebCrawler_Parser.data,
      qt_meta_data_WebCrawler_Parser,  qt_static_metacall, 0, 0}
};


const QMetaObject *WebCrawler_Parser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebCrawler_Parser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WebCrawler_Parser.stringdata))
        return static_cast<void*>(const_cast< WebCrawler_Parser*>(this));
    return QObject::qt_metacast(_clname);
}

int WebCrawler_Parser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WebCrawler_Parser::signalCreateNode(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WebCrawler_Parser::signalCreateEdge(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WebCrawler_Parser::startSpider()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void WebCrawler_Parser::finished(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_WebCrawler_Spider_t {
    QByteArrayData data[8];
    char stringdata[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_WebCrawler_Spider_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_WebCrawler_Spider_t qt_meta_stringdata_WebCrawler_Spider = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 5),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 14),
QT_MOC_LITERAL(4, 40, 5),
QT_MOC_LITERAL(5, 46, 8),
QT_MOC_LITERAL(6, 55, 3),
QT_MOC_LITERAL(7, 59, 12)
    },
    "WebCrawler_Spider\0parse\0\0QNetworkReply*\0"
    "reply\0finished\0get\0httpFinished\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebCrawler_Spider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x05,
       5,    1,   37,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       6,    0,   40,    2, 0x0a,
       7,    1,   41,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void WebCrawler_Spider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WebCrawler_Spider *_t = static_cast<WebCrawler_Spider *>(_o);
        switch (_id) {
        case 0: _t->parse((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->finished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->get(); break;
        case 3: _t->httpFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WebCrawler_Spider::*_t)(QNetworkReply * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebCrawler_Spider::parse)) {
                *result = 0;
            }
        }
        {
            typedef void (WebCrawler_Spider::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebCrawler_Spider::finished)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject WebCrawler_Spider::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WebCrawler_Spider.data,
      qt_meta_data_WebCrawler_Spider,  qt_static_metacall, 0, 0}
};


const QMetaObject *WebCrawler_Spider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebCrawler_Spider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WebCrawler_Spider.stringdata))
        return static_cast<void*>(const_cast< WebCrawler_Spider*>(this));
    return QObject::qt_metacast(_clname);
}

int WebCrawler_Spider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void WebCrawler_Spider::parse(QNetworkReply * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WebCrawler_Spider::finished(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
