#include <algorithm>
#include <regex>

/*
Let's go over the code step by step:

1. We define a struct `Edge` to represent an edge in the graph. It has three fields `u`, `v`, and `weight`,
which represent the two endpoints of the edge and its weight.

2. We define a struct `DisjointSet` to represent a disjoint set data structure. It has two vectors `parent` and `rank`,
which represent the parent of each node in the disjoint set and the rank of each node, respectively. We also define two member
functions `find` and `merge`, which are used to find the parent of a node and merge two sets, respectively.

3. We define a function `readInput` to read input from a file. It takes a filename as an argument and returns a vector of edges.
We first open the input file and check if it's successfully opened. Then we read the number of vertices from the first line of the file,
and subsequently read each edge with its weight from the subsequent lines of the file. Finally, we close the input file and return the vector of edges.

4. We define a function `writeOutput` to write output to both a file and the screen. It takes two arguments:
a vector of edges representing the minimum spanning tree, and a filename to write the output to.
We first open the output file and check if it's successfully opened. Then we iterate over each edge in the minimum spanning tree,
write its two endpoints and weight to the output file, and compute the total weight of the minimum spanning tree. Finally,
we write the total weight of the minimum spanning tree to the output file and close it. We also write the minimum spanning tree
and its total weight to the screen.

5. We define the main function, which reads input from a file using `readInput`, finds the minimum spanning tree using `kruskal`,
and writes output to both a file and the screen using `writeOutput`.

6. We define a function `kruskal` to find the minimum spanning tree using Kruskal's algorithm.
It takes two arguments: a vector of edges, and the number of vertices in the graph.
We first create a disjoint set object `dsu` with `n` nodes. Then, we sort the edges in increasing order of weight using a lambda function as the comparator.
We iterate over each edge in the sorted order, and if its two endpoints are not in the same set, we merge the sets using `dsu.merge` and add the edge to the minimum spanning tree.
Finally, we return the minimum spanning tree.
*/



vector<Edge> adjacencyMatrixToList(const vector<vector<int>> &matrix)
{
    int n = matrix.size();
    vector<Edge> edges;

    for (int i = 0; i < n; i++)
    {
        vector<int> y = matrix[i];
        for (int j = 0; j < y.size(); j++)
        {
            if(matrix[i][j] == 0) continue;
            edges.push_back({i, j, matrix[i][j]});
        }
    }

    return edges;
}

// Function to read input from a file
Graph readInput(string filename)
{
    Graph graph;

    ifstream fin(filename);
    if (!fin)
    {
        cout << "Error: Unable to open input file!" << endl;
        exit(1);
    }
    int n;
    fin >> n;

    // store vertices index and names

    for (int i = 0; i < n; i++)
    {
        int index;
        string name;
        fin >> index >> name;
        graph.vertics.push_back({i, name});
    }

    // load adjecency matrix

    vector<vector<int>> adjacencyMatrix;
    for (std::string line; std::getline(fin, line);)
    {
        vector<int> out;
        tokenize(line, " ", out);
        adjacencyMatrix.push_back(out);
    }

    // convert adjecency matrix to list

    graph.edges = adjacencyMatrixToList(adjacencyMatrix);

    fin.close();
    return graph;
}

// Function to write output to a file and the screen
void writeOutput(vector<Edge> MST, string filename, int counter, std::chrono::system_clock::time_point start)
{
    ofstream fout(filename);
    if (!fout)
    {
        cout << "Error: Unable to open output file!" << endl;
        exit(1);
    }
    int totalWeight = 0;

    fout << counter << endl;

    for (int i = 0; i < counter; i++)
    {
        fout << i << " " << getVertixName(i) << endl;
    }    

    for (Edge edge : MST)
    {
        fout << getVertixName(edge.u) << " " <<  getVertixName(edge.v) << " " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    fout << "Total weight of MST: " << totalWeight << endl;

    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end - start;

    fout << "Total Time taken of MST: " << duration.count() << "s" << endl;

    fout.close();

}

// Kruskal's algorithm to find the minimum spanning tree
vector<Edge> kruskal(vector<Edge> &edges, int n)
{
    DisjointSet dsu(n);
    vector<Edge> MST;
    // Sort edges in increasing order of weight
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.weight < b.weight; });
    for (Edge edge : edges)
    {
        if (dsu.find(edge.u) != dsu.find(edge.v))
        {
            dsu.merge(edge.u, edge.v);
            MST.push_back(edge);
        }
    }
    return MST;
}

int extractNumber(const std::string& text) {
    std::regex numberRegex("\\d+");
    std::smatch match;

    if (std::regex_search(text, match, numberRegex)) {
        return std::stoi(match[0]);
    }

    // Return a default value (or throw an exception) if no number is found
    return -1;
}

int initKruskal()
{
    // Read input from a file
    const string path = "kruskalwithoutpq";
    for (auto &entry : fs::directory_iterator(path))
    {
        std::chrono::system_clock::time_point start = chrono::system_clock::now();

        string pathName = entry.path().string();
        int counter = extractNumber(pathName);

        Graph graph = readInput(pathName);
        int n = graph.edges.size();

        // Find the minimum spanning tree using Kruskal's algorithm
        vector<Edge> MST = kruskal(graph.edges, n);
        // Write output to a file and the screen

        fs::create_directory("kruskalwithoutpq_output");
        string filename = "kruskalwithoutpq_output/kruskalwithoutpq_am_" + std::to_string(counter) + "_output.txt";
        writeOutput(MST, filename, counter, start);
    }

    return 0;
}
