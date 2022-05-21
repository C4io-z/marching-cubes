#include "marching_cubes.h"

marchingCubes::marchingCubes(vec3 pos, vec3 size){
    for(int x = 0; x < size.x; x++){
        std::vector<std::vector<int> > a;
            for(int y = 0; y < size.y; y++){
                std::vector<int> b;
                for(int z = 0; z < size.z; z++){
                b.push_back(0);
            }
        a.push_back(b);
        }
    pontos.push_back(a);
    material.push_back(a);
    }
    Size = size;
    Pos = pos;
}
marchingCubes::~marchingCubes(){

}
void marchingCubes::setPoint(vec3 pos, int val, int _material){
    pontos[(int)pos.x][(int)pos.y][(int)pos.z] = val;
    material[(int)pos.x][(int)pos.y][(int)pos.z] = _material;
}
void marchingCubes::create(){
    if(debug){
        std::cout<< "criando malha..." << std::endl;
    }
    vertices2.clear();
    indices2.clear();
    vertMaterial2.clear();
    float time = (float)glfwGetTime();
    indice = 0;
    for(int x = 0; x < Size.x-1; x++){
        for(int y = 0; y < Size.y-1; y++){
            for(int z = 0; z < Size.z-1; z++){
                MC::gridBox box;
                box.points[0] = pontos[x  ][y  ][z  ];
                box.points[1] = pontos[x+1][y  ][z  ];
                box.points[2] = pontos[x+1][y+1][z  ];
                box.points[3] = pontos[x  ][y+1][z  ];
                box.points[4] = pontos[x  ][y  ][z+1];
                box.points[5] = pontos[x+1][y  ][z+1];
                box.points[6] = pontos[x+1][y+1][z+1];
                box.points[7] = pontos[x  ][y+1][z+1];
                box.material[0] = material[x  ][y  ][z  ];
                box.material[1] = material[x+1][y  ][z  ];
                box.material[2] = material[x+1][y+1][z  ];
                box.material[3] = material[x  ][y+1][z  ];
                box.material[4] = material[x  ][y  ][z+1];
                box.material[5] = material[x+1][y  ][z+1];
                box.material[6] = material[x+1][y+1][z+1];
                box.material[7] = material[x  ][y+1][z+1];
                box.p[0] = vec3(x  ,y  ,z  );
                box.p[1] = vec3(x+1,y  ,z  );
                box.p[2] = vec3(x+1,y+1,z  );
                box.p[3] = vec3(x  ,y+1,z  );
                box.p[4] = vec3(x  ,y  ,z+1);
                box.p[5] = vec3(x+1,y  ,z+1);
                box.p[6] = vec3(x+1,y+1,z+1);
                box.p[7] = vec3(x  ,y+1,z+1);
                createCube(box);
            }
        }
    }
    vertices = vertices2;
    indices = indices2;
    vertMaterial = vertMaterial2;
    time = (float)glfwGetTime()-time;
    if(debug){
        std::cout<< "malha criada em: " << time << " s" <<std::endl;
    }
    vertices2.clear();
    indices2.clear();
    vertMaterial2.clear();
}
void marchingCubes::createCube(MC::gridBox box){

    int index = 0;
    for(int i = 0; i < 8; i++){
        if(box.points[i] > isolevel){index |= (1<<i);}
    }
    if(index == 0 || index == 255){
        return;
    }
    for(int i = 0; MC::triTable[index][i] != -1; i+=3){
        int materials[3];
        int materials2[3];
        int scl = 1;
        vec3 a;
        a = VertexInterp(isolevel,box.p[MC::vertexA[MC::triTable[index][i]]],
                       box.p[MC::vertexB[MC::triTable[index][i]]],
                       box.points[MC::vertexA[MC::triTable[index][i]]],
                       box.points[MC::vertexB[MC::triTable[index][i]]],
                       materials[0]);
        vertices2.push_back((a+Pos)*scl);
        indices2.push_back(indice);
        indice++;
        a = VertexInterp(isolevel,box.p[MC::vertexA[MC::triTable[index][i+1]]],
                       box.p[MC::vertexB[MC::triTable[index][i+1]]],
                       box.points[MC::vertexA[MC::triTable[index][i+1]]],
                       box.points[MC::vertexB[MC::triTable[index][i+1]]],
                       materials[1]);
        vertices2.push_back((a+Pos)*scl);
        indices2.push_back(indice);
        indice++;
        a = VertexInterp(isolevel,box.p[MC::vertexA[MC::triTable[index][i+2]]],
                       box.p[MC::vertexB[MC::triTable[index][i+2]]],
                       box.points[MC::vertexA[MC::triTable[index][i+2]]],
                       box.points[MC::vertexB[MC::triTable[index][i+2]]],
                       materials[2]);
        vertices2.push_back((a+Pos)*scl);
        indices2.push_back(indice);
        indice++;
        if(materials[0] == 1){materials2[0] =  box.points[MC::vertexA[MC::triTable[index][i]]];}else if(materials[0] == 2){materials2[0] = box.points[MC::vertexB[MC::triTable[index][i]]];}
        if(materials[1] == 1){materials2[1] =  box.points[MC::vertexA[MC::triTable[index][i+1]]];}else if(materials[1] == 2){materials2[1] = box.points[MC::vertexB[MC::triTable[index][i+1]]];}
        if(materials[2] == 1){materials2[2] =  box.points[MC::vertexA[MC::triTable[index][i+2]]];}else if(materials[2] == 2){materials2[2] = box.points[MC::vertexB[MC::triTable[index][i+2]]];}
        if(materials2[0] >= materials2[1] && materials2[0] >= materials2[2]){
            if(materials[0] == 1){
                vertMaterial2.push_back(box.material[MC::vertexA[MC::triTable[index][i]]]);
            }else if(materials[0] == 2){
                vertMaterial2.push_back(box.material[MC::vertexB[MC::triTable[index][i]]]);
            }
        }else if(materials2[1] >= materials2[0] && materials2[1] >= materials2[2]){
            if(materials[1] == 1){
                vertMaterial2.push_back(box.material[MC::vertexA[MC::triTable[index][i+1]]]);
            }else if(materials[1] == 2){
                vertMaterial2.push_back(box.material[MC::vertexB[MC::triTable[index][i+1]]]);
            }
        }else if(materials2[2] >= materials2[1] && materials2[2] >= materials2[0]){
            if(materials[2] == 1){
                vertMaterial2.push_back(box.material[MC::vertexA[MC::triTable[index][i+2]]]);
            }else if(materials[2] == 2){
                vertMaterial2.push_back(box.material[MC::vertexB[MC::triTable[index][i+2]]]);
            }
        }
    }
}
void marchingCubes::calcNormals(){
    /*std::vector<vec3> vNormals2;
    vNormals2.clear();
    vNormals2.resize(vertices.size()+1);//*/
    vNormals.resize(vertices.size()+1);
    for(unsigned int i = 0; i < vNormals.size(); i++){
        vNormals[i] = vec3(0,0,0);
    }

    float time = 0;
    if(debug){
        std::cout<< "calculando normals..." << std::endl;
        time = (float)glfwGetTime();
    }
    vec3 normal;
    vec3 b;
    vec3 a;
    for(unsigned int i = 0; i < indices.size(); i += 3){
        b = SQRT(vertices[indices[i+1]],vertices[indices[i]]);
        a = SQRT(vertices[indices[i+2]],vertices[indices[i]]);
        normal.x = ((a.y*b.z)-(a.z*b.y));
        normal.y = ((a.z*b.x)-(a.x*b.z));
        normal.z = ((a.x*b.y)-(a.y*b.x));
        normal.normaliza();
        vNormals[indices[i]] = (vNormals[indices[i]]+normal);
        vNormals[indices[i]].normaliza();
        vNormals[indices[i+1]] = (vNormals[indices[i+1]]+normal);
        vNormals[indices[i+1]].normaliza();
        vNormals[indices[i+2]] = (vNormals[indices[i+2]]+normal);
        vNormals[indices[i+2]].normaliza();
    }
    if(debug){
        time = (float)glfwGetTime()-time;
        std::cout<< "normals calculadas em: " << time << " s" <<std::endl;
        std::cout<< "memoria total =" << ((vertices.size()*sizeof(vec3))+(indices.size()*sizeof(int))+(vNormals.size()*sizeof(vec3)))/1024 << "Kb" <<std::endl;
    }
    vNormals.clear();
}
vec3 marchingCubes::SQRT(vec3 &a, vec3 &b){
    vec3 c;
    c.x = (a.x-b.x);
    c.y = (a.y-b.y);
    c.z = (a.z-b.z);
    return c;
}
vec3 marchingCubes::VertexInterp(float isolevel,vec3 p1,vec3 p2,float valp1,float valp2, int &_material){
    if(valp1 > valp2){_material = 1;}else{_material = 2;}

    float mu;
    vec3 p;

    mu = (isolevel - valp1) / (valp2 - valp1);
    p = p2-p1;
    p = p*mu;
    return(p+p1);
}
void marchingCubes::setIsoLevel(float iL){
    isolevel = iL;
}
void marchingCubes::weldVertices(){
    float time;
    if(debug){
        std::cout<< "soldando a malha..." << std::endl;
        std::cout<< "tamanho inicial da malha: " << vertices.size() << " /---/ bytes usados: " << (vertices.size()*sizeof(vec3))/1024 << "Kb" <<std::endl;
    }
    time = (float)glfwGetTime();
    obj.elements = vertices;
    obj.indices = indices;
    obj.startIndex();
    obj.Quicksort();
    obj.setIndex();
    vertices = obj.elements;
    indices = obj.indices;//*/
    time = (float)glfwGetTime()-time;
    std::cout<< vertices.size() <<std::endl;
    if(debug){
        std::cout<< "malha soldada em: " << time << " s" <<std::endl;
        std::cout<< "tamanho final da malha: " << vertices.size() << " /---/ bytes usados: " << (vertices.size()*sizeof(vec3))/1024 << "Kb" <<std::endl;
        std::cout<< "faces: " << indices.size() << vertices.size() << "/---/ bytes usados: " << (indices.size()*sizeof(int))/1024 << "Kb" <<std::endl;
    }
}
void marchingCubes::setDebuging(bool a){
    debug = a;
}
bool marchingCubes::edit(vec3 pos, float power, bool distroi, int _material){
    pos = pos-Pos;
    vec3 dist;
    int t = 3;
    bool editado = false;
        for(int x = pos.x-power-t; x < pos.x+power+t; x++){
            for(int y = pos.y-power-t; y < pos.y+power+t; y++){
                for(int z = pos.z-power-t; z < pos.z+power+t; z++){
                    if(x < 0 || x > Size.x-1 || y < 0 || y > Size.y-1 || z < 0 || z > Size.z-1){continue;}
                    dist = vec3(x,y,z) - pos;
                    if(dist.mag() < power+1){
                        if(distroi){
                            if(pontos[x][y][z] > isolevel && pontos[x][y][z] > (dist.mag()/power) * isolevel){
                                pontos[x][y][z] = (dist.mag()/power) * isolevel;
                                editado = true;
                            }
                        }else{
                        if(pontos[x][y][z] < isolevel && pontos[x][y][z] < isolevel*2 - ((dist.mag()/power)*isolevel)){
                                pontos[x][y][z] = isolevel*2 - ((dist.mag()/power)*isolevel);
                                material[x][y][z] = _material;
                                editado = true;
                        }
                    }
                }
            }
        }
    }
    return editado;
}
void marchingCubes::recreate(){
    float time2 = (float)glfwGetTime();
    create();
    weldVertices();
    calcNormals();
    createTexture();
    time2 = (float)glfwGetTime()-time2;
    std::cout<< 1/time2 <<std::endl;
}
void marchingCubes::drawMeshTri(vec3 cor){
    int materialAnt = -1;
    glBegin(GL_TRIANGLES);
    for(unsigned int i = 0; i < indices.size(); i+=3){
        if(i == 0)materialAnt = materialID[vertMaterial[(int)i/3]];
        if(materialAnt != materialID[vertMaterial[(int)i/3]]){
            glEnd();
            materialAnt = materialID[vertMaterial[(int)i/3]];
            glBindTexture(GL_TEXTURE_2D, materialID[vertMaterial[(int)i/3]]);
            glBegin(GL_TRIANGLES);
        }//*/
        glColor3fv(&cor.x);
        glNormal3fv(&vNormals[indices[i]].x);
        glTexCoord2fv(&textureMap[i].x);
        glVertex3fv(&vertices[indices[i]].x);

        glNormal3fv(&vNormals[indices[i+1]].x);
        glTexCoord2fv(&textureMap[i+1].x);
        glVertex3fv(&vertices[indices[i+1]].x);

        glNormal3fv(&vNormals[indices[i+2]].x);
        glTexCoord2fv(&textureMap[i+2].x);
        glVertex3fv(&vertices[indices[i+2]].x);
    }
    glEnd();
}
void marchingCubes::createTexture(){
    textureMap2.clear();
    textureMap2.resize(indices.size());
    for(unsigned int i = 0; i < indices.size(); i+= 3){
        vec3 normal = vNormals[indices[i]];
        normal = normal + vNormals[indices[i+1]];
        normal = normal + vNormals[indices[i+2]];
        //normal.normaliza();
        normal = normal.abs();
        float resolucao = (1/16.0);


        if(normal.x > normal.z && normal.x > normal.y){
            textureMap2[i] = vec2(vertices[indices[i]].y*resolucao ,vertices[indices[i]].z*resolucao);
            textureMap2[i+1] = vec2(vertices[indices[i+1]].y*resolucao ,vertices[indices[i+1]].z*resolucao);
            textureMap2[i+2] = vec2(vertices[indices[i+2]].y*resolucao ,vertices[indices[i+2]].z*resolucao);
        }else if(normal.y > normal.z && normal.y > normal.x){
            textureMap2[i] = vec2(vertices[indices[i]].z*resolucao ,vertices[indices[i]].x*resolucao);
            textureMap2[i+1] = vec2(vertices[indices[i+1]].z*resolucao ,vertices[indices[i+1]].x*resolucao);
            textureMap2[i+2] = vec2(vertices[indices[i+2]].z*resolucao ,vertices[indices[i+2]].x*resolucao);
        }else if(normal.z > normal.x && normal.z > normal.y){
            textureMap2[i] = vec2(vertices[indices[i]].x*resolucao ,vertices[indices[i]].y*resolucao);
            textureMap2[i+1] = vec2(vertices[indices[i+1]].x*resolucao ,vertices[indices[i+1]].y*resolucao);
            textureMap2[i+2] = vec2(vertices[indices[i+2]].x*resolucao ,vertices[indices[i+2]].y*resolucao);
        }
    }
    textureMap = textureMap2;
    textureMap2.clear();
}
int marchingCubes::setMaterial(GLuint ID){
    materialID.push_back(ID);
    return (int)materialID.size()-1;
}
std::string marchingCubes::CompactToSend(){
    const int size = 64;
    std::string s = "";
    if(Size.x != size)return s;

    chunck_64  *points_to_send = new chunck_64();
    chunck_64  *material_to_send = new chunck_64();

    for(int x = 0; x < size; x++){
        for(int y = 0; y < size; y++){
            for(int z = 0; z < size; z++){
                points_to_send->cube[x][y][z] = pontos[x][y][z];
                material_to_send->cube[x][y][z] = material[x][y][z];
            }
        }
    }

    char *data;
    data = (char*)points_to_send;
    for(int i = 0; i < sizeof(chunck_64); i++){
        s += data[i];
    }
    data = (char*)                 material_to_send;
    for(int i = 0; i < sizeof(chunck_64); i++){
        s += data[i];
    }
    delete points_to_send;
    delete material_to_send;
    return s;
}
int marchingCubes::descompact_and_use(std::string s){
    const int size = 64;
    const int Ssize = sizeof(chunck_64);

    chunck_64  *points_to_reciv = new chunck_64();
    chunck_64  *material_to_reciv = new chunck_64();

    char *points_data = new char[Ssize];
    char *material_data = new char[Ssize];

    for(int i = 0; i < Ssize; i++){
        points_data[i] = s[i];
        material_data[i] = s[i+Ssize];
    }
    points_to_reciv = (chunck_64*)points_data;
    material_to_reciv = (chunck_64*)material_data;

    for(int x = 0; x < size; x++){
        for(int y = 0; y < size; y++){
            for(int z = 0; z < size; z++){
                pontos[x][y][z] = points_to_reciv->cube[x][y][z];
                material[x][y][z] = material_to_reciv->cube[x][y][z];
            }
        }
    }
}
