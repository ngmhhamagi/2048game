#include "widget.h"
#include "./ui_widget.h"
#include <QKeyEvent>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton->setCursor(Qt::PointingHandCursor);
    ui->textBrowser->setFocusPolicy(Qt::NoFocus); // 禁用 textBrowser 的焦点
    setFocusPolicy(Qt::StrongFocus); // 确保 Widget 能够接收键盘焦点
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::on_pushButton_clicked);
    updateBoard();
    updateScore();
    updateHighScore();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    bool moved = false;
    qDebug() << "Key pressed:" << event->key(); // 添加调试信息
    switch (event->key()) {
    case Qt::Key_Left:
        moved = game.moveLeft();
        break;
    case Qt::Key_Right:
        moved = game.moveRight();
        break;
    case Qt::Key_Up:
        moved = game.moveUp();
        break;
    case Qt::Key_Down:
        moved = game.moveDown();
        break;
    default:
        QWidget::keyPressEvent(event);
        return;
    }

    qDebug() << "Moved:" << moved; // 添加调试信息
    if (moved) {
        updateBoard();
        updateScore();
        updateHighScore(); // 添加这行
        if (game.isGameOver()) {
            QMessageBox::information(this, "Game Over", "游戏结束! 你的分数是: " + QString::number(game.getScore()));
        }
    }
}

void Widget::on_pushButton_clicked()
{
    game.reset();
    updateBoard();
    updateScore();
    updateHighScore();
}

void Widget::updateBoard()
{
    const auto &board = game.getBoard();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            QLabel *label = findChild<QLabel *>(QString("label_%1_%2").arg(i).arg(j));
            if (label) {
                int value = board[i][j];
                label->setText(value == 0 ? "" : QString::number(value));
                label->setStyleSheet(value == 0 ? "background-color: #CDC1B4;" : "background-color: #EEE4DA; font-size: 24px; font-weight: bold; color: #776E65;");
            }
        }
    }
}

void Widget::updateScore()
{
    // 更新分数显示
    QLabel *scoreLabel = findChild<QLabel *>("label_4");
    if (scoreLabel) {
        scoreLabel->setText(QString::number(game.getScore()));
    }
}

void Widget::updateHighScore()
{
    QLabel *highScoreLabel = findChild<QLabel *>("label_5");
    if (highScoreLabel) {
        highScoreLabel->setText(QString::number(game.getHighScore()));
    }
}
