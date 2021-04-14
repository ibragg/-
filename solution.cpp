#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <iostream>

struct Card {
    explicit Card(int _value) : value(_value) {}

    int value; // от масти не зависит, кодировка карт тривиальная 1 - 6, 2 - 7, ... , 8 - король, 9 - туз
};

struct Deck {

    explicit Deck(std::vector<int> _deck) {
        deck = std::vector<Card>(9);
        for (int i = 0; i < 9; ++i) {
            deck[i] = Card(_deck[i]);
        }
    }

    std::vector<Card> deck;
    int size = 9;
};

struct Vertex {
    std::vector<Deck> vertex = std::vector<Deck>(8);
    int size = 8;

    explicit Vertex(std::vector<int> &mass) {
        for (int i = 0; i < 8; ++i) {
            int j = 0;
            std::vector<int> tmp(9, 0);
            while (j < 9) {
                tmp[j] = mass[8 * i + j];
                ++j;
            }
            vertex.emplace_back(tmp);
        }
    }


    std::vector<Vertex, char> GetNextVertices() const;


    //char для восстановления пути
    bool is_ans() {

    };

private:
    friend struct std::hash<Vertex>;

};

bool is_ans() {
    //проверка того является ли вершина выигрышной
}

bool operator<(std::pair<int, int> &v1, std::pair<int, int> &v2) {
    if (v1.first == v2.first)
        return v1.second < v2.second;
    return v1.first < v2.second;
}

bool operator==(const Vertex &v1, const Vertex &v2) {
    return v1.vertex == v2.vertex;
}

std::vector<Vertex, char> Vertex::GetNextVertices() const {

}


template<>
class std::hash<Vertex> {
public:

};


char number_of_chaos(std::vector<char> input) {

}

unsigned int heuristic(const Vertex &v) {
}

bool is_correct(Vertex vertex) {

}

std::string findsolution(std::vector<int> &input) {
    if (!is_correct(Vertex(input)))
        return "-1";
    if (Vertex(input).is_ans())
        return "";
    Vertex vertex(input);
    std::unordered_set<Vertex> visited;
    std::unordered_map<Vertex, std::pair<unsigned int, std::stack<Vertex>>> len;
    std::set<std::pair<unsigned int, Vertex>> qu;
    unsigned int l = heuristic(vertex) + 1;
    qu.insert(std::pair<unsigned int, Vertex>(l, vertex));
    len.insert(std::pair<Vertex, std::pair<unsigned int, std::stack<Vertex>>>(vertex,
                                                                              std::pair<unsigned int, std::stack<Vertex>>(
                                                                                      l, std::stack<Vertex>())));
    visited.insert(vertex.vertex);

    while (qu.size() != 0) {
        std::pair<unsigned int, Vertex> current = *(qu.begin());
        qu.erase(qu.begin());
        std::vector<std::pair<Vertex, char>> next = current.second.GetNextVertices();
        for (auto u : next) {
            l = heuristic(u.first) + len[u.first].second.size();
            if (visited.find(u.first) == visited.end()) {
                if (u.first.is_ans())
                    len[u.first].second.push(u.first);
                return "YES";
                qu.insert(std::pair<unsigned int, Vertex>(l, u.first));
                len.insert(std::pair<Vertex,
                std::pair<unsigned int, std::stack<Vertex>>(u.first,
                                                            std::pair<unsigned int, std::stack<Vertex>>(
                                                                    l, len[u.first].second.push(u.first))));
                visited.insert(u.first);
            } else if (len[u.first].first > l &&
                       qu.find(std::pair<unsigned int, Vertex>(len[u.first].first, u.first)) != qu.end()) {
                qu.erase(qu.find(std::pair<unsigned int, Vertex>(len[u.first].first, u.first)));
                len[u.first].first = l;
                len[u.first].second = len[u.first].second + u.second;
                qu.insert(std::pair<unsigned int, Vertex>(l, u.first));
            }
        }
    }
}

unsigned int
search(std::unordered_set<Vertex> &visited, const Vertex &v, const std::stack<Vertex> &way, unsigned int &bound,
       std::stack<Vertex> &seek_way) {
    visited.insert(v);
    unsigned int f = way.size() + heuristic(v);
    if (f > bound)
        return f;
    if (v.is_ans()) {
        seek_way = way;
        return -1;
    }
    unsigned int min = -2;
    std::vector<std::pair<Vertex, char>> next = v.GetNextVertices();
    for (auto u : next) {
        if (visited.find(u.first) == visited.end()) {
            unsigned int current = search(visited, u.first, way + u.second, bound, seek_way);
            if (current == -1)
                return -1;
            if (current < min || min == -2)
                min = current;
        }
    }
    visited.erase(visited.find(v));
    return min;
}


std::string idastar(std::vector<int> &input) {
    if (!is_correct(Vertex(input))
        return "NO";
    if (Vertex(input).is_ans())
        return "YES";
    Vertex vertex(input);
    unsigned int bound = heuristic(vertex);
    std::stack<Vertex> way;
    std::stack<Vertex> seek_way;
    while (true) {
        std::unordered_set<Vertex> visited;
        unsigned int current = search(visited, vertex, way, bound, seek_way);
        if (current == -1) {
            return "YES";
        }
        bound = current;
    }
}

int main() {
    std::vector<int> mass(72);
    for (int i = 0; i < 72; ++i) {
        int x;
        std::cin >> x;
        mass.push_back(x);
    }
    std::cout << findsolution(mass);
    return 0;

}
