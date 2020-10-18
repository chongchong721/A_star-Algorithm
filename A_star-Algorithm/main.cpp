#include <iostream>
#include "status.h"

std::vector<status*> statlist;
std::vector<status*> closed;
status* destination = nullptr;
void search(status* , field* );
void showRoute(std::vector<status*>);

int main() {
	int n;
	std::vector<int> init;
	std::vector<int> end;
	std::cout << "n*n?:" << std::endl;
	std::cin >> n;
	std::cout << "initial status:" << std::endl;
	for (int i = 0; i < n*n; i++) {
		int temp;
		std::cin >> temp;
		init.push_back(temp);
	}
	std::cout << "end status:" << std::endl;
	for (int i = 0; i < n*n; i++) {
		int temp;
		std::cin >> temp;
		end.push_back(temp);
	}

	field* fstart = new field(n, init, 0);
	field* fend = new field(n, end, 0x7FFFFFFF);

	status* s = new status(fstart, nullptr, fend);

	search(s, fend);
	if (destination == nullptr) {
		std::cout << "NOT Solvable" << std::endl;
	}
	else {
		status* temproute = destination;
		std::vector<status*> route;
		while (temproute != nullptr) {
			route.push_back(temproute);
			temproute = temproute->parent;
		}
		showRoute(route);
	}
	system("pause");

}

void search(status* stat, field* dest) {
	if (stat->isFinal(dest)) {
		destination = stat;
		return;
	}

	closed.push_back(stat);

	for (int i = 0; i < 4; i++) {
		field* temp;
		temp=stat->s->move((MyEnum)i);
		if (temp != nullptr) {
			status* tempStatus = new status(temp, stat, dest);
			bool flagPush = true;
			for (auto iterator = closed.begin(); iterator != closed.end(); iterator++) {
				if (tempStatus->isEqual(*iterator)) {
					flagPush = false;
					break;
				}
			}
			if (flagPush) {
				statlist.push_back(tempStatus);
			}
		}
	}

	status* temp;
	std::vector<status*>::iterator iter;
	int minh = 0x7FFFFFFF;
	for (auto iterator=statlist.begin(); iterator!=statlist.end(); iterator++) {
		if ((*iterator)->h < minh) {
			iter = iterator;
			minh = (*iterator)->h;
		}
	}

	temp = (*iter);
	statlist.erase(iter);
	search(temp, dest);

}
void showRoute(std::vector<status*> route) {
	std::reverse(std::begin(route), std::end(route));
	std::cout << "----------------------------------------------------------------------------" << std::endl;
	for (auto iterator = route.begin(); iterator != route.end(); iterator++) {
		for (int i = 0; i < (*iterator)->s->n; i++) {
			for (int j = 0; j < (*iterator)->s->n; j++) {
				std::cout << (*iterator)->s->myfield[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "----------------------------------------------------------------------------" << std::endl;
	}
}