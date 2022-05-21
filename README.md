# marching-cubes
gerador de merching cubes com  interpolação, texturização, remoção de vertices duplicados e alizamento de normals
(explicação e exemplos em breve...)

```cpp
class marchingCubes{

    public:
    
        marchingCubes(vec3 pos, vec3 size);
        /// construtor, recebe a posição da "chunk", um cubo de size.x por size.y por size.z.
        
        virtual ~marchingCubes(); 
        /// desconstrutor
        
        void setPoint(vec3 pos, int val, int _material);
        /// defie o valor de densidade de um ponto da grade.
        
        void setIsoLevel(float iL);
        /// define o valor de superficie, este será o valor de densidade minimo considerado solido.
        
        void setDebuging(bool a = true);
        /// ativa alguns prints que dizem o tempo e a memoria usada em alguns dos processos.
        
        void create();
        /// gera a mlha baseada na densidade de cada ponto.
        
        void recreate();
        /// recria a malha e executa todos os processos necessarios para criar a malha final.
        
        bool edit(vec3 pos, float power, bool distroi, int _material);
        /// remove ou adiciona uma efera em uma posição (vec3 pos), com uma força(float power), um material(int _materia), e recebe se deve adicionar ou subtrair a esfera da malha.
        
        int setMaterial(GLuint ID);
        /// recebe o ID de uma textura para renderizar, id de textura gerado com opengl(glfw no meu caso).
        
        std::string CompactToSend();
        ///compacta as informações deste objeto em texto para enviar pela internet.
        
        int descompact_and_use(std::string s);
        /// descompacta informações compactadas em CompactToSend();

        void createCube(MC::gridBox box);
        /// função privada.
        
        void calcNormals();
        /// calcula as normals da malha.
        
        void weldVertices();
        /// remove vertices duplicados.
        
        vec3 SQRT(vec3 &a, vec3 &b);
        /// função privada
        
        vec3 VertexInterp(float isolevel,vec3 p1,vec3 p2,float valp1,float valp2, int &_material);
        ///função privada.
        
        void drawMeshTri(vec3 cor);
        /// desenha a malha usando openg glfw.
        
        void createTexture();
        /// cria as cordenadas UV da textura usando texturização triplanar.
};

```
exemplo de uso:
```cpp
#include "vec3"
#include <math.h>

int main(){
    marchingCubes cube(vec3(0,0,0), vec3(32,32,32);
    cube.setIsoLevel(50);///quanto maior o iso level maior o nivel de detalha, mas também é necessario aumentar os valores gerados para os pontos.
    cube.setMaterial(ID)/// gerar um "ID" de textura com opengl primeiro. podem ser adicionadas mais texturas, elas ficam salvas na oredem que foram adicionadas.
    for(int x = 0; x < 32; x++){
        for(int y = 0; y < 32; y++){
            for(int z = 0; z < 32; z++){
                cube.setPoint(vec3(x,y,z), rand()%99, 0);///gera um valor de 0 a 99 para os pontos, seria melhor usar um tipo de simplex noise. o "0" é o endereço da primeira(e unica) textura que foi passada para setMaterial(), o indice delas é na ordem que elas foram informadas, começando em zero.
            }
        }
    }
    cube.create(); 
    cube.weldVertices(); /// remove vertices duplicados(até 24 vertices identicos podem ser gerados), ele é opcional e tira o efeito low-poly da malha(com textura fica menos aparente os erros de sombreamento devido faces muito pequenas que são geradas).
    cube.calcNormals(); 
    cube.createTexture(); /// estes processo devem ser feitos nessa ordem(os opcionais não podem ser chamados depois). também pode ser usada a função recreate() para isto mesmo na primeira vez de criação.
    
    while(true){
        cube.drawMeshTri();/// renderiza a malha.
    }
    return 0;
}








