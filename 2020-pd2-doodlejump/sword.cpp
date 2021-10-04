#include "sword.h"

sword::sword()
{
    SwordSound = new QMediaPlayer();
    SwordSound->setMedia(QUrl("qrc:/res/sword_sound.mp3"));
    SwordSound->play();
}

void sword::fly()
{
    setPos(x(), y() - 3);
}
