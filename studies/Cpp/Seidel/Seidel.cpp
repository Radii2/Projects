#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <random>

std::vector<double> Seidel(std::vector<std::vector<double>> A, std::vector<std::string> signs, std::vector<std::vector<double>> b, std::vector<double> goal_function) {
	std::vector<double> OPT(2, 0);
	// w przypadku gdy jest tylko jedna zmienna
	if (A[0].size() == 1) {
		/*
		for (int i = 0; i < A.size(); i++) {
			double result;
			if (A[i][0] == 0) {
				result = b[i][0]/A[i][1];
			}
			else {
				result = b[i][0] / A[i][0];
			}
			if (i == 0) {
				if (A[i][0] == 0) {
					OPT[1] = result;
				}
				else {
					OPT[0] = result;
				}
			}
			*/
		for (int i = 0; i < A.size();i++){
			if (A[i][0] != 0) {
				double result = 0;
				double tmp = b[i][0] / A[i][0];
				double value = tmp * goal_function[0];
				if (i == 0) {
					result = value;
					OPT[0] = tmp;
					OPT[1] = 0;
				}
				else {
					if (result < tmp) {
						result = value;
						OPT[0] = tmp;
						OPT[1] = 0;
					}
				}
			}
		}
		return OPT;
	}
	// w przypadku gdy jest tyle samo zmiennych co ograniczeñ
	std::vector<double> answers(A[0].size(), 0);
	if (b.size() == A[0].size()) {
		for (int i = 0; i < A.size(); i++) {
			if (A[i][i] != 1) {
				if (A[i][i] == 0) {
					for (int j = 0; j < A.size(); j++) {
						if (j != i && j > i && A[j][i] != 0) {
							std::swap(A[i], A[j]);
							std::swap(b[i], b[j]);
							break;
						}
					}
				}
				double k = std::pow(A[i][i], -1);
				for (int j = 0; j < A[i].size(); j++) {
					A[i][j] *= k;
				}
				b[i][0] *= k;	
			}
			if (i + 1 != A.size()) {
				for (int j = i + 1; j < A.size(); j++) {
					double k = A[i][i] * A[j][i];
					for (int l = 0; l < A[j].size(); l++) {
						A[j][l] = A[j][l] - (A[i][l] * k);
					}
					b[j][0] = b[j][0] - (b[i][0] * k);
				}
			}
		}
		answers[A.size() - 1] = b[b.size() - 1][0] / A[A.size() - 1][A.size()-1];
		for (int i = A.size() - 2; i >= 0; i--) {
			double sum = 0;
			for (int j = 0; j < A[i].size(); j++) {
				if (j != i) {
					sum += answers[j] * A[i][j];
				}
			}
			answers[i] = b[i][0] - sum;
		}
		for (int i = 0; i < OPT.size(); i++) {
			OPT[i] = answers[i];
		}
		return OPT;
	}

	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> distr(0, A.size() - 1);
	std::vector<std::vector<double>> Ai;
	std::vector<std::vector<double>> bi;
	std::vector<std::string> signsi;
	int index = distr(generator);
	for (int i = 0; i < A.size(); i++) {
		Ai.push_back(A[i]);
	}
	for (int i = 0; i < b.size(); i++) {
		bi.push_back(b[i]);
	}
	for (int i = 0; i < signs.size(); i++) {
		signsi.push_back(signs[i]);
	}

	Ai.erase(Ai.begin() + index);
	bi.erase(bi.begin() + index);
	signsi.erase(signsi.begin() + index);

	// x = Seidel(A - ai, b - bi, c)
	std::vector<double> x = Seidel(Ai, signsi, bi, goal_function);
	//warunek czy ax<=b
	if (signs[index] == "<=") {
		if ((x[0] * A[index][0] + x[1] * A[index][1]) <= b[index][0]) {
			return x;
		}
		else {
			std::vector<double> constraint{ (-1.0) * A[index][0] / A[index][1],b[index][0] / A[index][1] };
			for (int i = 0; i < Ai.size(); i++) {
				Ai[i][0] += constraint[0] * Ai[i][1];
				bi[i][0] += (-1.0) * constraint[1] * Ai[i][1];
				Ai[i].pop_back();

			}
			return Seidel(Ai, signsi, bi, goal_function);
		}
	}
	else if (signs[index] == ">=") {
		if ((x[0] * A[index][0] + x[1] * A[index][1]) >= b[index][0]) {
			return x;
		}
		else {
			std::vector<double> constraint{ (-1.0) * A[index][0] / A[index][1],b[index][0] / A[index][1] };
			for (int i = 0; i < Ai.size(); i++) {
				Ai[i][0] += constraint[0] * Ai[i][1];
				bi[i][0] += (-1.0) * constraint[1] * Ai[i][1];
				Ai[i].pop_back();

			}
			return Seidel(Ai, signsi, bi, goal_function);
		}
	}
}

