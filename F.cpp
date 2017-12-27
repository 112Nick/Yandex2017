#include <iostream>
#include <vector>
#include <algorithm>



struct Node {
    int index;
    Node* hillDestionation;
    std::vector<Node*> destinations;
    Node() {
        this->index = 0;
        this->hillDestionation = nullptr;
    }
    Node(int n) {
        this->index = n;
        this->hillDestionation = nullptr;
    }
    void addDestination(Node* n, bool isHill) {
        if (isHill) {
            this->hillDestionation = n;
        } else {
            this->destinations.push_back(n);
        }   
    }
};

int main() {
    int n, m, l, k; 
    std::cin >> n >> m >> l >> k;
    std::vector<Node> field(n + 1);
    std::vector<int> steps(k);
    
    for (int i = 1; i < n + 1; i++) {
        Node n(i);
        field[i] = n;
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        field[x].addDestination(& field[y], false);
    }

    for (int i = 0; i < l; i++) {
        int x, y;
        std::cin >> x >> y;
        field[x].addDestination(& field[y], true);
    }

    for (int i = 0; i < k; i++) {
        int x;
        std::cin >> x;
        steps[i] = x;
    }

    std::vector<Node*> currentPositions;
    std::vector<Node*> newPositions;
    currentPositions.push_back(& field[1]);
    for (int step = 0; step < steps.size(); step++) {
        for (int move = steps[step]; move > 0; move--) {
            for (int i = 0; i < currentPositions.size(); i++) {
                if (currentPositions[i]->destinations.empty()){
                    newPositions.push_back(currentPositions[i]); //TODO UNIQUE
                } else {
                    newPositions.insert(newPositions.end(), currentPositions[i]->destinations.begin(), currentPositions[i]->destinations.end());
                }
                
            }
            auto last = std::unique(newPositions.begin(), newPositions.end());
            newPositions.erase(last, newPositions.end()); 
            currentPositions = newPositions;
            newPositions.clear();
        }
        //TODO
        if(std::find(currentPositions.begin(), currentPositions.end(), &field[n]) != currentPositions.end()) {
            std::cout << step + 1 << std::endl;
            return 0;
        } 
        //Hills
        newPositions.clear();        
        for (int i = 0; i < currentPositions.size(); i++) {
            if (currentPositions[i]->hillDestionation != nullptr) {
                newPositions.push_back(currentPositions[i]->hillDestionation); //TODO UNIQUE
            } else {
                newPositions.push_back(currentPositions[i]);
            }
        }
        auto last = std::unique(newPositions.begin(), newPositions.end());
        newPositions.erase(last, newPositions.end()); 
        currentPositions = newPositions;
        newPositions.clear();
    }
    std::cout << -1 << std::endl;
    return 0;   
}