/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007-2008  Jon Ander Peñalba <jonan88@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#include "battle.hpp"
#include "cell.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "hero.hpp"
#include "unit.hpp"

// This function is executed in the main loop. If
// it returns true, the loop ends, else it continues.
bool battle::frame(void) {
   if (keys[SDLK_ESCAPE]) {
      while (keys[SDLK_ESCAPE]) input->readInput();
      endBattle = true;
   }
   if (keys[SDLK_SPACE]) {
      while (keys[SDLK_SPACE]) input->readInput();
      selectedUnit->getPosition()->unselect();
      nextTurn();
   }
   if (selectedUnit->getMaster() == NULL)
      ai();
   else
      moveMouse(mouse[POSITION_X], mouse[POSITION_Y], mouse[BUTTON]);
   draw();
   return endBattle;
}

// Function to execute when the cell where the mouse is over is detected.
void battle::mouseOver(const int x, const int y, const int button) {
   if ( button == 1  &&  (selectedUnit->getPosition() != &battleMap[x][y]) ) {
      if ( battleMap[x][y].canMoveHere() ) {
         moveCreature(&battleMap[x][y]);
         nextTurn();
      } else if ( battleMap[x][y].canAttackHere() ) {
         if ( battleMap[x][y].getCreature()->getMaster() != selectedUnit->getMaster() ) {
            moveCreature(&battleMap[x][y]);
            selectedUnit->attack( *battleMap[x][y].getCreature() );
            // Check if the creatures is dead.
            if ( battleMap[x][y].getCreature()->getNumber() == 0 ) {
               deleteCreature(*battleMap[x][y].getCreature());
               battleMap[x][y].setCreature(NULL);
            }
            nextTurn();
         }
      }
   }
}

// Returns the next unit.
void battle::nextTurn(void) {
   bool done = false;
   unit* creature;

   // Check if the battle has ended
   // Check if the hero is dead
   if (player == NULL) endBattle = true;
   // Check if all enemy creatures are dead
   int counter = 0;
   for (int i = 0; i<MAX_TEAM_UNITS; i++)
      if (creatures[i] == NULL) counter++;
   if (counter == MAX_TEAM_UNITS) endBattle = true;
   // If the battle hasn't ended continue
   if (!endBattle) {
      // Search for the next creature
      while (!done) {
         // Look if it's someones turn
         for (int i=0; i<MAX_BATTLE_UNITS && !done; i++)
            if (turns[i]>=TURN) {
               turns[i] -= TURN;
               if (i==0) {
                  if (player) {
                     done = true;
                     turn = 0;
                     creature = player;
                  }
               } else if (i<MAX_TEAM_UNITS+1) {
                  if (player->getCreature(i-1)) {
                     done = true;
                     turn = i;
                     creature = player->getCreature(i-1);
                  }
               } else if ( i<(2*MAX_TEAM_UNITS+1) ) {
                  if (creatures[i-MAX_TEAM_UNITS-1]) {
                     done = true;
                     turn = i;
                     creature = creatures[i-MAX_TEAM_UNITS-1];
                  }
               }

            }
         // Increase all the turns
         for (int j=0; j<MAX_BATTLE_UNITS && !done; j++) {
            if (j==0) {
               if (player)
                  turns[j] += player->getAgility();
            } else if (j<MAX_TEAM_UNITS+1) {
               if (player->getCreature(j-1))
                  turns[j] += player->getCreature(j-1)->getAgility();
            } else if ( j<(2*MAX_TEAM_UNITS+1) ) {
               if (creatures[j-MAX_TEAM_UNITS-1])
               turns[j] += creatures[j-MAX_TEAM_UNITS-1]->getAgility();
            }
         }
      }
      selectedUnit = creature;
      selectedUnit->getPosition()->select();
      // Wait until the mouse button is released.
      while (mouse[BUTTON]) input->readInput();
   }
}

