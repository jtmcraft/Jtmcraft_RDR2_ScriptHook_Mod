# Jtmcraft RDR2 Trainer

This is a complete rewrite of the original mod.
It needs some work and I have other ideas, but it's functional.

This mod adds a menu, named "Jtmcraft", to
AB's [Native Trainer](http://www.dev-c.com/rdr2/scripthookrdr2/).
The original functionality of that Native Trainer remains in tact
so this mod can be used instead.

Menu items can be removed from the Jtmcraft menu through the
configuration file. Various parameters are also set in the
configuration file, `jtmcraft.json`
(in the JSON node `jtmcraft:menu_items`).

This mod includes an initial attempt to
port [rpx-cinematic](https://github.com/RPX-RedM/rpx-cinematic)
(licensed GPLv2)
with the idea of running cinematics when certain events occur.
It doesn't quite work as expected
and is a WIP that might never get completed (by me).
Cinematics are stored in the file `jtmcraft_cinematics.json`.
The sample cinematic ported from rpx-cinematic can be launched
from the Jtmcraft menu.

I have removed the vigilantes and vampire spawning from this mod
as I never got them
to work like I wanted. I may add them in later if I settle on
something I'm satisfied with. I use the
[Bandit Hideouts](https://www.nexusmods.com/reddeadredemption2/mods/2213/?tab=description&topic_id=14563908)
mod instead.

# Installation

Copy all three of the files in the `bin/Release` folder to your game folder:
* `JtmcraftTrainder.asi` is the mod
* `jtmcraft.json` is the mod's configuration file
* `jtmcraft_cinematics.json` defines the cinematics
