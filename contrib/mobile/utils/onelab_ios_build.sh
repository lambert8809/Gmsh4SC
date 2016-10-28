#/usr/bin/env bash

gmsh_svn="${HOME}/src/gmsh/"
getdp_svn="${HOME}/src/getdp/"
frameworks_dir="${HOME}/src/gmsh/contrib/mobile/frameworks_ios/"

petsc_framework="$frameworks_dir/petsc.framework"
slepc_framework="$frameworks_dir/slepc.framework"

cmake_default="-DDEFAULT=0 -DCMAKE_TOOLCHAIN_FILE=$gmsh_svn/contrib/mobile/utils/iOS.cmake -DENABLE_BUILD_IOS=1 -DCMAKE_BUILD_TYPE=Release -GXcode"

build_cmd="xcodebuild -verbose -target lib -configuration Release"
headers_cmd="xcodebuild -verbose -target get_headers -configuration Release"

function check {
  return_code=$?
  if [ $return_code != 0 ]; then
    echo "last command failed (return $return_code)"
    exit $return_code
  fi
}

function build_gmsh {
  if [ $# -ne 1 ]; then
    echo "You must specify an architecture (e.g. armv7, armv7s, arm64, ...)"
    return
  fi
  if [ ! -d "$gmsh_svn/build_ios_$1" ]; then
    mkdir $gmsh_svn/build_ios_$1
  fi
  cd $gmsh_svn/build_ios_$1
  cmake $cmake_default -DENABLE_BLAS_LAPACK=1 -DENABLE_BUILD_LIB=1 -DENABLE_MATHEX=1 -DENABLE_MESH=1 -DENABLE_ONELAB=1 -DENABLE_PARSER=1 -DENABLE_POST=1 -DENABLE_ANN=1 -DENABLE_TETGEN=1 -DCMAKE_OSX_ARCHITECTURES="$1" ..
  check
  $build_cmd
  check
  $headers_cmd
  cd -
}
function build_getdp {
  if [ $# -ne 1 ]; then
    echo "You must specify an architecture (e.g. armv7, armv7s, arm64, ...)"
    return
  fi
  if [ ! -d "$getdp_svn/build_ios_$1" ]; then
    mkdir $getdp_svn/build_ios_$1
  fi
  cd $getdp_svn/build_ios_$1
  PETSC_DIR= PETSC_ARCH= SLEPC_DIR= cmake $cmake_default -DENABLE_BLAS_LAPACK=1 -DENABLE_BUILD_LIB=1 -DENABLE_GMSH=1 -DENABLE_LEGACY=1 -DENABLE_PETSC=1 -DPETSC_INC="$petsc_framework/Headers/" -DPETSC_LIBS="$petsc_framework/petsc" -DENABLE_SLEPC=1 -DSLEPC_INC="$slepc_framework/Headers/" -DSLEPC_LIB="$slepc_framework/slepc" -DGMSH_INC="$gmsh_svn/build_ios_$1/Headers/" -DGMSH_LIB="$gmsh_svn/build_ios_$1/Release-iphoneos/libGmsh.a" -DCMAKE_OSX_ARCHITECTURES="$1" ..
  check
  $build_cmd
  check
  $headers_cmd
  cd -
}

# build gmsh framework
cd $gmsh_svn && svn up
build_gmsh armv7
build_gmsh armv7s
build_gmsh arm64
mkdir -p $frameworks_dir/Gmsh.framework/Headers
lipo -create $gmsh_svn/build_ios_armv7/Release-iphoneos/libGmsh.a $gmsh_svn/build_ios_arm64/Release-iphoneos/libGmsh.a $gmsh_svn/build_ios_armv7s/Release-iphoneos/libGmsh.a -output $frameworks_dir/Gmsh.framework/Gmsh
cd $frameworks_dir/Gmsh.framework/Headers
cp $gmsh_svn/build_ios_armv7/Headers/gmsh/* .
ln -s . gmsh

# build getdp framework
cd $getdp_svn && svn up
build_getdp armv7
build_getdp armv7s
build_getdp arm64
mkdir -p $frameworks_dir/GetDP.framework/Headers
lipo -create $getdp_svn/build_ios_armv7/Release-iphoneos/libGetDP.a $getdp_svn/build_ios_arm64/Release-iphoneos/libGetDP.a $getdp_svn/build_ios_armv7s/Release-iphoneos/libGetDP.a -output $frameworks_dir/GetDP.framework/GetDP
cd $frameworks_dir/GetDP.framework/Headers
cp $getdp_svn/build_ios_armv7/Headers/getdp/* .

# create xcode project
mkdir $gmsh_svn/contrib/mobile/build_ios
cd $gmsh_svn/contrib/mobile/build_ios
cmake -DCMAKE_INCLUDE_PATH="$frameworks_dir;$getdp_svn" ..
make xcodeProject

# Potentially modify source tree for alternate branding


#TODO
#xcodebuild -project "Onelab" -target "Onelab" -configuration Release
#xcrun -sdk iphoneos PackageApplication -v "Onelab.app" -o "Onelab.ipa" --sign "iPhone Distribution: Your Signature\" --embed enterprise.mobileprovision
