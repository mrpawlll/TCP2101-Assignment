#include <fstream>
#include <random>
#include <chrono>

// Function to generate a random integer between min and max (inclusive)
int randInt(int min, int max)
{
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// Function to generate a random adjacency matrix with n vertices and random edge weights
void generateRandomGraph(int n, ofstream &file)
{
    file << n << endl;

    string alphapet = "ABCDEFGHIJKLMNOPQRSTUPWXYZ";

    for (int i = 0; i < n && i < 26; i++)
    {
        file << i << " " << alphapet[i] << endl;
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (randInt(0, 1) == 1){
                int weight = randInt(1, 9);
                file << weight << " ";
            }else{
                file << "i" << " ";
            }
        }
        file << endl;
    }
}

int initGenerateRandomGraph()
{
    // Generate 5 random input files with various sizes
    for (int n : {10})  //  100, 1000, 10000, 100000
    {
        fs::create_directory("kruskalwithoutpq");
        
        string filename = "kruskalwithoutpq/kruskalwithoutpq_kruskalwithpq_am_" + std::to_string(n) + "_input.txt";
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Unable to open file " << filename << endl;
            return 1;
        }
        generateRandomGraph(n, file);
        file.close();
        cout << "File " << filename << " created successfully." << endl;
    }
    return 0;
}
