#include "knight.h"

using namespace std;

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
	cout << "HP=" << HP
		<< ", level=" << level
		<< ", remedy=" << remedy
		<< ", maidenkiss=" << maidenkiss
		<< ", phoenixdown=" << phoenixdown
		<< ", rescue=" << rescue << endl;
}


int pow1(int x, int n)
{
	int sum = 1;
	if (n == 0)
	{
		sum = 1;
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{
			sum = sum * x;
		}
	}
	return sum;
}  

int chuyen(char c)
{
	return (int)c - 48;
}

int STRING_TO_INT(string str) {
	int k = 0;
	int sum = 0;
	if (str[0] != '-') {
		for (int i = str.length() - 1; i >= 0; i--)
		{
			sum = sum + chuyen(str[i]) * pow1(10, k);
			k++;
		}
		return sum;
	}
	else {
		int size = str.length();
		string cut = str.substr(1, size - 1);
		size -= 1;
		for (int i = size - 1; i >= 0; i--)
		{
			sum = sum + chuyen(cut[i]) * pow1(10, k);
			k++;
		}
		return -sum;
	}
}



///////////////////  ///passed

bool Arthur_king(int maxHP)
{
	if (maxHP == 999) { return 1; }
	else
		return 0;
}



bool Lancelot(int maxHP)
{
	int count = 0;
	for (int i = 1; i <= maxHP; i++)
	{
		if (maxHP % i == 0) { count++; }
	}
	if (count == 2) { return 1; }
	else{
		return 0;
	}
}

void level_up(int& level)
{
	if (level < 10)
		level += 1;
}

int level_o(int i) // sự kiện thứ i
{
	int b = i % 10;
	if (i > 6)
	{
		if (b > 5)
		{
			return b;
		}
		else
			return 5;
	}
	else
	{
		return b;
	}
}

void fight(int i, double basedame, int& HP, int maxHP, int& level, int& phoenixdown, int& rescue) // 1-5
{
	int levelO = level_o(i);
	if (level > levelO || Arthur_king(maxHP) || Lancelot(maxHP))
	{
		level_up(level);
	}
	if(level < levelO)
	{
		int damage = int(basedame * levelO * 10);
		HP = HP - damage;
		if (HP <= 0)
		{
			if (phoenixdown > 0){
				HP = maxHP;
				phoenixdown -= 1;
			}
			else
				rescue = 0;
		}
	}
}

void little_mode(int i, int turna, int& HP)
{
	{
		if (HP > 5)
		{
			HP = HP / 5;
		}
		else
			HP = 1;
	}
}

void out_of_little_mode(int eventID, int i, int& turna, int& HP, int& remedy)
{
	if (turna == i)
	{
		HP = HP * 5;
		turna = 0;
	}
	else if (eventID == 6 && remedy > 0)
	{
		HP = HP * 5;
		remedy -= 1;
		turna = 0;
	}
	else if ((eventID == 6 && remedy > 0) && (turna + 3 == i))
	{
		HP = HP * 5;
		turna = 0;
	}
}

void forg_mode(int i, int turnb, int& level, int& pre_level)
{
	if (turnb == i)
	{
		pre_level = level;
		level = 1;
	}
}

void out_of_forg_mode(int eventID, int i, int& turnb, int& level, int& pre_level, int& maidenkiss)
{
	if (turnb == i)
	{
		level = pre_level;
		turnb = 0;
	}
	else if (eventID == 7 && maidenkiss > 0)
	{
		level = pre_level;
		maidenkiss -= 1;
		turnb = 0;
	}
	else if (eventID == 7 && (maidenkiss  > 0) && (turnb + 3 == i))
	{
		level = pre_level;
		turnb = 0;
	}
}

void MushMario(int& HP, int maxHP, int level, int phoenixdown)
{
	int n1; n1 = ((level + phoenixdown) % 5 + 1) * 3;
	int max = 99;
	int min = 1;
	int s1 = 0; //total
	//odd number with digits 2 (1,2,3,5..,99)
	for (int i = 0; i < n1; i++)
	{
		if (min > max)
		{
			break;
		}
		else
		{
			s1 = s1 + max;
			max -= 2;
		}
	}
	HP = HP + (s1 % 100);
	// find prime number which is nearest sum
	int prime1 = 0;
	int prime2 = 0;
	for (int i = 2; i <= HP; i++)
	{
		int count = 0;
		for (int j = 1; j <= i; j++)
		{
			if (i % j == 0)
			{
				count += 1;
			}
		}
		if (count == 2)
		{
			prime1 = prime2;
			prime2 = i;
		}
	}
	{
		if (HP - prime1 >= prime2 - HP)
		{
			HP = prime2;
		}
		else
		{
			HP = prime1;
		}
	}
	if (HP > maxHP)
	{
		HP = maxHP;
	}
}

