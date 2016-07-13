/****************************************************************************
** Meta object code from reading C++ file 'framegl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../a_server/framegl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framegl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FrameGL_t {
    QByteArrayData data[26];
    char stringdata0[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FrameGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FrameGL_t qt_meta_stringdata_FrameGL = {
    {
QT_MOC_LITERAL(0, 0, 7), // "FrameGL"
QT_MOC_LITERAL(1, 8, 7), // "clicked"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 10), // "xRotChange"
QT_MOC_LITERAL(4, 28, 5), // "angle"
QT_MOC_LITERAL(5, 34, 10), // "yRotChange"
QT_MOC_LITERAL(6, 45, 10), // "zRotChange"
QT_MOC_LITERAL(7, 56, 9), // "setpCloud"
QT_MOC_LITERAL(8, 66, 20), // "std::vector<point3c>"
QT_MOC_LITERAL(9, 87, 1), // "c"
QT_MOC_LITERAL(10, 89, 5), // "count"
QT_MOC_LITERAL(11, 95, 12), // "initializeGL"
QT_MOC_LITERAL(12, 108, 7), // "paintGL"
QT_MOC_LITERAL(13, 116, 8), // "resizeGL"
QT_MOC_LITERAL(14, 125, 5), // "width"
QT_MOC_LITERAL(15, 131, 6), // "height"
QT_MOC_LITERAL(16, 138, 15), // "mousePressEvent"
QT_MOC_LITERAL(17, 154, 12), // "QMouseEvent*"
QT_MOC_LITERAL(18, 167, 5), // "event"
QT_MOC_LITERAL(19, 173, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(20, 188, 10), // "wheelEvent"
QT_MOC_LITERAL(21, 199, 12), // "QWheelEvent*"
QT_MOC_LITERAL(22, 212, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(23, 230, 9), // "drawCloud"
QT_MOC_LITERAL(24, 240, 8), // "drawAxis"
QT_MOC_LITERAL(25, 249, 9) // "drawLines"

    },
    "FrameGL\0clicked\0\0xRotChange\0angle\0"
    "yRotChange\0zRotChange\0setpCloud\0"
    "std::vector<point3c>\0c\0count\0initializeGL\0"
    "paintGL\0resizeGL\0width\0height\0"
    "mousePressEvent\0QMouseEvent*\0event\0"
    "mouseMoveEvent\0wheelEvent\0QWheelEvent*\0"
    "mouseReleaseEvent\0drawCloud\0drawAxis\0"
    "drawLines"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FrameGL[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    1,   90,    2, 0x06 /* Public */,
       5,    1,   93,    2, 0x06 /* Public */,
       6,    1,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   99,    2, 0x0a /* Public */,
      11,    0,  104,    2, 0x0a /* Public */,
      12,    0,  105,    2, 0x0a /* Public */,
      13,    2,  106,    2, 0x0a /* Public */,
      16,    1,  111,    2, 0x0a /* Public */,
      19,    1,  114,    2, 0x0a /* Public */,
      20,    1,  117,    2, 0x0a /* Public */,
      22,    1,  120,    2, 0x0a /* Public */,
      23,    0,  123,    2, 0x0a /* Public */,
      24,    0,  124,    2, 0x0a /* Public */,
      25,    0,  125,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int,    9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 21,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FrameGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FrameGL *_t = static_cast<FrameGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->xRotChange((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->yRotChange((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->zRotChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setpCloud((*reinterpret_cast< std::vector<point3c>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->initializeGL(); break;
        case 6: _t->paintGL(); break;
        case 7: _t->resizeGL((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 9: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 10: _t->wheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 11: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 12: _t->drawCloud(); break;
        case 13: _t->drawAxis(); break;
        case 14: _t->drawLines(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FrameGL::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FrameGL::clicked)) {
                *result = 0;
            }
        }
        {
            typedef void (FrameGL::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FrameGL::xRotChange)) {
                *result = 1;
            }
        }
        {
            typedef void (FrameGL::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FrameGL::yRotChange)) {
                *result = 2;
            }
        }
        {
            typedef void (FrameGL::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FrameGL::zRotChange)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject FrameGL::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_FrameGL.data,
      qt_meta_data_FrameGL,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FrameGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrameGL::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FrameGL.stringdata0))
        return static_cast<void*>(const_cast< FrameGL*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int FrameGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
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
void FrameGL::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FrameGL::xRotChange(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FrameGL::yRotChange(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FrameGL::zRotChange(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
