#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <random>
#include <time.h>
using namespace std;

vector<Player> Players;
vector<int> pRatings;
vector<string> matchResults;

void bubbleSort(vector<int> &arr, int n) {
	bool isUnsorted;
	do {
		isUnsorted = false;
		for (int i = 0; i < (n - 1); i++) {
			if (arr[i] > arr[i + 1]) {
				isUnsorted = true;
				for (; i < (n - 1); i++) {
					if (arr[i] > arr[i + 1]) {
						swap(arr[i], arr[i + 1]);
					}
				}
			}
		}
	} while (isUnsorted);
}

void createPlayer() {
	string _fname;
	string _lname;
	int _rating;
	cout << "Oyuncunun ismini girin. (Soy isim olmadan) : ";
	cin >> _fname;
	cout << "Oyuncunun soyismini girin. : ";
	cin >> _lname;
	cout << "Oyuncunun reytingini girin. (Reyting yoksa 0 girin) : ";
	cin >> _rating;

	Players.push_back(Player(_fname, _lname, _rating));
}

void setRatingsList() {

	pRatings.clear();

	int psize = Players.size();

	for (int i = 0; i < psize; i++) {
		pRatings.push_back(Players[i].getRating());
	}
}

void getMatchResults(vector<string> arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i] << " "<<endl;
	cout << endl;
}

void mRatingMatch(vector<Player>& parr, vector<int>& rarr, int size) {

	matchResults.clear();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (parr[j].getRating() == rarr[i]) {
				matchResults.push_back(parr[j].getName() + " - " + to_string(rarr[i]));
				continue;
			}
		}
	}
}

void getPlayerList() {
	for (int i = 0;i < Players.size();i++) {
		cout << "Oyuncu "<< i+1 << " | " << Players[i].getName() << " - " << Players[i].getRating() << endl;
	}
	cout << endl << "Toplam Oyuncu Sayisi: " << Players[0].getPlayerCount()<<endl;
}

void removePlayer() {
	getPlayerList();
	int choice;
	cout << "Silmek Istediginiz Oyuncu: " << endl;
	cin >> choice;
	Players.erase(Players.begin() + choice - 1);
}

int mWayTest() {
	int diff = 10000;
	int chosenOne = 0;
	int size = pRatings.size();
	random_shuffle(pRatings.begin(), pRatings.end());
	for (int j = 0; j < size; j++) {
		int ref = abs(pRatings[0] - pRatings[j]);
		if (ref != 0 && diff > ref) {
			diff = ref;
			chosenOne = pRatings[j];
		}
	}
	return chosenOne;
}

void menu() {
	int choice;

	cout << "M-RATING - \"Lokal Turnuvalara Genel Cozum!\"" << endl << endl;

	cout << "Oyuncu Ekle (1)" << endl;
	cout << "Oyuncu Cikar (2)" << endl;
	cout << "Oyuncu Listesini Goruntule (3)" << endl;
	cout << "Oyunculari Reytinge Gore Sirala (4)" << endl;
	cout << "Oyunculari Eslestir (5)" << endl;
	cout << "Programi Sonlandir (6)" << endl;

	cout << endl << "Secimizini Girin: ";

	cin >> choice;

	if (choice == 1) {
		system("cls");
		createPlayer();
		system("cls");
		menu();
	}
	else if (choice == 2) {
		system("cls");
		removePlayer();
		system("cls");
		menu();
	}
	else if (choice == 3) {
		system("cls");
		getPlayerList();
		system("pause");
		system("cls");
		menu();
	}
	else if (choice == 4) {
		system("cls");
		setRatingsList();
		bubbleSort(pRatings, pRatings.size());
		mRatingMatch(Players, pRatings, Players.size());
		getMatchResults(matchResults, matchResults.size());
		system("pause");
		system("cls");
		menu();

	}
	else if (choice == 5) {
		system("cls");
		setRatingsList();
		if (pRatings.size() % 2 == 1) {
			cout << "Oyuncu sayisi eslestirme icin cift sayi olmalidir." << endl;
			system("pause");
			system("cls");
			menu();
		}
		srand(time(NULL));
		for (int i = 0; i <= pRatings.size();i++) {
				int mRes = mWayTest();
				cout << "Eslesme " << i+1 << endl;
				for (int j = 0; j < Players.size(); j++) {
					if (Players[j].getRating() == mRes) {
						cout << Players[j].getName() << " - " << Players[j].getRating() << endl;
					}
					else if (Players[j].getRating() == pRatings[0]) {
						cout << Players[j].getName() << " - " << Players[j].getRating() << endl;
					}
				}
				cout << endl;
				pRatings.erase(pRatings.begin());
				pRatings.erase(remove(pRatings.begin(), pRatings.end(), mRes), pRatings.end());
		}
		//if (pRatings.size() % 2 == 1) {
		//	determineSubstitute();
		//}
		//else{
		//matchPlayers();
		//}
		system("pause");
		system("cls");
		menu();
	}
}

int main() {


	Player t1("Emre", "Dolas", 2000);
	Player t2("Gizem", "Temelcan", 3000);
	Player t3("Beyza", "Baki", 2850);
	Player t4("Dedi", "Dido", 2900);
	Player t5("Emo", "Delo", 1999);
	Player t6("Emolingo", "Deloli", 3400);

	Players.push_back(t1);
	Players.push_back(t2);
	Players.push_back(t3);
	Players.push_back(t4);
	Players.push_back(t5);
	Players.push_back(t6);
	menu();






}

//createPlayer();
//createPlayer();
//createPlayer();

//setRatingsList();
//bubbleSort(pRatings, pRatings.size());
//getRatingsList(pRatings, pRatings.size());

//mRatingMatch(Players, pRatings, Players.size());
//cout << matchResults[0] << endl;
//cout << matchResults[1] << endl;
//cout << matchResults[2] << endl;