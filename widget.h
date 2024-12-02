#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    Game game;
    void updateBoard();
    void updateScore();
    void updateHighScore();
};

#endif // WIDGET_H
