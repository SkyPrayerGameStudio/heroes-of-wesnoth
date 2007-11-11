/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007  Jon Ander Pe�alba <jonan88@gmail.com>

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

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <SDL/SDL_image.h>

/*#include <cstdio>
#include <cstdlib>*/
#include <string>

/// A class to control images.
///
/// It should only be used by the imageList class.
class image {
   private:
      image *next; // Next image in the list
      char *name; // Unique name of each image (the fisical image name)
      //SDL_Rect position; // Position of the image on the screen

      // Returns a pointer to the image that needs to be
      // load if there's no error. Otherwise, exits the program.
      SDL_Surface* loadImage(const char *imageName, const int alpha);

   public:
      /// @param[in] imageName The image's name, without the img/...png
      /// @param[in] alpha Alpha value of the image. 0 transparent, 255 opaque.
      /// @param[in] next The next image in the list.
      image(const char *imageName, const int alpha, image *next); // Constructor
      ~image(void); // Destructor

      /// Returns the image name.
      ///
      /// -no detailed description-
      ///
      /// @return image name.
      char* getName(void);
      /// Returns the next image in the imageList.
      ///
      /// -no detailed description-
      ///
      /// @return next image in the imageList.
      image* getNext(void);
      //SDL_Surface* getSurface(void); Don't know why it doesn't work

      /// @todo make img private. First need to get getSurface() working.
      // It's really private. Put here just until I get getSurface() working
      SDL_Surface *img;
};

/// A list of image classes.
///
/// Store an image and look for any other previously
/// stored. It should only be used by graphics.
class imageList {
   private:
      image *first; // First image of the list

   public:
      imageList(void); // Constructor
      ~imageList(void); // Destructor

      /// Adds the image to the list.
      ///
      /// Loads the image and then places it at
      /// the beginning or the list.
      ///
      /// @param[in] imageName  The image's name, without the img/...png
      /// @param[in] alpha Alpha value of the image. 0 transparent, 255 opaque.
      void addImage(const char *imageName, const int alpha);
      /// Looks for an image in the list.
      ///
      /// If the image doesn't exist, exits the program and
      /// prints an error message.
      ///
      /// @param[in] imageName  The image's name, without the img/...png
      image* findImage(const char *imageName);
};

#endif

/* Last Version: Jonan */
