#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Artorias

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
    typedef pair<int, Dir> movj;  
    #define s_alta_prio = 0;
    #define alta_prio = 1;
    #define mid_prio = 2;
    #define baixa_prio = 3;

    //Devuelve true si la en la casilla hay enemigo o un zombie
    bool z_o_e(int fila, int col) {
      int id = cell(fila, col).id;
      if (id != -1 and unit(id).type != Dead and (unit(id).type == Zombie or (unit(id).type == Alive and unit(id).player != me()))) return true;
      return false;
    }

    //Devuelve true si hay algun elemento en casillas adyacentes
    bool moviment_inicial(int id, Dir& d) {
      Pos aux = unit(id).pos;
      int f = aux.i, c = aux.j;
      if (c-1 >= 0 and cell(f, c-1).type != Waste and (cell(f, c-1).food or z_o_e(f, c-1))) {d = Left; return true;}
      if (c+1 < board_cols() and cell(f, c+1).type != Waste and (cell(f, c+1).food or z_o_e(f, c+1))) {d = Right; return true;}
      if (f-1 >= 0 and cell(f-1, c).type != Waste and (cell(f-1, c).food or z_o_e(f-1, c))) {d = Up; return true;}
      if (f+1 < board_rows() and cell(f+1, c).type != Waste and (cell(f+1, c).food or z_o_e(f+1, c))) {d = Down; return true;}
      return false;
    }
    
    bool bfs_menjar(int id, Dir& d) {
      Pos aux = unit(id).pos;
      int f = aux.i, c = aux.j;
      VVB visit(board_rows(), vector<bool>(board_cols(), false));
      queue<pair<Pos, pair<Dir, int>>> Q;
      visit[f][c] = true;

      //Primero comprobamos si las posiciones adyacentes tienen algo, en caso contrario miramos más profundidad        
      if (pos_ok(aux+Left) and not visit[f][c-1] and cell(f, c-1).type != Waste) {
          if (cell(f, c-1).food) {d = Left; return true;}
          else Q.push(make_pair(aux+Left, make_pair(Left, 1)));
      }

      if (pos_ok(aux+Right) and not visit[f][c+1] and cell(f, c+1).type != Waste) {
          if (cell(f, c+1).food) {d = Right; return true;}
          else Q.push(make_pair(aux+Right, make_pair(Right, 1)));
      }
      
      if (pos_ok(aux+Up) and not visit[f-1][c] and cell(f-1, c).type != Waste) {
          if (cell(f-1, c).food) {d = Up; return true;}
          else Q.push(make_pair(aux+Up, make_pair(Up, 1)));
      }

      if (pos_ok(aux+Down) and not visit[f+1][c] and cell(f+1, c).type != Waste) {
          if (cell(f+1, c).food) {d = Down; return true;}
          else Q.push(make_pair(aux+Down, make_pair(Down, 1)));
      }

      while (not Q.empty()) {
        Dir de = Q.front().second.first;
        int distance = Q.front().second.second+1;
        Pos p = Q.front().first;
        f = p.i, c = p.j;
        Q.pop();

      if (distance > 20) return false;
      if (c-1 >= 0 and not visit[f][c-1] and cell(f, c-1).type != Waste) {
        visit[f][c-1] = true;
        if (cell(f, c-1).food) {d = de; return true;}
        else Q.push(make_pair(p+Left, make_pair(de, distance)));
      }

      if (c+1 < board_cols() and not visit[f][c+1] and cell(f, c+1).type != Waste) {
        visit[f][c+1] = true;
        if (cell(f, c+1).food) {d = de; return true;} 
        else Q.push(make_pair(p+Right, make_pair(de, distance)));
      }
      
      if (f-1 >= 0 and not visit[f-1][c] and cell(f-1, c).type != Waste) {
        visit[f-1][c] = true; 
        if (cell(f-1, c).food) {d = de; return true;}
        else Q.push(make_pair(p+Up, make_pair(de, distance)));
      }

      if (f+1 < board_rows() and not visit[f+1][c] and cell(f+1, c).type != Waste) {
        visit[f+1][c] = true;
        if (cell(f+1, c).food) {d = de; return true;}
        else Q.push(make_pair(p+Down, make_pair(de, distance)));
      }
      }
      return false;
    }

    

   bool bfs_atacar(int id, Dir& d) {
      Pos aux = unit(id).pos;
      int f = aux.i, c = aux.j;
      VVB visit(board_rows(), vector<bool>(board_cols(), false));
      queue<pair<Pos, pair<Dir, int>>> Q;
      visit[f][c] = true;

      //Primero comprobamos si las posiciones adyacentes tienen algo, en caso contrario miramos más profundidad        
      if (pos_ok(aux+Left) and not visit[f][c-1] and cell(f, c-1).type != Waste) {
          if (z_o_e(f, c-1)) {d = Left; return true;}
          else Q.push(make_pair(aux+Left, make_pair(Left, 1)));
      }

      if (pos_ok(aux+Right) and not visit[f][c+1] and cell(f, c+1).type != Waste) {
          if (z_o_e(f, c+1)) {d = Right; return true;}
          else Q.push(make_pair(aux+Right, make_pair(Right, 1)));
      }
      
      if (pos_ok(aux+Up) and not visit[f-1][c] and cell(f-1, c).type != Waste) {
          if (z_o_e(f-1, c)) {d = Up; return true;}
          else Q.push(make_pair(aux+Up, make_pair(Up, 1)));
      }

      if (pos_ok(aux+Down) and not visit[f+1][c] and cell(f+1, c).type != Waste) {
          if (z_o_e(f+1, c)) {d = Down; return true;}
          else Q.push(make_pair(aux+Down, make_pair(Down, 1)));
      }

      while (not Q.empty()) {
        Dir de = Q.front().second.first;
        int distance = Q.front().second.second+1;
        Pos p = Q.front().first;
        f = p.i, c = p.j;
        Q.pop();

      if (distance > 20) return false;
      if (c-1 >= 0 and not visit[f][c-1] and cell(f, c-1).type != Waste) {
        visit[f][c-1] = true;
        if (z_o_e(f, c-1)) {d = de; return true;}
        else Q.push(make_pair(p+Left, make_pair(de, distance)));
      }

      if (c+1 < board_cols() and not visit[f][c+1] and cell(f, c+1).type != Waste) {
        visit[f][c+1] = true;
        if (z_o_e(f, c+1)) {d = de; return true;} 
        else Q.push(make_pair(p+Right, make_pair(de, distance)));
      }
      
      if (f-1 >= 0 and not visit[f-1][c] and cell(f-1, c).type != Waste) {
        visit[f-1][c] = true; 
        if (z_o_e(f-1, c)) {d = de; return true;}
        else Q.push(make_pair(p+Up, make_pair(de, distance)));
      }

      if (f+1 < board_rows() and not visit[f+1][c] and cell(f+1, c).type != Waste) {
        visit[f+1][c] = true;
        if (z_o_e(f+1, c)) {d = de; return true;}
        else Q.push(make_pair(p+Down, make_pair(de, distance)));
      }
      }
      return false;
    }

    const vector<Dir> dirs = {Up, Down, Left, Right};

  void moure_peces() {
    priority_queue < pair<int, movj>, vector<pair<int, movj>>, greater<pair<int,movj>> > PQ;
    vector<int> alive = alive_units(me());
     
      for (auto id : alive) {
        Dir moviment;
        bool mov = moviment_inicial(id, moviment);
        if (mov) PQ.push(make_pair(0, make_pair(id, moviment)));
        else {
          bool mv = bfs_menjar(id, moviment);
          if (mv) PQ.push(make_pair(1, make_pair(id, moviment)));
          else {
              bool ataque = bfs_atacar(id, moviment);
              if (ataque) PQ.push(make_pair(2, make_pair(id, moviment)));
              else {
                bool ataque = false;
                int i = 0;
                while (i < 4 and not ataque) {
                  Dir d = dirs[0];
	                Pos new_pos = unit(id).pos + d;
	                if (pos_ok(new_pos) and (cell(new_pos).id == -1 or (cell(new_pos).id != -1 and cell(new_pos).owner != me())) and cell(new_pos.i,new_pos.j).type != Waste) {PQ.push(make_pair(3, make_pair(id, moviment))); ataque = true;}
                  ++i;
                }
              }
            }
          }
        }
        while (not PQ.empty()) {
          int id1 = PQ.top().second.first;
          Dir d1 = PQ.top().second.second;
          PQ.pop();
          move(id1, d1);
        }
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    // Getting the alive units
    moure_peces();
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
