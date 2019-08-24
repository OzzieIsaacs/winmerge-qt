/****************************************************************************
** Meta object code from reading C++ file 'MainFrm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainFrm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainFrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[265];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 10), // "OnAppAbout"
QT_MOC_LITERAL(4, 45, 10), // "OnFileOpen"
QT_MOC_LITERAL(5, 56, 13), // "OnToolbarSize"
QT_MOC_LITERAL(6, 70, 2), // "id"
QT_MOC_LITERAL(7, 73, 6), // "OnHelp"
QT_MOC_LITERAL(8, 80, 8), // "ShowHelp"
QT_MOC_LITERAL(9, 89, 16), // "OnHelpGnulicense"
QT_MOC_LITERAL(10, 106, 18), // "OnHelpReleasenotes"
QT_MOC_LITERAL(11, 125, 18), // "OnHelpTranslations"
QT_MOC_LITERAL(12, 144, 17), // "OnFileOpenProject"
QT_MOC_LITERAL(13, 162, 9), // "OnOptions"
QT_MOC_LITERAL(14, 172, 13), // "OnMergingMode"
QT_MOC_LITERAL(15, 186, 27), // "on_listWidget_doubleClicked"
QT_MOC_LITERAL(16, 214, 5), // "index"
QT_MOC_LITERAL(17, 220, 13), // "OpenFileOrUrl"
QT_MOC_LITERAL(18, 234, 6), // "QFile&"
QT_MOC_LITERAL(19, 241, 4), // "file"
QT_MOC_LITERAL(20, 246, 12), // "const TCHAR*"
QT_MOC_LITERAL(21, 259, 5) // "szUrl"

    },
    "MainWindow\0on_pushButton_clicked\0\0"
    "OnAppAbout\0OnFileOpen\0OnToolbarSize\0"
    "id\0OnHelp\0ShowHelp\0OnHelpGnulicense\0"
    "OnHelpReleasenotes\0OnHelpTranslations\0"
    "OnFileOpenProject\0OnOptions\0OnMergingMode\0"
    "on_listWidget_doubleClicked\0index\0"
    "OpenFileOrUrl\0QFile&\0file\0const TCHAR*\0"
    "szUrl"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    1,   87,    2, 0x0a /* Public */,
       7,    0,   90,    2, 0x0a /* Public */,
       8,    0,   91,    2, 0x0a /* Public */,
       9,    0,   92,    2, 0x0a /* Public */,
      10,    0,   93,    2, 0x0a /* Public */,
      11,    0,   94,    2, 0x0a /* Public */,
      12,    0,   95,    2, 0x0a /* Public */,
      13,    0,   96,    2, 0x0a /* Public */,
      14,    0,   97,    2, 0x0a /* Public */,
      15,    1,   98,    2, 0x0a /* Public */,
      17,    2,  101,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   16,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 20,   19,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->OnAppAbout(); break;
        case 2: _t->OnFileOpen(); break;
        case 3: _t->OnToolbarSize((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 4: _t->OnHelp(); break;
        case 5: _t->ShowHelp(); break;
        case 6: _t->OnHelpGnulicense(); break;
        case 7: _t->OnHelpReleasenotes(); break;
        case 8: _t->OnHelpTranslations(); break;
        case 9: _t->OnFileOpenProject(); break;
        case 10: _t->OnOptions(); break;
        case 11: _t->OnMergingMode(); break;
        case 12: _t->on_listWidget_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 13: _t->OpenFileOrUrl((*reinterpret_cast< QFile(*)>(_a[1])),(*reinterpret_cast< const TCHAR*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
