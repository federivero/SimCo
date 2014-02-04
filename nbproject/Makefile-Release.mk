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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1966265013/Instrucition.o \
	${OBJECTDIR}/_ext/1145095373/Queue.o \
	${OBJECTDIR}/_ext/994054922/ExecutionManager.o \
	${OBJECTDIR}/_ext/1422153699/MemoryRequest.o \
	${OBJECTDIR}/_ext/1422153699/MemoryResponse.o \
	${OBJECTDIR}/_ext/997839248/FetchStage.o \
	${OBJECTDIR}/_ext/997839248/Processor.o \
	${OBJECTDIR}/_ext/1612582161/InterconnectionNetwork.o \
	${OBJECTDIR}/architecture/Loader.o \
	${OBJECTDIR}/architecture/MIPS32ISA.o \
	${OBJECTDIR}/architecture/MIPS32Loader.o \
	${OBJECTDIR}/architecture/StaticInstruction.o \
	${OBJECTDIR}/common/SimpleFileParser.o \
	${OBJECTDIR}/execution/ConfigManager.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/system/ComputationalSystem.o \
	${OBJECTDIR}/system/MemoryMapEntry.o \
	${OBJECTDIR}/system/MemorySystem.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f1

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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/esimco.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/esimco.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/esimco ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1966265013/Instrucition.o: ../ESimCO/architecture/Instrucition.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1966265013
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1966265013/Instrucition.o ../ESimCO/architecture/Instrucition.cpp

${OBJECTDIR}/_ext/1145095373/Queue.o: ../ESimCO/common/Queue.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1145095373
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1145095373/Queue.o ../ESimCO/common/Queue.cpp

${OBJECTDIR}/_ext/994054922/ExecutionManager.o: ../ESimCO/execution/ExecutionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/994054922
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/994054922/ExecutionManager.o ../ESimCO/execution/ExecutionManager.cpp

${OBJECTDIR}/_ext/1422153699/MemoryRequest.o: ../ESimCO/memory/MemoryRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422153699
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1422153699/MemoryRequest.o ../ESimCO/memory/MemoryRequest.cpp

${OBJECTDIR}/_ext/1422153699/MemoryResponse.o: ../ESimCO/memory/MemoryResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422153699
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1422153699/MemoryResponse.o ../ESimCO/memory/MemoryResponse.cpp

${OBJECTDIR}/_ext/997839248/FetchStage.o: ../ESimCO/processor/FetchStage.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/997839248
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/997839248/FetchStage.o ../ESimCO/processor/FetchStage.cpp

${OBJECTDIR}/_ext/997839248/Processor.o: ../ESimCO/processor/Processor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/997839248
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/997839248/Processor.o ../ESimCO/processor/Processor.cpp

${OBJECTDIR}/_ext/1612582161/InterconnectionNetwork.o: ../ESimCO/system/InterconnectionNetwork.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1612582161
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1612582161/InterconnectionNetwork.o ../ESimCO/system/InterconnectionNetwork.cpp

${OBJECTDIR}/architecture/Loader.o: architecture/Loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/Loader.o architecture/Loader.cpp

${OBJECTDIR}/architecture/MIPS32ISA.o: architecture/MIPS32ISA.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/MIPS32ISA.o architecture/MIPS32ISA.cpp

${OBJECTDIR}/architecture/MIPS32Loader.o: architecture/MIPS32Loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/MIPS32Loader.o architecture/MIPS32Loader.cpp

${OBJECTDIR}/architecture/StaticInstruction.o: architecture/StaticInstruction.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/StaticInstruction.o architecture/StaticInstruction.cpp

${OBJECTDIR}/common/SimpleFileParser.o: common/SimpleFileParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/SimpleFileParser.o common/SimpleFileParser.cpp

${OBJECTDIR}/execution/ConfigManager.o: execution/ConfigManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/execution
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/execution/ConfigManager.o execution/ConfigManager.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/system/ComputationalSystem.o: system/ComputationalSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/ComputationalSystem.o system/ComputationalSystem.cpp

