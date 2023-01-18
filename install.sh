#!/usr/bin/env bash

IFS=$'\n'
DEST="/c/Program Files (x86)/Steam/steamapps/common/Red Dead Redemption 2/"
DEV_MODE="./DevMode/bin/Release/DevMode.asi"
FALSE_ACCUSATIONS="./FalseAccusations/bin/Release/FalseAccusations.asi"
SNOW_BLANKET="./SnowBlanket/bin/Release/SnowBlanket.asi"
VAMPIRE="./Vampire/bin/Release/Vampire.asi"

for asi in $DEV_MODE $FALSE_ACCUSATIONS $SNOW_BLANKET $VAMPIRE
do
    cp $asi $DEST
done