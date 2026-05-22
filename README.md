# NSMBU-Haxx
A compilation of code hacks for NSMBU, following v3.0 of the [WUAPPS](https://zenith.miraheze.org/wiki/Other:WUAPPS) project standard. Also an example for the [CafeLoader Project Compiler (CLPC)](https://github.com/aboood40091/CLPC).  
Pre-built versions can be found in the `build` folder. Stable builds will be posted in the [releases](https://github.com/aboood40091/NSMBU-Haxx-Rewrite/releases) page.  
Old version can be found [here](https://github.com/aboood40091/NSMBU-haxx).

## Current haxx:
* Support for Classic Controller & Nunchuk  
* Dynamic effect ID count (Completely dependent on the contents of the `Eset.param` game file.)  
* Custom music list (Currently does nothing, but can be used to add new music slots. Check out our sound tool, [TuneBloom](https://github.com/stupidestmodder/TuneBloom)!)  
* Space physics as area option (Area data `loopType & 2`.)  
* NSMBW-style SFX reverb and delay  
* Optional disabling of Fast approximate anti-aliasing (FXAA) (Enable `aa` module in `project/project.yaml`.)  
* Fixed zone BG offsets  
* Collision Drawer  
* Custom Profile setup to allow for new sprites  
* Actor Spawner sprite (Added as sprite 724.)  
* Flip Block sprite (Added as sprite 725. Currently uses the Snake Block model.), with custom Fire particle effect (Added as emitter set 566 & effect ID 1234. Requires patches in `Resources`.)  
* Magic Platform sprite (Added as sprite 726.)  
* Effect Viewer (Added as sprite 727. Check `EffectPlayer.cpp` for controls.)  
* Fixed Rolling Hill with Pipe (sprite 355) Resource List  
* Optional disabling of Quick Save (and enforcing Save at all times) in the world map (Enable `course_select` module in `project/project.yaml`.)  
* Fixed missing propeller mushroom item glide sound  
* Enabled NSLU fix for `BlockLightLift` despawning in NSMBU as well  
* Clearing of frame buffer on every frame (to the color red) to disable the "void"  
* Transform `ChangePlayerNum` into a global instance instead of being an attribute of `CourseSelectMap`  

## Libraries:
* [SEAD](https://github.com/aboood40091/sead) - Nintendo EAD Standard Library (sead), agl, NintendoWareForCafe (NW4F) Eft.  
* [NintendoWareForCafe (NW4F) Sys](https://github.com/nw4f/Sys).  
* [NintendoWareForCafe (NW4F) G3d](https://github.com/nw4f/G3d).  
* [NintendoWareForCafe (NW4F) Lyt](https://github.com/nw4f/Lyt).  
* [NintendoWareForCafe (NW4F) Snd](https://github.com/nw4f/Snd).  
* [CafeFaceLibrary (FFL)](https://github.com/aboood40091/FFL).  
* Modified dynamic_libs to work with this project, based on original implementation by dimok and [Maschell fork](https://github.com/Maschell/dynamic_libs).
