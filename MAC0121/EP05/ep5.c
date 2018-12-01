#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batalha-final-ep5-master/robot_fight.h"

/*
ALUNOS
Erica Cope - NUSP 9299091
João Pedro Turri - NUSP 6805993 
*/

int quickTurn(int ini, int end) {
	int i, j;
	for(i = ini, j = 0; i != end; i = (i+1)%6, j++)
		if (i >= 6) i-= 6;
	if (j > 3) j = 6-j;
	return j;
}

Action fastTurn(int ini, int end) {
	int dif = end-ini;
	if((dif <= 3 && dif >= 0) || (dif <= -3))
		return TURN_RIGHT;
	else
		return TURN_LEFT;		
}

int isControlPoint(Grid *g, Position p) {
	return (g->map[p.x][p.y].isControlPoint);	
}

int valid(Position p, int m, int n, Grid *g) {
	return ((p.x >= 0 && p.x < m && p.y >= 0 && p.y < n) && (g->map[p.x][p.y].type == NONE));
}

Action processaTiro(Grid *g, Position pos, Direction dir){
    for (int i = -1; i<2; i++){
        Position tileAdjacente = getNeighbor(pos,dir+i);
        if (tileAdjacente.x>=0 && tileAdjacente.x<g->m && tileAdjacente.y>=0 && tileAdjacente.y<g->n){
            if ((g->map[tileAdjacente.x][tileAdjacente.y].type) == ROBOT){
                if(i==-1) return SHOOT_LEFT;
                else if(i==0) return SHOOT_CENTER;
                else if(i==1) return SHOOT_RIGHT;
            }
        }

    }
    return STAND;
}


int searchNearestControl(Grid *g, Position p, Robot *r) {
	int i, min = 500, best_dir = 0, cont;
	for(i = 0; i < 6; i++) {
		//Conta para chegar o numero de viradas necessarias ja que elas gastam um turno
		cont = 1 + quickTurn(r->dir, i);
		Position s = getNeighbor(p,i);
		while(valid(s, g->m, g->n, g)) {
			if(isControlPoint(g,s)) {
				if(cont < min) {
					min = cont;
					best_dir = i;
					break;
				}
			}
			cont++;
			s = getNeighbor(s, i);
		}
	}

	//Nao existe control points no mapa
	if (min == 500)
		return -1;
	
	else
		return best_dir;
}


/*
int valid(Position p, int m, int n) {
	return (p.x >= 0 && p.x < m && p.y >= 0 && p.y < n);
}
*/




void prepareGame(Grid *grid, Position pos, int turnCount){
    int init = 0;
    setName("Godot");

}

Action processTurn(Grid *grid, Position pos, int turnsLeft){
    Robot *r = &grid->map[pos.x][pos.y].object.robot;
    int m = grid->m;
    int n = grid->n;

    /*
    if (!init){
        //Bloco de inicialização
        init = 1;
    }
    */
	
    /*
	if(grid->map[pos.x][pos.y].isControlPoint)
        //Robô está diretamente no control point
		return STAND;
    */

    int isValid = 0; //Verificar se uma dada posição está vazia
    if ((pos.x >= 0 && pos.x < m && pos.y >= 0 && pos.y < n) && (grid->map[pos.x][pos.y].type == NONE)) isValid = 1;

    static int neighbors[2][6][2] = {                          
		{{-1, 0}, {-1, -1}, {0, -1}, {1, 0}, {0, 1}, {-1, 1}}, //Linha par        A partir da esquerda, em
		{{-1, 0}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}}    //Linha ímpar      sentido horário
	};

    //Verificar os conteúdos dos tiles adjantes
    for (int i=0;i<6;i++){
        Position tileAdjacente = {pos.x + neighbors[pos.y % 2][(r->dir+i)%6][0], pos.y + neighbors[pos.y % 2][(r->dir+i)%6][1]};
        if (grid->map[tileAdjacente.x][tileAdjacente.y].type == NONE){
            //TILE VAZIO
        }
        if (grid->map[tileAdjacente.x][tileAdjacente.y].type == BLOCK){
            //BLOCO
        }
        if (grid->map[tileAdjacente.x][tileAdjacente.y].type == ROBOT){
            Action tiro = processaTiro(grid, pos,r->dir);
            if (tiro != STAND) return tiro;
            //ROBÔ INIMIGO
        }
        if (grid->map[tileAdjacente.x][tileAdjacente.y].type == PROJECTILE){
            //TIRO
            Position linhaDeTiro = {tileAdjacente.x+neighbors[pos.y % 2][grid->map[tileAdjacente.x][tileAdjacente.y].object.projectile.dir][0],tileAdjacente.y+neighbors[pos.y % 2][grid->map[tileAdjacente.x][tileAdjacente.y].object.projectile.dir][1]};
            if (linhaDeTiro.x == pos.x && linhaDeTiro.y == pos.y){
                //ESTOU NA LINHA DE TIRO
            }
        }
    }

    //Checar balas nas diagonais

    if(!(grid->map[pos.x][pos.y].isControlPoint)){
        int control_dir = searchNearestControl(grid, pos, r);
        /*Caso em nenhuma direcao tem um control point livre
        andar em uma direcao valida, ou comeca a virar para uma direcao valida*/
        if (control_dir == -1) {
            int i,j;
            for(i = r->dir, j = 0; j < 6; i++,j++){
                if (i >= 6) i-=6;
                Position s = getNeighbor(pos,i);
                if(valid(s, grid->m, grid->n, grid)) {
                    if(i == r->dir) {
                        return WALK;
                    }
                    else {
                        return fastTurn(r->dir, i);
                    }
                }
            }
            /*Se nenhuma posicao em volta eh valida, SAD TIME*/
            return STAND;
        }
        /*Se encontrou um control point em alguma direcao,
            comeca a virar e andar em sua direcao*/
        else if(control_dir == r->dir)
            return WALK;
        else {
            return fastTurn(r->dir, control_dir);
        }
    }

    return STAND;
}



