/****************************************************************************
** Meta object code from reading C++ file 'SetFontDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SetFontDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SetFontDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SetFontDlg_t {
    QByteArrayData data[16];
    char stringdata[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SetFontDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SetFontDlg_t qt_meta_stringdata_SetFontDlg = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 13),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 5),
QT_MOC_LITERAL(4, 32, 5),
QT_MOC_LITERAL(5, 38, 15),
QT_MOC_LITERAL(6, 54, 7),
QT_MOC_LITERAL(7, 62, 17),
QT_MOC_LITERAL(8, 80, 8),
QT_MOC_LITERAL(9, 89, 18),
QT_MOC_LITERAL(10, 108, 9),
QT_MOC_LITERAL(11, 118, 7),
QT_MOC_LITERAL(12, 126, 6),
QT_MOC_LITERAL(13, 133, 9),
QT_MOC_LITERAL(14, 143, 11),
QT_MOC_LITERAL(15, 155, 12)
    },
    "SetFontDlg\0SetBoldSignal\0\0index\0bBold\0"
    "SetItalicSignal\0bItalic\0SetFontSizeSignal\0"
    "fontSize\0SetFontColorSignal\0fontColor\0"
    "SetBold\0status\0SetItalic\0SetFontSize\0"
    "SetFontColor\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetFontDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x05,
       5,    2,   59,    2, 0x05,
       7,    2,   64,    2, 0x05,
       9,    2,   69,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      11,    1,   74,    2, 0x0a,
      13,    1,   77,    2, 0x0a,
      14,    1,   80,    2, 0x0a,
      15,    1,   83,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QColor,    3,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void SetFontDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetFontDlg *_t = static_cast<SetFontDlg *>(_o);
        switch (_id) {
        case 0: _t->SetBoldSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->SetItalicSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->SetFontSizeSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->SetFontColorSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2]))); break;
        case 4: _t->SetBold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SetItalic((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->SetFontSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->SetFontColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SetFontDlg::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetFontDlg::SetBoldSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (SetFontDlg::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetFontDlg::SetItalicSignal)) {
                *result = 1;
            }
        }
        {
            typedef void (SetFontDlg::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetFontDlg::SetFontSizeSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (SetFontDlg::*_t)(int , const QColor & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetFontDlg::SetFontColorSignal)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject SetFontDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SetFontDlg.data,
      qt_meta_data_SetFontDlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *SetFontDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetFontDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SetFontDlg.stringdata))
        return static_cast<void*>(const_cast< SetFontDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int SetFontDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void SetFontDlg::SetBoldSignal(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SetFontDlg::SetItalicSignal(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SetFontDlg::SetFontSizeSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SetFontDlg::SetFontColorSignal(int _t1, const QColor & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
