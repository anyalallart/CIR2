#include "objets.hpp"
#include <algorithm>
#include <sstream>

using namespace std;

vector<string> split(const string &str, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream token_stream(str);
    while (getline(token_stream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int rangedRand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}