/****************************************************************************
** Meta object code from reading C++ file 'qtmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "qtmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtModel_t {
    QByteArrayData data[14];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtModel_t qt_meta_stringdata_QtModel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "QtModel"
QT_MOC_LITERAL(1, 8, 11), // "turnChanged"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 5), // "turns"
QT_MOC_LITERAL(4, 27, 12), // "stateChanged"
QT_MOC_LITERAL(5, 40, 15), // "Game::GameState"
QT_MOC_LITERAL(6, 56, 8), // "redTally"
QT_MOC_LITERAL(7, 65, 10), // "blackTally"
QT_MOC_LITERAL(8, 76, 10), // "roundTally"
QT_MOC_LITERAL(9, 87, 7), // "endGame"
QT_MOC_LITERAL(10, 95, 25), // "moveStacksOnColumnClicked"
QT_MOC_LITERAL(11, 121, 11), // "QModelIndex"
QT_MOC_LITERAL(12, 133, 3), // "idx"
QT_MOC_LITERAL(13, 137, 6) // "replay"

    },
    "QtModel\0turnChanged\0\0turns\0stateChanged\0"
    "Game::GameState\0redTally\0blackTally\0"
    "roundTally\0endGame\0moveStacksOnColumnClicked\0"
    "QModelIndex\0idx\0replay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    1,   60,    2, 0x06 /* Public */,
       7,    1,   63,    2, 0x06 /* Public */,
       8,    2,   66,    2, 0x06 /* Public */,
       9,    2,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   76,    2, 0x0a /* Public */,
      13,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void QtModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->turnChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->stateChanged((*reinterpret_cast< Game::GameState(*)>(_a[1]))); break;
        case 2: _t->redTally((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->blackTally((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->roundTally((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->endGame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->moveStacksOnColumnClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 7: _t->replay(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtModel::turnChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QtModel::*)(Game::GameState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtModel::stateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QtModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtModel::redTally)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QtModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtModel::blackTally)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QtModel::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtModel::roundTally)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QtModel::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtModel::endGame)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractTableModel::staticMetaObject>(),
    qt_meta_stringdata_QtModel.data,
    qt_meta_data_QtModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int QtModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
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
void QtModel::turnChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtModel::stateChanged(Game::GameState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QtModel::redTally(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QtModel::blackTally(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QtModel::roundTally(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QtModel::endGame(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
