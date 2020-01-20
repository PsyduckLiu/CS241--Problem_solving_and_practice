#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include<cmath>

using namespace std;

const int Population_size = 100;
const int Chromosome_length = 16;
double rate_crossover = 0.7;
double rate_mutation = 0.3;
int iteration_num = 5000;

typedef struct Chromosome
{
	int bit[Chromosome_length];
	double value;
	double fitness;
	double rate_fit;
	double cumu_fit;
}chromosome;

void population_initialize(chromosome(&population_current)[Population_size]);
void decode(chromosome &population_current);
double objective_function(double x);
void fresh_property(chromosome(&population_current)[Population_size]);
void seletc_prw(chromosome(&population_current)[Population_size], chromosome(&population_next_generation)[Population_size], chromosome &best_individual);
void crossover(chromosome(&population_next_generation)[Population_size]);
void mutation(chromosome(&population_next_generation)[Population_size]);


int main()
{
	chromosome population_current[Population_size];
	chromosome population_next_generation[Population_size];
	chromosome best_individual;
	chromosome zeros_chromosome;

	int i = 0, j = 0;
	double average = 0.0;

	for (i = 0; i < Chromosome_length; i++) {
		zeros_chromosome.bit[i] = 0;
	}
	zeros_chromosome.fitness = 0.0;
	zeros_chromosome.value = 0.0;
	zeros_chromosome.rate_fit = 0.0;
	zeros_chromosome.cumu_fit = 0.0;
	best_individual = zeros_chromosome;

	for (i = 0; i < Population_size; i++) {
		population_current[i] = zeros_chromosome;
		population_next_generation[i] = zeros_chromosome;
	}

	population_initialize(population_current);
	fresh_property(population_current);

	for (i = 0; i < iteration_num; i++) {

		seletc_prw(population_current, population_next_generation, best_individual);
		crossover(population_next_generation);
		mutation(population_next_generation);
		fresh_property(population_next_generation);

		for (j = 0; j < Population_size; j++) {
			population_current[j] = population_next_generation[j];
			population_next_generation[j] = zeros_chromosome;
		}


       average += best_individual.value;
	   average = average/ (i+1);
	   cout<<"Generation:"<<i+1<<" the average x is:"<<average<<" the best fitness score is:"<<best_individual.fitness<<endl;
	   if (average > 11.08&&average < 11.10) break;
       else average=average*(i+1);
	}
	if (average > 11.08&&average < 11.10) average=average;
	else average=average/5000;

	cout << "x*=arg minx x*sinx ="<<average <<endl;
	
system("pause");

}

void population_initialize(chromosome(&population_current)[Population_size])
{
	int i = 0, j = 0;
	srand((unsigned)time(NULL));
	for (j = 0; j < Population_size; j++) {
		for (i = 0; i < Chromosome_length; i++) {
			population_current[j].bit[i] = rand() % 2;
		}
	}
}

void decode(chromosome &population_current) {
	int i = 0;
	population_current.value = 0;
	for (i = 0; i < Chromosome_length; i++)
		population_current.value += (double)pow(2, 15-i) * (double)population_current.bit[i];

	population_current.value = -1 + 16 * population_current.value / (pow(2, 16) - 1);


}

double objective_function(double x)
{

	double y;
	y = x * sin(x);
	return(y);

}

void fresh_property(chromosome(&population_current)[Population_size])
{
	int j = 0;
	double sum = 0;

	for (j = 0; j < Population_size; j++) {
		decode(population_current[j]);
		population_current[j].fitness = objective_function(population_current[j].value);
		if (population_current[j].fitness<0)
            sum = sum + population_current[j].fitness;
        else sum=sum;
	}

	if (population_current[0].fitness<0)
        population_current[0].rate_fit = population_current[0].fitness / sum;
    else population_current[0].rate_fit=0;
	population_current[0].cumu_fit = population_current[0].rate_fit;

	for (j = 1; j < Population_size; j++) {
    if (population_current[j].fitness<0)
        population_current[j].rate_fit = population_current[j].fitness / sum;
    else population_current[j].rate_fit=0;

    population_current[j].cumu_fit = population_current[j].rate_fit + population_current[j - 1].cumu_fit;
	}
}

void seletc_prw(chromosome(&population_current)[Population_size], chromosome(&population_next_generation)[Population_size]
	, chromosome &best_individual)
{
	int i = 0, j = 0;
	double rate_rand = 0.0;

	best_individual = population_current[0];
	srand((unsigned)time(NULL));

	for (i = 0; i < Population_size; i++) {
		rate_rand = (float)rand() / (RAND_MAX);
		if (rate_rand < population_current[0].cumu_fit)
			population_next_generation[i] = population_current[0];
		else {
			for (j = 0; j < Population_size; j++) {
				if (population_current[j].cumu_fit <= rate_rand && rate_rand < population_current[j + 1].cumu_fit) {
					population_next_generation[i] = population_current[j + 1];
					break;
				}
			}
		}
		if (population_current[i].fitness < best_individual.fitness)
			best_individual = population_current[i];
	}

}

void crossover(chromosome(&population_next_generation)[Population_size])
{
	int i = 0, j = 0;
	double rate_rand = 0.0;
	short int bit_temp = 0;
	int num1_rand = 0, num2_rand = 0, position_rand = 0;
	srand((unsigned)time(NULL));

	for (j = 0; j < Population_size; j++) {
		rate_rand = (float)rand() / (RAND_MAX);
		if (rate_rand <= rate_crossover) {
			num1_rand = (int)rand() % (Population_size);
			num2_rand = (int)rand() % (Population_size);
			position_rand = (int)rand() % (Chromosome_length - 1);
			for (i = position_rand; i < Chromosome_length; i++) {
				bit_temp = population_next_generation[num1_rand].bit[i];
				population_next_generation[num1_rand].bit[i] = population_next_generation[num2_rand].bit[i];
				population_next_generation[num2_rand].bit[i] = bit_temp;
			}
		}
	}
}

void mutation(chromosome(&population_next_generation)[Population_size])
{
	int position_rand = 0;
	int i = 0;
	double rate_rand = 0.0;
	srand((unsigned)time(NULL));

	for (i = 0; i < Population_size; i++) {
		rate_rand = (float)rand() / (RAND_MAX);
		if (rate_rand <= rate_mutation) {
			position_rand = (int)rand() % (Chromosome_length);
			if (population_next_generation[i].bit[position_rand] == 0)
				population_next_generation[i].bit[position_rand] = 1;
			else
				population_next_generation[i].bit[position_rand] = 0;

		}
	}
}

