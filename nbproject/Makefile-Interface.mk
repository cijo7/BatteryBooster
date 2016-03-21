#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Interface
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1440904924/app.o \
	${OBJECTDIR}/_ext/532462128/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-mwindows
CXXFLAGS=-mwindows

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/lib resource.o -lmanager

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/battery_booster.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/battery_booster.exe: resource.o

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/battery_booster.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/battery_booster ${OBJECTFILES} ${LDLIBSOPTIONS} -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

${OBJECTDIR}/_ext/1440904924/app.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/app.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1440904924
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1440904924/app.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/app.cpp

${OBJECTDIR}/_ext/532462128/main.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/gui/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/532462128
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/532462128/main.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/gui/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/battery_booster.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
