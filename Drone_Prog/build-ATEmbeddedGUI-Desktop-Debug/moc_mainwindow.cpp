/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Documents/INSA/5SEC/Drone/Drone_Prog/ATEmbeddedGUI/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata[354];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 14),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 14),
QT_MOC_LITERAL(4, 42, 18),
QT_MOC_LITERAL(5, 61, 15),
QT_MOC_LITERAL(6, 77, 14),
QT_MOC_LITERAL(7, 92, 17),
QT_MOC_LITERAL(8, 110, 15),
QT_MOC_LITERAL(9, 126, 15),
QT_MOC_LITERAL(10, 142, 19),
QT_MOC_LITERAL(11, 162, 18),
QT_MOC_LITERAL(12, 181, 18),
QT_MOC_LITERAL(13, 200, 21),
QT_MOC_LITERAL(14, 222, 13),
QT_MOC_LITERAL(15, 236, 14),
QT_MOC_LITERAL(16, 251, 15),
QT_MOC_LITERAL(17, 267, 16),
QT_MOC_LITERAL(18, 284, 7),
QT_MOC_LITERAL(19, 292, 10),
QT_MOC_LITERAL(20, 303, 5),
QT_MOC_LITERAL(21, 309, 15),
QT_MOC_LITERAL(22, 325, 12),
QT_MOC_LITERAL(23, 338, 14)
    },
    "MainWindow\0process_gauche\0\0process_droite\0"
    "process_taking_off\0process_landing\0"
    "process_monter\0process_descendre\0"
    "process_avancer\0process_reculer\0"
    "process_trans_right\0process_trans_left\0"
    "process_emerg_stop\0process_no_emerg_stop\0"
    "process_close\0process_layout\0"
    "process_mission\0process_nav_data\0"
    "checked\0handle_wdg\0value\0handle_nav_data\0"
    "process_init\0handle_mission\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x0a,
       3,    0,  115,    2, 0x0a,
       4,    0,  116,    2, 0x0a,
       5,    0,  117,    2, 0x0a,
       6,    0,  118,    2, 0x0a,
       7,    0,  119,    2, 0x0a,
       8,    0,  120,    2, 0x0a,
       9,    0,  121,    2, 0x0a,
      10,    0,  122,    2, 0x0a,
      11,    0,  123,    2, 0x0a,
      12,    0,  124,    2, 0x0a,
      13,    0,  125,    2, 0x0a,
      14,    0,  126,    2, 0x0a,
      15,    0,  127,    2, 0x0a,
      16,    0,  128,    2, 0x0a,
      17,    1,  129,    2, 0x0a,
      19,    1,  132,    2, 0x0a,
      21,    0,  135,    2, 0x0a,
      22,    0,  136,    2, 0x0a,
      23,    0,  137,    2, 0x0a,

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
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->process_gauche(); break;
        case 1: _t->process_droite(); break;
        case 2: _t->process_taking_off(); break;
        case 3: _t->process_landing(); break;
        case 4: _t->process_monter(); break;
        case 5: _t->process_descendre(); break;
        case 6: _t->process_avancer(); break;
        case 7: _t->process_reculer(); break;
        case 8: _t->process_trans_right(); break;
        case 9: _t->process_trans_left(); break;
        case 10: _t->process_emerg_stop(); break;
        case 11: _t->process_no_emerg_stop(); break;
        case 12: _t->process_close(); break;
        case 13: _t->process_layout(); break;
        case 14: _t->process_mission(); break;
        case 15: _t->process_nav_data((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->handle_wdg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->handle_nav_data(); break;
        case 18: _t->process_init(); break;
        case 19: _t->handle_mission(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
