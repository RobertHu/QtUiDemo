/****************************************************************************
** Meta object code from reading C++ file 'InstantOrderTab.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../InstantOrderTab.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InstantOrderTab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InstantOrderTab_t {
    QByteArrayData data[9];
    char stringdata[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_InstantOrderTab_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_InstantOrderTab_t qt_meta_stringdata_InstantOrderTab = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 23),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 9),
QT_MOC_LITERAL(4, 51, 15),
QT_MOC_LITERAL(5, 67, 16),
QT_MOC_LITERAL(6, 84, 5),
QT_MOC_LITERAL(7, 90, 19),
QT_MOC_LITERAL(8, 110, 16)
    },
    "InstantOrderTab\0AppendOrderRecordSignal\0"
    "\0OrderData\0SetCloseAllSlot\0PlaceAnOrderSlot\0"
    "isBid\0GetCurrentPriceSlot\0CurrentPriceData\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InstantOrderTab[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x0a,
       5,    1,   38,    2, 0x0a,
       7,    1,   41,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, 0x80000000 | 8,    2,

       0        // eod
};

void InstantOrderTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InstantOrderTab *_t = static_cast<InstantOrderTab *>(_o);
        switch (_id) {
        case 0: _t->AppendOrderRecordSignal((*reinterpret_cast< const OrderData(*)>(_a[1]))); break;
        case 1: _t->SetCloseAllSlot(); break;
        case 2: _t->PlaceAnOrderSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->GetCurrentPriceSlot((*reinterpret_cast< const CurrentPriceData(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (InstantOrderTab::*_t)(const OrderData & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InstantOrderTab::AppendOrderRecordSignal)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject InstantOrderTab::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InstantOrderTab.data,
      qt_meta_data_InstantOrderTab,  qt_static_metacall, 0, 0}
};


const QMetaObject *InstantOrderTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InstantOrderTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InstantOrderTab.stringdata))
        return static_cast<void*>(const_cast< InstantOrderTab*>(this));
    return QDialog::qt_metacast(_clname);
}

int InstantOrderTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void InstantOrderTab::AppendOrderRecordSignal(const OrderData & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
