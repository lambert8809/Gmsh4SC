#!/bin/sh

mkdir -p ios.iconset
# App icons (iPad)
convert -scale 152 ../../../utils/icons/gmsh_mobile_master.png ios.iconset/icon_app_ipad_retina.png
convert -scale 76 ../../../utils/icons/gmsh_mobile_master.png ios.iconset/icon_app_ipad.png

# App icon (iPhone)
convert -scale 120 ../../../utils/icons/gmsh_mobile_master.png ios.iconset/icon_app_iphone_retina.png
