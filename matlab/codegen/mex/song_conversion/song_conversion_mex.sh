MATLAB="/Applications/MATLAB_R2017b.app"
Arch=maci64
ENTRYPOINT=mexFunction
MAPFILE=$ENTRYPOINT'.map'
PREFDIR="/Users/drewsdunne/Library/Application Support/MathWorks/MATLAB/R2017b"
OPTSFILE_NAME="./setEnv.sh"
. $OPTSFILE_NAME
COMPILER=$CC
. $OPTSFILE_NAME
echo "# Make settings for song_conversion" > song_conversion_mex.mki
echo "CC=$CC" >> song_conversion_mex.mki
echo "CFLAGS=$CFLAGS" >> song_conversion_mex.mki
echo "CLIBS=$CLIBS" >> song_conversion_mex.mki
echo "COPTIMFLAGS=$COPTIMFLAGS" >> song_conversion_mex.mki
echo "CDEBUGFLAGS=$CDEBUGFLAGS" >> song_conversion_mex.mki
echo "CXX=$CXX" >> song_conversion_mex.mki
echo "CXXFLAGS=$CXXFLAGS" >> song_conversion_mex.mki
echo "CXXLIBS=$CXXLIBS" >> song_conversion_mex.mki
echo "CXXOPTIMFLAGS=$CXXOPTIMFLAGS" >> song_conversion_mex.mki
echo "CXXDEBUGFLAGS=$CXXDEBUGFLAGS" >> song_conversion_mex.mki
echo "LDFLAGS=$LDFLAGS" >> song_conversion_mex.mki
echo "LDOPTIMFLAGS=$LDOPTIMFLAGS" >> song_conversion_mex.mki
echo "LDDEBUGFLAGS=$LDDEBUGFLAGS" >> song_conversion_mex.mki
echo "Arch=$Arch" >> song_conversion_mex.mki
echo "LD=$LD" >> song_conversion_mex.mki
echo OMPFLAGS= >> song_conversion_mex.mki
echo OMPLINKFLAGS= >> song_conversion_mex.mki
echo "EMC_COMPILER=clang" >> song_conversion_mex.mki
echo "EMC_CONFIG=optim" >> song_conversion_mex.mki
"/Applications/MATLAB_R2017b.app/bin/maci64/gmake" -B -f song_conversion_mex.mk
