/****************************************************************************
** Meta object code from reading C++ file 'attendclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../a_server/attendclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'attendclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AttendClient_t {
    QByteArrayData data[19];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AttendClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AttendClient_t qt_meta_stringdata_AttendClient = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AttendClient"
QT_MOC_LITERAL(1, 13, 12), // "newSrvKinect"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 9), // "srvKinect"
QT_MOC_LITERAL(4, 37, 7), // "newSrvK"
QT_MOC_LITERAL(5, 45, 12), // "startServers"
QT_MOC_LITERAL(6, 58, 12), // "readSrvKdata"
QT_MOC_LITERAL(7, 71, 13), // "incomingVideo"
QT_MOC_LITERAL(8, 85, 9), // "sendVideo"
QT_MOC_LITERAL(9, 95, 13), // "incomingDepth"
QT_MOC_LITERAL(10, 109, 9), // "sendDepth"
QT_MOC_LITERAL(11, 119, 10), // "incoming3d"
QT_MOC_LITERAL(12, 130, 6), // "send3d"
QT_MOC_LITERAL(13, 137, 10), // "incoming2d"
QT_MOC_LITERAL(14, 148, 6), // "send2d"
QT_MOC_LITERAL(15, 155, 15), // "incomingBarrido"
QT_MOC_LITERAL(16, 171, 11), // "sendBarrido"
QT_MOC_LITERAL(17, 183, 13), // "incomingAccel"
QT_MOC_LITERAL(18, 197, 9) // "sendAccel"

    },
    "AttendClient\0newSrvKinect\0\0srvKinect\0"
    "newSrvK\0startServers\0readSrvKdata\0"
    "incomingVideo\0sendVideo\0incomingDepth\0"
    "sendDepth\0incoming3d\0send3d\0incoming2d\0"
    "send2d\0incomingBarrido\0sendBarrido\0"
    "incomingAccel\0sendAccel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AttendClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   92,    2, 0x0a /* Public */,
       6,    0,   93,    2, 0x0a /* Public */,
       7,    0,   94,    2, 0x0a /* Public */,
       8,    0,   95,    2, 0x0a /* Public */,
       9,    0,   96,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,
      17,    0,  104,    2, 0x0a /* Public */,
      18,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AttendClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AttendClient *_t = static_cast<AttendClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newSrvKinect((*reinterpret_cast< srvKinect(*)>(_a[1]))); break;
        case 1: _t->startServers(); break;
        case 2: _t->readSrvKdata(); break;
        case 3: _t->incomingVideo(); break;
        case 4: _t->sendVideo(); break;
        case 5: _t->incomingDepth(); break;
        case 6: _t->sendDepth(); break;
        case 7: _t->incoming3d(); break;
        case 8: _t->send3d(); break;
        case 9: _t->incoming2d(); break;
        case 10: _t->send2d(); break;
        case 11: _t->incomingBarrido(); break;
        case 12: _t->sendBarrido(); break;
        case 13: _t->incomingAccel(); break;
        case 14: _t->sendAccel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AttendClient::*_t)(srvKinect );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AttendClient::newSrvKinect)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject AttendClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AttendClient.data,
      qt_meta_data_AttendClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AttendClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AttendClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AttendClient.stringdata0))
        return static_cast<void*>(const_cast< AttendClient*>(this));
    return QObject::qt_metacast(_clname);
}

int AttendClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void AttendClient::newSrvKinect(srvKinect _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
