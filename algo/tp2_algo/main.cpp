#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <chrono>

int dicho (std::vector<int> v, int val_rech, int taille){
    int min = 0;
    int max = taille;
    while(min < max) {
        int mid = (min + max)/2;
        if (v[mid] < val_rech){
            min = mid + 1;
        }
        else{
            max = mid;
        }
    }
    if (v[min] == val_rech){
        return min;
    }
    else{
        return -1;
    }
}

int dicho_2(std::vector<int> v, int val_rech){
    std::vector<int>::iterator min = v.begin();
    std::vector<int>::iterator max = v.end() - 1;
    while(min < max) {
        auto distance = std::distance(min, max) / 2;
        distance += std::distance(v.begin(), min);
        auto mid = v.begin() + distance;
        if (*mid < val_rech) {
            min = mid;
            std::advance(min, 1);
        } else {
            max = mid;
        }
    }
    if (*min == val_rech){
        return std::distance(v.begin(), min);
    }
    else{
        return -1;
    }
}

int main() {
    using namespace std::chrono;

    std::chrono::time_point<std::chrono::system_clock> start, end;



    std::srand(std::time(nullptr));
    std::vector<int> vect (1000000000, 0);
    for (int i =0; i < 1000000000; i++) {
        int b = rand() % 1000 + 1;
        vect.push_back(b);
    }

    vect[2] = 10;

    std::sort(vect.begin(), vect.end());

    start = std::chrono::system_clock::now();
    std::cout << dicho(vect, 10, 1000000000) << std::endl; //54.3381s
    //std::cout << dicho_2 (vect, 10) << std::endl; //0.00046s
    //std::cout << std::binary_search(vect.begin(), vect.end(), 10); //0.0003038s
    end = std::chrono::system_clock::now();

    /*for (auto i : vect){
        std::cout << i << std::endl;
    }*/




    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

}
