#pragma once
#include <iostream>
#include <vector>
#include <utility>

enum MyEnum
{
	left,right,up,down
};



class field {

public:

	std::vector<std::vector<int>> myfield;
	int n;
	std::vector<std::pair<int, int>> cost_map;
	int depth;

	field(int num, std::vector<int> arr,int depth) {
		this->n = num;
		myfield.resize(n);
		this->depth = depth;
		for (int i = 0; i < n; i++) {
			myfield[i].resize(n);
			for (int j = 0; j < n; j++) {
				myfield[i][j]=arr[j + n * i];
			}
		}
		int temp = n * n ;
		cost_map.resize(temp);
		for (int si = 0; si < n; si++) {
			for (int sj = 0; sj < n; sj++) {
				cost_map[myfield[si][sj]].first = si;
				cost_map[myfield[si][sj]].second = sj;
			}
		}
		
	}

	void re_calculate() {
		int temp = n * n;
		for (int i = 1; i < temp; i++) {
			for (int si = 0; si < n; si++) {
				for (int sj = 0; sj < n; sj++) {
					cost_map[myfield[si][sj]].first = si;
					cost_map[myfield[si][sj]].second = sj;
				}
			}
		}
	}

	field* move(MyEnum dir) {

		field* temp = new field(*this);
		int i;
		int j;

		bool flag = true;
		for (i = 0; i < temp->n; i++) {
			if (!flag) {
				break;
			}
			for (j = 0; j < temp->n; j++) {
				if (temp->myfield[i][j] == 0) {
					flag = false;
					break;
				}
			}
		}
		i--;
		switch (dir) {
		case left:
			if (j == 0) {
				return nullptr;
			}
			else {
				std::swap(temp->myfield[i][j], temp->myfield[i][j - 1]);
				temp->depth++;
				temp->re_calculate();
				return temp;
			}
			break;
		case right:
			if (j == n-1) {
				return nullptr;
			}
			else {
				std::swap(temp->myfield[i][j], temp->myfield[i][j + 1]);
				temp->depth++;
				temp->re_calculate();
				return temp;
			}
			break;
		case up:
			if (i == 0) {
				return nullptr;
			}
			else {
				std::swap(temp->myfield[i][j], temp->myfield[i - 1][j]);
				temp->depth++;
				temp->re_calculate();
				return temp;
			}
			break;
		case down:
			if (i == n-1) {
				return nullptr;
			}
			else {
				std::swap(temp->myfield[i][j], temp->myfield[i + 1][j]);
				temp->depth++;
				temp->re_calculate();
				return temp;
			}


		}
	}
};

class status {
public:
	field* s;
	status* parent;
	int cost;
	int h;
	
	status(field* s,status* parent,field * dest) {
		this->s = s;
		this->parent = parent;
		calculate_cost(dest);
		h = cost + s->depth;
	}

	bool isFinal(field* dest) {
		for (int i = 0; i < s->n; i++) {
			for (int j = 0; j < s->n; j++) {
				if (dest->myfield[i][j] != s->myfield[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	void calculate_cost(field* dest) {
		int n = s->n;
		cost = 0;
		for (int i = 1; i <n*n; i++) {
			cost = cost + std::abs(s->cost_map[i].first - dest->cost_map[i].first) + std::abs(s->cost_map[i].second - dest->cost_map[i].second);
		}
	}

	bool isEqual(status* inList) {
		for (int i = 0; i < this->s->n; i++) {
			for (int j = 0; j < this->s->n; j++) {
				if (this->s->myfield[i][j] != inList->s->myfield[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
};

