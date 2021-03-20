# arduino1602ShieldTimer

Simple timer sketch for Arduino Uno and LCD 1602 shield with buttons. Very simple timer for very specific purpose -- rest time between weightlifting sets.

On boot, instructions are briefly displayed, then the screen goes dark.

Left button illuminates the display.
Up button starts a 60-second timer.
Down button starts a 90-second timer.
Display remains illuminated until timer expired, then goes dark.

Backlight pin is set to LOW in setup, then is set to INPUT or OUTPUT to determine whether the screen is lit. This is a safety fix for some broken shields where supposedly setting it to HIGH and OUTPUT might blow the AVR.  Mine is one of those shields (the HiLetGo version on Amazon for $6.49 as of March 2021): https://www.amazon.com/gp/product/B00OGYXN8C/ref=ppx_yo_dt_b_asin_image_o01_s00?ie=UTF8&psc=1

Feel free to modify for your own purposes.

Oh, the reason I chose this platform is that I found a simple 3D-printed case on Thingiverse that nicely houses the Arduino Uno and that shield, including button extenders: https://www.thingiverse.com/thing:845415 

I might remix this case to include room for a speaker or piezo, and add sound feedback to the sketch.