void MushFib(int& HP)
{
	int Fibo0 = 0;
	int Fibo1 = 0;
	for (int n = 0; true; n++)
	{
		int a1 = 1, a2 = 1;
		if (n == 1 || n == 2)
			Fibo0 = 1;
		int i = 3, a = 0;
		while (i <= n)
		{
			a = a1 + a2;
			a1 = a2;
			a2 = a;
			i++;
		}
		Fibo1 = Fibo0;
		Fibo0 = a;
		if (Fibo0 >= HP)
		{
			HP = Fibo1;
			break;
		}
	}
}

void MushGhost_Type_1(int arr[], int d1, int& HP)
{
	// Find Location of Max & Min
	int maxi = 0;
	int mini = 0;
	int max = INT8_MIN;
	for (int i = 0; i < d1; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			maxi = i;
		}
	}
	int min = INT8_MAX;
	for (int i = 0; i < d1; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			mini = i;
		}
	}
	HP = (HP - (maxi + mini));
}

bool checkup(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (a[i] > a[i + 1]) return false;
	}
	return true;
}

bool checkdown(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (a[i] < a[i + 1]) return false;
	}
	return true;
}

void MushGhost_Type_2(int arr[], int d1, int& HP)
{
	int mtx = -2;
	int mti = -3;
	// up mountain
	bool up = checkup(arr, d1);
	bool down = checkdown(arr, d1);

	if (up == true) {
		mtx = arr[d1 - 1];
		mti = d1 - 1;
	}
	else if (down == true)
	{
		mtx = arr[0];
		mti = 0;
	}
	else
	{
		int l_max = 0;
		int max = 0;
		for (int i = 0; i < d1; i++) {
			if (arr[i] > max) {
				max = arr[i];
				l_max = i;
			}
		}
		int suonlen[50];
		int numlen = 0;
		for (int i = 0; i <= l_max; i++) {
			suonlen[i] = arr[i];
			numlen++;
		}
		int suonxuong[50];
		int numxuong = 0;
		for (int i = l_max; i < d1; i++) {
			suonlen[i] = arr[i];
			numxuong++;
		}
		if (checkup(suonlen, numlen) == true && checkdown(suonxuong, numxuong) == true) {
			mtx = max;
			mti = l_max;
		}
	}
	HP = HP - (mtx + mti);
}

void MushGhost_Type_3(int arr[], int d1, int& HP)
{
	// Find Location of Max & Min
	int maxi2 = 0;
	int mini2 = 0;
	int c_arr[100];
	for (int i = 0; i < d1; i++)
	{
		if (arr[i] < 0) {
			c_arr[i] = ((17 * (-arr[i]) + 9)) % 257;
		}
		else
			c_arr[i] = ((17 * arr[i] + 9)) % 257;
	}
	int max = INT8_MIN;
	for (int i = 0; i < d1; i++)
	{
		if (c_arr[i] > max)
		{
			max = c_arr[i];
			maxi2 = i;
		}
	}
	int min = INT8_MAX;
	for (int i = 0; i < d1; i++)
	{
		if (c_arr[i] < min)
		{
			min = c_arr[i];
			mini2 = i;
		}
	}
	HP = (HP - (maxi2 + mini2));
}

void MushGhost_Type_4(int arr[], int d1, int& HP)
{
	int max2_3i = 0;
	int max2_3x = 0;
	int c_arr[100]={};
	for (int i = 0; i < d1; i++)
	{
		if (arr[i] < 0) {
			c_arr[i] = (17 * (-arr[i]) + 9) % 257;
		}
		else
			c_arr[i] = (17 * arr[i] + 9) % 257;
	}

	if (c_arr[0] == c_arr[1] && c_arr[1] == c_arr[2]) {
		max2_3x = -5; max2_3i = -7;
	}
	else {
		int max1 = INT8_MIN;
		int max2 = INT8_MIN;
		int maxi1 = 0;
		int maxi2 = 0;
		int i;
		for (i = 0; i < 2; i++) {
			if (max1 < c_arr[i]) {
				max2 = max1;
				maxi2 = maxi1;
				max1 = c_arr[i];
				maxi1 = i;
			}
			else if (max1 > c_arr[i] && max2 < c_arr[i]) {
				max2 = c_arr[i];
				maxi2 = i;
			}
		}
		max2_3x = max2;
		max2_3i = maxi2;
	}
	HP = (HP - (max2_3x + max2_3i));
}

