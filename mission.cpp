/*
This file is part of Heroes of Wesnoth.
Copyright (C) 2007, 2008, 2009 Jon Ander Peñalba <jonan88@gmail.com>

Heroes of Wesnoth is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

Heroes of Wesnoth is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#include "mission.hpp"

#include "hero.hpp"
#include "world.hpp"

// Creates and starts a mission.
void createMission(const char *map, const int number_allies,
                   const int width, const int height,
                   const int hero_position_x, const int hero_position_y
                  ) {
   World war(map, width, height);

   Hero *player = new Hero(HUMAN);
   Unit *temp;
   // Set the hero's units.
   for (int j=0; j<9; j++) {
      temp = new Unit(SERGEANT, number_allies);
      player->recruitCreature(temp);
   }

   war.setHero(*player, hero_position_x, hero_position_y);
   war.start();
}

// Create and start mission 1.
void mission1(void) {
   createMission("mission1", 10, 32, 17, 2, 2);
}

// Create and start mission 2.
void mission2(void) {
   createMission("mission2", 15, 32, 28, 3, 6);
}

// Create and start mission 3.
void mission3(void) {
   createMission("mission3", 25, 32, 22, 4, 9);
}
