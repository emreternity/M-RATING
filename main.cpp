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
vector<Player> matchedPlayers;

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

vector<Player> preFinalist;

void premadeFinalist(vector<Player>& parr, vector<int>& rarr, int size) {
	int a = pRatings.size();
	for (int j = 0; j < size; j++) {
		if (parr[j].getRating() == rarr[a-1]) {
			cout<<(parr[j].getName() + " - " + to_string(rarr[a-1]))<<endl<<endl;
			preFinalist.push_back(parr[j]);
			continue;
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
	int diffV = 10000;
	int chosenOne = 0;
	int size = pRatings.size();
	int a = 0;
	while (a == 0) {
		random_shuffle(pRatings.begin(), pRatings.end());
		for (int j = 0; j < size; j++) {
			int ref = abs(pRatings[0] - pRatings[j]);
			if (ref != 0 && diff > ref) {
				diff = ref;
				chosenOne = pRatings[j];
			}
		}

		for (int y = 0; y < size; y++) {
			int refV = abs(chosenOne - pRatings[y]);
			if (refV != 0 && diffV > refV) {
				diffV = refV;
			}
		}

		if (diff == diffV) {
			return chosenOne;
			a++;
		}
	}

	
}

void menu() {
	int choice;

	cout << "M-RATING - \"Lokal Turnuvalara Genel Cozum!\"" << endl << endl;

	cout << "Oyuncu Ekle (1)" << endl;
	cout << "Oyuncu Cikar (2)" << endl;
	cout << "Oyuncu Listesini Goruntule (3)" << endl;
	cout << "Oyunculari Reytinge Gore Sirala (4)" << endl;
	cout << "Turnuvaya Basla (5)" << endl;
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
		bubbleSort(pRatings, pRatings.size());
		if (pRatings.size() % 2 == 1) {
			cout << "Oyuncu sayisi tek sayi oldugundan en yuksek reytingli oyuncu finale yukseltildi." << endl<<endl;
			cout << "Belirlenen Finalist: ";
			premadeFinalist(Players, pRatings, Players.size());

			pRatings.pop_back();
			srand(time(NULL));
			for (int i = 0; i <= pRatings.size()+2;i++) {
				int mRes = mWayTest();
				cout << "Eslesme " << i + 1 << endl;
				for (int j = 0; j < Players.size(); j++) {
					if (Players[j].getRating() == mRes) {
						cout << Players[j].getName() << " - " << Players[j].getRating() << endl;
						matchedPlayers.push_back(Players[j]);
					}
					else if (Players[j].getRating() == pRatings[0]) {
						cout << Players[j].getName() << " - " << Players[j].getRating() << endl;
						matchedPlayers.push_back(Players[j]);
					}
				}
				cout << endl;
				pRatings.erase(pRatings.begin());
				pRatings.erase(remove(pRatings.begin(), pRatings.end(), mRes), pRatings.end());
			}


		}
		else {
			srand(time(NULL));
			for (int i = 0; i <= pRatings.size()+2;i++) {
					int mRes = mWayTest();
					cout << "Eslesme " << i+1 << endl;
					for (int j = 0; j < Players.size(); j++) {
						if (Players[j].getRating() == mRes) {
							cout << Players[j].getName() << " - " << Players[j].getRating() << endl;
							matchedPlayers.push_back(Players[j]);
						}
						else if (Players[j].getRating() == pRatings[0]) {
							cout << Players[j].getName() << " - " << Players[j].getRating() << endl;
							matchedPlayers.push_back(Players[j]);
						}
					}
					cout << endl;
					pRatings.erase(pRatings.begin());
					pRatings.erase(remove(pRatings.begin(), pRatings.end(), mRes), pRatings.end());
			}
		}

		//if (pRatings.size() % 2 == 1) {
		//	determineSubstitute();
		//}
		//else{
		//matchPlayers();
		//}
		system("pause");
		system("cls");

		if (matchedPlayers.size() == 2 || matchedPlayers.size() % 4 == 0) {

			int branchCount = 1;

			while (matchedPlayers.size() != 1) {

				int calcSize = matchedPlayers.size() / 2;
				int matchCount = 0;
				for (int x = 1; x <= calcSize; x++) {
					cout << "Seri " << branchCount << " Karsilasma " << x << endl << endl;
					cout << matchedPlayers[x - 1].getName() << " vs. " << matchedPlayers[x].getName() << endl << endl;

					cout << "Eslesme Sonucunu Giriniz (1 = " << matchedPlayers[x - 1].getName() << "  Galip | 2 = " << matchedPlayers[x].getName() << " Galip): ";
					int gameResult;
					cin >> gameResult;
					cout << endl;
					NewRating(matchedPlayers[x - 1], matchedPlayers[x], gameResult);
					if (gameResult == 1) {
						cout << matchedPlayers[x].getName() << " turnuvadan elendi." << endl;
						cout << "Son Reytingi: " << matchedPlayers[x].getRating() << endl;
						matchedPlayers.erase(matchedPlayers.begin() + x);
					}
					else if (gameResult == 2) {
						cout << matchedPlayers[x - 1].getName() << " turnuvadan elendi." << endl;
						cout << "Son Reytingi: " << matchedPlayers[x - 1].getRating() << endl;
						matchedPlayers.erase(matchedPlayers.begin() + (x - 1));
					}
					matchCount++;
					system("pause");
					system("cls");
				}
				calcSize - (matchCount / 2);
				branchCount++;
			}

			if (preFinalist.size() > 0) {
				cout << "Final Karsilasmasi " << endl << endl;
				cout << matchedPlayers[0].getName() << " vs. " << preFinalist[0].getName() << endl << endl;
				cout << "Eslesme Sonucunu Giriniz (1 = " << matchedPlayers[0].getName() << "  Galip | 2 = " << preFinalist[0].getName() << " Galip): ";
				int gameResult;
				cin >> gameResult;
				cout << endl;
				NewRating(matchedPlayers[0], preFinalist[0], gameResult);
				system("cls");
				if (gameResult == 1) {
					cout << preFinalist[0].getName() << " turnuvadan elendi." << endl;
					cout << "Son Reytingi: " << preFinalist[0].getRating() << endl << endl;
					cout << "Turnuvanin kazanani: " << matchedPlayers[0].getName() << endl;
					cout << "Yeni Reytingi: " << matchedPlayers[0].getRating() << endl << endl;
					system("pause");
					system("cls");
					matchedPlayers.clear();
					preFinalist.clear();
				}
				else if (gameResult == 2) {
					cout << matchedPlayers[0].getName() << " turnuvadan elendi." << endl;
					cout << "Son Reytingi: " << matchedPlayers[0].getRating() << endl << endl;
					cout << "Turnuvanin kazanani: " << preFinalist[0].getName() << endl;
					cout << "Yeni Reytingi: " << preFinalist[0].getRating() << endl << endl;
					system("pause");
					system("cls");
					matchedPlayers.clear();
					preFinalist.clear();
				}
			}
			else {
				cout << "Turnuvanin kazanani: " << matchedPlayers[0].getName() << endl;
				cout << "Yeni Reytingi: " << matchedPlayers[0].getRating() << endl << endl;
				system("pause");
				system("cls");
				matchedPlayers.clear();
				preFinalist.clear();
			}
		}
		else {
			cout << "Oyuncu sayisi oyunlarin oynanmasi icin uygun degil." << endl << endl;
			system("pause");
			system("cls");
			matchedPlayers.clear();
			preFinalist.clear();
		}

		menu();
	}
}

int main() {

	Player t1("Emre", "Dolas", 2000);
	Player t2("Gizem", "Temelcan", 3000);
	Player t3("Beyza", "Baki", 2850);
	Player t4("Melodi", "Vezir", 2900);
	Player t5("Busra", "Sah", 1999);
	Player t6("Metin", "Piyon", 3400);
	Player t7("Marcus", "Carlsen", 3800);
	Player t8("Denmar", "Dansen", 1000);
	Player t9("Peter", "Griffin", 1100);

	Players.push_back(t1);
	Players.push_back(t2);
	Players.push_back(t3);
	Players.push_back(t4);
	Players.push_back(t5);
	Players.push_back(t6);
	Players.push_back(t7);
	Players.push_back(t8);
	Players.push_back(t9);
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