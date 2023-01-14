#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;



int main(){
  cout << "Enter the input file name: ";
  string input_filename;
  cin >> input_filename;
  ifstream input;
  input.open(input_filename.data());
  assert(input.is_open());
  cout << "Enter the output file name: ";
  string output_filename;
  cin >> output_filename;
  ifstream output;
  output.open(output_filename.data());
  assert(output.is_open());

  int num_vertices;
  int num_edges;
  input >> num_vertices;
  input >> num_edges;
  int num_colors;
  output >> num_colors;
  cout << "claimed colors: " << num_colors << endl;
  vector<vector<bool> > Edges(num_vertices);
  for(int i = 0; i < Edges.size(); i++)
    Edges[i].resize(num_vertices, false);
  
  for(int i = 0; i < num_edges; i++){
    int u,v;
    input>> u >> v;
    Edges[u][v] = true;
    Edges[v][u] = true;
  }
  vector<int> colors(num_vertices);
  
  for(int i = 0; i < num_vertices; i++){
    int color;
    output >> color;
    if(color >= num_colors || color < 0){
      cout << "ERROR: Color of vertex " << i << " is illegal: " << color;
    }
    colors[i] = color;
  }
  for(int i = 0; i < num_vertices; i++)
    for(int j = 0; j < num_vertices; j++){
      if(Edges[i][j] && colors[i] == colors[j])
	cout << "ERROR: The edge from " << i << " to " << j << " both have color << " << colors[i] << endl;
    }
  cout << "Done checking" << endl;
  return 0;
}