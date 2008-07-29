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
/// All the different missions that can be created.
/// @author Jonan

#ifndef MISSION_HPP
#define MISSION_HPP

#include "world.hpp"

#include "macros.hpp"

/// Represents a scenario.
///
/// -no detailed description-
class Mission {
  public:
    /// @param[in] map The name of the map to use in the mission.
    /// @param[in] number_allies The number of units each of the heroes allies has.
    /// @param[in] width The width of the map.
    /// @param[in] height The height of the map.
    /// @param[in] hero_position_x Starting position of the hero - x-coordinate.
    /// @param[in] hero_position_y Starting position of the hero - y-coordinate.
    Mission(const char *map, const int number_allies,
          const int width, const int height,
          const int hero_position_x, const int hero_position_y); // Constructor
    ~Mission(); // Destructor

    /// Launches the mission.
    ///
    /// -no detailed description-
    void startMission();

  private:
    World *war;
    Hero *player;
    int hero_position_x;
    int hero_position_y;
    int number_allies;

    DISALLOW_COPY_AND_ASSIGN(Mission);
};

/// Creates and starts mission 1.
///
/// -no detailed description-
void mission1(void);
/// Creates and starts mission 2.
///
/// -no detailed description-
void mission2(void);
/// Creates and starts mission 3.
///
/// -no detailed description-
void mission3(void);

#endif // MISSION_HPP
