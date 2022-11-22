#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Demo

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
    bool z_o_e(Pos p) {
      int id = cell(p).id;
      if (id != -1 and (unit(id).type == Zombie or (unit(id).type == Alive and cell(p).owner != me()))) return true;
      return false;
    }

    //Devuelve true si hay algun elemento en casillas adyacentes
    bool moviment_inicial(int id, Dir& d) {
      Pos aux = unit(id).pos;
      if (pos_ok(aux+Up) and cell(aux+Up).type != Waste and (cell(aux+Up).food or z_o_e(aux+Up))) {d = Up; return true;}
      if (pos_ok(aux+Down) and cell(aux+Down).type != Waste and (cell(aux+Down).food or z_o_e(aux+Down))) {d = Down; return true;}
      if (pos_ok(aux+Left) and cell(aux+Left).type != Waste and (cell(aux+Left).food or z_o_e(aux+Left))) {d = Left; return true;}
      if (pos_ok(aux+Right) and cell(aux+Right).type != Waste and (cell(aux+Right).food or z_o_e(aux+Right))) {d = Right; return true;}
      return false;
    }
    

    void moure_unitats() {
      vector<int> alive = alive_units(me());
      for (auto id : alive) {
        bool mov_i;
        Dir moviment;
        mov_i = moviment_inicial(id, moviment);
        
        if (mov_i) move(id, moviment);
      }
    }



  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    // Getting the alive units
    moure_unitats();
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
