#ifndef ANIM_H
#define ANIM_H

#include <QThread>

class Anim : public QThread
{
    Q_OBJECT
    const double ms;
    const uint steps;

public:
    Anim(const double ms, const uint steps) : ms(ms), steps(steps) { }

    void run() override
    {
        if (steps == 0)
            return;

        else if (steps == 1)
            emit update(1.0);

        else
        {
            for (uint i=0;i!=steps;++i)
            {
                const double v = i / double(steps - 1);
//                QMetaObject::invokeMethod(listener, "gui_update", Qt::QueuedConnection);

                emit update(v);

                auto delay = ms / steps;
                msleep(delay);
            }
        }
    }

signals:
    void update(const double value);
};

#endif // ANIM_H
