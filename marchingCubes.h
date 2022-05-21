#ifndef MARCHINGCUBES_H
#define MARCHINGCUBES_H
#include "struct.h"
#include <vector>
#include <algorithm>
#include <string>
#include <thread>
#include "qucksort.h"
#include "structs.h"

class marchingCubes{

    public:
        marchingCubes(vec3 pos, vec3 size); 
        virtual ~marchingCubes();
        void setPoint(vec3 pos, int val, int _material);
        void setIsoLevel(float iL);
        void setDebuging(bool a = true);
        void create();
        void recreate();
        bool edit(vec3 pos, float power, bool distroi, int _material);
        int setMaterial(GLuint ID);
        std::string CompactToSend();
        int descompact_and_use(std::string s);
  //  private:

        float isolevel;
        vec3 Size;
        quicksort obj;
        vec3 Pos;
        int indice = 0;
        int materiais = 0;
        bool debug = false;
        std::vector<std::vector<std::vector<int> > > pontos;
        std::vector<vec3> vertices;
        std::vector<vec3> vertices2;
        std::vector<vec3> vNormals;
        std::vector<vec2> textureMap;
        std::vector<vec2> textureMap2;
        std::vector<int> indices;
        std::vector<int> indices2;
        std::vector<std::vector<std::vector<int> > > material;
        std::vector<int> vertMaterial;
        std::vector<int> vertMaterial2;
        std::vector<GLuint> materialID;

        void createCube(MC::gridBox box);
        void calcNormals();
        void weldVertices();
        vec3 SQRT(vec3 &a, vec3 &b);
        vec3 VertexInterp(float isolevel,vec3 p1,vec3 p2,float valp1,float valp2, int &_material);
        void drawMeshTri(vec3 cor);
        void createTexture();
};
