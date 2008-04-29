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

#include "cell.hpp"

// @{
/// Types of terrain.
#define GRASS 0
#define WATER 1
// @}

class hero;
class unit;

/// Controls all the attributes of a map.
///
/// Basically consist of lots of cell classes working
/// together to create a map an to be able to use it.
class map {
   protected:
      int sizeX, sizeY; // The map's size
      cell **battleMap;
      cell *mouseOverCell; // The cell where the mouse is
      unit *selectedUnit; // The unit that's selected

      // Connects all the cells in the map.
      void connectCells(void);
      // Function to execute when the cell where the mouse is over is detected.
      virtual void mouseOver(const int x, const int y, const int button) = 0;

      // Moves a unit to a cell.
      void moveUnit(unit &creature, int* &path, const int movements);

      // Returns a cell where the creature can attack.
      cell* getAttackCell(void);

   public:
      /// @param[in] sizeX Number of cell rows in the map
      /// @param[in] sizeY Number of cell columns in the map
      map(const int sizeX, const int sizeY); // Constructor
      ~map(void); // Destructor

      /// Indicates the terrain image of the map.
      ///
      /// -no detailed description-
      ///
      /// @param[in] terrainName Name of the terrain.
      // (Implemented in unit_type.cpp)
      void setTerrain(const int terrainName);
      /// Puts the hero in the map.
      ///
      /// -no detailed description-
      ///
      /// @param[in] player The player's hero.
      void setHero(hero &player);

      /// Tells the map the mouse's position.
      ///
      /// Every time the mouse's position or the mouse's buttons
      /// change, this function should be called.
      ///
      /// @param[in] x The x coordinate of the mouse's position
      /// @param[in] y The y coordinate of the mouse's position
      /// @param[in] pressed If the mouse left button is pressed or not
      void moveMouse(const int x, const int y, const int button);

      /// Draws the map in the screen.
      ///
      /// -no detailed description-
      void draw(void);
};

#endif // MAP_HPP
