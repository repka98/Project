#include "customscence.h"

CustomScence::~CustomScence ()
{

}

void CustomScence::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate (event->scenePos ());
}

CustomScence::CustomScence(QObject *parent)
    : QGraphicsScene(parent)
{

}
