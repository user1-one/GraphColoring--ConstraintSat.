#ifndef vertexInfo_h
#define vertexInfo_h
// For storing information related to vertices.
class vertexInfo{
public:
     vertexInfo(int s, int d, int v);
    // Saturation 
    int sat;

    // degree 
    int deg;
 
    // index of vertex.
    int vertex;
};
// constructor
vertexInfo::vertexInfo(int s, int d, int v){
  sat = s;
  deg = d;
  vertex = v;
}
#endif /* Vertexinfo_h */