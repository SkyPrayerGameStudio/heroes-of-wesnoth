/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007  Jon Ander Peñalba <jonan88@gmail.com>

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

#include <iostream>

#include "timer.hpp"

using namespace std;

// The moment from which to start counting time. Make
// sure you call endFPS(int) one time every time you use it.
void timer::start(void) {
   now = before = SDL_GetTicks();
}

// Indicates the ending point.
void timer::end(int ms) {
   now = SDL_GetTicks();

   if ( (now-before) > ms ) {
      cout << (now - before - ms) << " ms slow\n";
   } else SDL_Delay( ms - (now - before) );
}
