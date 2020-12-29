#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

#define populacaoInicial 10     // número de indivíduos da geração 1
#define diasPorGeracao 10       // quantidade de ciclos por verificação
#define geracoesPorPredacao 10  // quantidade de gerações até ser aplicada a predação 
#define taxaDePredacao 0.3      // taxa de predação padrão
#define pontosPorComida 1       // quantidade de pontos obtidos para cada comida coletaa
#define energiaInicial 10       // valor inicial de energia de um indivíduo
#define mutacaoBase 0.02        // taxa de mutação de referência
#define mutacaoNatural 0.2      // taxa de mutação para o modo "Seleção Natural"
#define maxMutation 0.1         // taxa de mutação máxima
#define energyCostBias 5        // numero multiplicado pela fórmula de energia 
#define energyAgain 2           // energia ganha ao comer
#define generationsEffect 4     // gerações afetadas após pouca mutação
#define minSumMutation 0.3      // menor distância da soma de avg, min, max para começar grande mudanca de gerações 
#define drasticMutation 4       // mutação drástica gerada 

#define minVelocidade 0.2
#define maxVelocidade 1.0
#define minRadius 0.04
#define maxRadius 0.1
#define minPercep 0.4
#define maxPercep 0.8

#define slowness 10                   // taxa de lentidão durante a execução      
#define timeEnergyCheck 100/slowness  // define o tempo em que atualizamos a energia 

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
    @return número aleatório
