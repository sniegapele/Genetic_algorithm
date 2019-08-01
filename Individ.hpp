#pragma once
#include <iostream>
#include <string>

const int LENGTH = 6;
const int POPULATION_SIZE = LENGTH * 4;

class individ {
	std::string word;
	int fitness; //counts zeroes, how many left to change
	void count_fitness();
public:
	individ(std::string word);
	void print();

	int get_fitness() const { return fitness; }
	std::string get_begin() const;
	std::string get_end() const;

	bool operator >= (const individ& other) const {
		return fitness >= other.fitness;
	}
};

individ::individ(std::string new_word) {
	word = new_word;
	fitness = 0;
	count_fitness();
}

void individ::count_fitness() {
	for (int i = 0; i < LENGTH; ++i) {
		if (word[i] == '0')
			fitness++;
	}
}

std::string individ::get_begin() const {
	std::string half = "";
	for (int i = 0; i < LENGTH / 2; ++i)
		half.push_back(word[i]);
	return half;
}

std::string individ::get_end() const {
	std::string half = "";
	for (int i = LENGTH/2; i < LENGTH; ++i)
		half.push_back(word[i]);
	return half;
}

void individ::print() {
	std::cout << word <<  std::endl;
}
