#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include <queue>
#include <stack>

#include "graph.h"

class TopologicalSort {
 public:
  // Perform topological sort on @G
  TopologicalSort(Graph& G);
  // Return true if at least one linear ordering exists
  bool HasOrdering();
  // Return possible linear ordering of all vertices
  std::vector<int> GetOrdering();

 private:
  // TODO (Q2.1): Add private data members

  std::vector<bool> visitedNodes;
  std::vector<int> inDegrees;
  std::vector<int> finalOrdering;
  // Hint: You need to track visited vertices, in-degrees, and the final
  // ordering

  // TODO (Q2.1): Implement helper functions
  void SetVisited(int v);
  bool IsVisited(int v);
  void FillInDegree(Graph& G);

  // TODO (Q2.2): Implement the main algorithm
  std::vector<int> LinearOrdering(Graph& G);
};

// TODO (Q2.3): Implement the constructor
// It should:
// 1. Initialize visited vector (all false)
// 2. Initialize indegree vector (all 0)
// 3. Call FillInDegree to compute in-degrees
// 4. Call LinearOrdering to perform topological sort
TopologicalSort::TopologicalSort(Graph& G)
    : visitedNodes(std::vector<bool>(G.V())),
      inDegrees(std::vector<int>(G.V())) {
  FillInDegree(G);
  finalOrdering = LinearOrdering(G);
}

// TODO (Q2.3): Implement HasOrdering()
// Return true if order is not empty
bool TopologicalSort::HasOrdering() {
  try {
    GetOrdering();
  } catch (std::logic_error& e) {
    return false;
  }

  return true;
}

// Throw an exception if there's no ordering (graph has a cycle)
// Otherwise return the order vector
std::vector<int> TopologicalSort::GetOrdering() {
  if (finalOrdering.size() == 0) {
    throw std::logic_error("no ordering is possible (graph has a cycle)");
  }

  return finalOrdering;
}

// Mark vertex v as visited
void TopologicalSort::SetVisited(int v) {
  // make sure visitedNodes is large enough
  if (visitedNodes.size() <= v) {
    visitedNodes.resize(v + 1);
  }

  visitedNodes.at(v) = true;
}

// Return whether vertex v has been visited
bool TopologicalSort::IsVisited(int v) {
  // if v doesn't exist in visitedNodes, it's unvisited
  if (visitedNodes.size() <= v) {
    return false;
  }

  return visitedNodes.at(v);
}

// For each vertex v in G:
//   For each adjacent vertex w of v:
//     Increment indegree[w]
void TopologicalSort::FillInDegree(Graph& G) {
  for (unsigned int i = 0; i < G.V(); ++i) {
    // adjacency lists are a list of every node the node is pointing to, so just
    // add one for every occurence of each pointed to node
    for (int adjacent : G.Adj(i)) {
      inDegrees.at(adjacent) += 1;
    }
  }
}

// TODO (Q2.2): Implement LinearOrdering(Graph G)
// 1. Create a queue and a sequence vector
// 2. Find all vertices with in-degree 0 and add them to queue
// 3. While queue is not empty:
//    a. Dequeue a vertex and add it to sequence
//    b. For each adjacent vertex:
//       - Decrement its in-degree
//       - If in-degree becomes 0, add to queue
// 4. If sequence size != number of vertices, return empty vector (cycle
// detected)
// 5. Otherwise return sequence
std::vector<int> TopologicalSort::LinearOrdering(Graph& G) {
  // 1. Create a queue and a sequence vector
  std::queue<int> queue;
  std::vector<int> seq;

  // 2. Find all vertices with in-degree 0 and add them to queue
  for (unsigned int i = 0; i < inDegrees.size(); ++i) {
    if (inDegrees.at(i) == 0) {
      queue.push(i);
    }
  }

  // return an empty vector if there's no 0-degree nodes
  if (queue.size() == 0) return seq;

  while (!queue.empty()) {
    // Dequeue a vertex and add it to sequence
    int v = queue.front();
    queue.pop();

    // decrement all adjacent indegrees
    for (int adj : G.Adj(v)) {
      inDegrees.at(adj) -= 1;

      // If in-degree becomes 0, add to queue
      if (inDegrees.at(adj) == 0) {
        queue.push(adj);
      }
    }

    seq.push_back(v);
  }

  // If sequence size != number of vertices, return empty vector (cycle
  // detected)
  if (seq.size() != G.V()) {
    return std::vector<int>(0);
  }

  // Otherwise return sequence
  return seq;
}

// TODO (Q2.4): What is the time complexity of this algorithm?
// Answer: The time complexity is O(V+E)

#endif