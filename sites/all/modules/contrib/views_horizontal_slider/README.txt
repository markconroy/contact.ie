/* $Id$ */

-- INSTALLATION --

Enable the module like any other Drupal Module /admin/build/modules


-- CONFIGURATION --

1.) Add a view and specify the fields you want to output. 
2.) Activate the style plugin in the view -> Basic settings -> Style and chose "Horizontal Slider"
3.) Settings:
    - Animate In: The speed that the image will be slided when you hover it.
    - Animate Out: The speed that the image will be slided back when you move the mouse out.
    - Min Width: This is the size that an image will have in default state
    - Max width: This is the maximum width an image will have when you hover over it

-- REQUIREMENTS --

* Views Module installed    

-- ADDITIONAL MODULES SUGESTION --


    
 -- THEMING --
 
The provided base css is sufficient to demonstrate the functionality (tested with Garland)
Take a look at the views_horizontal_slider.css for some css hints. I intentionally used no inline css for the initial width of an image, because of the priority of inline css.


-- CONTACT --

Current maintainers:
* Marco Kleine-Albers (e-anima) -> http://drupal.org/user/255202


This project has been sponsored by:
* ARTWAVES
* http://www.artwaves.de for more information.

* Thanks to "dereine" http://drupal.org/user/99340 for some help.