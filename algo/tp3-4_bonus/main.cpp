#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <ctime>
#include <chrono>
using namespace std::chrono;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &v)
{
    os << "[";
    for(int i = 0; i < v.size(); ++i)
    {
        os << v[i];
        if(i != v.size() - 1)
            os << ", ";
    }
    os << "]\n";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T> &l)
{
    os << "[";
    for(auto e : l){
        os << e;
        if(e != l.back())
            os << ", ";
    }
    os << "]\n";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::stack<T> &s)
{
    std::stack<int> stack2;
    os << "[";
    while(!s.empty()){
        os << s.top();
        stack2.push(s.top());
        s.pop();
        if(s.size() != 0) os << ", ";
    }
    os << "]\n";
    while(!stack2.empty()) {
        s.push(stack2.top());
        stack2.pop();
    }
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::queue<T> &q)
{
    std::queue<int> q2;
    os << "[";
    while(!q.empty()){
        os << q.front();
        q2.push(q.front());
        q.pop();
        if(q.size() != 0) os << ", ";
    }
    os << "]\n";
    while(!q2.empty()) {
        q.push(q2.front());
        q2.pop();
    }

    return os;
}

template<typename T,typename S>
std::ostream& operator<<(std::ostream &monCrayon, const std::map <T,S> &m){
    for(auto it : m) monCrayon<<it.first<<" : "<<it.second<<"\n";
    return monCrayon;
}

template<typename T,typename S>
std::ostream& operator<<(std::ostream &monCrayon, const std::multimap <T,S> &mm){
    for(auto it : mm) monCrayon<<it.first<<" : "<<it.second<<"\n";
    return monCrayon;
}

template<typename T>
std::ostream& operator<<(std::ostream &monCrayon, const std::set <T> &s){
    int i = 0;
    for(auto it : s){
        monCrayon << it ;
        if(i != s.size()-1) monCrayon << ", ";
        i++;
    }
    monCrayon << "\n";
    return monCrayon;
}

template<typename T>
std::ostream& operator<<(std::ostream &monCrayon, const std::multiset<T> &ms){
    int i = 0;
    for(auto it : ms){
        monCrayon << it ;
        if(i != ms.size()-1) monCrayon << ", ";
        i++;
    }
    monCrayon << "\n";
    return monCrayon;
}


bool premier(int n){
    int i = 2;
    bool v = true;

    while (i <= sqrt(n) && v){
        if (n % i == 0){
            v = false;
        }
        i ++;
    }
    return v;
}

std::vector<int> aff_prem(int n){
    std::vector<int> tab;
    for (int i = 2; i < n; i++){
        if (premier(i)){
            tab.push_back(i);
        }
    }
    return tab;
}

