/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../a_server/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "videoDataReady"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "depthDataReady"
QT_MOC_LITERAL(4, 42, 14), // "barreDataReady"
QT_MOC_LITERAL(5, 57, 9), // "barreInit"
QT_MOC_LITERAL(6, 67, 4), // "init"
QT_MOC_LITERAL(7, 72, 11), // "setServerIp"
QT_MOC_LITERAL(8, 84, 9), // "putKcombo"
QT_MOC_LITERAL(9, 94, 6), // "startK"
QT_MOC_LITERAL(10, 101, 6), // "indexK"
QT_MOC_LITERAL(11, 108, 5), // "stopK"
QT_MOC_LITERAL(12, 114, 4), // "loop"
QT_MOC_LITERAL(13, 119, 8), // "stoploop"
QT_MOC_LITERAL(14, 128, 15), // "on_pbGo_clicked"
QT_MOC_LITERAL(15, 144, 17), // "on_pbStop_clicked"
QT_MOC_LITERAL(16, 162, 18), // "on_combo_activated"
QT_MOC_LITERAL(17, 181, 4), // "arg1"
QT_MOC_LITERAL(18, 186, 15) // "attendNewClient"

    },
    "MainWindow\0videoDataReady\0\0depthDataReady\0"
    "barreDataReady\0barreInit\0init\0setServerIp\0"
    "putKcombo\0startK\0indexK\0stopK\0loop\0"
    "stoploop\0on_pbGo_clicked\0on_pbStop_clicked\0"
    "on_combo_activated\0arg1\0attendNewClient"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a /* Public */,
       3,    0,   90,    2, 0x0a /* Public */,
       4,    0,   91,    2, 0x0a /* Public */,
       5,    0,   92,    2, 0x0a /* Public */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    1,   96,    2, 0x08 /* Private */,
      11,    1,   99,    2, 0x08 /* Private */,
      12,    0,  102,    2, 0x08 /* Private */,
      13,    0,  103,    2, 0x08 /* Private */,
      14,    0,  104,    2, 0x08 /* Private */,
      15,    0,  105,    2, 0x08 /* Private */,
      16,    1,  106,    2, 0x08 /* Private */,
      18,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->videoDataReady(); break;
        case 1: _t->depthDataReady(); break;
        case 2: _t->barreDataReady(); break;
        case 3: _t->barreInit(); break;
        case 4: _t->init(); break;
        case 5: _t->setServerIp(); break;
        case 6: _t->putKcombo(); break;
        case 7: _t->startK((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->stopK((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->loop(); break;
        case 10: _t->stoploop(); break;
        case 11: _t->on_pbGo_clicked(); break;
        case 12: _t->on_pbStop_clicked(); break;
        case 13: _t->on_combo_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->attendNewClient(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
