#ifndef MYRECT_H
#define MYRECT_H

#include <QPen>
#include <QRect>

class MyRect
{
public:

    MyRect();
    MyRect(QRect rect, QPen pen);
    MyRect(int x, int y, int width, int height, QColor color = Qt::black);
    MyRect(QColor color, Qt::PenStyle style, int penWidth, int x, int y, int width, int height);
    /**
     * @brief прямтоугольник
     * @return
     */
    QRect rect() const;
    /**
     * @brief Цвет пера
     * @return
     */
    QColor color() const;
    /**
     * @brief Установить прямтоугольник
     */
    void setRect(int x, int y, int width, int height);
    /**
     * @brief Установить цвет
     * @param color
     */
    void setColor(QColor color);
    /**
     * @brief Стиль пера
     * @return
     */
    Qt::PenStyle penStyle() const;
    /**
     * @brief Установить стиль пера
     */
    void setStyle(Qt::PenStyle style);
    /**
     * @brief толщина перв
     * @return
     */
    int penWidth() const;
    /**
     * @brief Установить толщину пера
     */
    void setPenWidth(int width);
    /**
     * @brief Установить x
     * @param x
     */
    void setLeft(int x);
    /**
     * @brief Установить y
     * @param y
     */
    void setTop(int y);
    /**
     * @brief Установить ширину
     * @param width
     */
    void setWidth(int width);
    /**
     * @brief Установить высоту
     * @param height
     */
    void setHeight(int height);

private:
    QRect rect_;
    QPen  pen_;
};

#endif // MYRECT_H
