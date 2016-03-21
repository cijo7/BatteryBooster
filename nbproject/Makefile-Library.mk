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
CND_PLATFORM=Cygwin_4.x-Windows
CND_DLIB_EXT=dll
CND_CONF=Library
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/532465287/managerInterface.o \
	${OBJECTDIR}/_ext/1760719583/class_button.o \
	${OBJECTDIR}/_ext/1760719583/class_displayWindows.o \
	${OBJECTDIR}/_ext/1760719583/class_interfaceWindows.o \
	${OBJECTDIR}/_ext/1760719583/class_textbox.o \
	${OBJECTDIR}/_ext/1760719583/class_texture.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/manager.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/manager.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/manager.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -lSDL2 -lSDL2_image -lSDL2_ttf -shared

${OBJECTDIR}/_ext/532465287/managerInterface.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/dll/managerInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/532465287
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/532465287/managerInterface.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/dll/managerInterface.cpp

${OBJECTDIR}/_ext/1760719583/class_button.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/interface/Definitions/class_button.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1760719583
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1760719583/class_button.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/interface/Definitions/class_button.cpp

${OBJECTDIR}/_ext/1760719583/class_displayWindows.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/interface/Definitions/class_displayWindows.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1760719583
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1760719583/class_displayWindows.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/interface/Definitions/class_displayWindows.cpp

${OBJECTDIR}/_ext/1760719583/class_interfaceWindows.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/interface/Definitions/class_interfaceWindows.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1760719583
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1760719583/class_interfaceWindows.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/interface/Definitions/class_interfaceWindows.cpp

${OBJECTDIR}/_ext/1760719583/class_textbox.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/interface/Definitions/class_textbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1760719583
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1760719583/class_textbox.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/interface/Definitions/class_textbox.cpp

${OBJECTDIR}/_ext/1760719583/class_texture.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/interface/Definitions/class_texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1760719583
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1760719583/class_texture.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/interface/Definitions/class_texture.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/manager.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