// Removes a unit from the battle and deletes it.
void battle::deleteCreature(unit &creature) {
   bool found = false;
   int i = 0;

   while (i<MAX_BATTLE_UNITS && !found) {
      if (i==0) {
         if (player == &creature) {
            player = NULL;
            found = true;
         }
      } else if (i<MAX_TEAM_UNITS+1) {
         if (player->getCreature(i-1) == &creature) {
            /// @todo Do the same without recruitCreature(unit*, int)
            player->recruitCreature(NULL, i-1);
            found = true;
         }
      } else if (i<(2*MAX_TEAM_UNITS+1)) {
         if (creatures[i-MAX_TEAM_UNITS-1] == &creature) {
            creatures[i-MAX_TEAM_UNITS-1] = NULL;
            found = true;
         }
      }
      i++;
   }
   delete &creature;
}

// Controls the units not controled by the player.
void battle::ai(void) {
   cell *temp;
   temp = getAttackCell();

   if (temp) { // Attack a unit
      moveCreature(temp);
      selectedUnit->attack( *temp->getCreature() );
      if ( temp->getCreature()->getNumber() == 0 ) {
         deleteCreature( *temp->getCreature() );
         temp->setCreature(NULL);
      }
      nextTurn();
   } else { // Move the unit
      int x, y;
      selectedUnit->getPosition()->getCoordinates(x, y);
      x=0;
      while(!battleMap[x][y].canMoveHere() && x<sizeX) x++;
      if (x!=sizeX) {
         moveCreature(&battleMap[x][y]);
         nextTurn();
      } else {
         selectedUnit->getPosition()->unselect();
         nextTurn();
      }
   }
}

// Constructor
battle::battle(hero &player, unit **enemies, const int numberEnemies) : map(18, 9) {
   this->player = &player;
   for (int i=0; i<numberEnemies && i<MAX_TEAM_UNITS; i++) {
      creatures[i] = enemies[i];
   }
   if (numberEnemies<MAX_TEAM_UNITS) {
      for (int j=numberEnemies; j<MAX_TEAM_UNITS; j++) creatures[j] = NULL;
   }

   for (int t=0; t<MAX_BATTLE_UNITS; t++) turns[t] = 0;

   endBattle = false;

   // Put the hero and his units in the map.
   battleMap[0][4].setCreature(&player);
   for (int i=0; i<9; i++)
      battleMap[1][i].setCreature(player.getCreature(i));
   // Put the enemy creatures in the map.
   for (int i=0; i<MAX_TEAM_UNITS; i++)
      battleMap[sizeX-2][i].setCreature(creatures[i]);
}

// Creates and starts a battle.
void createBattle(void) {
   hero *player;
   unit *creature[9];
   unit *temp;

   // Create the hero and it's units.
   player = new hero(FIGHTER, HUMAN);
   for (int j=0; j<9; j++) {
      temp = new unit(SERGEANT, 3);
      player->recruitCreature(temp);
   }
   // Create the enemy creatures.
   for (int i=0; i<5; i++) {
      creature[i] = new unit(SKELETON, 5);
   }
   for (int t=5; t<9; t++) {
      creature[t] = new unit(BAT, 1);
   }

   battle war(*player, creature, 9);
   war.start();
   //war.results(&player, &creature);

   /// @todo Free memory
   // Free memory
   /*if (player) delete player;
   for (int i=0; i<9; i++) {
      if (creature[i]) delete creature[i];
   }*/
}

// Creates and starts a battle.
void createFastBattle(hero &player, const int enemyType, const int terrainType) {
   cell *temp;
   unit *creature[9];

   // Save players position
   temp = player.getPosition();

   // Create the enemy creatures.
   for (int i=0; i<9; i++) {
      creature[i] = new unit(enemyType, 5);
   }

   battle war(player, creature, 9);
   war.setTerrain(terrainType);
   war.start();

   // Restore player's position
   temp->setCreature(&player);
}
