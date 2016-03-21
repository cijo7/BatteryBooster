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
CND_CONF=Uninstall_Trigger
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1440904924/app.o \
	${OBJECTDIR}/_ext/1601682874/main.o \
	${OBJECTDIR}/_ext/1601682874/trigger.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/triggerUninstall.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/triggerUninstall.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/triggerUninstall ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1440904924/app.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/app.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1440904924
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1440904924/app.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/app.cpp

${OBJECTDIR}/_ext/1601682874/main.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/triggers/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1601682874
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1601682874/main.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/triggers/main.cpp

${OBJECTDIR}/_ext/1601682874/trigger.o: /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/triggers/trigger.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1601682874
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1601682874/trigger.o /cygdrive/C/Users/cijo/Documents/Codes/cpp/Battery\ Booster/modules/triggers/trigger.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/triggerUninstall.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
