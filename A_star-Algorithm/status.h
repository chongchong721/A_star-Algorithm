#pragma once
#include <iostream>
#include <vector>

enum MyEnum
{
	left,right,up,down
};

class status {
	
};

class field {
public:

	std::vector<std::vector<int>> myfield;
	int n;

	field(int n,int* arr) {
		n = this->n;
		for (int i = 0; i < n; i++) {
			myfield[i].resize(n);
			for (int j = 0; j < n; j++) {
				myfield[i].push_back(arr[j + n * i]);
			}
		}
	}

	field move(MyEnum dir) {

		field temp = *this;
		int i, j;
		switch (dir) {
		case left:
			for (i = 0; i < temp.n; i++) {
				for (j = 0; j < temp.n; j++) {
					if (temp.myfield[i][j] == 0) {
						break;
					}
				}
			}

		}
	}
};