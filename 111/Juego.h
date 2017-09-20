#ifndef JUEGO_H
#define JUEGO_H

#include "Jugador.h"
#include "CNTree.h"
#include <stdlib.h>


class Juego
{
    public:
        int **tablero;
        Juego()
        {
            tablero = new int*[8];
            for(int i=0;i<8;i++)
                tablero[i] = new int[8];

            //inicializando en ceros
            for(int i =0;i<8;i++)
                for(int j=0;j<8;j++)
                    tablero[i][j] = 0;
            //posicionando fichas
            tablero[0][1] = 1;
            tablero[0][3] = 1;            tablero[0][5] = 1;            tablero[0][7] = 1;            tablero[1][0] = 1;            tablero[1][2] = 1;            tablero[1][4] = 1;            tablero[1][6] = 1;            tablero[2][1] = 1;            tablero[2][3] = 1;            tablero[2][5] = 1;            tablero[2][7] = 1;
            tablero[5][0] = 2;            tablero[5][2] = 2;            tablero[5][4] = 2;            tablero[5][6] = 2;            tablero[6][1] = 2;            tablero[6][3] = 2;            tablero[6][5] = 2;            tablero[6][7] = 2;            tablero[7][0] = 2;            tablero[7][2] = 2;            tablero[7][4] = 2;            tablero[7][6] = 2;
        }

        void imprimir_tablero()
        {
            cout << "   0 1 2 3 4 5 6 7\n\n";
            for(int i = 0;i<8;i++)
            {
                cout << i << "  ";
                for(int j=0;j<8;j++)
                {
                    cout << tablero[i][j] << " ";
                }
                cout << "\n";
            }
            cout << endl << endl;
        }

        void jugar()
        {
            CNTree *ia;
            int ficha_jugador,ficha_ia,dificultad;
            bool turno;
            cout << "escoja la ficha 1 o 2:"  << endl;
            cin >> ficha_jugador;

            if(ficha_jugador > 2 || ficha_jugador < 1)
            {
                cout << "se asigno ficha 1" << endl;
                ficha_jugador = 1;
                ficha_ia =2;
            }
            else if(ficha_jugador == 1)
                ficha_ia = 2;
            else
                ficha_ia = 1;
            cout  <<  "ingrese el dificultad 0-6: ";
            cin >> dificultad;
            if (dificultad <0 || dificultad > 6)
            {
                cout << "se asigno dificultad en 6" << endl;
                dificultad = 6;
            }

            Jugador jugador1(ficha_jugador);

            if(ficha_jugador == 1)
                turno =true;
            else
                turno =false;

            ///loop
            while(victoria_derrota())
            {
                system("cls");
                imprimir_tablero();
                cout << endl;

                if(turno)
                {
                    jugador1.calcular_mov(tablero);
                    while(!jugador1.jugada(tablero))
                    {
                        cout << "valores incorectos\n";

                    }
                    turno =false;

                }
                else
                {
                    ia = new CNTree(ia->copiar_matriz(tablero),dificultad,ficha_ia);
                    ia->natalidad(ia->c_root);
                    //prueba1.imprimirComportamiento(prueba1.c_root);
                    int neo = ia->camino(ia->c_root);

                    tablero = ia->c_root->c_hijos[neo]->tablero_estado;
                    delete ia;
                    turno =true;
                }

                system("Pause");
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



        virtual ~Juego() {}
};

#endif // JUEGO_H