// Funkcja sprawdza czy znaleziony punkt spe³nia wszystkie ograniczeniach (elementarne i nieelementarne)
bool check_point_if_is_valid(std::vector<std::vector<double>> A, std::vector<std::string> signs, std::vector<std::vector<double>> b, std::vector<double> point) {

	bool check = true;

	if (point[0] >= 0 && point[1] >= 0) {
		for (int k = 0; k < A.size(); k++) {
			if (signs[k] == "<=") {
				if (A[k][0] * point[0] + A[k][1] * point[1] <= b[k][0]) {
				}
				else {
					check = false;
				}
			}
			else {
				if (A[k][0] * point[0] + A[k][1] * point[1] >= b[k][0]) {
				}
				else {
					check = false;
				}
			}
		}
		if (check == true) {
			return true;
		}
	}
	return false;
}

// Funkcja sprawdza czy w ograniczeniach nieelementarnych jest tylko jedna zmienna
bool check_if_only_one_variable(std::vector<std::vector<double>> A) {
	bool check = true;
	if (A[0][0] == 0 || A[0][1] == 0) {
		for (int j = 0; j < A.size() - 2; j++) {
			if (A[j][0] != 0) {
				check = false;
			}
		}
		if (check == true) {
			return true;
		}
		for (int j = 0; j < A.size() - 2; j++) {
			if (A[j][1] != 0) {
				return false;
			}
		}
		return true;
	}
	return false;
}
// Funkcja odpowiedzialna za wykonanie x razy algorytm Seidla oraz zweyfikowanie czy otrzymany wynik spe³nia wszystkie ograniczenia (elementarne jak i nieelementarne) oraz wybranie najbardziej optymalnego wyniku
std::vector<double> Seidel_results(std::vector<std::vector<double>> A, std::vector<std::string> signs, std::vector<std::vector<double>> b, std::vector<double> goal_function) {
	std::vector<std::vector<double>> results{{0,0}};
	std::vector<double> final_result(2, 0);
	std::vector<double> point{2, 0};
	if (check_if_only_one_variable(A)) {
		if(A[0][0] != 0){
			for (int i = 0; i < A.size(); i++) {
				double result = 0;
				double tmp = b[i][0] / A[i][0];
				double value = tmp * goal_function[0];
				if (i == 0) {
					result = value;
					point[0] = tmp;
					point[1] = 0;
				}
				else {
					if (result < tmp) {
						result = value;
						point[0] = tmp;
						point[1] = 0;
					}
				}
			}
		}
		else {
			for (int i = 0; i < A.size(); i++) {
				double result = 0;
				double tmp = b[i][0] / A[i][1];
				double value = tmp * goal_function[1];
				if (i == 0) {
					result = value;
					point[1] = tmp;
					point[0] = 0;
				}
				else {
					if (result < tmp) {
						result = value;
						point[1] = tmp;
						point[0] = 0;
					}
				}
			}
		}
		std::cout << "Obszar nieograniczony\n";
		results.push_back(point);
	}
	else {
		for (int i = 0; i < 10; i++) {
			point = Seidel(A, signs, b, goal_function);
			if (check_point_if_is_valid(A, signs, b, point)) {
				std::cout << point[0] << " " << point[1] << "\n";
				results.push_back(point);
			}
		}
	}
	if (results.size() != 1) {
		double max = 0;
		bool check = true;
		for (int i = 0; i < results.size(); i++) {
			if (max < results[i][0] * goal_function[0] + results[i][1] * goal_function[1]) {
				max = results[i][0] * goal_function[0] + results[i][1] * goal_function[1];
				final_result[0] = results[i][0];
				final_result[1] = results[i][1];
			}
		}
		for (int k = 0; k < A.size(); k++) {
			if (A[k][1] < 0) {
				if (signs[k] == "<=") {
					if (A[k][0] * final_result[0] + A[k][1] * (final_result[1] + 100.0) <= b[k][0]) {
					}
					else {
						check = false;
					}
				}
				else {
					if (A[k][0] * final_result[0] + A[k][1] * (final_result[1] + 100.0) >= b[k][0]) {
					}
					else {
						check = false;
					}
				}
			}
			else {
				if (signs[k] == "<=") {
					if (A[k][0] * (final_result[0] + 100.0) + A[k][1] * final_result[1] <= b[k][0]) {
					}
					else {
						check = false;
					}
				}
				else {
					if (A[k][0] * (final_result[0] + 100.0) + A[k][1] * final_result[1] >= b[k][0]) {
					}
					else {
						check = false;
					}
				}
			}
		}
		if (check == true) {
			std::cout << "Obszar nieograniczony\n";
			std::cout << "nieskonczenie wiele rozwiazan\n";
		}
		return final_result;
	}
	else {
		std::cout << "\nBrak rozwiazan\n";
		final_result[0] = results[0][0];
		final_result[1] = results[0][1];
		return final_result;
	}
}

