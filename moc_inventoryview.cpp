/****************************************************************************
** Meta object code from reading C++ file 'inventoryview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "views/inventoryview.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inventoryview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSInventoryViewENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSInventoryViewENDCLASS = QtMocHelpers::stringData(
    "InventoryView",
    "addProduct",
    "",
    "editProduct",
    "deleteProduct",
    "searchProducts",
    "refreshTable",
    "loadCategories"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSInventoryViewENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[14];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[14];
    char stringdata5[15];
    char stringdata6[13];
    char stringdata7[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSInventoryViewENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSInventoryViewENDCLASS_t qt_meta_stringdata_CLASSInventoryViewENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "InventoryView"
        QT_MOC_LITERAL(14, 10),  // "addProduct"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 11),  // "editProduct"
        QT_MOC_LITERAL(38, 13),  // "deleteProduct"
        QT_MOC_LITERAL(52, 14),  // "searchProducts"
        QT_MOC_LITERAL(67, 12),  // "refreshTable"
        QT_MOC_LITERAL(80, 14)   // "loadCategories"
    },
    "InventoryView",
    "addProduct",
    "",
    "editProduct",
    "deleteProduct",
    "searchProducts",
    "refreshTable",
    "loadCategories"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSInventoryViewENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject InventoryView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSInventoryViewENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSInventoryViewENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSInventoryViewENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<InventoryView, std::true_type>,
        // method 'addProduct'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editProduct'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteProduct'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchProducts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refreshTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadCategories'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void InventoryView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InventoryView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addProduct(); break;
        case 1: _t->editProduct(); break;
        case 2: _t->deleteProduct(); break;
        case 3: _t->searchProducts(); break;
        case 4: _t->refreshTable(); break;
        case 5: _t->loadCategories(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *InventoryView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InventoryView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSInventoryViewENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int InventoryView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