void event(int eventID, string mush, string asci, string merlin1, int i, int& turna, int& turnb, int maxHP, bool& met_asclepius, int& pre_level, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue)
{

	if (eventID == 0)
	{
		rescue = 1;
	}
	else if (eventID == 1) {
		fight(i, 1.0, HP, maxHP, level, phoenixdown, rescue);
	}
	else if (eventID == 2) {
		fight(i, 1.5, HP, maxHP, level, phoenixdown, rescue);
	}
	else if (eventID == 3) {
		fight(i, 4.5, HP, maxHP, level, phoenixdown, rescue);
	}
	else if (eventID == 4) {
		fight(i, 7.5, HP, maxHP, level, phoenixdown, rescue);
	}
	else if (eventID == 5) {
		fight(i, 9.5, HP, maxHP, level, phoenixdown, rescue);
	}
	else if (eventID == 6) {
		if (turnb == 0) {
			int levelO = level_o(i);
			if (level > levelO || Arthur_king(maxHP) || Lancelot(maxHP)) {
				level_up(level);
				level_up(level);
			}
			if(level <levelO) {
				turna = i + 3;
				little_mode(i, turna, HP);
			}
		}

	}
	else if (eventID == 7)
	{
		if (turna == 0)
		{
			int levelO = level_o(i);
			if (level > levelO || Arthur_king(maxHP) || Lancelot(maxHP))
			{
				level_up(level);
				level_up(level);
			}
			if (level < levelO)
			{
				turnb = i + 3;
				forg_mode(i, turnb, level, pre_level);
			}
		}
	}
	else if (eventID == 11) {
		MushMario(HP, maxHP, level, phoenixdown);
	}
	else if (eventID == 12) {
		MushFib(HP);
	}
	else if (eventID == 15) {
		remedy += 1;
	}
	else if (eventID == 16) {
		maidenkiss += 1;
	}
	else if (eventID == 17) {
		phoenixdown += 1;
	}
	else if (eventID == 18) {
		int n;
		string temp;
		ifstream merlin;
		merlin.open(merlin1);

		int getm = 0, gete = 0, getr = 0, getl = 0, geti = 0, getn = 0;
		int merlinname = 0;
		int merlinfullname = 0;
		merlin >> n;

		for (int i = 0; i < n; i++)
		{
			getline(merlin, temp);
			for (int j = 0; j < temp.length(); j++) {
				if ((temp[j] == 'M' || temp[j] == 'm') && getm == 0) {
					merlinname += 1;
					getm = 1;
				}
				if ((temp[j] == 'E' || temp[j] == 'e') && gete == 0) {
					merlinname += 1;
					gete = 1;
				}
				if ((temp[j] == 'M' || temp[j] == 'm') && getr == 0) {
					merlinname += 1;
					getr = 1;
				}
				if ((temp[j] == 'L' || temp[j] == 'l') && getl == 0) {
					merlinname += 1;
					getl = 1;
				}
				if ((temp[j] == 'I' || temp[j] == 'i') && geti == 0) {
					merlinname += 1;
					geti = 1;
				}
				if ((temp[j] == 'N' || temp[j] == 'n') && getn == 0) {
					merlinname += 1;
					getn = 1;
				}
			}
			if (merlinname == 6)
			{
				for (int i = 0; i < temp.length(); i++)
				{
					if ((temp.substr(i, 6)).compare("Merlin") == 0 || (temp.substr(i, 6)).compare("merlin") == 0) {
						merlinfullname = 1;
					}
				}
				if (merlinfullname == 1) {
					HP = HP + 3;
				}
				else
					HP = HP + 2;
			}
			getm = 0, gete = 0, getr = 0, getl = 0, geti = 0, getn = 0;
			merlinname = 0;
			merlinfullname = 0;
		}
		merlin.close();
	}
	else if (eventID == 19) {

		int r1 = 0, c1 = 0;
		int get = 0;
		int data[10][10] = {};

		if (met_asclepius == false) {
			ifstream asclepius;
			asclepius.open(asci);
			asclepius >> r1;
			asclepius >> c1;
			for (int i = 0; i < r1; i++) {
				for (int j = 0; j < c1; j++) {
					asclepius >> data[i][j];
				}
			}
			asclepius.close();

			for (int i = 0; i < r1; i++) {
				for (int j = 0; j < c1; j++) {
					if (get < 3) {
						if (data[i][j] == 16) {
							remedy += 1;
							get += 1;
						}
						if (data[i][j] == 17) {
							maidenkiss += 1;
							get += 1;
						}
						if (data[i][j] == 18) {
							phoenixdown += 1;
							get += 1;
						}
					}
				}
				get = 0;
			}
			met_asclepius = true;
		}
	}
	else if (eventID == 99) {
		if (Arthur_king(maxHP) || ((Lancelot(maxHP)) && (level >= 8)) || (level = 10))
		{
			level = 10;
		}
		else
			rescue = 0;
	}
	else // su kien  13
	{
		// Xu li file
		ifstream mushfile;
		mushfile.open(mush);
		int d1; // dong 1
		string d2; // d2
		string emty;
		int r2[100] = {};
		mushfile >> d1;
		getline(mushfile, emty);
		getline(mushfile, d2);

		int n = 0;
		int p = 0;
		for (int i = 0; i < d2.length(); i++)
		{
			if (d2[i] == ',') {
				r2[p] = STRING_TO_INT(d2.substr(n, i - n));
				n = i + 1;
				p++;
			}
			if (i == d2.length() - 1) {
				r2[p] = STRING_TO_INT(d2.substr(n, d2.length() - n));
			}
		}
		mushfile.close();

		// tach so
		int count = 0;
		int temp = 0;
		string s = to_string(eventID);

		for (int i = 2; i < s.length(); i++) {
			if (s[i] == '1')
			{
				MushGhost_Type_1(r2, d1, HP);
			}
			else if (s[i] == '2')
			{
				MushGhost_Type_2(r2, d1, HP);
			}
			else if (s[i] == '3')
			{
				MushGhost_Type_3(r2, d1, HP);
			}
			else
			{
				MushGhost_Type_4(r2, d1, HP);
			}
		}
	}
}