void non_associatif(int t){
    std::vector<int> vector = aff_prem(t);
    std::list<int> list;
    std::stack<int> stack;
    std::queue<int> queue;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int nb_tour = 1;

    start = std::chrono::system_clock::now();
    for (auto i = 0; i < nb_tour; i++){
        while(vector.size()) {
            list.push_back(vector.back());
            vector.pop_back();
        }
        std::cout << list;

        while(list.size()) {
            stack.push(list.back());
            list.pop_back();
        }
        std::cout << stack;

        while(stack.size()) {
            queue.push(stack.top());
            stack.pop();
        }
        std::cout << queue;

        while(queue.size()) {
            vector.push_back(queue.front());
            queue.pop();
        }
        std::cout << vector;
    }
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "Pour non-associatif : finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}


void associatif(int t){
    std::vector<int> vector = aff_prem(t);
    std::set<int> set;
    std::map<int, int> map;
    std::multiset<int> multiset;
    std::multimap<int, int> multimap;
    std::chrono::time_point<std::chrono::system_clock> start2, end2;
    int nb_tour = 1;

    for (int & i : vector){
        set.insert(i);
    }

    start2 = std::chrono::system_clock::now();
    for (auto i = 0; i < nb_tour; i++){
        for(auto it = set.begin(); it != set.end();) {
            multiset.insert(*it);
            set.erase(it++ );
        }
        std::cout << multiset;

        int k= 0;
        for(auto it = multiset.begin(); it != multiset.end();) {
            map.insert({k, *it});
            multiset.erase(it++);
            k++;
        }
        std::cout << map;

        for(auto it = map.begin(); it != map.end();) {
            multimap.insert({it->first, it->second});
            map.erase(it++);
        }
        std::cout << multimap;

        for(auto it = multimap.begin(); it != multimap.end();) {
            set.insert(it->second);
            multimap.erase(it++);
        }
        std::cout << set;
    }
    end2 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
    std::time_t end_time2 = std::chrono::system_clock::to_time_t(end2);

    std::cout << "Pour associatif : finished computation at " << std::ctime(&end_time2)
              << "elapsed time: " << elapsed_seconds2.count() << "s\n";
}

void course_insertion(){
    int n = 100000;

    // mesure du temps pour les insertions dans un vecteur
    auto start = high_resolution_clock::now();
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        v.push_back(i);
    }
    auto stop = high_resolution_clock::now();
    auto duration_vector = duration_cast<microseconds>(stop - start);
    std::cout << "Temps d'insertion dans un vecteur : " << duration_vector.count() << " microsecondes" << std::endl;

    // mesure du temps pour les insertions dans une liste
    start = high_resolution_clock::now();
    std::list<int> l;
    for (int i = 0; i < n; i++) {
        l.push_back(i);
    }
    stop = high_resolution_clock::now();
    auto duration_list = duration_cast<microseconds>(stop - start);
    std::cout << "Temps d'insertion dans une liste : " << duration_list.count() << " microsecondes" << std::endl;

    // mesure du temps pour les insertions dans une pile
    start = high_resolution_clock::now();
    std::stack<int> s;
    for (int i = 0; i < n; i++) {
        s.push(i);
    }
    stop = high_resolution_clock::now();
    auto duration_stack = duration_cast<microseconds>(stop - start);
    std::cout << "Temps d'insertion dans une pile : " << duration_stack.count() << " microsecondes" << std::endl;

    // mesure du temps pour les insertions dans une file
    start = high_resolution_clock::now();
    std::queue<int> q;
    for (int i = 0; i < n; i++) {
        q.push(i);
    }
    stop = high_resolution_clock::now();
    auto duration_queue = duration_cast<microseconds>(stop - start);
    std::cout << "Temps d'insertion dans une file : " << duration_queue.count() << " microsecondes" << std::endl;
}

void course_suppression(){
    // Initialisation des containers avec des valeurs
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::list<int> l = {1, 2, 3, 4, 5};
    std::stack<int> s;
    for (int i = 1; i <= 5; i++) {
        s.push(i);
    }
    std::queue<int> q;
    for (int i = 1; i <= 5; i++) {
        q.push(i);
    }

    // Suppression des éléments dans les containers vector
    auto start = high_resolution_clock::now();
    while (!v.empty()) {
        v.pop_back();
    }
    auto end = high_resolution_clock::now();
    auto vec_time = duration_cast<microseconds>(end - start).count();
    std::cout << "Temps d'exécution pour vector : " << vec_time << " microseconds" << std::endl;

    // Suppression des éléments dans les containers list
    start = high_resolution_clock::now();
    while (!l.empty()) {
        l.pop_back();
    }
    end = high_resolution_clock::now();
    auto lst_time = duration_cast<microseconds>(end - start).count();
    std::cout << "Temps d'exécution pour list : " << lst_time << " microseconds" << std::endl;

    // Suppression des éléments dans les containers stack
    start = high_resolution_clock::now();
    while (!s.empty()) {
        s.pop();
    }
    end = high_resolution_clock::now();
    auto stk_time = duration_cast<microseconds>(end - start).count();
    std::cout << "Temps d'exécution pour stack : " << stk_time << " microseconds" << std::endl;

    // Suppression des éléments dans les containers queue
    start = high_resolution_clock::now();
    while (!q.empty()) {
        q.pop();
    }
    end = high_resolution_clock::now();
    auto que_time = duration_cast<microseconds>(end - start).count();
    std::cout << "Temps d'exécution pour queue : " << que_time << " microseconds" << std::endl;
}

int main() {
    course_insertion();
    course_suppression();
    return 0;
}