${OBJECTDIR}/system/MemoryMapEntry.o: system/MemoryMapEntry.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/MemoryMapEntry.o system/MemoryMapEntry.cpp

${OBJECTDIR}/system/MemorySystem.o: system/MemorySystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/MemorySystem.o system/MemorySystem.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/MIPS32ISAUnitTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/ConfigFileTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/MIPS32ISAUnitTest.o: tests/MIPS32ISAUnitTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/MIPS32ISAUnitTest.o tests/MIPS32ISAUnitTest.cpp


${TESTDIR}/tests/ConfigFileTest.o: tests/ConfigFileTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ConfigFileTest.o tests/ConfigFileTest.cpp


${OBJECTDIR}/_ext/1966265013/Instrucition_nomain.o: ${OBJECTDIR}/_ext/1966265013/Instrucition.o ../ESimCO/architecture/Instrucition.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1966265013
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1966265013/Instrucition.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1966265013/Instrucition_nomain.o ../ESimCO/architecture/Instrucition.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1966265013/Instrucition.o ${OBJECTDIR}/_ext/1966265013/Instrucition_nomain.o;\
	fi

${OBJECTDIR}/_ext/1145095373/Queue_nomain.o: ${OBJECTDIR}/_ext/1145095373/Queue.o ../ESimCO/common/Queue.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1145095373
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1145095373/Queue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1145095373/Queue_nomain.o ../ESimCO/common/Queue.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1145095373/Queue.o ${OBJECTDIR}/_ext/1145095373/Queue_nomain.o;\
	fi

${OBJECTDIR}/_ext/994054922/ExecutionManager_nomain.o: ${OBJECTDIR}/_ext/994054922/ExecutionManager.o ../ESimCO/execution/ExecutionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/994054922
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/994054922/ExecutionManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/994054922/ExecutionManager_nomain.o ../ESimCO/execution/ExecutionManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/994054922/ExecutionManager.o ${OBJECTDIR}/_ext/994054922/ExecutionManager_nomain.o;\
	fi

${OBJECTDIR}/_ext/1422153699/MemoryRequest_nomain.o: ${OBJECTDIR}/_ext/1422153699/MemoryRequest.o ../ESimCO/memory/MemoryRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422153699
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1422153699/MemoryRequest.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1422153699/MemoryRequest_nomain.o ../ESimCO/memory/MemoryRequest.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1422153699/MemoryRequest.o ${OBJECTDIR}/_ext/1422153699/MemoryRequest_nomain.o;\
	fi

${OBJECTDIR}/_ext/1422153699/MemoryResponse_nomain.o: ${OBJECTDIR}/_ext/1422153699/MemoryResponse.o ../ESimCO/memory/MemoryResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422153699
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1422153699/MemoryResponse.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1422153699/MemoryResponse_nomain.o ../ESimCO/memory/MemoryResponse.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1422153699/MemoryResponse.o ${OBJECTDIR}/_ext/1422153699/MemoryResponse_nomain.o;\
	fi

${OBJECTDIR}/_ext/997839248/FetchStage_nomain.o: ${OBJECTDIR}/_ext/997839248/FetchStage.o ../ESimCO/processor/FetchStage.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/997839248
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/997839248/FetchStage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/997839248/FetchStage_nomain.o ../ESimCO/processor/FetchStage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/997839248/FetchStage.o ${OBJECTDIR}/_ext/997839248/FetchStage_nomain.o;\
	fi

${OBJECTDIR}/_ext/997839248/Processor_nomain.o: ${OBJECTDIR}/_ext/997839248/Processor.o ../ESimCO/processor/Processor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/997839248
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/997839248/Processor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/997839248/Processor_nomain.o ../ESimCO/processor/Processor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/997839248/Processor.o ${OBJECTDIR}/_ext/997839248/Processor_nomain.o;\
	fi

