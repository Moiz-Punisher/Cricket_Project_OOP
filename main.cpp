#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <algorithm>


using namespace std;
//Engine
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
ifstream rdr("Teams.txt");
string tempS;
int tempInt;
int Namecounter = 0;
int PlayerCounter = 0;
int PlIndex1 = 0;
int PlIndex2 = 0;
int BallIndex = 0;
int rdrCounter = 0;
bool st = 0;
bool overChk=false;
int batOverChck = 0;
int ballOverChck = 0;
float batRepeatChck[11];
bool Wide = false;
bool WideDisplay = false;
bool real_wala_wide = false;
bool noBall = false;
bool secondHalf = false;
bool autoplay = false;
bool OtherSide = false;
static int t_1 = 0, t_2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;
bool Auto = false;
bool autoCommentry = false;
//Classes
class Teams {
	string name;
	int players;

public:
	string* pNames;
	Teams() {
		name = '\0';

		pNames = NULL;
	}
	void setName();
	string getName();
	void setPlayers(int);
	int getPlayers();
	void Array();
	string* Names();
};
class Match :public Teams {
	int overs;
	int tOvers;
	int balls;
	int total;
	int wickets;
	string batTeam, ballTeam;
	string bat1, bat2;
	string baller;
	int run;
	int target;
	int bCommentry = 0;
	string ArrayComm[15];
public:
	bool secondInnings = false;
	Teams bat, ball;
	int bi;

