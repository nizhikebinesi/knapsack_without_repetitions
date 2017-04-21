#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <utility>


//#include <fstream>
//std::ofstream cout("output.txt");
using std::cout;
//using namespace std;
using std::cin;
using std::vector;
using std::pair;

#define EPS 1e-9

struct Element {
	int id,
		v,
		w;
	long double v_div_w;
};

struct SortElement {
	bool operator() (const Element &i, const Element &j) {
		if (fabs(i.v_div_w - j.v_div_w) < EPS) {
			if (i.v == j.v) {
				return i.w < j.w;
			}
			return i.v > j.v;
		}
		return i.v_div_w > j.v_div_w;
	}
} x_sort;

struct CompElementByCost {
	bool operator() (const Element &i, const Element &j) {
		if (i.v == j.v) {
			return i.w < j.w;
		}
		return i.v < j.v;
	}
} y_comp;

int greedy_method(int W, vector<int> w, vector<int> v) {
	vector<Element> w_prime(w.size());
	for (size_t i = 0; i < w.size(); i++) {
		w_prime[i].id = i;
		w_prime[i].v = v[i];
		w_prime[i].w = w[i];
		w_prime[i].v_div_w = 0.0 + (double) v[i] / w[i];
	}
	sort(w_prime.begin(), w_prime.end(), x_sort);
	bool one_element = false;
	vector<Element>::iterator maximum = max_element(w_prime.begin(), w_prime.end(), y_comp);
	int F1 = 0, F2 = (*maximum).w > W ? 0 : (*maximum).v, F, id = 0, W1 = 0;
	for (size_t i = 0; i < w_prime.size(); i++) {
		if (W1 < W) {
			F1 += w_prime[i].v;
			W1 += w_prime[i].w;
			id = i;
		}
		else {
			break;
		}
	}
	cout << "F1 = " << F1 << "\nF2 = " << F2 << "\n";
	if (F1 >= F2) {
		cout << "ELEMENTS WITH ID:\n";
		for (size_t i = 0; i <= id; i++) {
			cout << (w_prime[i].id + 1) << " ";
		}
		cout << "\n";
		F = F1;
	}
	else {
		cout << "ID OF MAXIMUM ELEMENT:\n" << ((*maximum).id + 1) << "\n";
		F = F2;
	}
	cout << "F = " << F << "\n";
	return F;
}

int optimal_weight(int W, vector<int> w, vector<int> v) {
	w.insert(w.begin(), 0);
	v.insert(v.begin(), 0);
	vector< vector< pair<int, int> > > value(W + 1, vector< pair<int, int> >(w.size(), pair<int, int>(0, 0)));

	for (int i = 1; i < w.size(); i++) {
		for (int ww = 1; ww <= W; ww++) {
			value[ww][i].first = value[ww][i - 1].first;
			value[ww][i].second = 0;
			if (w[i] <= ww) {
				int val = value[ww - w[i]][i - 1].first + v[i];
				if (value[ww][i].first < val) {
					value[ww][i].first = val;
					value[ww][i].second = 1;
				}
			}
		}
	}
	cout << "\n\nWEIGHTS:\n";
	cout << "  ";
	for (int j = 0; j < value[0].size(); j++) {
		cout << j << " ";
	}
	cout << "\n";
	for (int i = 0; i < value.size(); i++) {
		cout << i << " ";
		for (int j = 0; j < value[0].size(); j++) {
			cout << value[i][j].first << " ";
		}
		cout << "\n";
	}

	cout << "\n\nTAKE THIS ELEMENT?:\n";
	cout << "  ";
	for (int j = 0; j < value[0].size(); j++) {
		cout << j << " ";
	}
	cout << "\n";
	for (int i = 0; i < value.size(); i++) {
		cout << i << " ";
		for (int j = 0; j < value[0].size(); j++) {
			cout << value[i][j].second << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";

	cout << "ID OF SOLUTION ELEMENTS:\n";
	int j = w.size() - 1, i = W;
	while (i != 0) {
		if (!!value[i][j].second) {
			cout << (j) << " ";
			i -= w[j];
		}
		j--;
	}
	cout << "\n";

	return value[W][w.size() - 1].first;
}

int main() {
	int n, W;
	cout << "A(Knapsack weight) = ";
	cin >> W;
	cout << W << "\n";
	cout << "n(Size of weight and value vectors) = ";
	cin >> n;
	cout << n << "\n";
	vector<int> w(n), v(n);
	cout << "a(Weight vector of subjects):\n";
	for (int i = 0; i < n; i++) {
		cin >> w[i];
		cout << w[i] << " ";
	}
	cout << "\n";
	cout << "c(Value vector of subjects):\n";
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		cout << v[i] << " ";
	}
	cout << "\n";
	cout << "RESULT = " << optimal_weight(W, w, v) << '\n';
	cout << "GREEDY RESULT = " << greedy_method(W, w, v) << "\n";
	return 0;
}