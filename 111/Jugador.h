#ifndef JUGADOR_H
#define JUGADOR_H
#include <iostream>

using namespace std;

class Jugador
{
    public:
        int m_player;
        Jugador(int f) {m_player = f; }
        virtual ~Jugador() {}

        bool jugada(int ** &tablero_estado)
        {
            int m_y,m_x,m_y2,m_x2;
            cout << "ingrese las coordenadas de la ficha a mover: (y,x) ";
            cin >> m_y >> m_x;

            if(m_y < 0 || m_y > 7|| m_x < 0 || m_x > 7) return false;

            cout << "ingrese las coordenadas de movimiento de su ficha: (y x) ";
            cin >> m_y2 >> m_x2;

            if(m_y2 < 0 || m_y2 > 7 || m_x2 < 0 || m_x2 > 7) return false;

            if(m_x2-2 == m_x && aux_calc(m_y,2) == m_y2 && comer_der(m_y,m_x,tablero_estado))
            {
                tablero_estado[m_y][m_x] = 0;
                tablero_estado[aux_calc(m_y,1)][m_x+1] = 0;
                tablero_estado[m_y2][m_x+2] = m_player;
                return true;
            }
            else if(m_x2+2 == m_x && aux_calc(m_y,2) == m_y2 && comer_izq(m_y,m_x,tablero_estado))
            {
                tablero_estado[m_y][m_x] = 0;
                tablero_estado[aux_calc(m_y,1)][m_x-1] = 0;
                tablero_estado[m_y2][m_x2] = m_player;
                return true;
            }
            else if(m_x2-1 == m_x && aux_calc(m_y,1) == m_y2 && mover_der(m_y,m_x,tablero_estado))
            {
                tablero_estado[m_y][m_x] = 0;
                tablero_estado[m_y2][m_x2] = m_player;
                return true;
            }
            else if(m_x2+1 == m_x && aux_calc(m_y,1) == m_y2 && mover_izq(m_y,m_x,tablero_estado))
            {
                tablero_estado[m_y][m_x] = 0;
                tablero_estado[m_y2][m_x2] = m_player;
                return true;
            }


            return false;
        }



        void calcular_mov(int **tablero_estado)
        {
            cout << "movimientos:\n";
            bool comer_primero;
            for(int i = 0;i<8;i++)
                for(int j=0;j<8;j++)
                {
                    if(tablero_estado[i][j] == m_player)
                    {
                        comer_primero = false;
                        if(comer_der(i,j,tablero_estado))
                        {
                            cout << "ficha: ("  << i << "," << j << ") -> (" << aux_calc(i,2) <<"," <<j-2 << ")" << endl;
                            comer_primero =true;
                        }

                        if(comer_der(i,j,tablero_estado))
                        {
                            cout << "ficha: ("  << i << "," << j << ") -> (" << aux_calc(i,2) <<"," <<j+2 << ")" << endl;
                            comer_primero = true;
                        }
                        if(mover_izq(i,j,tablero_estado) && !comer_primero)
                        {
                            cout << "ficha: ("  << i << "," << j << ") -> (" << aux_calc(i,1) <<"," <<j-1 << ")" << endl;
                        }

                        if(mover_der(i,j,tablero_estado) && !comer_primero)
                        {
                            cout << "ficha: ("  << i << "," << j << ") -> (" << aux_calc(i,1) <<"," <<j+1 << ")" << endl;
                        }
                    }
                }
        }


        bool mover_izq(int y,int x,int **matriz)
        {
            int new_y =  aux_calc(y,1);
            if(x-1 >= 0 && aux_calc2(new_y) && matriz[new_y][x-1] == 0)
            {
                /*
                matriz[y][x] = 0;
                matriz[new_y][x-1] = m_player;
                */
                return 1;
            }
            return 0;
        }

        bool mover_der(int y, int x,int **matriz)
        {
            int new_y =  aux_calc(y,1);
            if(x+1 < 8 && aux_calc2(new_y) && matriz[new_y][x+1] == 0)
            {
                /*
                matriz[y][x] = 0;
                matriz[new_y][x+1] = m_player;
                */
                return 1;
            }
            return 0;
        }

        bool comer_izq(int y,int x,int **matriz)
        {
            if(x-2 >= 0 && aux_calc2(aux_calc(y,2)) && matriz[aux_calc(y,1)][x-1] !=0 && matriz[aux_calc(y,1)][x-1] !=m_player )
            {
                /*
                matriz[y][x] = 0;
                matriz[aux_calc(y,1)][x-1] = 0;
                matriz[aux_calc(y,2)][x-2] = m_player;
                */
                return 1;
            }
            return 0;
        }

        bool comer_der(int y, int x,int **matriz)
        {
            if(x+2 < 8 && aux_calc2(aux_calc(y,2)) && matriz[aux_calc(y,1)][x+1] !=0 && matriz[aux_calc(y,1)][x+1] !=m_player )
            {
                /*
                matriz[y][x] = 0;
                matriz[aux_calc(y,1)][x+1] = 0;
                matriz[aux_calc(y,2)][x+2] = m_player;
                */
                return 1;
            }
            return 0;
        }

        int aux_calc(int y,int sum_res)
        {
            if(m_player==1)
                return y+sum_res;
            return y-sum_res;
        }
        bool aux_calc2(int y)
        {
            if(m_player==1)
                return y<8;
            return y>=0;
        }

    private:
};

#endif // JUGADOR_H
