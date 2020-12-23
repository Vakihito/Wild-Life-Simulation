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
  float theta;    // ângulo de rotacao
  float r,g,b;    // parâmetros de cor

  bool active;    // estado de ativação no mapa

}Comida;

typedef struct _bixinho {
  float radius;       // comprimento do raio (tamanho)
  float x;            // coordenada x
  float y;            // coordenada y
  float theta;        // ângulo de rotação
  float r,g,b;        // parâmetros de cor

  float energia;      // energia = (1/2) * (m v^2) - no nosso caso será (tamanho * v^2)/2 
  float pontos;       // o número de comidas adquiridas ao longo do tempo x 
  float velocidade;   // velocidade que o animal se move 
  float percep;       // raio de percepcao em que o boneco começa a caminhar

  bool active;         // define se o bixinho está ativo ou não 

  Comida *curComida;  // comida para a qual o bixinho está se dirigindo  
  
}Bixinho;


//----------------------------------------------//
//------------------ Funções -------------------//
//----------------------------------------------//

/*
    Produz um número com ponto flutuante no intervalo especificado
    @param a: valor mínimo
    @param b: valor máximo
    @return: número aleatório
*/
float RandomFloat(float a, float b);
/*
    Calcula cor de um indivíduo de acordo com o valor de seus atributos
    @param b: bixinho sobre o qual será aplicado o cálculo da cor
    @return: vetor de três posições (r,g,b) com os valores no intervalo [0,1]
*/
vector<float> calcularCor(Bixinho b);
/*
    Produz um individuo aleatório
    @return: novo bixinho
*/
Bixinho gerarBixinho();
/*
    Verifica a proximidade de um bixinho com uma comida
    @param b: bixinho da análise
    @param c: comida da análise
    @return: valor booleano indicando se existe proximidade 
*/
bool checkIfNear(Bixinho *b, Comida *c);
/*
    Decide o tipo de movimento do bixinho. Se a comida estiver no range de visão do bixinho e estiver ativa, o bixinho é rotationado na direção da comida.
    @param b: bixinho da anáĺise
    @param c: comida da análise
    @return: ????
*/
float decideMovement(Bixinho *b, Comida *c);
/*
    Modifica o ângulo de rotação de um bixinho
    @param bixinho: bixinho que será rotacionado
    @param angle: ângulo de rotação
*/
void rotateBixinho(Bixinho *bixinho, float angle);
/*
    Movimenta bixinho pelo mapa na direção em que ele está olhando
    @param bixinho: bixinho que se deslocará
    @param distance: distância do deslocamento
*/
void moveBixinho(Bixinho *bixinho, float distance);
/*
    Movimenta o bixinho aleatoriamente
    @param b: bixinho que se deslocará
    @return: booleano indicando se a movimentação foi efetuada
*/
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