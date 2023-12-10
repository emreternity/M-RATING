#include "Player.h"
#include <string>
using namespace std;

int Player::playerCount = 0;

Player::Player(string _fname, string _lname, int _rating) {
	setFName(_fname);
	setLName(_lname);
	setRating(_rating);
	playerCount++;
}

void Player::setFName(string _fname) {
	fname = _fname;
}

void Player::setLName(string _lname) {
	lname = _lname;
}

void Player::setRating(int _rating) {
	rating = _rating;
}

string Player::getFName() const {
	return fname;
}

string Player::getLname() const {
	return lname;
}

int Player::getRating() const {
	return rating;
}

string Player::getName() const {
	return fname + " " + lname;
}

vector<int> Player::getGameResults() const {
	return gameResults;
}

void Player::newResult(int result) {
	gameResults.push_back(result);
}

int Player::getPlayerCount() {
	return playerCount;
}

void NewRating(Player &p1, Player &p2, int outcome) {
	if (outcome == 0) {
		p1.gameResults.push_back(0);
		p2.gameResults.push_back(0);
	}
	else if (outcome == 1) {
		p1.gameResults.push_back(1);
		p2.gameResults.push_back(2);
		p1.rating += 8;
		p2.rating -= 8;
	}
	else if (outcome == 2) {
		p2.gameResults.push_back(1);
		p1.gameResults.push_back(2);
		p2.rating += 8;
		p1.rating -= 8;
	}
}

