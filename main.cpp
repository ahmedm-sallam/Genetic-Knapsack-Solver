/*

   _____              _        _                   __  __
  / ____|     /\     | |      | |          /\     |  \/  |
 | (___      /  \    | |      | |         /  \    | \  / |
  \___ \    / /\ \   | |      | |        / /\ \   | |\/| |
  ____) |  / ____ \  | |____  | |____   / ____ \  | |  | |
 |_____/  /_/    \_\ |______| |______| /_/    \_\ |_|  |_|

    لا غالب الا الله
    Free Palestine
*/

/*
 * Ahmed Mohamed Sallam 20210614
 * Omar Walid Ahmed 20201126
 * Ahmed Alaa 20200029
 * */



#include <bits/stdc++.h>
using namespace std;

const long long Solutions = 100, Generations = 20, N = 5000 ,K=2;
vector<vector<bool>> chromosomes, offspring;
map<long long, long long> fitnessRepeated;
long long numOfItems, weight, itemsWeight[N], itemsValue[N], fitness[Solutions];

void initiPopulation() {
    chromosomes.resize(Solutions);
    for (long long i = 0; i < Solutions; ++i) {
        chromosomes[i].resize(numOfItems);
        for (long long j = 0; j < numOfItems; ++j) {
            long long r = rand() % 2;
            chromosomes[i][j] = r;
        }
    }
}

void calculateFitness() {
    fitnessRepeated.clear();
    long long totalFitness = 0,totalValue ,totalWeight ;
    for (long long i = 0; i < Solutions; ++i) {
        totalValue = 0, totalWeight = 0;
        for (long long j = 0; j < numOfItems; ++j) {
            if (chromosomes[i][j]) {
                totalWeight += itemsWeight[j];
                totalValue += itemsValue[j];
            }
        }
        if (totalWeight > weight) {
            while (totalWeight > weight) {
                long long r = 0;
                while (chromosomes[i][r] == 0)
                    r++;
                chromosomes[i][r] = 0;
                totalWeight -= itemsWeight[r];
                totalValue -= itemsValue[r];
            }
        }
        fitness[i] = totalValue;
        fitnessRepeated[fitness[i]]++;
        totalFitness += fitness[i];
    }
}

long long maxFitness() {
    long long maxF = -1 , index = -1;
    for (long long i = 0; i < Solutions; ++i) {
        if (maxF < fitness[i]) {
            maxF = fitness[i];
            index = i;
        }
    }
    return index;
}

void elitism() {
    //store the value in fitness ---->its index to make sort by the fitness
    vector<pair<long long,long long>>indexFitness;
    for (long long i = 0; i < Solutions; ++i) {
        indexFitness.push_back({fitness[i],i});
    }
    sort(indexFitness.begin(), indexFitness.end());
    reverse(indexFitness.begin(), indexFitness.end());
    for (long long i = 0; i < K; ++i) {
        //this give the offspring the best K chromosomes fitness
        offspring.push_back(chromosomes[indexFitness[i].second]);
    }
}

long long rankSelection() {
    //store the value in fitness ---->its index to make sort by the fitness
    multimap<long long,long long>indexFitness;
    for (long long i = 0; i < Solutions; ++i) {
        indexFitness.insert({fitness[i],i});
    }
    double r = ((double) rand() / (RAND_MAX)), sum = 0;
    long long i=1,sumOfAllRanks=(Solutions*(Solutions+1))/2;
    //form this we make the roulette_wheel
    for(auto it:indexFitness){
        sum += (double)i/sumOfAllRanks;
        if (sum > r)
            return it.second;
        i++;
    }
    return -1;
}

void mutation(vector<bool> &chromosome) {
    for (long long i = 0; i < numOfItems; ++i) {
        //mutation change with 0.005
        long long r = rand() % 200;
        if (r < 1)
            chromosome[i] = !chromosome[i];
    }
    offspring.push_back(chromosome);
}

void crossover(long long chromosomeIndex1, long long chromosomeIndex2) {
    long long r = rand() % numOfItems;
    vector<bool> chromosome1 = chromosomes[chromosomeIndex1];
    vector<bool> chromosome2 = chromosomes[chromosomeIndex2];
    for (long long i = 0; i < r; ++i)
        swap(chromosome1[i], chromosome2[i]);
    mutation(chromosome1);
    mutation(chromosome2);
}

void selection(){
    while (offspring.size() < Solutions) {
        long long chromosomeIndex1 = rankSelection();
        long long chromosomeIndex2 = rankSelection();
        crossover(chromosomeIndex1, chromosomeIndex2);
    }
}

void replacement() {
    //this is important to store the best k fittness values in the next generation
    elitism();
    //to get the selected parents
    selection();
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    srand(time(NULL));
    long long t,totalWeight=0,totalValue=0;
    cin >> t;
    vector<bool>selectedChromosome;
    for (long long i = 1; i <= t; ++i) {
        long long loops=0;
        offspring.clear();
        cin >> weight >> numOfItems;
        for (long long i = 0; i < numOfItems; ++i)
            cin >> itemsWeight[i] >> itemsValue[i];
        long long equalFitness = 0, generation_number = 0, max_cnt;
        initiPopulation();
        while (equalFitness < 100 && generation_number < Generations) {
            max_cnt = 0;
            if (generation_number) {
                chromosomes = offspring;
                offspring.clear();
            }
            calculateFitness();
            //to calculate if the all fitness of the solutions equal or not
            for (auto x: fitnessRepeated)
                max_cnt = max(max_cnt, x.second);
            equalFitness= max_cnt * 100 / Solutions;
            ++generation_number;
            // think if the percentage will be lost !!
            if (equalFitness < 100 && generation_number < Generations)
                replacement();
            loops++;
        }
        long long fittest_index = maxFitness();
        selectedChromosome=chromosomes[fittest_index];

        cout << "Test Case " << i << endl;
        cout<<"the weight and values: "<<endl;
        for (long long j = 0; j < numOfItems; ++j) {
            if(selectedChromosome[j]){
                totalWeight+=itemsWeight[j];
                cout<<itemsWeight[j]<<" "<<itemsValue[j]<<endl;
            }
        }
        cout<<"total weight : "<<totalWeight<<" "<<"totel value : "<<fitness[fittest_index]<<endl<<endl;
        //cout<<loops<<" "<<equalFitness<<endl;
    }
    return 0;
}