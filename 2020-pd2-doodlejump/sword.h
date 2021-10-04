#ifndef SWORD_H
#define SWORD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMediaPlayer>

class sword : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    sword();

public slots:
    void fly();

private:
    QMediaPlayer *SwordSound;
};

#endif // SWORD_H
