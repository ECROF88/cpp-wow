#include "mycommon.h"

using namespace std;

class Vertex
{
public:
  int id;
  int weight;
  Vertex(int id, int weight) : id(id), weight(weight) {}
  Vertex(int id) : id(id), weight(0) {}
  Vertex() : id(0), weight(0) {}
  bool operator<(const Vertex &v) const { return weight < v.weight; }
  bool operator>(const Vertex &v) const { return weight > v.weight; }
  bool operator==(const Vertex &v) const { return weight == v.weight; }
  bool operator!=(const Vertex &v) const { return weight != v.weight; }
  bool operator<=(const Vertex &v) const { return weight <= v.weight; }
  bool operator>=(const Vertex &v) const { return weight >= v.weight; }
};
class GraphAdjlist
{
public:
  bool isDirected;
  unordered_map<Vertex *, vector<Vertex *>> adjlist;
  GraphAdjlist(const vector<vector<Vertex *>> &edges) : isDirected(true)
  {
    for (vector<Vertex *> edge : edges)
    {
      addVertex(edge[0]);
      addVertex(edge[1]);
      if (isDirected)
        addEdge(edge[0], edge[1]);
      else
      {
        addEdge(edge[0], edge[1]);
        addEdge(edge[1], edge[0]);
      }
    }
  }

  void addEdge(Vertex *v1, Vertex *v2)
  {
    if (adjlist.count(v1) == 0 || adjlist.count(v2) == 0)
      throw invalid_argument("Vertex not in graph");
    else if (v1 == v2)
      throw invalid_argument("Self loop is not allowed");

    adjlist[v1].push_back(v2);
    adjlist[v2].push_back(v1);
  }
  void addVertex(Vertex *v)
  {
    if (adjlist.find(v) == adjlist.end())
      adjlist[v] = vector<Vertex *>();
    else
      return;
  }
  int sizeofVertex() { return adjlist.size(); }
  void print()
  {
    removeDuplicateEdges();
    cout << "size:" << sizeofVertex() << endl;
    for (auto it = adjlist.begin(); it != adjlist.end(); it++)
    {
      cout << it->first->id << " : ";
      for (Vertex *v : it->second)
      {
        cout << v->id << " ";
      }
      cout << endl;
    }
  }

  // 删去重复的边
  void removeDuplicateEdges()
  {
    for (auto it = adjlist.begin(); it != adjlist.end(); it++)
    {
      sort(it->second.begin(), it->second.end());
      it->second.erase(unique(it->second.begin(), it->second.end()), it->second.end());
    }
  }
  void bfs(Vertex *start)
  {
    unordered_set<Vertex *> visited = {start};  // 先把起始点加入到visited中
    queue<Vertex *> q;
    q.push(start);
    while (!q.empty())
    {
      Vertex *vet = q.front();
      q.pop();
      cout << vet->id << " ";
      for (Vertex *v : adjlist[vet])
      {
        if (visited.count(v) == 0)
        {
          visited.insert(v);
          q.push(v);
        }
      }
    }
  }
  void dfshelper(Vertex *start, unordered_set<Vertex *> &visited)
  {
    // cout << start->id << " ";
    visited.insert(start);
    for (Vertex *v : adjlist[start])
    {
      if (visited.count(v) == 0)
      {
        dfshelper(v, visited);
      }
    }
    cout << start->id << " ";  // 如果放在这里，就是后序遍历
  }
  void dfs(Vertex *start)
  {
    unordered_set<Vertex *> visited;
    dfshelper(start, visited);
  }
  Vertex *returnrandomVertex()
  {
    srand(time(0));
    int index = rand() % adjlist.size();
    cout << "index: " << index << endl;
    auto it = adjlist.begin();
    advance(it, index);
    return it->first;
  }
};

int main()
{
  cout << "cpp版本: " << __cplusplus << endl;
  vector<vector<Vertex *>> edges;
  Vertex *v1 = new Vertex(1);
  Vertex *v2 = new Vertex(2);
  Vertex *v3 = new Vertex(3);
  Vertex *v4 = new Vertex(4);
  Vertex *v5 = new Vertex(5);
  Vertex *v6 = new Vertex(6);
  edges.push_back({v1, v2});
  edges.push_back({v1, v3});
  edges.push_back({v2, v4});
  edges.push_back({v2, v5});

  GraphAdjlist graph(edges);
  graph.print();

  cout << "BFS: ";
  graph.bfs(v1);
  cout << endl;
  cout << "DFS: ";
  graph.dfs(v1);
  return 0;
}