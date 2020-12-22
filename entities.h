#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>

using namespace std;

#define populacaoInicial 10     // número de indivíduos da geração 1
#define diasPorGeracao 10       // quantidade de ciclos por verificação
#define pontosPorComida 1       // quantidade de pontos obtidos para cada comida coletaa
#define energiaInicial 10      // valor inicial de energia de um indivíduo
#define mutacaoBase 0.02        // taxa de mutação de referência
#define energyCostBias 5       // numero multiplicado pelo formula de energia 
#define timeEnergyCheck 1    // define o tempo em que atualizamos a energia 
#define enegyAgain 5            // energia ganha ao comer

#define minVelocidade 0.3
#define maxVelocidade 1.0
#define minRadius 0.03
#define maxRadius 0.1
#define minPercep 0.3
#define maxPercep 1.0
#define slowness 100

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
vector<float> calcularCor(Bixinho b);
Bixinho gerarBixinho();
bool checkIfNear(Bixinho *b, Comida *c);
float decideMovement(Bixinho *b, Comida *c);
void rotateBixinho(Bixinho *bixinho, float angle);
void moveBixinho(Bixinho *bixinho, float distance);
bool moveRandom(Bixinho *b);
void subtractEnergy(vector<Bixinho> &populacao);
bool checkIf2CirclesColide(float x1, float y1, float r1, float x2, float y2, float r2);
bool checkForColisionBC(Bixinho *b, Comida *c);
bool checkForColisionBB(Bixinho b1, Bixinho b2);
float distBetweenBC(Bixinho b, Comida c);                                               
float checkIfInSight(Bixinho b, Comida c);
float rotateToFood(Bixinho *b, Comida *c);
int chooseBest(vector<Bixinho> population);
float averageFitness(vector<Bixinho> population);
float mutation(float min, float max, float taxaMutacao);
void elitism(vector<Bixinho> &pop, int best);

#endif