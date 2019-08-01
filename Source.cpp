#include <vector>
#include <time.h>
#include <algorithm>
#include "Individ.hpp"

using namespace std;

void create_population(vector<individ>& population);
string create_individ();
void sort(vector<individ>& population);
bool check_if_found(vector<individ>& population);
void grow_population(vector<individ>& population);
string create_child(individ first, individ second);
void mutate(string child);
void kill_individs(vector<individ>& population);

void print_population(vector<individ>& population) {
	for (int i = 0; i < population.size(); ++i)
		population[i].print();
}

int main() {
	srand(time(0));
	
	vector<individ> population;
	create_population(population);

	cout << "Population in the beginning:\n";
	print_population(population);
	
	int n = 0;
	while (true) {
		if (check_if_found(population))
			break;

		grow_population(population);
		kill_individs(population);
		++n;
	}
	cout << "Population in the end (generation: " << n << "):\n";
	print_population(population);
	population.clear();

	return 0;
}

void create_population(vector<individ>& population) {
	for (int i = 0; i < POPULATION_SIZE; ++i) {
		population.push_back(individ(create_individ()));
	}
	sort(population);
}

string create_individ() {
	string word = "";
	for (int i = 0; i < LENGTH; ++i) {
		int c = rand() % 2;
		if (c)
			word.push_back('1');
		else
			word.push_back('0');
	}
	return word;
}

void sort(vector<individ>& population) {
	for (int i = 0; i < population.size() - 1; ++i) {
		for (int j = i + 1; j < population.size(); ++j) {
			if (population[i] >= population[j])
				swap(population[i], population[j]);
		}
	}
}

bool check_if_found(vector<individ>& population) {
	if (population[0].get_fitness() > 0)
		return false;
	return true;
}

void grow_population(vector<individ>& population) {
	vector<individ> new_generation;

	for (int i = 0; i < POPULATION_SIZE - 1; ++i) {
		for (int j = i + 1; j < POPULATION_SIZE; ++j) {
			new_generation.push_back(create_child(population[i], population[j]));
			new_generation.push_back(create_child(population[j], population[i]));
		}
	}
	for (int i = 0; i < new_generation.size(); ++i)
		population.push_back(new_generation[i]);
	new_generation.clear();
}

string create_child(individ first, individ second) {
	string child = first.get_begin();
	child.append(second.get_end());
	if (rand() % 10 == 0)
		mutate(child);
	return child;
}

void mutate(string child) {
	int n = rand() % LENGTH;
	if (child[n] == '1')
		child[n] = '0';
	else
		child[n] = '1';
}

void kill_individs(vector<individ>& population) {
	sort(population);
	population.erase(population.begin() + POPULATION_SIZE, population.end());
}