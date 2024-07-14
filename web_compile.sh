#!/bin/bash

source ~/emsdk/emsdk_env.sh

SRC_DIR="src"
INCLUDE_DIR="$SRC_DIR/include"
OBJ_DIR="objects"
OUT_DIR="web_build"
ASSETS_DIR="assets"
C_FLAGS="-Lweb-raylib/lib -Iweb-raylib/include -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s ASYNCIFY -s -s TOTAL_MEMORY=67108864 -lraylib -Wall"

mkdir -p $OUT_DIR

#for file in $SRC_DIR/*.c; do
#	$CC -c $file -I $INCLUDE_DIR -o "$OBJ_DIR/$(basename $file .c).o" -Wall $C_FLAGS
#done

#$CC $SRC_DIR/*.c -o $OUT_DIR/index.html $C_FLAGS --preload-file $ASSETS_DIR
emcc "$SRC_DIR"/*.c -o "$OUT_DIR/index.html" $C_FLAGS --preload-file "$ASSETS_DIR" -Wno-implicit-int-float-conversion
