#ifndef GAME_H
#define GAME_H

#include <vector>

class Game {
public:
    Game();
    void reset();
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    const std::vector<std::vector<int>>& getBoard() const;
    int getScore() const;
    int getHighScore() const;
    bool isGameOver() const; // 添加游戏结束判断方法

private:
    std::vector<std::vector<int>> board;
    int score;
    int highScore;
    void addRandomTile();
    bool canMove() const;
    bool canMoveInDirection(int dx, int dy) const;
    bool slideAndMerge(int dx, int dy);
};

#endif // GAME_H
