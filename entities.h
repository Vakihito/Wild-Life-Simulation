#ifndef ENTITIES_H
#define ENTITIES_H

#define populacaoInicial 10     // número de indivíduos da geração 1
#define diasPorGeracao 10       // quantidade de ciclos por verificação
#define pontosPorComida 1       // quantidade de pontos obtidos para cada comida coletaa
#define energiaInicial 100      // valor inicial de energia de um indivíduo

typedef struct _comida {
  float radius;   // comprimento do raio (tamanho)
  float x;        // coordenada x
  float y;        // coordenada y
  float theta;    // angulo de rotacao
  float r,g,b;    // parametros de cor

  bool active;    // estado de ativacao no mapa

}Comida;

typedef struct _bixinho {
  float radius;       // comprimento do raio (tamanho)
  float x;            // coordenada x
  float y;            // coordenada y
  float theta;        // angulo de rotacao
  float r,g,b;        // parametros de cor

  float energia;      // energia = (1/2) * (m v^2) - no nosso caso será (tamanho * v^2)/2 
  float pontos;       // o número de comidas adquiridas ao longo do tempo x 
  float velocidade;   // velocidade que o animal se move 
  float percep;       // raio de percepcao em que o boneco começa a caminhar

  Comida *curComida;
  
}Bixinho;


//----------------------------------------------//
//----------- Funções para o bixinho -----------//
//----------------------------------------------//

float RandomFloat(float a, float b);
bool checkIfNear(Bixinho *b, Comida *c);
float decideMovement(Bixinho *b, Comida *c);
void rotateBixinho(Bixinho *bixinho, float angle);
void moveBixinho(Bixinho *bixinho, float distance);
bool moveRandom(Bixinho *b);
bool checkIf2CirclesColide(float x1, float y1, float r1, float x2, float y2, float r2);
bool checkForColisionBC(Bixinho *b, Comida *c);
bool checkForColisionBB(Bixinho b1, Bixinho b2);
float distBetweenBC(Bixinho b, Comida c);                                               
float checkIfInSight(Bixinho b, Comida c);
float rotateToFood(Bixinho *b, Comida *c);

#endif