// Funkcja g³ówna - wprowadzenie problemu oraz wydrukowanie wyników
int main() {
	std::vector<double> OPT(2, 0);
	
	// Przyk³ad jedna zmienna - nieskoñczenie wiele rozwi¹zañ
	/*
	std::vector<double> goal_function{ 5, 0 };
	std::vector<std::vector<double>> A{ {-1, 0},{-2, 0},{1, 0}, {0,1} };
	std::vector<std::string> signs{"<=","<=",">=",">="};
	std::vector<std::vector<double>> b{ {-6},{4},{0},{0} };
	*/
	/*
	// Obszar nieograniczony OPT = [0.8, 0.6] wartoœæ: 0.4
	std::vector<double> goal_function{-1,2};
	std::vector<std::vector<double>> A{ {-2,1},{-1,-2},{1,0},{0,1} };
	std::vector<std::string> signs{">=","<=",">=",">="};
	std::vector<std::vector<double>> b{ {-1},{-2},{0},{0} };
	*/
	// Przyk³ad obszar ograniczony OPT = [5, 2] wartoœæ: 27
	/*
	std::vector<double> goal_function{5,1};
	std::vector<std::vector<double>> A{ {5,-2},{1,1},{1,0},{1,0},{0,1}};
	std::vector<std::string> signs{ ">=","<=","<=",">=",">="};
	std::vector<std::vector<double>> b{ {0},{7},{5},{0},{0} };
	*/
	/*
	// Przyk³ad TEST 1 ograniczony OPT = [0.5, 1] lub OPT = [1.5, 0] wartoœæ : 1.5
	std::vector<double> goal_function{ 1,1 };
	std::vector<std::vector<double>> A{ {6,2},{1,3},{2,1},{-2,1},{2,2},{1,0},{0,1} };
	std::vector<std::string> signs{ "<=","<=","<=","<=","<=",">=",">="};
	std::vector<std::vector<double>> b{ {24},{12},{4},{0},{3},{0},{0} };
	*/
	// Przyk³ad - brak rozwi¹zañ
	/*
	std::vector<double> goal_function{ 3,-2 };
	std::vector<std::vector<double>> A{ {1,1},{-2,-2}, {1,0},{0,1} };
	std::vector<std::string> signs{ "<=","<=",">=",">=" };
	std::vector<std::vector<double>> b{ {2},{-10},{0},{0} };
	*/
	/*
	// Przyk³ad TEST 2 ograniczony OPT = [1, 2] wartoœæ: 1
	std::vector<double> goal_function{ -1,1 };
	std::vector<std::vector<double>> A{ {-3,1},{2,1},{6,2},{-2,-2},{-2,1}, {1,0},{0,1} };
	std::vector<std::string> signs{ "<=","<=","<=","<=","<=",">=",">="};
	std::vector<std::vector<double>> b{ {4},{4},{24},{-3},{0},{0},{0}};
	*/
	
	// Przyk³ad TEST 3 nieskoñczenie wiele rozwi¹zañ
	std::vector<double> goal_function{ -1,1 };
	std::vector<std::vector<double>> A{ {-1,1},{-1,1},{-1,1}, {1,0},{0,1} };
	std::vector<std::string> signs{ "<=","<=","<=",">=",">=" };
	std::vector<std::vector<double>> b{ {1},{2},{3},{0},{0} };
	
	OPT = Seidel_results(A, signs,b, goal_function);
	std::cout << "Funkcja celu: " << goal_function[0] << "x" << " + " << goal_function[1] << "y";
	double max = 0;

	for (int i = 0; i < OPT.size(); i++) {
		max += OPT[i] * goal_function[i];
	}
	std::cout << "\n\n";
	for (int i = 0; i < A.size(); i++) {
		if (i == 0) {
			std::cout << "Ograniczenia nieelementarne:\n";
		}
		if (i == A.size() - 2) {
			std::cout << "Ograniczenia elementarne:\n";
		}
		std::cout << A[i][0] << "x + " << A[i][1] << "y " << signs[i] << " " << b[i][0] << "\n";
	}
	std::cout << "\nOPT = [ " << OPT[0] << ", " << OPT[1] << " ]\n\n";
	std::cout << "Wartosc max dla funkcji celu = " << max << "\n";
	return 0;
}

//rozwi¹zaæ problem punktów na osi X