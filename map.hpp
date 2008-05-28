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

/// @file
/// The map class.
/// @author Jonan

#ifndef MAP_HPP
#define MAP_HPP

// @{
/// Types of terrain.
#define CAVE  0
#define GRASS 1
#define WATER 2
// @}

class cell;
class unit;

// Struct to store the coordinates of a cell.
struct cellCoor {
   int x;
   int y;
};

/// Controls all the attributes of a map.
///
/// Basically consist of lots of cell classes working
/// together to create a map an to be able to use it.
/// (This class is meant to be inherit, not to be used directly)
class map {
   private:
      cell *mouseOverCell; // The cell where the mouse is.

      // Connects all the cells in the map.
      void connectCells(void);

   protected:
      int width, height; // The map's size.
      cell **battleMap;
      unit *selectedUnit; // The unit that's selected.
      cellCoor firstCell; // Coordinates of the top left cell.

      map(const int width, const int height); // Constructor
      ~map(void); // Destructor

      // Returns a cell where the creature can attack.
      cell* getAttackCell(void);

      // Tells the map the mouse's position.
      void moveMouse(const int x, const int y, const int button);
      // Function to execute when the cell where the mouse is over is detected.
      virtual void mouseOver(const int x, const int y, const int button) = 0;

      // Starts the next turn.
      virtual void nextTurn(void) = 0;

      // This function is executed in the main loop. If
      // it returns true, the loop ends, else it continues.
      virtual bool frame(void) = 0;

      // Moves a unit to a cell.
      void moveCreature(cell *endPosition);

      // Draws the map in the screen.
      void draw(void);

   public:
      /// Starts the map.
      ///
      /// -no detailed description-
      virtual void start(void);

      /// Indicates the terrain image of a cell.
      ///
      /// Specify only the terrainName attribute to
      /// apply the terrain to all the cells of the map.
      ///
      /// @param[in] terrainName Type of terrain.
      /// @param[in] x X coordinate of the cell.
      /// @param[in] y Y coordinate of the cell.
      // (Implemented in map_terrain.cpp)
      void setTerrain(const int terrainName, const int x = -1, const int y = -1);
};

#endif // MAP_HPP
