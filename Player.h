#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class Player {

	friend void NewRating(Player &p1, Player &p2, int outcome);

	private:
		static int playerCount;
		string fname;
		string lname;
		int rating;
		vector<int> gameResults;

	public:
		Player(string _fname, string _lname, int _rating = 0);

		void setFName(string _fname);
		void setLName(string _lname);
		void setRating(int _rating);

		string getFName() const;
		string getLname() const;
		int getRating() const;

		string getName() const;
		vector<int> getGameResults() const;
		void newResult(int newResult);
		static int getPlayerCount();
};

#endif // !PLAYER_H
