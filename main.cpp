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
/// The main function.
/// @author Jonan

#include <cstdlib>
#include <iostream>

#include "boot.hpp"
#include "menu_main.hpp"

using namespace std;

int main(int argc, char *argv[]) {
   // Default options
   bool fullscreen = false;
   int width = 1024;
   int height = 768;
   int bpp = 16;

   // Check the programs arguments
   for (int i=1; i<argc; i++) {
      const string val(argv[i]);

   // Fullscreen argument
      if (val == "-f" || val == "--full-screen") {
         fullscreen = true;
   // Resolution argument
      } else if ( val == "-r" || val == "--resolution") {
         if ( argc > i+2 ) {
            width = atoi(argv[i+1]);
            height = atoi(argv[i+2]);
            if (!width || !height) { // Go back to default
               width = 1024;
               height = 768;
            }
            i += 2; // Jump to next arg
         }
   // Bitrate argument
      } else if ( val == "-b" || val == "--bpp" ) {
         if ( argc > i+1 ) {
            bpp = atoi(argv[i+1]);
            if (!bpp) {
               bpp = 16;
            }
            ++i;
         }
   // Help & wrong argument
      } else {
         /// @todo Change version
         cout << "\nHeroes of Wesnoth SVN\n"
              << "\nusage: heroes [OPTIONS]\n"
              << "  -b, --bpp BITRATE\n"
              << "        starts the game with the given bitrate.\n\n"
              << "  -f, --full-screen\n"
              << "        starts the game in full screen mode.\n\n"
              << "  -r, --resolution HORIZONTAL_RESOLUTION VERTICAL_RESOLUTION\n"
              << "        starts the game with the given resolution.\n\n"
              << "  -h, --help\n"
              << "        prints this message and exits.\n"
              << endl;
         return EXIT_SUCCESS;
      }
   }
   // Start the game engine
   boot(fullscreen, width, height, bpp);
   // Start the main menu
   startMainMenu();

   return EXIT_SUCCESS;
}
