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

void associatif(int t){
    std::vector<int> vector = aff_prem(t);
    std::list<int> list;
    std::stack<int> stack;
    std::queue<int> queue;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int nb_tour = 100;

    start = std::chrono::system_clock::now();
    for (auto i = 0; i < nb_tour; i++){
        while(vector.size()) {
            list.push_back(vector.back());
            std::cout << " vector to list " << vector.back() << std::endl;
            vector.pop_back();
        }
        while(list.size()) {
            stack.push(list.back());
            std::cout << " list to stack " << list.back() << std::endl;
            list.pop_back();
        }
        while(stack.size()) {
            queue.push(stack.top());
            std::cout << " stack to queue " << stack.top() << std::endl;
            stack.pop();
        }
        while(queue.size()) {
            vector.push_back(queue.front());
            std::cout << " queue to vector " << queue.front() << std::endl;
            queue.pop();
        }
    }
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "Pour non-associatif : finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}


void non_associatif(int t){
    std::vector<int> vector = aff_prem(t);
    std::set<int> set;
    std::map<int, int> map;
    std::multiset<int> multiset;
    std::multimap<int, int> multimap;
    std::chrono::time_point<std::chrono::system_clock> start2, end2;
    int nb_tour = 100;

    for (int & i : vector){
        set.insert(i);
        std::cout << " vector to set " << i << std::endl;
    }

    start2 = std::chrono::system_clock::now();
    for (auto i = 0; i < nb_tour; i++){
        for(auto it = set.begin(); it != set.end();) {
            multiset.insert(*it);
            std::cout << " set to multiset " << *it << std::endl;
            set.erase(it++ );
        }
        int k= 0;
        for(auto it = multiset.begin(); it != multiset.end();) {
            map.insert({k, *it});
            std::cout << " multiset to map " << *it << std::endl;
            multiset.erase(it++);
            k++;
        }
        for(auto it = map.begin(); it != map.end();) {
            multimap.insert({it->first, it->second});
            std::cout << " map to multimap " << it->second << std::endl;
            map.erase(it++);
        }
        for(auto it = multimap.begin(); it != multimap.end();) {
            set.insert(it->second);
            std::cout << " multimap to set " << it->second << std::endl;
            multimap.erase(it++);
        }
    }
    end2 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
    std::time_t end_time2 = std::chrono::system_clock::to_time_t(end2);

    std::cout << "Pour associatif : finished computation at " << std::ctime(&end_time2)
              << "elapsed time: " << elapsed_seconds2.count() << "s\n";
}


int main() {

    return 0;
}