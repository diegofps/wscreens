#ifndef BLINK_H
#define BLINK_H

#include <QWidget>

namespace Ui {
class Blink;
}

class Blink : public QWidget
{
    Q_OBJECT

public:
    explicit Blink(QWidget *parent = nullptr);
    ~Blink();

private:
    Ui::Blink *ui;
};

#endif // BLINK_H
