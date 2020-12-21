#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "entities.h"
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

#define windowWidth 900
#define windowHeight 900
#define PI 3.14159265

/*
    Inicialmente, andaremos por x dias, os indivíduos durante esse tempo 
    guardam comida. O que tiver mais comida é escolhido como elite. 
    Dessa forma, ao final do processo, podemos fazer toneio de 2 ou elitismo.

    Como compilar : g++ versao1.cpp  -lglut -lGLU -lGL && ./a.out
*/

vector<Bixinho> populacao;
vector<Comida> melao;

// Cria os bixinhos: (radius) (x,y,theta)       (r,g,b)   (energia ini)    pontos vel   percep  comida atual
Bixinho wilson =     {0.05,   0,0,0,            0.8, 0,0  ,energiaInicial, 0     , 0    , 0.6,  NULL};
Bixinho robson =     {0.05,   -0.3,-0.3,M_PI,   0,0.8,0   ,energiaInicial, 0     , 0    , 0.6,  NULL};
Bixinho dikson =     {0.05,   -0.5,0,M_PI/2,    0,0, 0.8  ,energiaInicial, 0     , 0    , 0.6,  NULL};

int qMelao = 50;

//---------- Protótipos de função ----------//
void draw();                                          // Função para desenhar
void timer(int);                                      // Função de loop
void drawBixinho(Bixinho bixinho);                    // Desenhar bixinho
void drawPopulacao(int size);                         // Desenhar população de bixinhos
void drawComida(Comida comida);                       // Desenhar comida
float RandomFloat(float a, float b);                  // Gerar float aleatorio

//------------------ Main -----------------//
int main(int argc, char** argv){

  //inicializa população
  for(int i = 0; i < populacaoInicial; ++i) {
    populacao.push_back(gerarBixinho());
    populacao[i].theta = (360*i)/populacaoInicial;
    populacao[i].x = 1*cos(populacao[i].theta);
    populacao[i].y = 1*sin(populacao[i].theta);
  }

  // inicializa as comidas
  for(int i = 0; i < qMelao; i++) {
    melao.push_back({0.02, RandomFloat(-1,1), RandomFloat(-1,1),0, 0, 0.8, 0.8, true});
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Wild Life Simulator");           
  glClearColor(1.0, 1.0, 1.0, 1.0);                 
  glutDisplayFunc(draw);
  glutTimerFunc(0, timer, 0);                      
  glutMainLoop();

  return 0;
}

//------------------ Draw -----------------//
void draw() {
  glClear(GL_COLOR_BUFFER_BIT);
  drawPopulacao(populacao.size());

  for (int i = 0; i < qMelao; i++) {
    if(melao[i].active){
      drawComida(melao[i]);
    }
  }
  
  glutSwapBuffers();
}

//------------------ Timer -----------------//
void timer(int){
  // Essa função é chamada em loop, é aqui que realizaremos as animações
  int size = populacao.size();

  // Para mover os bixinhos
  for(int j = 0; j < size; j++)
    moveBixinho(&populacao[j], populacao[j].velocidade/slowness);

  // Para girar os bixinhos
  for(int i = 0; i < qMelao; i++) {
    for(int j = 0; j < size; j++) {
      decideMovement(&populacao[j], &melao[i]);
      checkForColisionBC(&populacao[j], &melao[i]);
    }
  }

  for(int j = 0; j < size; j++)
    moveRandom(&populacao[j]);

  // Executa a função draw para desenhar novamente
  glutPostRedisplay();

  // O primeiro parâmetro define de quanto em quanto tempo em milissegundos timer será chaamdo
  // Eu coloquei 1000/60 para definir que vai atualizar a 60hz
  glutTimerFunc(1000/60, timer, 0);// Garante que esta função será chamada de novo
}


//----------------------------------------------//
//----------- Funções para o bixinho -----------//
//----------------------------------------------//

void drawBixinho(Bixinho bixinho){
  // Função para desenhar o bixinho
  float radius = bixinho.radius;
  float x = bixinho.x;
  float y = bixinho.y;
  float theta = bixinho.theta;

  //----- Desenha corpo do bixinho -----//
  glColor3f(bixinho.r, bixinho.g, bixinho.b);// Bixinho verde
  glBegin(GL_POLYGON);
  for(int i = 0; i < 360; i += 5) {
    glVertex2d( radius*cos(i/180.0*M_PI) + x, radius*sin(i/180.0*M_PI) + y);
  }
  glEnd();

  //----- Desenha olho direito do bixinho -----//
  float eyeRadius = radius/8;
  float eyeDist = M_PI/6;

  glColor3f(0, 0, 0);
  glBegin(GL_POLYGON);
  for(int i = 0; i < 360; i += 5){
    float shiftX = radius/2*cos(theta-eyeDist);
    float shiftY = radius/2*sin(theta-eyeDist);
    glVertex2d( eyeRadius*cos(i/180.0*M_PI) + x + shiftX, eyeRadius*sin(i/180.0*M_PI) + y + shiftY);
  }
  glEnd();

  //----- Desenha olho esquerdo do bixinho -----//
  glColor3f(0, 0, 0);
  glBegin(GL_POLYGON);
  for(int i = 0; i < 360; i += 5){
    float shiftX = radius/2*cos(theta+eyeDist);
    float shiftY = radius/2*sin(theta+eyeDist);

    glVertex2d( eyeRadius*cos(i/180.0*M_PI) + x + shiftX, eyeRadius*sin(i/180.0*M_PI) + y + shiftY);
  }
  glEnd();
}

void drawPopulacao(int size){
  for(int i = 0; i < size; ++i)
    drawBixinho(populacao[i]);
  return;
}

void drawComida(Comida comida){
  // Função para desenhar o comida
  float radius = comida.radius;
  float x = comida.x;
  float y = comida.y;
  float theta = comida.theta;

  //----- Desenha corpo do comida -----//
  glColor3f(comida.r, comida.g, comida.b);// Bixinho verde
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i += 5) {
    glVertex2d( radius*cos(i/180.0*M_PI) + x, radius*sin(i/180.0*M_PI) + y);
  }
  glEnd();
}