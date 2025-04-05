#include "ScoreManager.hpp"
#include <fstream>
#include <iostream>

ScoreManager* ScoreManager::sharedInstance = nullptr;

ScoreManager* ScoreManager::getInstance() {
    if (sharedInstance == nullptr) {
        sharedInstance = new ScoreManager();
    }
    return sharedInstance;
}

// Constructor: Initialize score and load high score from file
ScoreManager::ScoreManager() : score(0), highScore(10000) {
    loadHighScore();
}

// EXAMPLE: Add 500 points
// ScoreManager::getInstance()->addScore(500);
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
int ScoreManager::getScore() const {
    return this->score;
}

// EXAMPLE: Reset the score when starting a new game
// ScoreManager::getInstance()->resetScore();
void ScoreManager::resetScore() {
    this->score = 0;
}

// EXAMPLE: Get high score
// int highScore = ScoreManager::getInstance()->getHighScore();
int ScoreManager::getHighScore() const {
    return this->highScore;
}

// Save high score to a file
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