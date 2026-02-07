#include "myrect.h"
//-------------------------------------------------------------------
//
MyRect::MyRect():
    rect_(0, 0, 0, 0),
    pen_(Qt::black)
{
}

//-------------------------------------------------------------------
//
MyRect::MyRect(QRect rect, QPen pen):
    rect_(rect),
    pen_(pen)
{
}

//-------------------------------------------------------------------
//
MyRect::MyRect(int x, int y, int width, int height, QColor color):
    rect_(x, y, width, height),
    pen_(color)
{
}

//-------------------------------------------------------------------
//
MyRect::MyRect(QColor color, Qt::PenStyle style, int penWidth, int x, int y, int width, int height):
      MyRect(x, y, width, height, color)
{
      pen_.setStyle(style);
      pen_.setWidth(penWidth);
}

//-------------------------------------------------------------------
//
QRect MyRect::rect() const
{
    return rect_;
}

//-------------------------------------------------------------------
//
QColor MyRect::color() const
{
    return pen_.color();
}

//-------------------------------------------------------------------
//
void MyRect::setRect(int x, int y, int width, int height)
{
    rect_.setRect(x, y, width, height);
}

//-------------------------------------------------------------------
//
void MyRect::setColor(QColor color)
{
    pen_.setColor(color);
}

//-------------------------------------------------------------------
//
void MyRect::setStyle(Qt::PenStyle style)
{
    pen_.setStyle(style);
}

//-------------------------------------------------------------------
//
void MyRect::setPenWidth(int width)
{
    pen_.setWidth(width);
}

//-------------------------------------------------------------------
//
void MyRect::setLeft(int x)
{
    rect_.moveLeft(x);

}

//-------------------------------------------------------------------
//
void MyRect::setTop(int y)
{
    rect_.moveTop(y);
}

//-------------------------------------------------------------------
//
void MyRect::setWidth(int width)
{
    rect_.setWidth(width);
}

//-------------------------------------------------------------------
//
void MyRect::setHeight(int height)
{
    rect_.setHeight(height);
}

//-------------------------------------------------------------------
//
int MyRect::penWidth() const
{
  return pen_.width();
}

//-------------------------------------------------------------------
//
Qt::PenStyle MyRect::penStyle() const
{
    return pen_.style();
}

//-------------------------------------------------------------------
//
