#ifndef CUSTOMSCENCE_H
#define CUSTOMSCENCE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>

class CustomScence : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScence(QObject *parent = 0);
    ~CustomScence();

signals:
    void signalTargetCoordinate(QPointF point);

public slots:

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENCE_H