	Match() {
		overs = 0;
		tOvers = 0;
		balls = 0;
		run = 0;
		total = 0;
		wickets = 0;
	}
	void setcommentary();
	void getCommentary();
	int getTarget();
	void setTarget(int);
	void settOvers(int);
	int gettOvers();
	int getOvers();
	int getBalls();
	void Over();
	void Ball();
	void setBat1() {
		bat1 = "\0";
	}
	void setBatBall(Teams&, Teams&);
	string getBat1();
	string getBat2();
	string getBaller();
	void setBat(Teams&);
	void setBall(Teams&);
	void setRun();
	int getRun();
	int ballType();
	int getTotal();
	int getWickets();
	int batType();
	void setTotal(int);
	void setWickets();
	void setOut();
	void Reset();
	void reduceBalls();
	void reduceWickets();
};
class Score :public Match {
	int* scoreIndiv = NULL;
	float* batterOvers = NULL;
	float* ballerOvers = NULL;
	int cBat = 0;
	int cBall = 0;
	int* Baller_wickets = NULL;
public:
	Score() {}
	Score(int players) {
		scoreIndiv = new int[players];
		batterOvers = new float[players];
		ballerOvers = new float[players];
		Baller_wickets = new int[players];
		for (int i = 0; i < players; i++) {
			scoreIndiv[i] = 0;
			batterOvers[i] = 0;
			ballerOvers[i] = 0;
			Baller_wickets[i] = 0;
		}
	}
	void updateScore(int, Match&, int,  Teams&, Teams&,Score&);
	void setcBat(int);
	void setcBall(int);
	int getcBat();
	int getcBall();
	float getIndivOver(int);
	int getIndivScore(int);
	float getIndivBallerOver(int);
	void setNegIndivOver(int, int);
	void Reset(int);
	void setBallerWickets(int);
	int getBallerWickets(int);
	void resetcBat();
	void setBallerWickets(int, int);
};
class SupportStaffAndOthers {
	string* Commentators=NULL;
	string* Umpires=NULL;
	string* Stadium = NULL;
public:
	SupportStaffAndOthers() {
		Commentators = new string[5];
		Umpires = new string[5];
		Stadium = new string[5];
		for (int i = 0; i < 5; i++) {
			Commentators[i] = "\0";
			Umpires[i] = "\0";
			Stadium[i] = "\0";
		}
	}
	void selectRandoms();
	void getSupportStaffAndOthers();
};
//Class Functions definitions
void Match::getCommentary() {
	srand(time(0));
	int index = 0;
	int lowerLimit = 0;
	int upperLimit = 0;

	
	 if (bCommentry == 1) {
		 index = rand() % 3;
		 cout << CYAN << ArrayComm[index] << RESET;
	}
	else if (bCommentry == 2) {
		lowerLimit = 3;
		upperLimit = 5;
		index = (rand() % (upperLimit - lowerLimit + 1)) + lowerLimit;
		cout << CYAN << ArrayComm[index] << RESET;
	}
	else if (bCommentry == 4) {
		lowerLimit = 6;
		upperLimit = 8;
		index = (rand() % (upperLimit - lowerLimit + 1)) + lowerLimit;
		cout << CYAN << ArrayComm[index] << RESET;
	}
	else if (bCommentry == 6) {
		 lowerLimit = 9;
		 upperLimit = 11;
		 index = (rand() % (upperLimit - lowerLimit + 1)) + lowerLimit;
		 cout << CYAN << ArrayComm[index] << RESET;
	}
	else if (bCommentry == 0) {
		 lowerLimit = 12;
		 upperLimit = 14;
		 index = (rand() % (upperLimit - lowerLimit + 1)) + lowerLimit;
		 cout << CYAN << ArrayComm[index] << RESET;
	 }
}
void Match::setcommentary() {
	string comm[15] = {"And that's a quick single taken by the batsmen, great running between the wickets.","A well-placed shot earns them a single, keeping the scoreboard ticking.","The fielder had to cover a lot of ground, but the batsmen managed to complete the single.",
						"They've hit it into the gap and running hard, it's a comfortable two for the batsmen.","Excellent placement, they're turning one into two, putting pressure on the fielding side.","The outfield is lightning quick today, allowing them to come back for the second run easily.",
						"That's a cracking shot! The ball races to the boundary for a beautiful four.","The fielders had no chance to cut that off, it's a boundary to the batsman.","The timing and placement on that shot were exquisite, finding the gap and reaching the fence.",
						"Oh, that's gone all the way! It's a massive six into the crowd.","He's launched that into orbit! A magnificent maximum from the batsman.","The ball disappeared out of the ground, sailing into the stands. A tremendous six.",
						"A dot ball, good bowling by the bowler, building up the pressure.","The batsman couldn't find the gap, a dot ball adds to the pressure on the batting side.","That's a good delivery, right on target, and the batsman can only defend it back to the bowler."};
	for (int i = 0; i < 15; i++) {
		ArrayComm[i] = comm[i];
		}
}
void SupportStaffAndOthers::getSupportStaffAndOthers() {
	cout << CYAN << "Commentators: " << YELLOW;
	for (int i = 0; i < 3; i++) {
		if (i == 3 - 1) {
			cout<<YELLOW << Commentators[i] << RESET << endl;
		}
		else
		cout <<YELLOW<< Commentators[i] << RESET"  AND  ";
	}
	cout << CYAN << "Umpires: " << YELLOW;
	for (int i = 0; i < 2; i++) {
		if (i == 2 - 1) {
			cout <<YELLOW<< Umpires[i] << RESET << endl;
		}
		else
			cout <<YELLOW<< Umpires[i] <<RESET<< "  AND  ";
	}
	cout << CYAN << "Stadium: " << GREEN;
	cout << Stadium[0] << RESET << endl;
}
void SupportStaffAndOthers::selectRandoms() {
	
	int temp1, temp2, temp3, j = 0;
	srand(time(0));
	temp1 = rand() % 3;
	temp2 = rand() % 2;
	temp3 = rand() % 5;
	ifstream readFromStaff("SupportStaffAndOthers.txt");
	readFromStaff >> tempS;
	for (int i = 0; i < 5; i++) {

		if (i == temp1) {
			readFromStaff >> Commentators[j]; j++;
			readFromStaff >> Commentators[j]; j++;
			readFromStaff >> Commentators[j];
			i += 2;
		}
		else {
			readFromStaff >> tempS;
		}
	}
	readFromStaff >> tempS;
	j = 0;
	for (int i = 0; i < 5; i++) {
		if (i == temp2) {
			readFromStaff >> Umpires[j]; j++;
			readFromStaff >> Umpires[j]; j++;
			i += 1;
		}
		else {
			readFromStaff >> tempS;
		}
	}
	readFromStaff >> tempS;
	j = 0;
	for (int i = 0; i < 5; i++) {
		if (i == temp3) {
			readFromStaff >> Stadium[j];
		}
		else {
			readFromStaff >> tempS;
		}
	}
}
void Match::setTarget(int t) {
	target = t;
}
int Match::getTarget() {
	return target;
}
void Score::resetcBat() {
	setcBat(0);
}
void Match::reduceWickets() {
	wickets--;
}
void Match::reduceBalls() {
	balls--;
}
int Score::getBallerWickets(int index) {
	return Baller_wickets[index];
}
void Score::setBallerWickets(int index) {
	Baller_wickets[index]++;
}
void Score::setBallerWickets(int ballerIndex, int wickets) {
	// Assuming you have an array or vector to store the baller wickets count
	Baller_wickets[ballerIndex] = wickets;
}
float Score::getIndivBallerOver(int index) {
	return ballerOvers[index];
}
void Score::Reset(int players) {
	cBat = 0;
	cBall = 0;
	for (int i = 0; i < players; i++) {
		scoreIndiv[i] = 0;
		batterOvers[i] = 0;
		ballerOvers[i] = 0;
		batRepeatChck[i] = 0;
	}
}
void Match::Reset() {
	overs = 0;
	balls = 1;
	run = 0;
	total = 0;
	wickets = 0;
	bi = 0;
	batTeam = ballTeam = bat1 = bat2 = baller = "\0";
}
void Score::setNegIndivOver(int index, int players) {
	if (batterOvers[index] == 0) {
		batRepeatChck[index] = -99;
	}
	if (batterOvers[index] > 0) {
		batRepeatChck[index] = batterOvers[index] * -10;
	}
	for (int i = 0; i < players; i++) {

		if (i == index) {
			continue;
		}
		batRepeatChck[i] = batterOvers[i];
	}
	cout << endl;
}
float Score::getIndivOver(int index) {
	if (batterOvers[index] < 0.0) {
		return 0.0;
	}
	else
		return batterOvers[index];
}
int Score::getIndivScore(int index) {
	return scoreIndiv[index];
}
int Score::getcBat() {
	return cBat;
}
int Score::getcBall() {
	return cBall;
}
void Score::setcBall(int ball) {
	cBall = ball;
}
void Score::setcBat(int bat) {
	cBat = bat;
}
void Score::updateScore(int plr_index,Match &obj ,int score, Teams& t1, Teams& t2,Score&scr) {
	if (WideDisplay != true)
		scoreIndiv[plr_index] += score;


	if (batOverChck != 0 && WideDisplay == false && noBall == false&&overChk!=true) {
		batterOvers[plr_index] += 0.1;
	}
	if (ballOverChck != 0 && WideDisplay == false && noBall == false) {
		ballerOvers[BallIndex] += 0.1;
	}
	ballOverChck = 1;
	batOverChck = 1;
	int B_overs = batterOvers[plr_index] * 10;
	B_overs = B_overs % 10;
	if (B_overs == 6) {
		batterOvers[plr_index]++;
		batterOvers[plr_index] -= static_cast<float>(B_overs) / 10.0;
	}
	int Ball_overs = ballerOvers[BallIndex] * 10;
	Ball_overs = Ball_overs % 10;
	if (Ball_overs == 6) {
		ballerOvers[BallIndex]++;
		ballerOvers[BallIndex] -= static_cast<float>(Ball_overs) / 10.0;
	}
	if (OtherSide == false) {
		ofstream writer("1stInnings.txt");
		writer << "Individual Score of Batsmen:" << endl;
		for (int i = 0; i < t1.getPlayers(); i++) {
			writer << scoreIndiv[i] << "  ";
		}
		writer << endl << "In Overs:" << endl;
		for (int i = 0; i < t1.getPlayers(); i++) {
			writer << batterOvers[i] << "  ";
		}
		writer << endl << "Individual Ballers Performance: " << endl;
		for (int i = 0; i < t1.getPlayers(); i++) {

			writer << ballerOvers[i] << "  ";
		}
		writer << endl << "And Taken Wickets: " << endl;
		for (int i = 0; i < t1.getPlayers(); i++) {
			if (i == t1.getPlayers() - 1) {
				writer << ballerOvers[i] << endl;
			}
			else {
				writer << Baller_wickets[i] << "  ";
			}
		}
	}
	else {
		ofstream writer2("2ndInnings.txt");
		writer2 << "Individual Score of Batsmen:" << endl;
		for (int i = 0; i < t1.getPlayers(); i++) {
			writer2 << scoreIndiv[i] << "  ";
		}
		writer2 << endl << "In Overs:" << endl;
		for (int i = 0; i < t1.getPlayers(); i++) {
			writer2 << batterOvers[i] << "  ";
		}
		writer2 << endl << "Individual Ballers Performance: " << endl;
		for (int i = 0; i < t1.getPlayers(); i++) {

			writer2 << ballerOvers[i] << "  ";
		}
		writer2 << endl << "And Taken Wickets: " << endl;
		for (int i = 0; i < t1.getPlayers(); i++) {
			if (i == t1.getPlayers() - 1) {
				writer2 << ballerOvers[i] << endl;
			}
			else {
				writer2 << Baller_wickets[i] << "  ";
			}
		}
	}
}
void Match::setOut() {
	system("cls");
	cout << RED << "OUT!!!" << RESET << endl;
	if (bi == 1) {
		bat1 = "\0";

	}
	else {
		bat2 = "\0";
	}
}
int Match::gettOvers() {
	return tOvers;
}
void Match::setWickets() {
	wickets++;
}
void Match::setTotal(int score) {
	total = score;
}
int Match::batType() {
	cout << "What is the player going to do\nPress 1 for single\nPress 2 for double\nPress 3 for four\nPress 4 for six\nPress 5 for dot Ball ";
	cin >> tempInt;
	while (tempInt <= 0 || tempInt >= 6) {
		cout << "Select correct option ";
		cin >> tempInt;
	}
	switch (tempInt) {
	case 1:
		bCommentry = 1;
		return 1;
		break;
	case 2:
		bCommentry = 2;
		return 2;
		break;
	case 3:
		bCommentry = 4;
		return 4;
		break;
	case 4:
		bCommentry = 6;
		return 6;
		break;
	case 5:
		bCommentry = 0;
		return 0;
		break;
	}
}
int Match::getWickets() {
	return wickets;
}
int Match::getTotal() {
	return total;
}
int Match::getRun() {
	return run;
}
void Match::setRun() {
	run++;
}
int Match::ballType() {
	cout << "How is the player going to ball\nPress 1 for Ball on line\nPress 2 for wide Ball\nPress 3 for no Ball\nPress 4 for wicket\nPress 5 for Catch out/Run out ";
	cin >> tempInt;
	switch (tempInt) {
	case 1:

		return 1;
		break;
	case 2:
		Wide = true;
		return 2;
		break;
	case 3:
		noBall = true;
		return 3;
		break;
	case 4:
		wickets++;

		return 4;
		break;
	case 5:
		wickets++;

		return 5;
		break;
	default:
		cout << "Select correct option: ";
		cin >> tempInt;
	}
}
void Match::setBall(Teams& obj) {
	cout << "Enter the exact name of baller ";
ball:
	cin >> tempS;
	bool chk = 0;
	for (int i = 0; i < obj.getPlayers(); i++) {
		if (tempS == obj.pNames[i]) {
			chk = 1;
			baller = obj.pNames[i];
			BallIndex = i;
			break;
		}
	}
	if (chk == 0) {
		cout << "Write correct name ";
		goto ball;
	}
	ballOverChck = 0;
}
void Match::setBat(Teams& obj) {
	if (st == 0) {
		cout << "Enter the exact name of the batsmen 1 who is going to open the innings ";
	b1:
		cin >> tempS;
		bool chk = 0;

		for (int i = 0; i < obj.getPlayers(); i++) {
			if (tempS == obj.pNames[i]) {
				chk = 1;
				bat1 = obj.pNames[i];
				PlIndex1 = i;
				break;
			}
		}
		if (chk == 0) {
			cout << "Write correct name ";
			goto b1;
		}
		chk = 0;
		cout << "Now the 2nd batsmen ";
	b2:
		cin >> tempS;
		for (int i = 0; i < obj.getPlayers(); i++) {
			if (tempS == obj.pNames[i]) {
				PlIndex2 = i;
				if (PlIndex2 != PlIndex1) {
					chk = 1;
					bat2 = obj.pNames[i];

					break;
				}
				else {
					cout << "Batsman already on strike ";
				}

			}
		}
		if (chk == 0) {
			cout << "Write correct name ";
			goto b2;
		}
		st = 1;
	}
	else {
		bool affan = 0;
		cout << "Enter the exact name of batsmen ";
	affan:
		cin >> tempS;
		for (int i = 0; i < obj.getPlayers(); i++) {
			if (tempS == obj.pNames[i]) {

				if (bat1 == "\0") {
					PlIndex1 = i;
					if (PlIndex1 != PlIndex2) {
						if (batRepeatChck[PlIndex1] >= 0) {
							affan = 1;
							bat1 = tempS;
						}
						else {
							cout << "Batsman out hogya vero sed loife ;-; ";
						}
					}
					else {
						cout << "Batsman already on strike ";
					}


				}
				else {
					PlIndex2 = i;
					if (PlIndex2 != PlIndex1) {
						if (batRepeatChck[PlIndex2] >= 0) {
							affan = 1;
							bat2 = tempS;
						}
						else {
							cout << "Batsman out hogya vero sed loife ;-; ";
						}
					}
					else {
						cout << "Batsman already on strike ";
					}
				}
				break;
			}
		}
		if (affan == 0) {
			cout << "Write correct name ";
			goto affan;
		}
	}
	batOverChck = 0;
}
string Match::getBat1() {
	return bat1;
}
string Match::getBat2() {
	return bat2;
}
string Match::getBaller() {
	return baller;
}
void Match::setBatBall(Teams& obj1, Teams& obj2) {
	bat = obj1;
	ball = obj2;
	batTeam = bat.getName();
	ballTeam = ball.getName();
}
void Match::settOvers(int overs) {
	tOvers = overs;
}
int Match::getOvers() {
	return overs;
}
int Match::getBalls() {
	return balls;
}
void Match::Over() {
	if (balls % 6 == 0) {
		balls = 0;
		overs++;
	}
}
void Match::Ball() {
	if (WideDisplay != true)
		balls++;
	else {
		balls--;
	}
}
string* Teams::Names() {
	return pNames;
}
void Teams::setName() {

	string name;

	rdr >> name;
	if (name[0] == '\0' || name[0] < 65) {
		cout << "Enter the name of the team: ";
		cin >> name;
	}

	this->name = name;
}
string Teams::getName() {
	return this->name;
}
void Teams::setPlayers(int players = 0) {

	if (Namecounter == 0)
		rdr >> players;
	if (players == 0) {
		cout << "Enter the number of players of both teams ";
		cin >> players;
	}
	this->players = players;
	Namecounter++;
}
int Teams::getPlayers() {
	return this->players;
}
void Teams::Array() {
	pNames = new string[getPlayers()];
	//rdr >> tempS;
	if (rdrCounter == 0)
		rdr >> tempS;
	for (int i = 0; i < getPlayers(); i++) {
		if (PlayerCounter == 0) {
			rdr >> pNames[i];
		}

		if (pNames[i] == "Team" || pNames[i] == ".") {
			PlayerCounter = 1;
			rdrCounter = 1;
		}
		if (PlayerCounter == 1) {
			cout <<RED<< "A Player is missing from file"<<RESET<<endl;
			cout << "Name " << i + 1 << ": ";
			cin >> pNames[i];
		}
		if (pNames[i] == "\0") {
			cout << RED << "A Player is missing from file" << RESET << endl;
			cout << "Name " << i + 1 << ": ";
			cin >> pNames[i];
		}
	}

	PlayerCounter = 0;

}
//Others
void Initialize(Teams& t1, Teams& t2) {


	t1.setName();

	t2.setName();

	t1.setPlayers();

	t2.setPlayers(t1.getPlayers());

	t1.Array();
	t2.Array();
}
void Initdisplay(Teams& t1, Teams& t2) {
	string* pNames1, * pNames2;

	cout << BLUE << "------------------------------------------------------------------" << RESET << endl;
	cout << MAGENTA << t1.getName() << "\t\t\t\t\t\t" << t2.getName() << RESET << endl << endl;
	cout << BLUE << "------------------------------------------------------------------" << RESET << endl;

	pNames1 = t1.Names();
	pNames2 = t2.Names();
	for (int i = 0; i < t1.getPlayers(); i++) {
		if (i == 0) {
			cout << left << setw(18) << t1.getName();
			cout << left << setw(1) << " \t\t\t\t";
			cout << right << setw(18) << t2.getName() << ":" << RESET << endl;
		}
		cout << left << setw(18) << pNames1[i];
		cout << left << setw(1) << " \t\t\t\t";
		cout << right << setw(18) << pNames2[i] << RESET << endl;
	}

}
void display(Teams& t1, Teams& t2, string bat1, string bat2, string baller, Match& obj, Score& scr) {
	string* pNames1, * pNames2;
	int previousTotal = 0;
	static int temp = 0;
	int score_Indiv = 0;
	

		
	if (Auto == true) {
		temp = obj.getTotal();
		Auto = false;
	}
	else {
		
		previousTotal = temp;
		temp = obj.getTotal();
		if (secondHalf == false) {
			score_Indiv = obj.getTotal() - previousTotal;
		}
		else {
			secondHalf = false;
		}

	}


	cout << BLUE << "------------------------------------------------------------------" << RESET << endl;
	cout << MAGENTA << t1.getName() << "\t\t\t\t\t\t" << t2.getName() << RESET << endl << endl;
	cout << CYAN << "    Batting\t\t\t\t\tBowling" << RESET << endl;
	cout << right << setw(10) << obj.getTotal() << "/" << obj.getWickets() << endl;
	if (obj.getRun() % 2 == 0) {
		if (score_Indiv == 1) {
			if (WideDisplay != true)
				scr.updateScore(PlIndex2,obj, score_Indiv, t1, t2,scr);
		}
		else
			if (WideDisplay != true)
				scr.updateScore(PlIndex1,obj, score_Indiv, t1, t2,scr);
		cout << RED << "->  " << RESET << left << setw(10) << bat1 << setw(0) << scr.getIndivScore(PlIndex1) << "/" << scr.getIndivOver(PlIndex1);
		cout << left << setw(1) << " \t\t\t";
		cout << right << setw(10) << baller << RESET << setw(1) << " " << scr.getBallerWickets(BallIndex) << "/" << scr.getIndivBallerOver(BallIndex) << endl;
		cout << "    " << left << setw(10) << bat2 << setw(0) << scr.getIndivScore(PlIndex2) << "/" << scr.getIndivOver(PlIndex2) << endl;
		obj.bi = 1;

	}
	else {
		if (score_Indiv == 1) {
			if (WideDisplay != true)
				scr.updateScore(PlIndex1,obj, score_Indiv, t1, t2,scr);
		}
		else
			if (WideDisplay != true)
				scr.updateScore(PlIndex2,obj, score_Indiv, t1, t2,scr);
		cout << "    " << left << setw(10) << bat1 << setw(0) << setw(0) << scr.getIndivScore(PlIndex1) << "/" << scr.getIndivOver(PlIndex1);
		cout << left << setw(1) << " \t\t\t";
		cout << right << setw(10) << baller << RESET << setw(1) << " " << scr.getBallerWickets(BallIndex) << "/" << scr.getIndivBallerOver(BallIndex) << endl;
		cout << RED << "->  " << RESET << left << setw(10) << bat2 << scr.getIndivScore(PlIndex2) << "/" << scr.getIndivOver(PlIndex2) << endl;
		obj.bi = 2;

	}

	cout << "                         ";
	if (WideDisplay == true) {
		cout << RED << "WD " << RESET;
		WideDisplay = false;
		goto IdharAo;
	}

	t6 = t5;
	t5 = t4;
	t4 = t3;
	t3 = t_2;
	t_2 = t_1;
	t_1 = scr.getcBat();
	cout << "\t\t";
	for (int i = 6; i >= 1; i--) {
		if (i >= obj.getBalls()) {
			if (i == 6) {
				if (t_1 == 0) {
					cout << "- ";
				}
				else
					cout << GREEN << t_1 << " " << RESET;
			}
			else if (i == 5) {
				if (t_2 == 0) {
					cout << "- ";
				}
				else
					cout << GREEN << t_2 << " " << RESET;
			}
			else if (i == 4) {
				if (t3 == 0) {
					cout << "- ";
				}
				else
					cout << GREEN << t3 << " " << RESET;
			}
			else if (i == 3) {
				if (t4 == 0) {
					cout << "- ";
				}
				else
					cout << GREEN << t4 << " " << RESET;
			}
			else if (i == 2) {
				if (t5 == 0) {
					cout << "- ";
				}
				else
					cout << GREEN << t5 << " " << RESET;
			}
			else if (i == 1) {
				if (t6 == 0) {
					cout << "- ";
				}
				else
					cout << GREEN << t6 << " " << RESET;
			}
		}
	}


IdharAo:
	cout << "/" << scr.getOvers() << endl;
	if (obj.secondInnings == true) {
		cout << RED << "                            Target=" << obj.getTarget() << RESET << endl;
	}
	cout << BLUE << "------------------------------------------------------------------" << RESET << endl;
	if (autoCommentry != true&&overChk!=true) {
		obj.getCommentary();
		cout << endl;
		cout << BLUE << "------------------------------------------------------------------" << RESET << endl;
	}
	pNames1 = t1.Names();
	pNames2 = t2.Names();
	for (int i = 0; i < t1.getPlayers(); i++) {
		if (i == 0) {
			cout << left << setw(18) << t1.getName();
			cout << left << setw(1) << " \t\t\t\t";
			cout << right << setw(18) << t2.getName() << ":" << RESET << endl;
		}
		cout << left << setw(18) << pNames1[i];
		cout << left << setw(1) << " \t\t\t\t";
		cout << right << setw(18) << pNames2[i] << RESET << endl;
	}
	autoCommentry = false;
}
bool toss() {
	srand(time(0));
	char toss;
	int res;
	cout << "Press H for heads and T for tails for team 1";
	cin >> toss;
	while (toss != 'H' && toss != 'h' && toss != 'T' && toss != 't') {
		cout << "Select again ";
		cin >> toss;
	}

	res = rand() % 2 + 1;

	if (res == 1 && toss == 'h') {
		return true;

	}
	else if (res == 1 && toss == 't') {
		return false;
	}
	else if (res == 2 && toss == 't') {
		return true;

	}
	else {
		return false;
	}


}
void countdownStart() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");// clear screen
	for (int i = 3; i > 0; i--) {
		SetConsoleTextAttribute(hConsole, i + 9); // set color
		cout << "Match will start in " << i << "...\n";
		Sleep(1000); // delay for 1 second
		cout << "\033[2J\033[1;1H"; // clear screen
	}
	SetConsoleTextAttribute(hConsole, 7); // reset color
	cout << "Match starts now!\n";
	Sleep(1000);
	system("cls");
}
void afterOver(Match& obj, Teams t1, Teams t2, Score& scr) {
	obj.setRun();
	obj.setBall(t2);
	/*for (int i = 0; i < MAX_PREV_SCORES; i++) {
		prevScores[i] = 0;
	}*/
	t_1 = t_2 = t3 = t4 = t5 = t6 = 0;
	scr.resetcBat();
}
int No_Ball(Match& obj) {

	system("cls");
	cout << RED << "FREE HIT!!" << RESET << endl;
	Sleep(1000);
	int cBall = obj.ballType();
	int cBat = 0;
	if (cBall != 4 && cBall != 5) {
		cBat = obj.batType();
	}
	else {
		obj.reduceWickets();
	}
	obj.Ball();
	obj.Over();
	return cBat;
}
void ViewPreviousScore() {
	ifstream PreviousScore("1stInnings.txt");
	cout <<RED<< "1st Innings " << CYAN<<endl;
	if (PreviousScore.is_open()) {  
		cout << PreviousScore.rdbuf(); 
		PreviousScore.close(); 
	}
	else {
		cout << "Failed to open the file." << endl;
	}
	cout << RED << "2nd Innings " << CYAN << endl;
	ifstream PreviousScore2("2ndInnings.txt");
	if (PreviousScore2.is_open()) { 
		cout << PreviousScore2.rdbuf(); 
		PreviousScore2.close();  
	}
	else {
		cout << "Failed to open the file." << endl;
	}
	cout << RESET;
}
int generateRandomScore() {
	int randomNum = rand() % 100;

	
	int probability0 = 10;  
	int probability1 = 30;  
	int probability2 = 25;  
	int probability4 = 20;  
	int probability6 = 15;   

	if (randomNum < probability0)
		return 0;
	else if (randomNum < probability0 + probability1)
		return 1;
	else if (randomNum < probability0 + probability1 + probability2)
		return 2;
	
	else if (randomNum < probability0 + probability1 + probability2 + probability4)
		return 4;
	else
		return 6;
}
void AutoPlay(Match &obj, Teams t1,Teams t2, Score &scr, int &count) {
	srand(time(0));
	while (scr.getOvers() < obj.gettOvers() && obj.getWickets() <= 10) {
		int Tscore;
		scr.Ball();
		scr.Over();
		int batsmanIndex = PlIndex1;
		int bowlerIndex = BallIndex;

		string batsman = obj.getBat1();
		string bowler = obj.getBaller();

		
		int runs = generateRandomScore();
		if (runs == 1) {
			obj.setRun();
			batsmanIndex = PlIndex2;
		}
		Tscore = obj.getTotal();
		Tscore += runs;
		cout << Tscore << "  " << runs << endl;
		obj.setTotal(Tscore);
		scr.updateScore(batsmanIndex,obj, runs, t1, t2,scr);
		count++;
		if ((rand() % 100) % 13 == 0) {
			return;
		}
	}
}
int main() {
	Teams team1, team2;
	SupportStaffAndOthers supportStaff;
	int bat = 0;
	Initialize(team1, team2);
	Match start;
	start.setcommentary();
	bool matchSide1 = false, matchSide2 = false;
	int Tscore = 0;
	int cBall = 0;
	int cBat = 0;
	int tWickets = 10;
	int cOvers = 0;
	int count = 0;
	int target = 0;
	int choice;
	bool overset = false;
	supportStaff.selectRandoms();

	do {
		system("cls"); // Clear the console
		cout << YELLOW << "Cricket Simulation Menu" << CYAN<<endl;
		cout << "1. " << CYAN << "Setup a Match" << endl;
		cout << "2. " << CYAN << "View Previous Match Scores" << endl;
		cout << "3. " << CYAN << "View Team" << endl;
		cout << "4. " << CYAN << "View Support Staff & Ground" <<RED<< endl;
		cout << "5. " << "Exit"<<RESET << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		// Perform actions based on user's choice
		switch (choice) {
		case 1:

			cout << CYAN<<endl;
			cout << "Select the type of match:" << endl;
			cout << "1. T20" << endl;
			cout << "2. One Day" << endl;
			cout << "3. Custom Overs" << RESET<<endl;
			cout << "Enter your choice: ";
			cin >> tempInt;

			// Perform actions based on the match type
			if (tempInt == 1) {
				system("cls");
				cout << RED<<"Setting up a T20 match...\n"<<CYAN<<"Remember team 1 is on the left and team 2 on right"<<RESET << endl;
				Sleep(1000);
				start.settOvers(20);
				overset = true;
			}
			else if (tempInt == 2) {
				system("cls");
				cout <<RED<< "Setting up a One Day match...\n" << CYAN << "Remember team 1 is on the left and team 2 on right"<<RESET << endl;
				Sleep(1000);
				start.settOvers(50);
				overset = true;
			}
			else if (tempInt==3) {
				system("cls");
				cout << "Setting up a Custom Overs match...\n" << CYAN << "Remember team 1 is on the left and team 2 on right" << RESET << endl;
				Sleep(1000);
			}
			else {
				cout << RED << "Invalid match type. Doing Customs\n" << CYAN << "Remember team 1 is on the left and team 2 on right" << RESET << endl;
				cout << RESET;
			}
			goto Start;
			break;
		case 2:
			ViewPreviousScore();
			system("pause");
			break;
		case 3:
			Initdisplay(team1, team2);
			system("pause");
			cout << endl;
			break;
		case 4:
			supportStaff.getSupportStaffAndOthers();
			system("pause");
			break;
		case 5:
			cout << RED << "Exiting the program. Goodbye!" << endl;
			break;
		default:
			cout << RED << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 5);

	return 0;
Start:
if (toss() == 1) {
	system("cls");
	cout << CYAN << "Team 1" << RESET << " won the toss\nPress 1 for batting.\nPress 2 for balling\n";
	cin >> tempInt;
	switch (tempInt) {
	case 1:
		start.setBatBall(team1, team2);
		bat = 1;
		system("cls");
		cout << "team 1" << GREEN << " bat" << RESET << " team 2" << RED << " ball" << RESET << endl;
		break;
	case 2:
		start.setBatBall(team2, team1);
		bat = 2;
		system("cls");
		cout << "team 1" << RED << " ball" << RESET" team 2" << GREEN << " bat" << RESET << endl;
		break;
	default:
		cout << "Select correct option ";
		cin >> tempInt;
	}
}
else {
	system("cls");
	cout << CYAN << "Team 2" << RESET << " won the toss\nPress 1 for batting.\nPress 2 for balling\n";
	cin >> tempInt;
	switch (tempInt) {
	case 1:
		start.setBatBall(team2, team1);
		bat = 2;
		system("cls");
		cout << "team 2" << GREEN << " bat" << RESET << " team 1 " << RED << "ball" << RESET << endl;
		break;
	case 2:
		start.setBatBall(team1, team2);
		bat = 1;
		system("cls");
		cout << "team 2" << RED << " ball" << RESET << " team 1" << GREEN << " bat" << RESET << endl;
		break;
	default:
		cout << "Select correct option ";
		cin >> tempInt;
	}
}
Initdisplay(team1, team2);
cout << "Select two opening batsmen ";
if (bat == 1) {
	start.setBat(team1);
	cout << endl;
	start.setBall(team2);
}
else {
	start.setBat(team2);
	cout << endl;
	start.setBall(team1);
}
system("cls");
if (overset != true) {
	cout << "Enter the total number of " << CYAN << "overs " << RESET;
	cin >> tempInt;
	start.settOvers(tempInt);
}
countdownStart();
Score scr(team1.getPlayers());
autoCommentry = true;
display(team1, team2, start.getBat1(), start.getBat2(), start.getBaller(), start, scr);
while (matchSide1 != true) {
	if (tWickets == start.getWickets() || cOvers == start.gettOvers() || scr.getOvers() == start.gettOvers()) {
		matchSide1 = true;
		break;
	}
	if (count % 6 == 0 && count != 0) {
		cout << RED << "END OF OVER " << scr.getOvers() << RESET << endl;
		system("pause");
		system("cls");
		cout << RED << "END OF OVER " << scr.getOvers() << RESET << endl;
		autoCommentry = true;
		overChk = true;
		Initdisplay(team1, team2);
		if (bat == 1)
			afterOver(start, team1, team2, scr);
		else
			afterOver(start, team2, team1, scr);
		system("cls");
		display(team1, team2, start.getBat1(), start.getBat2(), start.getBaller(), start, scr);
	}
	if (count ==7) {
		autoplay = true;
		Auto = true;
		autoCommentry = true;
		cout << CYAN << "Do you want to use autoplay feature till the next wicket?\nEnter yes or no " << RESET;
		cin >> tempS;
		if (tempS == "yes" || tempS == "Yes" || tempS == "YES") {
			cBat = cBall=0;
			AutoPlay(start, team1, team2, scr,count);
			cout << Tscore << endl;
			Tscore += start.getTotal();
			start.setTotal(Tscore);
			cOvers = count % 6;
			cout << Tscore << endl;
			start.setWickets();
			t6 = t5 = t4 = t3 = t_2 = t_1 = 0;
			goto out;
		}
	}
	
	
	Wide = false;
	noBall = false;
	WideDisplay = false;
	overChk = false;
	cBall = start.ballType();
	//cBall 4||5
	if (cBall != 4 && cBall != 5) {
		cBat = start.batType();
	}
	else {
		if (cBall == 5) {
			tempInt = start.batType();
		}
	out:	overChk = true;
		cBat = 0;
		start.setOut();
		autoCommentry = true;
		scr.setBallerWickets(BallIndex);
		if (start.bi == 1) {
			scr.setNegIndivOver(PlIndex1, team1.getPlayers());
		}
		else {
			scr.setNegIndivOver(PlIndex2, team1.getPlayers());
		}
		Initdisplay(team1, team2);
		if (bat == 1) {
			start.setBat(team1);
		}
		else {
			start.setBat(team2);
		}
		
	}
	overChk = false;
	scr.setcBat(cBat); scr.setcBall(cBall);
	//cBall ==1
	if (cBat == 1 && (cBall == 1)) {
		start.setRun();
		Tscore += cBat;
		start.setTotal(Tscore);
	}
	else if (cBat == 2 && cBall == 1) {
		Tscore += cBat;
		start.setTotal(Tscore);

	}
	else if (cBat == 4 && cBall == 1) {
		Tscore += cBat;
		start.setTotal(Tscore);
	}
	else if (cBat == 6 && cBall == 1) {
		Tscore += cBat;
		start.setTotal(Tscore);
	}
	else if (cBat == 0 && cBall == 1) {
		start.setTotal(Tscore);
	}
	//cBall ==2
	else if (cBat == 1 && cBall == 2) {
		start.setRun();
		Tscore += cBat;
		start.setTotal(Tscore);
		Wide = true;
	}
	else if (cBat == 2 && cBall == 2) {
		Tscore += cBat;
		start.setTotal(Tscore);
		Wide = true;
	}
	else if (cBat == 4 && cBall == 2) {
		Tscore += cBat;
		start.setTotal(Tscore);
		Wide = true;
	}
	else if (cBat == 6 && cBall == 2) {
		Tscore += cBat;
		start.setTotal(Tscore);
		Wide = true;
	}
	else if (cBat == 0 && cBall == 2) {
		Tscore++;
		start.setTotal(Tscore);
		Wide = true;
		WideDisplay = true;
		real_wala_wide = true;
	}
	//cBall==3
	else if (cBat == 1 && cBall == 3) {
		start.setRun();
		Tscore += cBat;
		Tscore += No_Ball(start);
		start.setTotal(Tscore);
		noBall = true;
	}
	else if (cBat == 2 && cBall == 3) {
		Tscore += cBat;
		Tscore += No_Ball(start);
		start.setTotal(Tscore);
		noBall = true;
	}
	else if (cBat == 4 && cBall == 3) {
		Tscore += cBat;
		Tscore += No_Ball(start);
		start.setTotal(Tscore);
		noBall = true;
	}
	else if (cBat == 6 && cBall == 3) {
		Tscore += cBat;

		start.setTotal(Tscore);
		Tscore += No_Ball(start);
		noBall = true;
	}
	else if (cBat == 0 && cBall == 3) {
		start.setTotal(Tscore);
		noBall = true;
		Tscore += No_Ball(start);
	}
	//cBall ==6
	else if (cBat == 4 && cBall == 6) {
		start.setWickets();
	}
	else if (cBat == 1 && cBall == 6) {
		start.setWickets();
	}
	else if (cBat == 2 && cBall == 6) {
		start.setWickets();
	}
	else if (cBat == 0 && cBall == 6) {
		start.setWickets();
	}
	else if (cBat == 6 && cBall == 6) {
		start.setWickets();
	}

	//Over


	if (!WideDisplay) {

		scr.Ball();
		scr.Over();
		count++;
	}




	/*else {
		if (WideDisplay != true) {
			scr.Ball();
			scr.Over();
		}
		count++;
	}*/
	if (noBall == true) {
		Tscore++;
		start.setTotal(Tscore);
		noBall = false;
		//here extra
	}

	cOvers = scr.getOvers();
	system("cls");
	display(team1, team2, start.getBat1(), start.getBat2(), start.getBaller(), start, scr);
	real_wala_wide = false;
	autoplay = false;
}
Tscore = 0;
st = 0;
count = 0;
secondHalf = true;
start.secondInnings = true;
OtherSide = true;
target = start.getTotal() + 1;
system("cls");
cout << RED << "TARGET = " << target << RESET << endl;
start.setTarget(target);
start.Reset();
Teams temp = team1;
team1 = team2;
team2 = temp;
cOvers = 0;
Initdisplay(team1, team2);
cout << "Select two opening batsmen ";
if (bat == 1) {
	start.setBat(team1);
	start.setBall(team2);
}
else {
	start.setBat(team2);
	start.setBall(team1);
}
countdownStart();
Score sc2(team1.getPlayers());
system("cls");
display(team1, team2, start.getBat1(), start.getBat2(), start.getBaller(), start, sc2);

while (matchSide2 != true) {
	if (tWickets == start.getWickets() || cOvers == start.gettOvers() || start.getTotal() >= target) {
		matchSide2 = true;
		break;
	}
	if (count % 6 == 0 && count != 0) {
		cout << RED << "END OF OVER " << scr.getOvers() << RESET << endl;
		system("pause");
		system("cls");
		overChk = true;
		autoCommentry = true;
		cout << RED << "END OF OVER " << sc2.getOvers() << RESET << endl;
		Initdisplay(team1, team2);
		if (bat == 1)
			afterOver(start, team1, team2, sc2);
		else
			afterOver(start, team2, team1, sc2);
		system("cls");
		display(team1, team2, start.getBat1(), start.getBat2(), start.getBaller(), start, sc2);
	}
	if (count ==7) {
		Auto = true;
		autoplay = true;
		autoCommentry = true;
		cout << CYAN << "Do you want to use autoPlay feature till the next wicket?\nEnter yes or no " << RESET;
		cin >> tempS;
		if (tempS == "yes" || tempS == "Yes" || tempS == "YES") {
			cBat = cBall = 500;
			AutoPlay(start, team1, team2, scr, count);
			Tscore += start.getTotal();
			cOvers = count % 6;
			start.setWickets();
			goto out2;
		}
	}
	
	Wide = false;
	noBall = false;
	WideDisplay = false;
	overChk = false;
	cBall = start.ballType();
	//cBall 4||5
	if (cBall != 4 && cBall != 5) {
		cBat = start.batType();
	}
	else {
		if (cBall == 5) {
			tempInt = start.batType();
		}
out2:
		cBat = 0;
		overChk = true;
		autoCommentry = true;
		start.setOut();
		sc2.setBallerWickets(BallIndex);
		if (start.bi == 1) {
			sc2.setNegIndivOver(PlIndex1, team1.getPlayers());
		}
		else {
			sc2.setNegIndivOver(PlIndex2, team1.getPlayers());
		}
		Initdisplay(team1, team2);
		if (bat == 1) {
			start.setBat(team1);
		}
		else {
			start.setBat(team2);
		}
	}
	overChk = false;
	sc2.setcBat(cBat); sc2.setcBall(cBall);

	//cBall ==1
	if (cBat == 1 && (cBall == 1)) {
		start.setRun();
		Tscore += cBat;
		start.setTotal(Tscore);
	}
	else if (cBat == 2 && cBall == 1) {
		Tscore += cBat;
		start.setTotal(Tscore);

	}
	else if (cBat == 4 && cBall == 1) {
		Tscore += cBat;
		start.setTotal(Tscore);
	}
	else if (cBat == 6 && cBall == 1) {
		Tscore += cBat;
		start.setTotal(Tscore);
	}
	else if (cBat == 0 && cBall == 1) {
		start.setTotal(Tscore);
	}
	//cBall ==2
	else if (cBat == 1 && cBall == 2) {
		start.setRun();
		Tscore += cBat;
		start.setTotal(Tscore);
		Wide = true;
	}
	else if (cBat == 2 && cBall == 2) {
		Tscore += cBat;
		start.setTotal(Tscore);
		Wide = true;
	}
	else if (cBat == 4 && cBall == 2) {
		Tscore += cBat;
		start.setTotal(Tscore);
		Wide = true;
	}
	else if (cBat == 6 && cBall == 2) {
		Tscore += cBat;
		start.setTotal(Tscore);
		Wide = true;
	}
	else if (cBat == 0 && cBall == 2) {
		Tscore++;
		start.setTotal(Tscore);
		Wide = true;
		WideDisplay = true;
		real_wala_wide = true;
	}
	//cBall==3
	else if (cBat == 1 && cBall == 3) {
		start.setRun();
		Tscore += cBat;
		Tscore += No_Ball(start);
		start.setTotal(Tscore);
		noBall = true;
	}
	else if (cBat == 2 && cBall == 3) {
		Tscore += cBat;
		Tscore += No_Ball(start);
		start.setTotal(Tscore);
		noBall = true;
	}
	else if (cBat == 4 && cBall == 3) {
		Tscore += cBat;
		Tscore += No_Ball(start);
		start.setTotal(Tscore);
		noBall = true;
	}
	else if (cBat == 6 && cBall == 3) {
		Tscore += cBat;

		start.setTotal(Tscore);
		Tscore += No_Ball(start);
		noBall = true;
	}
	else if (cBat == 0 && cBall == 3) {
		start.setTotal(Tscore);
		noBall = true;
		Tscore += No_Ball(start);
	}
	//cBall ==6
	else if (cBat == 4 && cBall == 6) {
		start.setWickets();
	}
	else if (cBat == 1 && cBall == 6) {
		start.setWickets();
	}
	else if (cBat == 2 && cBall == 6) {
		start.setWickets();
	}
	else if (cBat == 0 && cBall == 6) {
		start.setWickets();
	}
	else if (cBat == 6 && cBall == 6) {
		start.setWickets();
	}

	//Over


	if (!WideDisplay) {

		sc2.Ball();
		sc2.Over();
		count++;
	}





	if (noBall == true) {
		Tscore++;
		start.setTotal(Tscore);
		noBall = false;
		//here extra
	}
	cOvers = sc2.getOvers();
	cout << cOvers << endl;
	system("cls");
	display(team1, team2, start.getBat1(), start.getBat2(), start.getBaller(), start, sc2);
	real_wala_wide = false;
	Auto = false;
}
cout << "\n\n" << GREEN;
if (start.getTotal() >= target) {
	if (bat == 2)
		cout << team2.getName() << " WON THE MATCH" << RESET << endl;
	else {
		cout << team1.getName() << " WON THE MATCH" << RESET << endl;
	}
}
else {
	if (bat == 2) {
		cout << team1.getName() << " WON THE MATCH" << RESET << endl;
	}
	else {
		cout << team2.getName() << " WON THE MATCH" << RESET << endl;
	}
}
return 0;
}