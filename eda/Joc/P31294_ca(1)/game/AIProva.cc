#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Prova

// DISCLAIMER: The following Demo player is *not* meant to do anything
// sensible. It is provided just to illustrate how to use the API.
// Please use AINull.cc as a template for your player.

struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }


  /**
   * Types and attributes for your player can be defined here.
   */
    typedef vector<vector<bool>> VVB;  


    //Devuelve true si la en la casilla hay enemigo o un zombie
    bool z_o_e(int fila, int col) {
      int id = cell(fila, col).id;
      if (id != -1 and unit(id).type != Dead and (unit(id).type == Zombie or (unit(id).type == Alive and cell(fila, col).owner != me()))) return true;
      return false;
    }

    //Devuelve true si hay algun elemento en casillas adyacentes
    bool moviment_inicial(int id, Dir& d) {
      Pos aux = unit(id).pos;
      int f = aux.i, c = aux.j;
      if (c-1 > 0 and cell(f, c-1).type != Waste and (cell(f, c-1).food or z_o_e(f, c-1))) {d = Left; return true;}
      if (c+1 < 60 and cell(f, c+1).type != Waste and (cell(f, c+1).food or z_o_e(f, c+1))) {d = Right; return true;}
      if (f-1 > 0 and cell(f-1, c).type != Waste and (cell(f-1, c).food or z_o_e(f-1, c))) {d = Up; return true;}
      if (f+1 < 60 and cell(f+1, c).type != Waste and (cell(f+1, c).food or z_o_e(f+1, c))) {d = Down; return true;}
      return false;
    }
    
    bool bfs_general(int id, Dir& d) {
      Pos aux = unit(id).pos;
      int f = aux.i, c = aux.j;
      VVB visit(60, vector<bool>(60, false));
      queue<pair<Pos, Dir>> Q;
      visit[f][c] = true;

      //Primero comprobamos si las posiciones adyacentes tienen algo, en caso contrario miramos más profundidad        
      if (c-1 > 0 and not visit[f][c-1] and cell(f, c-1).type != Waste) {
          if (cell(f, c-1).food or z_o_e(f, c-1)) {d = Left; return true;}
          else Q.push(make_pair(aux, Left));
      }

      if (c+1 < 60 and not visit[f][c+1] and cell(f, c+1).type != Waste) {
          if (cell(f, c+1).food or z_o_e(f, c+1)) {d = Right; return true;}
          else Q.push(make_pair(aux, Right));
      }
      
      if (f-1 > 0 and not visit[f-1][c] and cell(f-1, c).type != Waste) {
          if (cell(f-1, c).food or z_o_e(f-1, c)) {d = Up; return true;}
          else Q.push(make_pair(aux, Up));
      }

      if (f+1 < 60 and not visit[f+1][c] and cell(f+1, c).type != Waste) {
          if (cell(f+1, c).food or z_o_e(f+1, c)) {d = Down; return true;}
          else Q.push(make_pair(aux, Down));
      }

      while (not Q.empty()) {
        Dir de = Q.front().second;
        Pos p = Q.front().first + de;
        f = p.i, c = p.j;
        Q.pop();
        visit[f][c] = true;
      
      if (c-1 >= 0 and not visit[f][c-1] and cell(f, c-1).type != Waste) {
        if (cell(f, c-1).food or z_o_e(f, c-1)) {d = Left; return true;}
        else Q.push(make_pair(aux, Left));
      }

      if (c+1 < 60 and not visit[f][c+1] and cell(f, c+1).type != Waste) {
        if (cell(f, c+1).food or z_o_e(f, c+1)) {d = Right; return true;} 
        else Q.push(make_pair(aux, Right));
      }
      
      if (f-1 >= 0 and not visit[f-1][c] and cell(f-1, c).type != Waste) {
        if (cell(f-1, c).food or z_o_e(f-1, c)) {d = Up; return true;}
        else Q.push(make_pair(aux, Up));
      }

      if (f+1 < 60 and not visit[f+1][c] and cell(f+1, c).type != Waste) {
        if (cell(f+1, c).food or z_o_e(f+1, c)) {d = Down; return true;}
        else Q.push(make_pair(aux, Down));
      }
       
      }
      return false;
    }


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    // Getting the alive units
    vector<int> alive = alive_units(me());
     
      for (auto id : alive) {
        Dir moviment;
        bool mov = moviment_inicial(id, moviment);
        if (mov) move(id, moviment);
        else {
          bool mov2 = false;
          mov2 = bfs_general(id, moviment);
          if (mov2) move(id, moviment);
        }
      }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
