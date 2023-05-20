#include <vector>

// Define a structure to represent an edge
struct Edge
{
    int u, v, weight;
};

struct Vertics
{
    int index;
    string name;
};

struct Graph
{
    vector<Edge> edges;
    vector<Vertics> vertics;
};

// Define a structure to represent a disjoint set
struct DisjointSet
{
    vector<int> parent, rank;

    // Constructor to initialize the disjoint set
    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Find the parent of a node in the disjoint set
    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    // Merge two sets in the disjoint set
    void merge(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] < rank[rootY])
            {
                swap(rootX, rootY);
            }
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY])
            {
                rank[rootX]++;
            }
        }
    }
};

struct LetterFrequency{
    char letter;
    int frequency;
};
