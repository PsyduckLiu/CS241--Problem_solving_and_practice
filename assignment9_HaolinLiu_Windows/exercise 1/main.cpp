#include <iostream>
#include <time.h>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define mutation_rate 100 

class Population
{
public:
	struct Member {
		string dna;
		int fitness = 0;
	};

	Population(const string target_string, int population_size) {
		members = vector<Member>(population_size);

		for (int i = 0; i < members.size(); i++) {	
			members.at(i).dna.resize(target_string.size());

			for (int j = 0; j < target_string.size(); j++)
				members.at(i).dna.at(j) = (unsigned char)rand() % 96 + 32; 
			
			members.at(i).fitness = 0;
		}
	}

	vector<Member> members;
};

int main() {

	srand(time(NULL));
	bool match_complete = false;
	unsigned int generation = 0;
	const string target_string = "Hello, World! 19/11/09";
	Population population(target_string, 5000);

	while (!match_complete) {
		generation++;

		for (int i = 0; i < population.members.size(); i++) {
			population.members.at(i).fitness = 0;

			for (int j = 0; j < population.members.at(i).dna.size(); j++) {
				if (population.members.at(i).dna.at(j) == target_string.at(j))
					population.members.at(i).fitness += 10;
			}

			if (population.members.at(i).fitness == target_string.size() * 10) 
				match_complete = true;
		}

		sort(population.members.begin(), population.members.end(), [](Population::Member const &a, Population::Member &b) {
			return a.fitness > b.fitness;
		}
		);


		vector<Population::Member> parents { population.members.at(0), population.members.at(1) };

		for (int i = 0; i < population.members.size(); i++) {
			for (int j = 0; j < population.members.at(i).dna.size(); j++) {

				int parent_random_gen = rand() % parents.size();
				population.members.at(i).dna.at(j) = parents.at(parent_random_gen).dna.at(j);

				if (rand() % 1000 < mutation_rate)
					population.members.at(i).dna.at(j) = (unsigned char)rand() % 96 + 32; 
			}
		}

		cout << "Generation: " << generation  << "  String: " << parents.at(0).dna.c_str() << endl;

		if (generation > 5000) break;

	}

	cout << endl;
	cout << "Generation:  " << generation << " Evolved to the full string! " << endl;

    system("pause");
	return 0;

}
