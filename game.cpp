#include "game.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <QDebug>

Game::Game() : score(0),highScore(0) {
    std::srand(std::time(0));
    reset();
}

void Game::reset() {
    board = std::vector<std::vector<int>>(4, std::vector<int>(4, 0));
    score = 0;
    addRandomTile();
    addRandomTile();
}

bool Game::moveLeft() {
    bool moved = slideAndMerge(0, -1);
    if (moved) addRandomTile();
    return moved;
}

bool Game::moveRight() {
    bool moved = slideAndMerge(0, 1);
    if (moved) addRandomTile();
    return moved;
}

bool Game::moveUp() {
    bool moved = slideAndMerge(-1, 0);
    if (moved) addRandomTile();
    return moved;
}

bool Game::moveDown() {
    bool moved = slideAndMerge(1, 0);
    if (moved) addRandomTile();
    return moved;
}

const std::vector<std::vector<int>>& Game::getBoard() const {
    return board;
}

int Game::getScore() const {
    return score;
}

int Game::getHighScore() const
{
    return highScore;
}

void Game::addRandomTile() {
    std::vector<std::pair<int, int>> emptyTiles;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0) {
                emptyTiles.emplace_back(i, j);
            }
        }
    }
    if (!emptyTiles.empty()) {
        auto [x, y] = emptyTiles[std::rand() % emptyTiles.size()];
        board[x][y] = (std::rand() % 10 == 0) ? 4 : 2;
    }
}

bool Game::slideAndMerge(int dx, int dy) {
    bool moved = false;
    qDebug() << "slideAndMerge called with dx:" << dx << "dy:" << dy; // 添加调试信息

    if (dx == 0 && dy == -1) { // Left
        for (int x = 0; x < 4; ++x) {
            int end = 0;
            for (int y = 1; y < 4; ++y) {
                for (int i = y; i > end; --i) {
                    if (board[x][i] && board[x][i] == board[x][i - 1]) {
                        board[x][i - 1] *= 2;
                        board[x][i] = 0;
                        end = i;
                        score += board[x][i - 1];
                        if (score > highScore) highScore = score; // 更新最高分
                        moved = true;
                    } else if (board[x][i] && !board[x][i - 1]) {
                        board[x][i - 1] = board[x][i];
                        board[x][i] = 0;
                        moved = true;
                    }
                }
            }
        }
    } else if (dx == 0 && dy == 1) { // Right
        for (int x = 0; x < 4; ++x) {
            int end = 3;
            for (int y = 2; y >= 0; --y) {
                for (int i = y; i < end; ++i) {
                    if (board[x][i] && board[x][i] == board[x][i + 1]) {
                        board[x][i + 1] *= 2;
                        board[x][i] = 0;
                        end = i;
                        score += board[x][i + 1];
                        if (score > highScore) highScore = score; // 更新最高分
                        moved = true;
                    } else if (board[x][i] && !board[x][i + 1]) {
                        board[x][i + 1] = board[x][i];
                        board[x][i] = 0;
                        moved = true;
                    }
                }
            }
        }
    } else if (dx == -1 && dy == 0) { // Up
        for (int y = 0; y < 4; ++y) {
            int end = 0;
            for (int x = 1; x < 4; ++x) {
                for (int i = x; i > end; --i) {
                    if (board[i][y] && board[i][y] == board[i - 1][y]) {
                        board[i - 1][y] *= 2;
                        board[i][y] = 0;
                        end = i;
                        score += board[i - 1][y];
                        if (score > highScore) highScore = score; // 更新最高分
                        moved = true;
                    } else if (board[i][y] && !board[i - 1][y]) {
                        board[i - 1][y] = board[i][y];
                        board[i][y] = 0;
                        moved = true;
                    }
                }
            }
        }
    } else if (dx == 1 && dy == 0) { // Down
        for (int y = 0; y < 4; ++y) {
            int end = 3;
            for (int x = 2; x >= 0; --x) {
                for (int i = x; i < end; ++i) {
                    if (board[i][y] && board[i][y] == board[i + 1][y]) {
                        board[i + 1][y] *= 2;
                        board[i][y] = 0;
                        end = i;
                        score += board[i + 1][y];
                        if (score > highScore) highScore = score; // 更新最高分
                        moved = true;
                    } else if (board[i][y] && !board[i + 1][y]) {
                        board[i + 1][y] = board[i][y];
                        board[i][y] = 0;
                        moved = true;
                    }
                }
            }
        }
    }

    qDebug() << "slideAndMerge finished, moved:" << moved; // 添加调试信息
    return moved;
}

bool Game::canMove() const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0) return true;
            if (i < 3 && board[i][j] == board[i + 1][j]) return true;
            if (j < 3 && board[i][j] == board[i][j + 1]) return true;
        }
    }
    return false;
}

bool Game::canMoveInDirection(int dx, int dy) const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x = i + dx, y = j + dy;
            if (x >= 0 && x < 4 && y >= 0 && y < 4) {
                if (board[i][j] == 0 || board[i][j] == board[x][y]) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::isGameOver() const {
    return !canMove();
}
