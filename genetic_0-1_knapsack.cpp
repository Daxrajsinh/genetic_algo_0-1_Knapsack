#include <bits/stdc++.h>
using namespace std;

struct Chromosome {
    vector<int> genes; // 0s and 1s (C1: 0 1 1 0 1 0 like that...)
    int fitness; // Fitness value based on total weight and value
};

int calculateFitness(const vector<pair<int, int>>& items, const vector<int>& genes, int capacity) {
    int totalWeight = 0, totalValue = 0;
    for (size_t i = 0; i < genes.size(); i++) {
        if (genes[i] == 1) {
            totalWeight += items[i].first;
            totalValue += items[i].second;
        }
    }
    // If over capacity, set fitness to low number (keeping 0).
    return (totalWeight <= capacity) ? totalValue : 0;
}

Chromosome createRandomChromosome(int n) {
    Chromosome chromosome;
    chromosome.genes.resize(n);
    for (int i = 0; i < n; i++) {
        chromosome.genes[i] = rand() % 2; // Randomly assign 0 or 1
    }
    return chromosome;
}

void evaluateFitness(vector<Chromosome>& population, const vector<pair<int, int>>& items, int capacity) {
    for (auto& chromosome : population) {
        chromosome.fitness = calculateFitness(items, chromosome.genes, capacity);
    }
}

vector<Chromosome> selectPopulation(const vector<Chromosome>& population) {
    vector<Chromosome> selected;

    // sum of fitness of each chromosome
    int totalFitness = accumulate(population.begin(), population.end(), 0,
                                   [](int sum, const Chromosome& c) { return sum + c.fitness; });
    
    // Select 4 chromosomes
    // I'm implementing ROULETTE WHEEL SELECTION.
    for (int i = 0; i < 4; i++) { 
        int randomValue = rand() % totalFitness;
        int runningSum = 0;
        
        for (const auto& chromosome : population) {
            runningSum += chromosome.fitness;
            if (runningSum >= randomValue) {
                selected.push_back(chromosome);
                break;
            }
        }
    }
    return selected;
}

Chromosome crossover(const Chromosome& parent1, const Chromosome& parent2) {
    Chromosome offspring;

    // any one point between the length of chromosome.
    int crossoverPoint = rand() % parent1.genes.size();
    offspring.genes.resize(parent1.genes.size());
    
   // I'M APPLYING ONE POINT CROSSOVER, So take bits from parent1 if left of the crossover point otherwise right for remaining ones.
    for (size_t i = 0; i < offspring.genes.size(); i++) {
        offspring.genes[i] = (i < crossoverPoint) ? parent1.genes[i] : parent2.genes[i];
    }  
    return offspring;
}

// Performing MUTATION to overcome the situation of getting stuck at Local Maxima. 
void mutate(Chromosome& chromosome) {
    //Keeping mutation rate 0.1, if less than this rate, Flip it otherwise not.
    const double mutationRate = 0.1;
    for (auto& gene : chromosome.genes) {
        if ((rand() / (double)RAND_MAX) < mutationRate) {
            gene = 1 - gene; // Randomly flipping the bit of any chromosome
        }
    }
}

int main() {
    srand(time(0));
    
    int n;
    cout << "Enter a number of items:\n";
    cin >> n;
    
    vector<pair<int, int>> items(n);
    
    for (int i = 0; i < n; i++) {
        int w, v;
        cout << "Enter a weight and value of Item " << i + 1 << ":\n";
        cin >> w >> v;
        items[i] = {w, v};
    }
    
    int capacity;
    cout << "Enter the capacity of a knapsack:\n";
    cin >> capacity;
    
    // Initialize population
    // Keeping no. of population = 4, currently.
    vector<Chromosome> population(4);
    for (int i = 0; i < population.size(); i++) {
        population[i] = createRandomChromosome(n);
    }
    
    // Pre decided creteria, like I'm keeping no. of generations to be 1000 then stop.
    const int generations = 1000;
    int bestFitness = 0;

    for (int gen = 0; gen < generations; gen++) {
        evaluateFitness(population, items, capacity);
        
        // Selection of chromosomes
        vector<Chromosome> selected = selectPopulation(population);
        
        // Calculate total fitness of selected chromosomes
        int totalFitnessOfSelected = accumulate(selected.begin(), selected.end(), 0,
                                                  [](int sum, const Chromosome& c) { return sum + c.fitness; });
        
        // // Print total fitness of selected chromosomes
        // cout << "Generation " << gen + 1 << ", Total fitness of selected chromosomes: " << totalFitnessOfSelected << endl;

        // Update best fitness
        for (const auto& chromo : selected) {
            if (chromo.fitness > bestFitness) {
                bestFitness = chromo.fitness;
            }
        }

        // Crossover and mutation
        vector<Chromosome> newPopulation;
        for (size_t i = 0; i < selected.size(); i += 2) {
            if (i + 1 < selected.size()) {
                Chromosome offspring1 = crossover(selected[i], selected[i + 1]);
                Chromosome offspring2 = crossover(selected[i + 1], selected[i]);
                
                mutate(offspring1);
                mutate(offspring2);
                
                newPopulation.push_back(offspring1);
                newPopulation.push_back(offspring2);
            }
        }
        population = newPopulation;
    }
    
    // Evaluate final population
    evaluateFitness(population, items, capacity);
    
    // Find the best solution
    Chromosome best = *max_element(population.begin(), population.end(),
                                   [](const Chromosome& a, const Chromosome& b) {
                                       return a.fitness < b.fitness;
                                   });
    
    cout << "Best solution found with total value: " << best.fitness << "\nItems included: ";
    for (size_t i = 0; i < best.genes.size(); i++) {
        if (best.genes[i] == 1) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
    return 0;
}
