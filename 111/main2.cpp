#include <GL/glut.h>
#include <iostream>
#include "Jugador.h"
#include "CNTree.h"
#include <stdlib.h>
#include <math.h>
#include <utility>
#include <vector>

using namespace std;

#define _USE_MATH_DEFINES
#define ficha_jugador 1
#define ficha_ia 2
#define dificultad 4

int **tablero;
int xx1, yy1, xx2,yy2;
bool turno=true;
CNTree *ia;
Jugador jugador1(ficha_jugador);

//inicializando en ceros
    
void starting();
void imprimir_tablero();
void jugar();
void display();    
bool victoria_derrota();

void mouse(int button, int state, int x, int y);

int main(int argc, char **argv)
{
    starting();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(480, 480); 
  glutInitWindowPosition(0, 95);
  glutCreateWindow("DAMAS");
  glClearColor(0, 0, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 480, 480, 0, -1.0, 1.0);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMainLoop();
}



void display(){

  glClear(GL_COLOR_BUFFER_BIT);
  for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
    {
      if ((x + y) % 2)
        glColor3f(0.0f, 0.0f, 0.0f);
      else
        glColor3f(1.0f, 1.0f, 1.0f);
      
        glBegin(GL_QUADS);
      glVertex2f(x * 480 / 8, y * 480 / 8);
      glVertex2f((x + 1) * 480 / 8, y * 480 / 8);
      glVertex2f((x + 1) * 480 / 8, (y + 1) * 480 / 8);
      glVertex2f(x * 480 / 8, (y + 1) * 480 / 8);
      glEnd();
      if(tablero[y][x]==1){
        
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        for (int a = 0; a < 5; ++a){
          float xx = 480 / 8 / 2 * cos(2 * M_PI * a / 5) + (x + 0.5f) * 480 / 8;
          float yy =  480 / 8 / 2 * sin(2 * M_PI * a / 5) + (y + 0.5f) * 480 / 8;
          glVertex2f(xx, yy);
        }
        glEnd();
        }
      else if(tablero[y][x]==2){
          glColor3f(0.7f, 0.7f, 0.7f);
        glBegin(GL_POLYGON);
        for (int a = 0; a < 5; ++a){
          float xx = 480 / 8 / 2 * cos(2 * M_PI * a / 5) + (x + 0.5f) * 480 / 8;
          float yy =  480 / 8 / 2 * sin(2 * M_PI * a / 5) + (y + 0.5f) * 480 / 8;
          glVertex2f(xx, yy);
        }
        glEnd();
      }
    }
  glutSwapBuffers();
}

bool click=false;
bool click2=false;

void mouse(int button, int state, int x, int y)
{
  if (state == GLUT_UP)
  {
    if(click==false){
        xx1 = int(x / (480 / 8));
        yy1 = int(y / (480 / 8));
        jugador1.calcular_mov(tablero,yy1,xx1);
        click=true;
    }
    
    else if(click==true){
        xx2 = int(x / (480 / 8));
        yy2 = int(y / (480 / 8));
        click2=true;
    }

    if (click2==true){
        click=click2=false;    
        cout<<"x1: "<<xx1<<" y1:"<<yy1<<endl;
        cout<<"x2: "<<xx2<<" y2:"<<yy2<<endl;
        jugar();
    }
    glutPostRedisplay();
  }
}





void jugar(){

    imprimir_tablero();
    if(turno)
    {
        if (!victoria_derrota() or !jugador1.jugada(tablero,xx1,yy1,xx2,yy2)){
            return;
        }
        turno= false;
    }

    if(!turno)
    {
        if(!victoria_derrota())
            return; 
        ia = new CNTree(ia->copiar_matriz(tablero),dificultad,ficha_ia);
        ia->natalidad(ia->c_root);
        //prueba1.imprimirComportamiento(prueba1.c_root);
        int neo = ia->camino(ia->c_root);

        tablero = ia->c_root->c_hijos[neo]->tablero_estado;
        delete ia;
        turno =true;
    }
}



bool victoria_derrota()
{
    bool p1 = 0; // fichas 1
    bool p2 = 0; // fichas 2

    for(int i = 0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(tablero[i][j] == 1)
                p1 =  true;
            if(tablero[i][j] == 2)
                p2 = true;
        }
    if(!p1)
    {
        cout << "fichas 2 ha ganado" << endl;
        return false;
    }
    if(!p2)
    {
        cout << "fichas 1 ha ganado" << endl;
        return false;
    }

    return true;
}

void imprimir_tablero(){

    cout << "   0 1 2 3 4 5 6 7\n\n";
    for(int i = 0;i<8;i++){
        cout << i << "  ";
        for(int j=0;j<8;j++){
            cout << tablero[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl << endl;
}

void starting(){
    
    tablero = new int*[8];
    for(int i=0;i<8;i++)
        tablero[i] = new int[8];
    

    for(int i =0;i<8;i++)
        for(int j=0;j<8;j++)
            tablero[i][j] = 0;
        //posicionando fichas
        tablero[0][1] = 1;
        tablero[0][3] = 1;
        tablero[0][5] = 1;
        tablero[0][7] = 1;
        tablero[1][0] = 1;
        tablero[1][2] = 1;
        tablero[1][4] = 1;
        tablero[1][6] = 1;
        tablero[2][1] = 1;
        tablero[2][3] = 1;
        tablero[2][5] = 1;
        tablero[2][7] = 1;

        tablero[5][0] = 2;
        tablero[5][2] = 2;
        tablero[5][4] = 2;
        tablero[5][6] = 2;
        tablero[6][1] = 2;
        tablero[6][3] = 2;
        tablero[6][5] = 2;
        tablero[6][7] = 2;
        tablero[7][0] = 2;
        tablero[7][2] = 2;
        tablero[7][4] = 2;
        tablero[7][6] = 2;

        if(!turno) jugar();
}
