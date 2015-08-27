#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
 public:
  vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites)
  {
    vector<int> order;
    
    vector<unordered_set<int>> prerequisites_of(numCourses);
    vector<vector<int>> neighbors_of(numCourses);
    for (auto p : prerequisites) {
      int prereq = p.second;
      int course = p.first;
      prerequisites_of[course].insert(prereq);
      neighbors_of[prereq].push_back(course);
    }
    
    // find roots
    vector<int> roots;
    for (int course = 0; course < numCourses; ++course) {
      if (prerequisites_of[course].size() == 0)
        roots.push_back(course);
    }
    if (roots.size() == 0)
      return order;
    
    vector<bool> visited(numCourses, false);
    while (roots.size() > 0) {
      int course = roots.back();
      roots.pop_back();
      order.push_back(course);
      
      for (size_t i = 0; i < visited.size(); ++i)
        visited[i] = false;
      
      for (int neighbor : neighbors_of[course]) {
        if (visited[neighbor])
          continue;
        visited[neighbor] = true;
        prerequisites_of[neighbor].erase(course);
        if (prerequisites_of[neighbor].size() == 0)
          roots.push_back(neighbor);
      }
    }
    
    for (const auto& p : prerequisites_of) {
      if (p.size() > 0)
        return vector<int>();
    }
    
    return order;
  }
};

int main() {
  Solution sol;
  
  auto numCourses = 4;
  vector<pair<int, int>> prerequisites{ {1,0}, {2,0}, {3,1}, {3,2} };
  
  /* auto numCourses = 3; */
  /* vector<pair<int, int>> prerequisites{ {0,1}, {0,2}, {1,2} }; */
  
  /* auto numCourses = 4; */
  /* vector<pair<int, int>> prerequisites{ {0,1},{3,1},{1,3},{3,2} }; */
  
  auto order = sol.findOrder(numCourses, prerequisites);
  for (auto course : order) {
    std::cout << "-> ";
    std::cout << course << " ";
  }
  std::cout << "\n";

  return 0;
}
