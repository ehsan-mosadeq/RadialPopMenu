#pragma once

#include <QToolButton>

class CircleToolButton : public QToolButton
{
public:
    using QToolButton::QToolButton;
    // 设置绘制的不透明度
    void setOpacity(qreal opacity);
protected:
    // 点击区域，因为窗口是矩形，限定圆形范围
    bool hitButton(const QPoint &pos) const;
    void paintEvent(QPaintEvent *);
    bool event(QEvent *e);
    // 坐标是否在圆形范围内
    bool posInCircle(const QPoint &pos) const;

private:
    qreal paintOpacaty = 1.0;
};
