#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

// создаю случайную родительскую перестановку
string create_permutation(int count) {
    string way = "12345";
    for (int i = 0; i < count; i++) {
        int x = rand() % count;
        x = x == i ? (x + 1) % count : x;
        swap(way[i], way[x]);
    }
    return way;
}

// вставляю гены вместо звездочек после первого обмена фрагментами (генами)
void insert_gens(string& child1, const string& sub, const string& child2, size_t pointer) {
    unordered_set<char> set_sub(sub.begin(), sub.end());
    for (char & i : child1) {
        if (i == '*') {
            while (set_sub.find(child2[pointer]) != set_sub.end())
                pointer = (pointer + 1) % child1.size();
            i = child2[pointer];
            pointer = (pointer + 1) % child1.size();
        }
    }
}

// обмен генами
void crossover(int par1, int par2, size_t size, vector<string>& population) {
    int left = rand() % size;
    int n = rand() % (size - left) + 1;

    string child1(size, '*'), child2(size, '*');
    string sub1 = population[par1].substr(left, n);     // создание фрагментов-
    string sub2 = population[par2].substr(left, n);     // внутри разделителей

    child1.replace(left, n, sub2);  // обмен этими фрагментами
    child2.replace(left, n, sub1);

    insert_gens(child1, sub2, population[par1], (left + 1) % size);
    insert_gens(child2, sub1, population[par2], (left + 1) % size);

    population[par1 + 4] = child1;  //увеличение популяции
    population[par2 + 4] = child2;
}

// нахождение дистанций до городов всей популяции
void distance(unordered_map<string, int>& distances, const vector<vector<int>>& graph,
              const vector<string>& population) {
    distances.clear();
    for(int i = 0; i < 8; i++) {
        distances[population[i]] = 0;
        for (int j = 0; j < population[i].size(); j++) {
            int index1 = population[i][j] - '0' - 1;
            int index2 = population[i][(j + 1) % graph.size()] - '0' - 1;
            distances[population[i]] += graph[index1][index2];
        }
    }
}

// мутация
void mutation(double prob, vector<string>& population) {
    if (rand() % 100 < prob * 100) {
        size_t size = population[0].size();
        int index = rand() % 7;                 // выбор случайной особи
        int left = rand() % (size - 1);         // выбор случайного гена
        swap(population[index][left], population[index][left + 1]);
    }
}

// основной метод генетического алгоритма
pair<string, int> travelling_genetic(const vector<vector<int>>& graph, int gens, double prob) {
    pair<string, int> min_way = {"*****", INT_MAX};

    for (int c = 0; c < 10; ++c) {                  //повторяю алгоритм 10 раз-
        vector<string> population(8);            // чтобы точно найти оптимальный ответ
        unordered_map<string, int> distances;
        for (int i = 0; i < 4; i++)
            population[i] = create_permutation(graph.size());   // случайные перестановки

        for (int i = 0; i < gens; ++i) {
            string pars = create_permutation(4);    // выбор случайных пар для скрещивания
            for (int j = 0; j < 4; j += 2)     // скрещивание
                crossover(pars[j] - '0' - 1, pars[j+1] - '0' - 1,
                          graph.size(), population);

            mutation(prob, population);                 // мутация
            distance(distances, graph, population);     // дистанция между городами
            sort(population.begin(), population.end(),  // удаление слабых особей-
                 [&distances](string& x1, string& x2)       // путем сортировки
                 -> bool {return distances[x1] < distances[x2];});
        }
        auto cur_min = *min_element(distances.begin(), distances.end());
        if (cur_min.second < min_way.second) // сохранение минимального пути
            min_way = cur_min;
    }
    return min_way;
}

int main() {
    srand(time(nullptr));
    vector<vector<int>> graph = {
            {0, 1, 7, 2, 8},
            {2, 0, 10, 3, 1},
            {7, 10, 0, 2, 6},
            {2, 3, 2, 0, 4},
            {8, 1, 6, 4, 0}
    };
    auto way = travelling_genetic(graph, 5, 0.01);
    cout << way.first << " " << way.second << endl;
    return 0;
}