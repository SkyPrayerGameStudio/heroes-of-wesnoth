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
/// Functions to boot and quit the game.
/// @author Jonan

#ifndef BOOT_HPP
#define BOOT_HPP

/// Starts the engine and loads the main images.
///
/// -no detailed description-
///
/// @param[in] fullscreen Indicates if it's supposed to boot in fullscreen.
/// @param[in] width The screen's width.
/// @param[in] height The screen's height.
/// @param[in] bpp The screen's bits-per-pixel.
void boot(const bool fullscreen, const int width, const int height, const int bpp);
/// Exits the game.
///
/// -no detailed description-
void quit(void);

#endif // BOOT_HPP
