#include "ScoreManager.hpp"
#include <fstream>
#include <iostream>

ScoreManager* ScoreManager::sharedInstance = nullptr;

/**
 * Returns the singleton instance of ScoreManager, creating it if it doesn't exist
 * @return Pointer to the ScoreManager instance
 */
ScoreManager* ScoreManager::getInstance() {
    if (sharedInstance == nullptr) {
        sharedInstance = new ScoreManager();
    }
    return sharedInstance;
}

/**
 * Constructor for ScoreManager
 * Initializes score to 0, high score to 10000, and bonus score to 5000
 * Loads the high score from file
 */
ScoreManager::ScoreManager() : score(0), highScore(10000), bonusScore(5000) {
    loadHighScore();
}

// EXAMPLE: Add 500 points
// ScoreManager::getInstance()->addScore(500);
/**
 * Adds points to the current score
 * Automatically updates and saves high score if current score exceeds it
 * @param points Number of points to add
 */
void ScoreManager::addScore(int points) {
    this->score += points;

    // Automatic high score saving woohoo--
    if (this->score > this->highScore) {
        this->highScore = this->score;
        saveHighScore();
    }
}

// EXAMPLE: Get current score
// int currentScore = ScoreManager::getInstance()->getScore();
/**
 * Gets the current score
 * @return Current score value
 */
int ScoreManager::getScore() const {
    return this->score;
}

// EXAMPLE: Reset the score when starting a new game
// ScoreManager::getInstance()->resetScore();
/**
 * Resets the current score to 0
 */
void ScoreManager::resetScore() {
    this->score = 0;
}

// Reset bonus score when starting a new game
/**
 * Resets the bonus score to its initial value of 5000
 */
void ScoreManager::resetBonusScore() {
    this->bonusScore = 5000; // Reset to initial bonus value
}

// EXAMPLE: Get high score
// int highScore = ScoreManager::getInstance()->getHighScore();
/**
 * Gets the current high score
 * @return High score value
 */
int ScoreManager::getHighScore() const {
    return this->highScore;
}

// Save high score to a file
/**
 * Saves the current high score to a file
 */
void ScoreManager::saveHighScore() const {
    std::ofstream outFile(highScoreFile);
    if (outFile.is_open()) {
        outFile << this->highScore;
        outFile.close();
    }
    else {
        std::cerr << "Error: Could not save high score!\n";
    }
}

// Load high score from a file
/**
 * Loads the high score from a file
 * If no file exists, sets high score to 0
 */
void ScoreManager::loadHighScore() {
    std::ifstream inFile(highScoreFile);
    if (inFile.is_open()) {
        inFile >> this->highScore;
        inFile.close();
    }
    else {
        std::cerr << "No previous high score found, starting fresh.\n";
        this->highScore = 0;
    }
}

/**
 * Saves a new bonus score value
 * @param bonusScore New bonus score value to save
 */
void ScoreManager::saveBonusScore(int bonusScore)
{
    this->bonusScore = bonusScore;
}

/**
 * Gets the current bonus score
 * @return Current bonus score value
 */
int ScoreManager::getBonusScore()
{
    return this->bonusScore;
}