*/
float RandomFloat(float a, float b);
/*
    Calcula cor de um indivíduo de acordo com o valor de seus atributos
    @param b: bixinho sobre o qual será aplicado o cálculo da cor
    @return vetor de três posições (r,g,b) com os valores no intervalo [0,1]
*/
vector<float> calcularCor(Bixinho b);
/*
    Produz um individuo aleatório
    @return novo bixinho
*/
Bixinho gerarBixinho();
/*
    Produz um individuo com valor de atributos iguais a (min + max) * taxa
    @param taxa: valor multiplicativo 
    @return novo bixinho
*/
Bixinho gerarBixinhoConstante(float taxa);
/*
    Verifica a proximidade de um bixinho com uma comida
    @param b: bixinho da análise
    @param c: comida da análise
    @return valor booleano indicando se existe proximidade 
*/
bool checkIfNear(Bixinho *b, Comida *c);
/*
    Decide o tipo de movimento do bixinho. Se a comida estiver no range de visão do bixinho e estiver ativa, o bixinho é rotationado na direção da comida.
    @param b: bixinho da anáĺise
    @param c: comida da análise
    @return ????
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
    @return booleano indicando se a movimentação foi efetuada
*/
bool moveRandom(Bixinho *b);
/*
    Remove um indivíduo da população
    @param populacao: população de bixinhos
    @param idx: índice do bixinho que será removido
*/
void killBixinho(vector<Bixinho> &populacao, int idx);
/*
    Decrementa a energia disponível de cada indivíduo da população 
    @param populacao: população de bixinhos
*/
void subtractEnergy(vector<Bixinho> &populacao);
/*
    Avalia a ocorrência de colisão entre dois circulos
    @param x1: coordenada x do primeiro circulo
    @param y1: coordenada y do primeiro circulo
    @param r1: comprimento do raio do primeiro circulo
    @param x2: coordenada x do segundo circulo
    @param y2: coordenada y do segundo circulo
    @param r2: comprimento do raio do segundo circulo
    @return booleano indicando se houve colisão
*/
bool checkIf2CirclesColide(float x1, float y1, float r1, float x2, float y2, float r2);
/*
    Avalia ocorrência de colisão entre um bixinho e uma comida
    @param b: bixinho
    @param c: comida
    @return booleano indicando se houve colisão
*/
bool checkForColisionBC(Bixinho *b, Comida *c);
/*
    Avalia ocorrência de colisão entre dois bixinhos
    @param b1: primeiro bixinho
    @param b2: segundo bixinho
    @return booleano indicando se houve colisão
*/
bool checkForColisionBB(Bixinho b1, Bixinho b2);
/*
    Calcula a distância euclidiana entre um bixinho e uma comida
    @param b: bixinho
    @param c: comida
    @return distância obtida
*/
float distBetweenBC(Bixinho b, Comida c);
/*
    Checa se a comida se encontra dentro do campo de visão do bixinho
    @param b: bixinho
    @param c: comida
    @return valor indicando verdadeiro/falso
*/                                               
float checkIfInSight(Bixinho b, Comida c);
/*
    Se a comida estiver no campo de visão e estiver ativa, o bixinho se move na direção dela 
    @param b: bixinho
    @param c: comida
    @return ângulo de rotação
*/
float rotateToFood(Bixinho *b, Comida *c);
/*
    Seleciona o melhor indivíduo da população (com maior pontuação)
    @param populacao: população que será avaliada
    @return índice do melhor indivíduo no vetor
*/
int chooseBest(vector<Bixinho> population);
/*
    Calcula o fitness (pontuação) médio da população 
    @param populacao: população que será avaliada
    @return valor médio encontrado
*/
float averageFitness(vector<Bixinho> population);
/*
    Calcula um valor de mutação para o cromossomo  
    @param min: parâmetro usado para cálculo da variabilidade
    @param max: parâmetro usado para cálculo da variabilidade
    @param taxaMutacao: taxa de mutação
    @return valor da mutação para o cromossomo
*/
float mutation(float min, float max, float taxaMutacao);
/*
    Verifica se os valores dos cromossomos se encontram dentro dos limites permitidos
    @param b: bixinho que será avaliado 
*/
void checkChromosomes(Bixinho *b);
/*
    Produz um novo indivíduo através da técnica de crossover com distribuição 50%/50% do valor dos cromossomos dos pais 
    @param b1: primeiro indivíduo
    @param b2: segundo indivíduo
    @param taxaMutacao: taxa de mutação
    @return bixinho gerado pelo crossover 
*/
Bixinho crossover(Bixinho b1, Bixinho b2, float taxaMutacao);
/*
    Aplica o método de reprodução por elitismo na população, com tamanho da elite igual a 1 
    @param pop: população
    @param best: índice do melhor indivíduo
*/
void elitism(vector<Bixinho> &pop, int best);
/*
    Aplica o método de reprodução por torneio de 2 na população
    @param pop: população
    @param best: índice do melhor indivíduo
*/
void tournament_2(vector<Bixinho> &pop, int best);
/*
    Aplica o método de reprodução por roleta na população
    @param pop: população
    @param best: índice do melhor indivíduo
*/
void roulette(vector<Bixinho> &pop, int best);
/*
    Aplica o método de reprodução assexuada em um indivíduo
    @param b: bixinho original
    @param taxaMutacao: taxa de mutação
    @return indivíduo similar ao original, mas com os cromossomos alterados pela mutação
*/
Bixinho asexualReproduction(Bixinho b, float taxaMutacao);
/*
    Escreve os dados de um bixinho no arquivo de nome especificado
    @param filename: nome do arquivo 
    @param mode: método de manipulação do arquivo
    @param B: bixinho que terá os dados armazenados
    @param geracao: número da geração à qual o bixinho pertence
*/
void writeBixinhoData(string filename, string mode, Bixinho B, int geracao);
/*
    Escreve os dados de uma população de bixinhos no arquivo de nome especificado
    @param populacao: população de bixinhos
    @param filename: nome do arquivo 
    @param mode: método de manipulação do arquivo
    @param geracao: número da geração à qual os bixinhos pertencem
*/
void writePopulacaoData(vector <Bixinho> &populacao,string filename, string mode, int geracao);
/*
    Aplica o método de genocídio na população
    @param pop: população de bixinhos 
    @param manterMelhorVivo: indica se o processo manterá o melhor indivíduo vivo
    @param idx: índice do melhor indivíduo no vetor da população
*/
void genocide(vector<Bixinho> &pop, bool manterMelhorVivo, int idx);
/*
    Aplica o método de predação aleatória em um conjunto de indivíduos da população
    @param pop: população de bixinhos
    @param taxaPredacao: taxa de bixinhos que serão predados
*/
void randomPredation(vector<Bixinho> &pop, float taxaPredacao);
/*
    Produz um indivíduo com seus atributos zerados
    @return novo bixinho
*/
Bixinho gerarBixinhoLimpo();
/*
    Aplica o método de predação por síntese em um conjunto de indivíduos da população
    @param pop: população de bixinhos
    @param taxaPredacao: taxa de bixinhos que serão predados
*/
void synthesisPredation(vector<Bixinho> &pop, float taxaPredacao);
/*
    Aplica o método de predação por síntese em um conjunto de indivíduos da população
    @param populacao: população de bixinhos
    @param Best: índice do melhor indivíduo no vetor da população
    @return valor da taxa de mutação
*/
float variableMutation(vector<Bixinho>populacao, int Best);

void writePopulacaoData(vector <Bixinho> &populacao,string filename, string mode, int geracao);

float variableMutation(vector<Bixinho>populacao, int Best);

float distanceBB(Bixinho a, Bixinho b);

#endif