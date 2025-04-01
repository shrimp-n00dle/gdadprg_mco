#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <string>

class ScoreManager {
public:
    static ScoreManager* getInstance();

    void addScore(int points);
    int getScore() const;
    void resetScore();

    int getHighScore() const;
    void saveHighScore() const;
    void loadHighScore();

private:
    ScoreManager() {};
    ScoreManager(ScoreManager const&) {};
    ScoreManager& operator=(ScoreManager const&) {};
    static ScoreManager* sharedInstance;

    int score = 0;
    int highScore = 0;
    const std::string highScoreFile = "highscore.txt"; // File to store the high score
};

#endif