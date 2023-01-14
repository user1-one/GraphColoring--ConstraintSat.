#include <iostream>
#include <vector>
// Used for efficient sorting, and allowing to select the vertex to color in constant time
#include <set>
// Used for comparing Vertexes by degree of saturation
#include <tuple>
// used for file handling
#include <fstream>
// Defines vertex Class
#include "vertexInfo.h"

using namespace std;

// compares Vertexes by their saturation. Ties are broken by comparing degree then vertex number.
class CompareSat{
  public: 
    bool operator()(const vertexInfo &x, const vertexInfo &y) const{
      return tie(x.sat, x.deg, x.vertex) > tie(y.sat, y.deg, y.vertex);
    }
};
 // Function to add edge between two vertices, given a graph as an array of vectors
void addEdgeBetween(vector<int> graph[], int a, int b){
    graph[a].push_back(b);
    graph[b].push_back(a);
}

// Function for ColorGraph algo.
void ColorGraph(vector<int> graph[], vector<int>& color, int V){
    // prepare vector to store status of used colors.
    vector<bool> used;
    used.resize(V);
    for(int i=0; i< used.size(); i++)
        used[i]=false;
    // Prepare vector to store colors.
    color.resize(V);
    vector<int> Satur;
    Satur.resize(V);
    // Colors of adjacent vertices stored here
    vector<set<int>> AdjCols;
    AdjCols.resize(V);
    // Store the vertexes into a set in order of their saturation. initially empty
    set<vertexInfo, CompareSat> CompareSet;
    for (int i = 0; i < V; i++){
        color[i] = -1;
        Satur[i] = graph[i].size();
        AdjCols[i] = set<int>();
        CompareSet.emplace(vertexInfo(0, Satur[i], i));
    }
    int Cur_high =0; 
    while (!CompareSet.empty()) {
      // Get the index of the vertex with the most saturation
      Cur_high = CompareSet.begin()->vertex;
      CompareSet.erase(CompareSet.begin());
      for (int v : graph[Cur_high]){
        // if uncolored, prepare to color it 
        if (color[v] != -1)
          used[color[v]] = true;
      }
      int i = 0;
      while (i != used.size()){
        if (used[i] == false)
          break;
        i++;
      }
      for (int v : graph[Cur_high])
        if (color[v] != -1)
          used[color[v]] = false;
      color[Cur_high] = i;
      for (int v : graph[Cur_high]){
        if (color[v] == -1){
          CompareSet.erase({int(AdjCols[v].size()), Satur[v], v});
          AdjCols[v].insert(i);
          Satur[v]--;
          CompareSet.emplace(vertexInfo(int(AdjCols[v].size()), Satur[v], v));
        }
      }
    }
    
    return;
}
 

int main(){
  
    string filename;
    ifstream InputFile;
    ofstream OutputFile;
    cout << "File name: ";
    cin >> filename;
    InputFile.open(filename.data());

    while (!InputFile.is_open()) {
      cout << "Wrong filename! Please try again: ";
      InputFile.clear();
      cout << "File name: ";
      cin >> filename;
      InputFile.open(filename.data());
    }

    int temp;
    InputFile >> temp;
    int V = temp;
    InputFile >> temp;
    long int E = temp;
  // Used an array of vectors
    vector<int> graph[V];
    for (int i = 0; i < E; i++){ 
      int a, b;
      InputFile>> temp;
      a = temp;
      InputFile >> temp;
      b = temp;
      // Insert edge between the vertices.
      addEdgeBetween(graph, a, b);
    }
    InputFile.close();
  vector<int> color;
  ColorGraph(graph, color, V);
  // Put all the colors into a set
  // This easly sorts them and also makes sure no repeated entry happens
  set<int> ans;
    for (int i = 0; i < V; i++)
        ans.insert(color[i]);
   
  OutputFile.open("output-" + filename);
    OutputFile << ans.size() << endl;
    for (int i = 0; i < color.size(); i++) {
      OutputFile << color[i]  << " ";
    }

    return 0;
}