${OBJECTDIR}/_ext/1612582161/InterconnectionNetwork_nomain.o: ${OBJECTDIR}/_ext/1612582161/InterconnectionNetwork.o ../ESimCO/system/InterconnectionNetwork.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1612582161
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1612582161/InterconnectionNetwork.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1612582161/InterconnectionNetwork_nomain.o ../ESimCO/system/InterconnectionNetwork.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1612582161/InterconnectionNetwork.o ${OBJECTDIR}/_ext/1612582161/InterconnectionNetwork_nomain.o;\
	fi

${OBJECTDIR}/architecture/Loader_nomain.o: ${OBJECTDIR}/architecture/Loader.o architecture/Loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	@NMOUTPUT=`${NM} ${OBJECTDIR}/architecture/Loader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/Loader_nomain.o architecture/Loader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/architecture/Loader.o ${OBJECTDIR}/architecture/Loader_nomain.o;\
	fi

${OBJECTDIR}/architecture/MIPS32ISA_nomain.o: ${OBJECTDIR}/architecture/MIPS32ISA.o architecture/MIPS32ISA.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	@NMOUTPUT=`${NM} ${OBJECTDIR}/architecture/MIPS32ISA.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/MIPS32ISA_nomain.o architecture/MIPS32ISA.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/architecture/MIPS32ISA.o ${OBJECTDIR}/architecture/MIPS32ISA_nomain.o;\
	fi

${OBJECTDIR}/architecture/MIPS32Loader_nomain.o: ${OBJECTDIR}/architecture/MIPS32Loader.o architecture/MIPS32Loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	@NMOUTPUT=`${NM} ${OBJECTDIR}/architecture/MIPS32Loader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/MIPS32Loader_nomain.o architecture/MIPS32Loader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/architecture/MIPS32Loader.o ${OBJECTDIR}/architecture/MIPS32Loader_nomain.o;\
	fi

${OBJECTDIR}/architecture/StaticInstruction_nomain.o: ${OBJECTDIR}/architecture/StaticInstruction.o architecture/StaticInstruction.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	@NMOUTPUT=`${NM} ${OBJECTDIR}/architecture/StaticInstruction.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/StaticInstruction_nomain.o architecture/StaticInstruction.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/architecture/StaticInstruction.o ${OBJECTDIR}/architecture/StaticInstruction_nomain.o;\
	fi

${OBJECTDIR}/common/SimpleFileParser_nomain.o: ${OBJECTDIR}/common/SimpleFileParser.o common/SimpleFileParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	@NMOUTPUT=`${NM} ${OBJECTDIR}/common/SimpleFileParser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/SimpleFileParser_nomain.o common/SimpleFileParser.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/common/SimpleFileParser.o ${OBJECTDIR}/common/SimpleFileParser_nomain.o;\
	fi

${OBJECTDIR}/execution/ConfigManager_nomain.o: ${OBJECTDIR}/execution/ConfigManager.o execution/ConfigManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/execution
	@NMOUTPUT=`${NM} ${OBJECTDIR}/execution/ConfigManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/execution/ConfigManager_nomain.o execution/ConfigManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/execution/ConfigManager.o ${OBJECTDIR}/execution/ConfigManager_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/system/ComputationalSystem_nomain.o: ${OBJECTDIR}/system/ComputationalSystem.o system/ComputationalSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/system/ComputationalSystem.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/ComputationalSystem_nomain.o system/ComputationalSystem.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/system/ComputationalSystem.o ${OBJECTDIR}/system/ComputationalSystem_nomain.o;\
	fi

${OBJECTDIR}/system/MemoryMapEntry_nomain.o: ${OBJECTDIR}/system/MemoryMapEntry.o system/MemoryMapEntry.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/system/MemoryMapEntry.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/MemoryMapEntry_nomain.o system/MemoryMapEntry.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/system/MemoryMapEntry.o ${OBJECTDIR}/system/MemoryMapEntry_nomain.o;\
	fi

${OBJECTDIR}/system/MemorySystem_nomain.o: ${OBJECTDIR}/system/MemorySystem.o system/MemorySystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/system/MemorySystem.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/MemorySystem_nomain.o system/MemorySystem.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/system/MemorySystem.o ${OBJECTDIR}/system/MemorySystem_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/esimco.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
