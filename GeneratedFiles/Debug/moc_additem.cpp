/****************************************************************************
** Meta object code from reading C++ file 'additem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../additem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'additem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AddItem_t {
    QByteArrayData data[12];
    char stringdata[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AddItem_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AddItem_t qt_meta_stringdata_AddItem = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 6),
QT_MOC_LITERAL(2, 15, 0),
QT_MOC_LITERAL(3, 16, 20),
QT_MOC_LITERAL(4, 37, 14),
QT_MOC_LITERAL(5, 52, 16),
QT_MOC_LITERAL(6, 69, 11),
QT_MOC_LITERAL(7, 81, 6),
QT_MOC_LITERAL(8, 88, 8),
QT_MOC_LITERAL(9, 97, 11),
QT_MOC_LITERAL(10, 109, 16),
QT_MOC_LITERAL(11, 126, 11)
    },
    "AddItem\0accept\0\0RemovedSelectedItems\0"
    "RemoveAllItems\0AddSelectedItems\0"
    "AddAllItems\0MoveUp\0MoveDown\0MoveUpToTop\0"
    "MoveDownToBotton\0Synchronous\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a,
       3,    0,   65,    2, 0x08,
       4,    0,   66,    2, 0x08,
       5,    0,   67,    2, 0x08,
       6,    0,   68,    2, 0x08,
       7,    0,   69,    2, 0x08,
       8,    0,   70,    2, 0x08,
       9,    0,   71,    2, 0x08,
      10,    0,   72,    2, 0x08,
      11,    0,   73,    2, 0x08,

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

       0        // eod
};

void AddItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddItem *_t = static_cast<AddItem *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->RemovedSelectedItems(); break;
        case 2: _t->RemoveAllItems(); break;
        case 3: _t->AddSelectedItems(); break;
        case 4: _t->AddAllItems(); break;
        case 5: _t->MoveUp(); break;
        case 6: _t->MoveDown(); break;
        case 7: _t->MoveUpToTop(); break;
        case 8: _t->MoveDownToBotton(); break;
        case 9: _t->Synchronous(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AddItem::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddItem.data,
      qt_meta_data_AddItem,  qt_static_metacall, 0, 0}
};


const QMetaObject *AddItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddItem.stringdata))
        return static_cast<void*>(const_cast< AddItem*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
