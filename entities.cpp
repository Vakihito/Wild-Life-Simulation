#include "entities.h"

/* Gera um float randomico */
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
  bixinho->x = bixinho->x>1 ? -1 : bixinho->x;
  bixinho->x = bixinho->x<-1 ? 1 : bixinho->x;

  bixinho->y = bixinho->y>1 ? -1 : bixinho->y;
  bixinho->y = bixinho->y<-1 ? 1 : bixinho->y;
}

bool moveRandom(Bixinho *b){
  if(b->curComida == NULL){
    // b->theta -= 0.02;
    if(rand() % 2 == 0)
      b->theta += RandomFloat(0.01, 0.1);
    else
      b->theta -= RandomFloat(0.01, 0.1);
  }
  return true;
}

bool checkIf2CirclesColide(float x1, float y1, float r1, float x2, float y2, float r2){
    float diffx = (x1 - x2) * (x1 - x2);
    float diffy = (y1 - y2) * (y1 - y2);
    float dist =  sqrt(diffx + diffy);
    if(dist <= (r1 + r2))
        return true;
    return false;
}

/*
    Verifica colisão entre o bixo b e a comida c
*/
bool checkForColisionBC(Bixinho *b, Comida *c){
    if(c->active && checkIf2CirclesColide(b->x,b->y,b->radius, c->x,c->y,c->radius)){
        c->active = false;
        b->curComida = NULL;
        b->pontos += 1;
        // c->x = RandomFloat(0.1, 1);
        // c->y = RandomFloat(0.1, 1);
        return true;
    }

    else return false;
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

/* Se a comida estiver no sight range, e caso ela esteja na ativa movemos na direção dela */
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

/*
  Decide o tipo de movimento do bixinho
  Se a comida estiver no range de visão do bixinho e estiver ativa,
  o bixinho é rotationado na direção da comida.
*/
float decideMovement(Bixinho *b, Comida *c){
  if(checkIfInSight(*b, *c) && c->active){
    if(checkIfNear(b, c)){
      rotateToFood(b, c);
    } 
  }
  /* precisa consertar essa parte, toda vez nas 100 iterações ele pode entrar qui o q gera o comportamento frenético a altas taxas de melões */
  return 0;
}