void adventureToKoopa(string file_input, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue)
{
	HP = 0, level = 0, remedy = 0, maidenkiss = 0, phoenixdown = 0,rescue = -1;

	/////////////////////	Xu li file

	string knight;
	string aventure1;
	string pack;
	int eventid[50]={}; // mang chua cac id

	ifstream file;
	file.open(file_input);
	file >> HP >> level >> remedy >> maidenkiss >> phoenixdown;
	getline(file, knight);
	getline(file, aventure1);
	getline(file, pack);
	file.close();

	string file_mush_ghost, file_asclepius_pack, file_merlin_pack;// khai bao chuoi chua ten pack
	int t = 0;
	int p = 1;
	for (int i = 0; i < pack.length(); i++){
		string save;
		if (pack[i] == ','){
			if (p == 1) {
				file_mush_ghost = pack.substr(t, i - t);
			}
			else {
				file_asclepius_pack =pack.substr(t, i - t);
			}
			t = i + 1;
			p++;
		}
		if (i == pack.length() - 1){
			file_merlin_pack = pack.substr(t, pack.length() - t);
		}
	}

	string aventure = aventure1.substr(0, aventure1.length()-1);

	int num = 0;//int num = 0; // so su kien xay ra = num+1 =turn cuoi
	int n = 0; // vi tri lay
	for (int i = 0; i < aventure.length(); i++){
		if (aventure[i] == ' ' && aventure[i + 1] != ' ') {
				eventid[num] = STRING_TO_INT(aventure.substr(n, i - n));
				n = i + 1;
				num++;
		}
		else if (i == aventure.length() - 1){
				eventid[num] = STRING_TO_INT(aventure.substr(n, aventure.length() - n));
		}
	}

	int maxHP = HP;
	int turn = 1;//luot choi
	int turn_little = 0;///// luot bien thanh little
	int turn_forg = 0;//// luot bien thanh forg
	int pre_level = 0;/// level truoc khi tru
	int pre_phoenix = phoenixdown;//// phoenix truoc khi tru
	bool met_asclepius = false;

	for (int j = 0; j <= num; j++)
	{
		event(eventid[j], file_mush_ghost, file_asclepius_pack, file_merlin_pack, turn, turn_little, turn_forg, maxHP, met_asclepius, pre_level, HP, level, remedy, maidenkiss, phoenixdown, rescue);
		out_of_little_mode(eventid[j], turn, turn_little, HP, remedy);
		out_of_forg_mode(eventid[j], turn, turn_forg, level, pre_level, maidenkiss);
		//check hp,remedy,maidenkiss,phoenixdown
		if (HP > maxHP) { HP = maxHP; }
		if (remedy > 99) { remedy = 99; }
		if (maidenkiss > 99) { maidenkiss = 99; }
		if (phoenixdown > 99) { phoenixdown = 99; }

		if (rescue == 0){
			display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
			break;
		}
		else if (rescue == 1){
			display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
			break;
		}
		else if ((turn == num + 1) && rescue == -1){
			rescue = 1;
			display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
			break;
		}
		else{
			display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
		}
		turn += 1;// turn
	}
}
