/****************************************************************************
** Meta object code from reading C++ file 'PriceDisplayBoardWindowBox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PriceDisplayBoardWindowBox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PriceDisplayBoardWindowBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PriceDisplayBoardWindowBox_t {
    QByteArrayData data[22];
    char stringdata[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PriceDisplayBoardWindowBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PriceDisplayBoardWindowBox_t qt_meta_stringdata_PriceDisplayBoardWindowBox = {
    {
QT_MOC_LITERAL(0, 0, 26),
QT_MOC_LITERAL(1, 27, 14),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 9),
QT_MOC_LITERAL(4, 53, 11),
QT_MOC_LITERAL(5, 65, 11),
QT_MOC_LITERAL(6, 77, 12),
QT_MOC_LITERAL(7, 90, 12),
QT_MOC_LITERAL(8, 103, 14),
QT_MOC_LITERAL(9, 118, 13),
QT_MOC_LITERAL(10, 132, 18),
QT_MOC_LITERAL(11, 151, 5),
QT_MOC_LITERAL(12, 157, 5),
QT_MOC_LITERAL(13, 163, 6),
QT_MOC_LITERAL(14, 170, 3),
QT_MOC_LITERAL(15, 174, 6),
QT_MOC_LITERAL(16, 181, 7),
QT_MOC_LITERAL(17, 189, 8),
QT_MOC_LITERAL(18, 198, 12),
QT_MOC_LITERAL(19, 211, 13),
QT_MOC_LITERAL(20, 225, 8),
QT_MOC_LITERAL(21, 234, 12)
    },
    "PriceDisplayBoardWindowBox\0TurnOverSignal\0"
    "\0AddSignal\0OrderSignal\0ChartSignal\0"
    "DeleteSignal\0MoveUpSignal\0MoveDownSignal\0"
    "UpToTopSignal\0DownToBottomSignal\0Order\0"
    "Chart\0Delete\0Add\0MoveUp\0UpToTop\0"
    "MoveDown\0DownToBottom\0HighestLowest\0"
    "PreClose\0InterestRate\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PriceDisplayBoardWindowBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  114,    2, 0x05,
       3,    0,  117,    2, 0x05,
       4,    1,  118,    2, 0x05,
       5,    1,  121,    2, 0x05,
       6,    1,  124,    2, 0x05,
       7,    1,  127,    2, 0x05,
       8,    1,  130,    2, 0x05,
       9,    1,  133,    2, 0x05,
      10,    1,  136,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      11,    0,  139,    2, 0x0a,
      12,    0,  140,    2, 0x0a,
      13,    0,  141,    2, 0x0a,
      14,    0,  142,    2, 0x0a,
      15,    0,  143,    2, 0x0a,
      16,    0,  144,    2, 0x0a,
      17,    0,  145,    2, 0x0a,
      18,    0,  146,    2, 0x0a,
      19,    0,  147,    2, 0x0a,
      20,    0,  148,    2, 0x0a,
      21,    0,  149,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

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

       0        // eod
};

void PriceDisplayBoardWindowBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PriceDisplayBoardWindowBox *_t = static_cast<PriceDisplayBoardWindowBox *>(_o);
        switch (_id) {
        case 0: _t->TurnOverSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->AddSignal(); break;
        case 2: _t->OrderSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->ChartSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->DeleteSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->MoveUpSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->MoveDownSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->UpToTopSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->DownToBottomSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->Order(); break;
        case 10: _t->Chart(); break;
        case 11: _t->Delete(); break;
        case 12: _t->Add(); break;
        case 13: _t->MoveUp(); break;
        case 14: _t->UpToTop(); break;
        case 15: _t->MoveDown(); break;
        case 16: _t->DownToBottom(); break;
        case 17: _t->HighestLowest(); break;
        case 18: _t->PreClose(); break;
        case 19: _t->InterestRate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PriceDisplayBoardWindowBox::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PriceDisplayBoardWindowBox::TurnOverSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (PriceDisplayBoardWindowBox::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PriceDisplayBoardWindowBox::AddSignal)) {
                *result = 1;
            }
        }
        {
            typedef void (PriceDisplayBoardWindowBox::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PriceDisplayBoardWindowBox::OrderSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (PriceDisplayBoardWindowBox::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PriceDisplayBoardWindowBox::ChartSignal)) {
                *result = 3;
            }
        }
        {
            typedef void (PriceDisplayBoardWindowBox::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PriceDisplayBoardWindowBox::DeleteSignal)) {
                *result = 4;
            }
        }
        {
            typedef void (PriceDisplayBoardWindowBox::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PriceDisplayBoardWindowBox::MoveUpSignal)) {
                *result = 5;
            }
        }
        {
            typedef void (PriceDisplayBoardWindowBox::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PriceDisplayBoardWindowBox::MoveDownSignal)) {
                *result = 6;
            }
        }
        {
            typedef void (PriceDisplayBoardWindowBox::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PriceDisplayBoardWindowBox::UpToTopSignal)) {
                *result = 7;
            }
        }
        {
            typedef void (PriceDisplayBoardWindowBox::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PriceDisplayBoardWindowBox::DownToBottomSignal)) {
                *result = 8;
            }
        }
    }
}

const QMetaObject PriceDisplayBoardWindowBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PriceDisplayBoardWindowBox.data,
      qt_meta_data_PriceDisplayBoardWindowBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *PriceDisplayBoardWindowBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PriceDisplayBoardWindowBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PriceDisplayBoardWindowBox.stringdata))
        return static_cast<void*>(const_cast< PriceDisplayBoardWindowBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int PriceDisplayBoardWindowBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void PriceDisplayBoardWindowBox::TurnOverSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PriceDisplayBoardWindowBox::AddSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PriceDisplayBoardWindowBox::OrderSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PriceDisplayBoardWindowBox::ChartSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PriceDisplayBoardWindowBox::DeleteSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PriceDisplayBoardWindowBox::MoveUpSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PriceDisplayBoardWindowBox::MoveDownSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PriceDisplayBoardWindowBox::UpToTopSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PriceDisplayBoardWindowBox::DownToBottomSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
