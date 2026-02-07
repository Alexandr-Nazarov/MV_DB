#include <QComboBox>
#include <QMap>
#include <QEvent>
#include <QMouseEvent>
#include <QColorDialog>
#include <QStyleOptionComboBox>
#include <QApplication>
#include <QDebug>
#include "mydelegate.h"

//-------------------------------------------------------------------
//
MyDelegate::MyDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

//-------------------------------------------------------------------
//
QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return QStyledItemDelegate::createEditor (parent, option, index);

    int column = index.column();

   if(index.isValid() && column == 2)
    {
        QComboBox *cmb = new QComboBox(parent);

        QMap<QString, Qt::PenStyle> styles =
        {{"NoPen", Qt::NoPen}, {"Solid", Qt::SolidLine}, {"Dash", Qt::DashLine}, {"Dot", Qt::DotLine}, {"DashDot", Qt::DashDotLine}};

        for (QMap<QString, Qt::PenStyle>::iterator it = styles.begin(); it != styles.end(); ++it)
        {
            cmb->addItem(it.key(), static_cast<int>(it.value()));
        }

        return cmb;
    }

    return QStyledItemDelegate::createEditor (parent, option, index);
}

//-------------------------------------------------------------------
//
void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
   if (!index.isValid() || index.column() != 2)
        return QStyledItemDelegate::setEditorData (editor, index);

    int column = index.column();

   if(index.isValid() && column == 2)
    {
        QComboBox *combo=static_cast<QComboBox*>(editor);

        //const QAbstractItemModel * currentModel =index. model ();
        //int style=currentModel->data (index, Qt::EditRole). toInt ();

        int style = index.data(Qt::EditRole).toInt();
        int indCombo = combo->findData(style);
        combo->setCurrentIndex(indCombo);
    }
}

//-------------------------------------------------------------------
//
void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!index.isValid() || index.column() != 2)
        return QStyledItemDelegate:: setModelData (editor, model, index);


   if(index.isValid() && index.column() == 2)
    {
        QComboBox *combo=static_cast<QComboBox*>(editor);
        int style = combo->currentData().toInt();
        model->setData(index, style);
    }
}

//-------------------------------------------------------------------
//
bool MyDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
   if (!index.isValid() || index.column() != 1)
        return QStyledItemDelegate::editorEvent (event, model, option, index);

    if (index.isValid() && index.column() == 1 && event->type() == QEvent::MouseButtonDblClick)
    {

        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            QColor tmpColor = QColorDialog::getColor();
            if (tmpColor.isValid())
            {
                model->setData(index, tmpColor);
                return true;
            }
        }
    }
    return QStyledItemDelegate::editorEvent (event, model, option, index);
}

//-------------------------------------------------------------------
//
void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // если обрабатывается колонка со стилем пера
       if (index. column () ==2)
         {
        QStyleOptionComboBox styleOptionCombo;
      //1) получаем из модели (а указатель на модель можно получить из модельного
      //     индекса index) числовое значение стиля пера. Данное из модели
      //     получали в методе setEditorData
         int style = index.data(Qt::EditRole).toInt();;//числовое значение стиля
      //2) получаем строковое значение стиля пера.
         const QStringList styles = {"NoPen", "Solid", "Dash", "Dot", "DashDot"};
        QString text= styles.at(index.data(Qt::EditRole).toInt());//строковое значение стиля

        styleOptionCombo.currentText = text;
        styleOptionCombo.rect = option.rect;
        QApplication::style()->drawComplexControl(QStyle::CC_ComboBox, &styleOptionCombo, painter);
        QApplication::style()->drawItemText (painter, styleOptionCombo.rect, Qt::AlignCenter, QApplication::palette(),
                                            true,styleOptionCombo.currentText);
        }
        else {
            return QStyledItemDelegate::paint (painter, option, index);
        }

}

//-------------------------------------------------------------------
//
