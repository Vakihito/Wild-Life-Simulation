#include "entities.h"

float RandomFloat(float a, float b){
  float random = ((float) rand()) / (float) RAND_MAX;
  float diff = b - a;
  float r = random * diff;
  return a + r;
}

vector<float> calcularCor(Bixinho b){
  vector<float> cor;

  cor.push_back((b.velocidade - minVelocidade)/maxVelocidade);  // R
  cor.push_back((b.percep - minPercep)/maxPercep);              // G
  cor.push_back((b.radius - minRadius)/maxRadius);              // B

  return cor;
}

Bixinho gerarBixinho(){
  Bixinho novo;
  vector<float> cor;

  novo.radius = RandomFloat(minRadius, maxRadius);
  novo.percep = RandomFloat(minPercep, maxPercep);
  novo.velocidade = RandomFloat(minVelocidade, maxVelocidade);
  novo.pontos = 0;
  novo.energia = energiaInicial;

  cor = calcularCor(novo);
  novo.r = cor[0];
  novo.g = cor[1];
  novo.b = cor[2];

  novo.curComida = NULL;

  return novo;
}

void rotateBixinho(Bixinho *bixinho, float angle){
    bixinho->theta += angle;
}

void moveBixinho(Bixinho *bixinho, float distance){
  // Para mover para onde ele está olhando (na direção theta)
  bixinho->x = bixinho->x + distance*cos(bixinho->theta);
  bixinho->y = bixinho->y + distance*sin(bixinho->theta);

  // Impede que o bixinho saia da tela
  bixinho->x = bixinho->x > 1 ? -1 : bixinho->x;
  bixinho->x = bixinho->x < -1 ? 1 : bixinho->x;

  bixinho->y = bixinho->y > 1 ? -1 : bixinho->y;
  bixinho->y = bixinho->y < -1 ? 1 : bixinho->y;
}

bool moveRandom(Bixinho *b){
  if(b->curComida == NULL){
    if(rand() % 2 == 0) b->theta += RandomFloat(0.01, 0.1);
    else b->theta -= RandomFloat(0.01, 0.1);
    return true;
  }
  return false;
}

void killBixinho(vector<Bixinho> &populacao, int idx){
  populacao.erase(populacao.begin() + idx);
}

float energyCost(Bixinho b){
  return ((b.radius * b.velocidade * b.velocidade)/2);   
}

void subtractEnergy(vector<Bixinho> &populacao){
  for (int i = 0; i < int(populacao.size()) ; i++)
  {
    populacao[i].energia = populacao[i].energia -(energyCost(populacao[i]) * energyCostBias);
    if (populacao[i].energia <= 0)
    {
      populacao[i].active = false;
    }
    
  }
}

bool checkIf2CirclesColide(float x1, float y1, float r1, float x2, float y2, float r2){
    float diffx = (x1 - x2) * (x1 - x2);
    float diffy = (y1 - y2) * (y1 - y2);
    float dist =  sqrt(diffx + diffy);
    if(dist <= (r1 + r2))
        return true;
    return false;
}

bool checkForColisionBC(Bixinho *b, Comida *c){
    if(b->active && c->active && checkIf2CirclesColide(b->x,b->y,b->radius, c->x,c->y,c->radius)){
        c->active = false;
        b->curComida = NULL;
        b->pontos += 1;
        b->energia += enegyAgain;
        // c->x = RandomFloat(0.1, 1);
        // c->y = RandomFloat(0.1, 1);
        return true;
    }
    
    return false;
}

bool checkForColisionBB(Bixinho b1, Bixinho b2){
    return checkIf2CirclesColide(b1.x,b1.y,b1.radius, b2.x,b2.y,b2.radius);
}

float distBetweenBC(Bixinho b, Comida c){
  float diffx = (b.x - c.x) * (b.x - c.x);
  float diffy = (b.y - c.y) * (b.y - c.y);
  return sqrt(diffx + diffy);
}

float checkIfInSight(Bixinho b, Comida c){
  return b.percep > distBetweenBC(b, c);
}

float rotateToFood(Bixinho *b, Comida *c){
  float diffx =  c->x - b->x;
  float diffy =  c->y - b->y;

  float rotation = (float)(atan2(diffy,diffx)) ;
  b->theta = rotation;
  b->curComida = c;
  return rotation;
}

bool checkIfNear(Bixinho *b, Comida *c){
  if(b->curComida == NULL)
    return true;
  
  if(!b->curComida->active){
    b->curComida = NULL;
    return true;
  }

  if(distBetweenBC(*b, *c) < distBetweenBC(*b, *(b->curComida)))
    return true;

  return false;
}

float decideMovement(Bixinho *b, Comida *c){
  if(checkIfInSight(*b, *c) && c->active){
    if(checkIfNear(b, c)){
      rotateToFood(b, c);
    } 
  }
  return 0;
}

int chooseBest(vector<Bixinho> population){
    pair<int,int> current;
    pair<int,int> best = {0, population[0].pontos};
    int size = population.size();

    for(int i = 1; i < size; ++i){
        current.first = i;
        current.second = population[i].pontos;

        if(current.second > best.second){
            best.first = current.first;
            best.second = current.second;
        }
    }

    return best.first;
}

