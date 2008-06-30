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
/// The button and menu classes.
/// @author Jonan

#ifndef MENU_HPP
#define MENU_HPP

#include <deque>

#include <SDL/SDL.h>

using namespace std;

#define NORMAL  0
#define ACTIVE  1
#define PRESSED 2

#define BUTTON_WIDTH 108
#define BUTTON_HEIGHT 22

/// Distance between two buttons
#define DISTANCE 30

/// The characteristics of each menu button.
///
/// All the information about a button and what can
/// it do. It should only be used by the menu class.
class button {
   private:
      void (*function)(void); // Function to execute when the button is pressed.
      char *text; // Text to be writen in the button.
      int state; // Can be NORMAL, ACTIVE or PRESSED.

   public:
      /// @param[in] text Text to be writen in the button.
      /// @param[in] function The function to execute when the button is pressed.
      button(const char *text, void (&function)(void)); // Constructor
      ~button(void); // Destructor

      /// Returns the button's text.
      ///
      /// -no detailed description-
      ///
      /// @return Text to be writen in the button.
      char* getText(void) {return text;}
      /// Executes the button's function.
      ///
      /// -no detailed description-
      void getFunction(void) {function();}
      /// Returns the button's state.
      ///
      /// -no detailed description-
      ///
      /// @return Button's state (NORMAL, ACTIVE or PRESSED).
      int getState(void) {return state;}

      /// Changes the button state.
      ///
      /// -no detailed description-
      ///
      /// @param[in] state New state of the button (NORMAL, ACTIVE or PRESSED).
      void setState(const int state) {this->state = state;}
};

/// Collection of related button classes.
///
/// Controls a set of various button classes as a group.
class menu {
   private:
      SDL_Rect position; // Position of the top left hand corner of the menu.
      SDL_Surface *buttonSurface[3]; // The three button images.
      deque<button*> buttons; // The buttons in the menu.
      int activeButton; // Number of the button with the mouse over.
      int pressedButton; // Number of the button pressed.
      bool background; // Indicates if the menu has a background.
      bool drawBackground; // Indicates if drawing the background is needed.
      void (*drawBackgroundFunction)(void); // Function that draws the background.


   public:
      /// @param[in] position Top left hand corner of the menu.
      menu(SDL_Rect position); // Constructor
      ~menu(void); // Destructor

      /// Adds a new button to the menu.
      ///
      /// -no detailed description-
      ///
      /// @param[in] text Text to be writen in the button.
      /// @param[in] function Function to execute when the button is pressed.
      void addButton(const char *text, void (&function)(void));

      /// Adds a background to the menu.
      ///
      /// From now on, the menu will call drawBackgroundFuntion()
      /// for drawing the menu every time this is needed.
      ///
      /// @param[in] drawBackgroundFunction Funtion that draws the background.
      void addBackground(void (&drawBackgroundFunction)(void));

      /// Tells the menu the mouse's position.
      ///
      /// Every time the mouse's position or the mouse's buttons change, this
      /// function should be called so the menu knows which button is being pressed.
      ///
      /// @param[in] x The x coordinate of the mouse's position.
      /// @param[in] y The y coordinate of the mouse's position.
      /// @param[in] pressed If the mouse left button is pressed or not.
      void moveMouse(const int x, const int y, const bool pressed);

      /// Draws the menu.
      ///
      /// -no detailed description-
      void draw(void);
};

#endif // MENU_HPP
