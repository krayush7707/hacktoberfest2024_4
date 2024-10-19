#include <iostream>
#include <vector>

#include <unordered_set>

using namespace std;
#include <cmath>
void dfs(int currentCost, int index, vector<int>& toppingCosts, unordered_set<int>& possibleCosts) {
    if (index >= toppingCosts.size()) {
        possibleCosts.insert(currentCost);
        return;
    }
    
    // Consider current topping 0, 1 or 2 times
    dfs(currentCost, index + 1, toppingCosts, possibleCosts);
    dfs(currentCost + toppingCosts[index], index + 1, toppingCosts, possibleCosts);
    dfs(currentCost + 2 * toppingCosts[index], index + 1, toppingCosts, possibleCosts);
}

int closestCost(int n, int m, vector<int> &baseCosts, vector<int> &toppingCosts, int target) {
    unordered_set<int> possibleCosts;
    
    // Calculate all possible costs with the toppings
    dfs(0, 0, toppingCosts, possibleCosts);
    
    int closestCost = INT_MAX;
    int minDiff = INT_MAX;
    
    // Try every base cost combined with each possible topping cost
    for (int base : baseCosts) {
        for (int topping : possibleCosts) {
            int totalCost = base + topping;
            int diff = abs(totalCost - target);
            
            if (diff < minDiff || (diff == minDiff && totalCost < closestCost)) {
                closestCost = totalCost;
                minDiff = diff;
            }
        }
    }
    
    return closestCost;
}
