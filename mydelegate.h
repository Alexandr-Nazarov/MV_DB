#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class MyDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MyDelegate(QObject *parent = nullptr);
    /**
     * @brief Создание специфического редактора для элемента таблицы
     * @param parent
     * @param option
     * @param index
     * @return
     */
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    /**
     * @brief Получение текущего данного из таблицы
     * @param editor
     * @param index
     */
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    /**
     * @brief Запись модифицированного значения обратно в модель
     * @param editor
     * @param model
     * @param index
     */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    /**
     * @brief Обработка пользовательских событий
     * @param event
     * @param model
     * @param option
     * @param index
     * @return
     */
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    /**
     * @brief Отрисовка делегата
     * @param painter
     * @param option
     * @param index
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

};

#endif // MYDELEGATE_H
