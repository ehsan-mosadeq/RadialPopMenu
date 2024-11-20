#pragma once
#include "CircleToolButton.h"

#include <QWidget>
#include <QToolButton>
#include <QTimeLine>
#include <QApplication>
#include <QMouseEvent>

// 跟菜单，处理拖拽移动窗口
class RadialMenuRoot : public CircleToolButton
{
public:
    using CircleToolButton::CircleToolButton;

    // 是否移动menu的顶层窗口，方便拖拽
    void setMoveTopWindow(bool top){
        moveTop = top;
    }
protected:
    bool event(QEvent *e)
    {
        switch (e->type()) {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonDblClick:
        {
            QMouseEvent * me = static_cast<QMouseEvent *>(e);
            if(me->button() == Qt::LeftButton)
            {
                oldMousePos = me->globalPos();
                mousePressed = true;
            }
        }
            break;
        case QEvent::MouseMove:
            if(mousePressed)
            {
                QMouseEvent * me = static_cast<QMouseEvent *>(e);
                QPoint delta = QPoint(me->globalPos() - oldMousePos);
                // 触发拖拽距离判定
                if(!startDrag)
                    startDrag = std::max(std::abs(delta.x()), std::abs(delta.y())) >= QApplication::startDragDistance();
                if(startDrag)
                {
                    QWidget * w = moveTop ? this->window() : this;
                    w->move(w->pos() + delta);
                    oldMousePos = me->globalPos();
                }
            }
            break;
        case QEvent::MouseButtonRelease:
        {
            if(static_cast<QMouseEvent *>(e)->button() == Qt::LeftButton)
                startDrag = mousePressed = false;
        }
            break;

        default:
            break;
        }
        return CircleToolButton::event(e);
    }
    bool hitButton(const QPoint &pos) const
    {
        // 如果处于拖拽中，这不处理按下逻辑
        // 这种处理方式可能有问题
        if(startDrag)
            return false;
        return CircleToolButton::hitButton(pos);
    }
private:
    QPoint oldMousePos;
    bool mousePressed = false;
    bool moveTop = true;
    bool startDrag = false;
};