float averageFitness(vector<Bixinho> population){
  float avg = 0;
  int size = population.size();

  for(int i = 0; i < size; ++i)
    avg += population[i].pontos;
  
  avg /= size;
  return avg;
}

float mutation(float min, float max, float taxaMutacao) {
  float var = (min + max)/2.0;
  return ((RandomFloat(0, var)) - var/2) * taxaMutacao;
}

void checkChromosomes(Bixinho *b){
  if(b->radius < minRadius) b->radius = minRadius;
  if(b->percep < minPercep) b->percep = minPercep;
  if(b->velocidade < minVelocidade) b->velocidade = minVelocidade;

  if(b->radius > maxRadius) b->radius = maxRadius;
  if(b->percep > maxPercep) b->percep = maxPercep;
  if(b->velocidade > maxVelocidade) b->velocidade = maxVelocidade;

  return;
}

Bixinho crossover(Bixinho b1, Bixinho b2, float taxaMutacao){
  Bixinho b;
  vector<float> color;

  b.curComida = NULL;
  b.pontos = 0;
  b.energia = energiaInicial;

  b.radius = (b1.radius + b2.radius)/2.0 + mutation(minRadius, maxRadius, taxaMutacao);
  b.percep = (b1.percep + b2.percep)/2.0 + mutation(minPercep, maxPercep, taxaMutacao);
  b.velocidade = (b1.velocidade + b2.velocidade)/2.0 + mutation(minVelocidade, maxVelocidade, taxaMutacao);

  checkChromosomes(&b);

  color = calcularCor(b);
  b.r = color[0];
  b.g = color[1];
  b.b = color[2];

  return b;
}

void elitism(vector<Bixinho> &pop, int best){
    vector<Bixinho> next_gen;
    Bixinho cur; 
    int size = pop.size();

    // produz novos indivíduos
    next_gen.push_back(pop[best]);
    for(int i = 0; i < size; ++i){
      if(i != best){
        cur = crossover(pop[best], pop[i], mutacaoBase);
        next_gen.push_back(cur);
      }
    } 

    // substitui a população atual pela nova
    pop = next_gen;

    return;
}

void tournament_2(vector<Bixinho> &pop, int best){
  vector<Bixinho> next_gen;
  Bixinho cur;
  int size = pop.size();
  next_gen.push_back(pop[best]);

  int father;          // índice do pai
  int mother;          // índice da mãe
  pair<int,int> duel;  // índice dos indivíduos que participarão do torneio

  // produz novos indivíduos
  for(int i = 1; i < size; ++i){
    // seleciona pai
    duel.first = rand() % size;
    duel.second = rand() % size;
    father = pop[duel.first].pontos > pop[duel.second].pontos ? duel.first : duel.second;

    // seleciona mãe
    duel.first = rand() % size;
    duel.second = rand() % size;
    mother = pop[duel.first].pontos > pop[duel.second].pontos ? duel.first : duel.second;

    cur = crossover(pop[father], pop[mother], mutacaoBase);
    next_gen.push_back(cur);
  }

  // substitui a população atual pela nova
  for(int i = 0; i < size; ++i) 
    pop[i] = next_gen[i];

  return;
}

Bixinho asexualReproduction(Bixinho b, float taxaMutacao){
  Bixinho novo;
  vector<float> color;

  novo.curComida = NULL;
  novo.pontos = 0;
  novo.energia = energiaInicial;

  novo.radius = b.radius + mutation(minRadius, maxRadius, taxaMutacao);
  novo.percep = b.percep + mutation(minPercep, maxPercep, taxaMutacao);
  novo.velocidade = b.velocidade + mutation(minVelocidade, maxVelocidade, taxaMutacao);

  checkChromosomes(&novo);

  color = calcularCor(novo);
  novo.r = color[0];
  novo.g = color[1];
  novo.b = color[2];

  return novo;
}

void writeBixinhoData(string filename, string mode, Bixinho B, int geracao){
  FILE *f;
  const char *auxFile = filename.c_str();
  const char *auxMode = mode.c_str();
  f = fopen(auxFile, auxMode);
  if (f != NULL)
  {
    fputs((to_string(geracao) + ",").c_str(),f);
    fputs((to_string(B.radius) + ",").c_str(),f);
    fputs((to_string(B.energia) + ",").c_str(),f);
    fputs((to_string(B.pontos) + ",").c_str(),f);
    fputs((to_string(B.velocidade) + ",").c_str(),f);
    fputs((to_string(B.percep) + "\n").c_str(),f);
    fclose(f);
  }
}
bool compareBixinho(Bixinho a, Bixinho b){
  return a.pontos > b.pontos;
}

void writePopulacaoData(vector <Bixinho> &populacao,string filename, string mode, int geracao){
  int sizePop = int(populacao.size());
  sort(populacao.begin(),populacao.end(), compareBixinho);
  for (int i = 0; i < sizePop; i++)
    writeBixinhoData(filename, mode ,populacao[i], geracao);
}