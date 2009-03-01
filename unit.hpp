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

/// @file
/// The Unit class.
/// @author Jonan

#ifndef UNIT_HPP
#define UNIT_HPP

#include <deque>

#include <SDL/SDL.h>

#include "macros.hpp"

class Cell;
class Hero;

struct SpecialImage;

/// Sides to face
enum {RIGHT, LEFT};

/// Types of units.
enum {ARCHER = '0',
      ARMAGEDDON,
      BAT,
      BLADE_MASTER,
      BLOOD_BAT,
      CAVE_SPIDER,
      CHAMPION,
      DEATH_BLADE,
      FIGHTER,
      FLANKER,
      PILLAGER = 'a',
      RANGER,
      SERGEANT,
      SHYDE,
      SKELETON,
      WOLF_RIDER,
      LAST_UNIT = WOLF_RIDER};

/// Types of projectiles.
enum {WHITE_MISSILE};

/// Types of animations.
enum {ATTACKING,
      DEFENDING,
      DYING,
      IDLE,
      STANDING,
      NUM_ANIMATIONS};

/// Number of frames to wait before changing to the next sprite.
const int NUM_FRAMES_FOR_SPRITE = 3;

/// Stores a unit's attributes.
class Unit {
  public:
    /// @param[in] type Type of unit.
    /// @param[in] number Number of units.
    Unit(const char type, const int number); // Constructor
    virtual ~Unit(void); // Destructor

    // @{
    /// Set functions.
    void setNumber     (const int number)       {this->number = number;     }
    void setPosition   (Cell &position)         {this->position = &position;}
    void setMaster     (Hero *master)           {this->master = master;     }
    void setAnimation  (const int animation);
    void setFacingSide (const int facing_side);
    // @}

    // @{
    /// Get functions.
    int   getNumber          (void)                const {return number;                      }
    int   getMovement        (void)                const {return movement;                    }
    int   getAgility         (void)                const {return agility;                     }
    int   getProjectiles     (void)                const {return projectiles;                 }
    Cell* getPosition        (void)                const {return position;                    }
    char  getType            (void)                const {return type;                        }
    Hero* getMaster          (void)                const {return master;                      }
    int   getNumSprites      (const int animation) const {return animations[animation].size();}
    int   getActualAnimation (void)                const {return actual_animation;            }
    // @}

    /// Attacks a given unit.
    /// @param[in] creature Unit to attack.
    void attackCreature(Unit &creature);

    /// Draws the creature in the given position.
    /// @param[in] position The position where the creature should be drawn.
    virtual void draw(SDL_Rect &position);

  protected:
    // Sets all the unit's attributes.
    void setAllAttributes(const int live, const int movement,
                          const int attack, const int agility,
                          const int projectiles, const int projectiles_type);
    // Sets the creature's attributes acording to his type.
    // (Implemented in unit_type.cpp)
    virtual void setCreaturesAttributes(void);

    // Adds an image to the an animation.
    void addAnimationImage(const char *image_name, const int animation);

    // Adds a magic animation.
    // (Implemented in unit_magic.cpp)
    void addMagicAnimation(const int spell);

    // Draws the creature in the given position.
    void drawUnit(SDL_Rect &position);

    char type;

    int number;      // Number of units
    int facing_side; // Indicates if the creature is facing left or right

    double live;                   // Actual live
    int live_max;                  // Maximun live
    int attack, agility, movement; // Unit's attributes
    int projectiles;               // Number of projectiles a unit can shoot.
    int projectiles_type;

    std::deque<SDL_Surface*> animations[NUM_ANIMATIONS];
    int actual_animation;
    SpecialImage *magic_spell;

    int sprite; // Last sprite drawn

    Cell *position; // The cell where the unit is
    Hero *master;   // The hero that controls the unit.

  private:
    DISALLOW_COPY_AND_ASSIGN(Unit);
};

#endif // UNIT_HPP
