#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>

#include <triangle.h>
#include <customscene.h>
#include <bullet.h>
#include <target.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    CustomScene  *scene;        /// Объявляем графическую сцену
    Triangle *triangle;         /// Объявляем треугольник
    QTimer *timerTarget;        // Таймер для создания мишеней
    static QList<QGraphicsItem *> targets;  // Список мишеней

    static void slotHitTarget(QGraphicsItem *item); // CallBack Функция

private slots:
    void slotBullet(QPointF start, QPointF end); /// Слот для создания пули
    void slotCreateTarget(); // Слот для создания мишеней

};

#endif // WIDGET_H
