#!/usr/bin/env bash

gmsh_svn="${HOME}/src/gmsh"
getdp_svn="${HOME}/src/getdp"
frameworks_dir="${HOME}/src/gmsh/contrib/mobile/frameworks_android"

petsc_lib="$frameworks_dir/petsc"
slepc_lib="$frameworks_dir/slepc"
android_ndk="${HOME}/android-ndk-r8b/" 
android_sdk="${HOME}/android-sdk/"

cmake_default="-DDEFAULT=0 -DCMAKE_TOOLCHAIN_FILE=$gmsh_svn/contrib/mobile/utils/Android.cmake -DENABLE_BUILD_ANDROID=1 -DCMAKE_BUILD_TYPE=Release"
cmake_thread=6

function check {
  return_code=$?
  if [ $return_code != 0 ]; then
    echo "last command failed (return $return_code)"
    exit $return_code
  fi
}

# PETSc and BLAS/LAPACK
echo $petsc_lib/libpetsc.so
if [ ! -f "$petsc_lib/libpetsc.so" ] || [ ! -f "$petsc_lib/libf2clapack.so" ] || [ ! -f "$petsc_lib/libf2cblas.so" ] || [ ! -d "$petsc_lib/Headers/" ]; then 
  echo -e "ERROR: Need BLAS (f2c), LAPACK (f2c) and PETSc\ncheck android_petsc_reconfigure-armv7-android-linux.py for compile options\n"
  exit 1
fi

export ANDROID_NDK=$android_ndk 

# Gmsh
cd $gmsh_svn
svn up
if [ ! -d "$gmsh_svn/build_android" ] || [ ! -f "$gmsh_svn/build_android/CMakeCache.txt" ]; then
  mkdir $gmsh_svn/build_android
fi
cd $gmsh_svn/build_android
cmake $cmake_default -DENABLE_BLAS_LAPACK=1 -DENABLE_BUILD_SHARED=1 -DENABLE_MATHEX=1 -DENABLE_MESH=1 -DENABLE_ONELAB=1 -DENABLE_PARSER=1 -DENABLE_POST=1 -DENABLE_ANN=1 -DENABLE_TETGEN=1 -DBLAS_LIB="$petsc_lib/libf2cblas.so" -DLAPACK_LIB="$petsc_lib/libf2clapack.so" ..
check
make androidGmsh -j$cmake_thread
check
make get_headers
check

# GetDP
cd $getdp_svn
svn up
if [ ! -d "$getdp_svn/build_android" ] || [ ! -f "$getdp_svn/build_android/CMakeCache.txt" ]; then
  mkdir $getdp_svn/build_android
fi
cd $getdp_svn/build_android
PETSC_DIR= PETSC_ARCH= SLEPC_DIR= cmake $cmake_default -DENABLE_BLAS_LAPACK=1 -DENABLE_BUILD_SHARED=1 -DENABLE_GMSH=1 -DENABLE_LEGACY=1 -DENABLE_PETSC=1 -DPETSC_INC="$petsc_lib/Headers;$petsc_lib/Headers/mpiuni" -DPETSC_LIBS="$petsc_lib/libpetsc.so" -DENABLE_SLEPC=1 -DSLEPC_INC="$slepc_lib/Headers/" -DSLEPC_LIB="$slepc_lib/libslepc.so" -DGMSH_INC="$gmsh_svn/build_android/Headers/" -DGMSH_LIB="$gmsh_svn/build_android/libs/libGmsh.so" -DBLAS_LAPACK_LIBRARIES="$petsc_lib/libf2cblas.so;$petsc_lib/libf2clapack.so" ..
check
make androidGetdp -j$cmake_thread
check
make get_headers
check

# Onelab/Mobile interface
if [ ! -d "$gmsh_svn/contrib/mobile/build_android" ]; then
  mkdir $gmsh_svn/contrib/mobile/build_android
fi
cd $gmsh_svn/contrib/mobile/build_android

cmake $cmake_default \
      -DCMAKE_INCLUDE_PATH="$getdp_svn/" \
      -DBLAS_LIB="$petsc_lib/libf2cblas.so" -DLAPACK_LIB="$petsc_lib/libf2clapack.so" \
      -DPETSC_LIB="$petsc_lib/libpetsc.so" -DSLEPC_LIB="$slepc_lib/libslepc.so" \
      -DGMSH_INC="$gmsh_svn/build_android/Headers" -DGMSH_LIB="$gmsh_svn/build_android/libs/libGmsh.so" \
      -DBENCHMARKSDIR="$getdp_svn/" \
      -DGETDP_INC="$getdp_svn/build_android/Headers" -DGETDP_LIB="$getdp_svn/build_android/libs/libGetDP.so" ..
check
make androidOnelab -j$cmake_thread
check
make androidProject
check

# Potentially modify source tree for alternate branding
cd Onelab
if [ $# -eq 1 ] ; then
  packagename=${1,,}
  appname=$1
  # change package name
  mv src/org/geuz/onelab/ src/org/geuz/$packagename
  mkdir src/org/geuz/onelab
  mv src/org/geuz/$packagename/Gmsh.java src/org/geuz/onelab
  find . -type f -name '*.java' -not -name 'Gmsh.java' -exec sed -i "s/org\.geuz\.onelab/org\.geuz\.$packagename/g" {} \;
  sed -i "s/org\.geuz\.onelab/org\.geuz\.$packagename/g" AndroidManifest.xml
  grep -r -m 1 'Gmsh' src | cut -d ':' -f 1 | xargs -n 1 sed -i "s/org\.geuz\.$packagename;/org\.geuz\.$packagename;\n\nimport org.geuz.onelab.Gmsh;/"
  # change app name
  sed -i "s/<string name=\"app_name\">Onelab<\/string>/<string name=\"app_name\">$appname<\/string>/" res/values/strings.xml
fi


# Onelab/Mobile package
if [ ! -d "libs/armeabi-v7a/" ]; then mkdir -p libs/armeabi-v7a/; fi
target=1
while read line; do
  read line # Name
  target_name=$(echo $line | awk '{print $2}')
  target_version=$(echo $line | awk '{print $3}')
  read line # Type
  read line # API level
  target_api=$(echo $line | awk '{print $3}')
  read line # Revision
  read line # Skins
  if [ $target_api -ge 14 ]; then
    $android_sdk/tools/android update project --name Onelab --path . --target $target
    check
    ant release
    check
    break
  fi
  read line # HACK
  target=$(($target+1))
done < <($android_sdk/tools/android list target | grep -A 5 "id:")

# to sign the APK:
# cp utils/ant.properties build_android/Onelab/

# to re-install on the device:
# $android_sdk/platform-tools/adb install -r $gmsh_svn/contrib/mobile/build_android/Onelab/bin/Onelab-release.apk

# to launch the app on the device:
# $android_sdk/platform-tools/adb shell am start -n org.geuz.onelab/org.geuz.onelab.SplashScreen

# to debug and check the log:
# $android_sdk/tools/ddms
