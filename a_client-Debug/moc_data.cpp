/****************************************************************************
** Meta object code from reading C++ file 'data.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../a_client/data.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'data.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Data_t {
    QByteArrayData data[13];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Data_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Data_t qt_meta_stringdata_Data = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Data"
QT_MOC_LITERAL(1, 5, 16), // "ledOptionChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "dataChanged"
QT_MOC_LITERAL(4, 35, 11), // "srvKChanged"
QT_MOC_LITERAL(5, 47, 9), // "srvKinect"
QT_MOC_LITERAL(6, 57, 7), // "newSrvK"
QT_MOC_LITERAL(7, 65, 12), // "setLedOption"
QT_MOC_LITERAL(8, 78, 6), // "option"
QT_MOC_LITERAL(9, 85, 12), // "getLedOption"
QT_MOC_LITERAL(10, 98, 7), // "setData"
QT_MOC_LITERAL(11, 106, 7), // "setSrvK"
QT_MOC_LITERAL(12, 114, 7) // "getSrvK"

    },
    "Data\0ledOptionChanged\0\0dataChanged\0"
    "srvKChanged\0srvKinect\0newSrvK\0"
    "setLedOption\0option\0getLedOption\0"
    "setData\0setSrvK\0getSrvK"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Data[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    1,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   59,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,
      11,    1,   64,    2, 0x0a /* Public */,
      12,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    0x80000000 | 5,

       0        // eod
};

void Data::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Data *_t = static_cast<Data *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ledOptionChanged(); break;
        case 1: _t->dataChanged(); break;
        case 2: _t->srvKChanged((*reinterpret_cast< srvKinect(*)>(_a[1]))); break;
        case 3: _t->setLedOption((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: { int _r = _t->getLedOption();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: _t->setData(); break;
        case 6: _t->setSrvK((*reinterpret_cast< srvKinect(*)>(_a[1]))); break;
        case 7: { srvKinect _r = _t->getSrvK();
            if (_a[0]) *reinterpret_cast< srvKinect*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Data::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Data::ledOptionChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (Data::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Data::dataChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (Data::*_t)(srvKinect );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Data::srvKChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Data::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Data.data,
      qt_meta_data_Data,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Data::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Data::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Data.stringdata0))
        return static_cast<void*>(const_cast< Data*>(this));
    return QWidget::qt_metacast(_clname);
}

int Data::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Data::ledOptionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Data::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Data::srvKChanged(srvKinect _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
