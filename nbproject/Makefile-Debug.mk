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
CND_PLATFORM=MinGW_TDM-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1966265013/Instruction.o \
	${OBJECTDIR}/_ext/1422153699/MemoryRequest.o \
	${OBJECTDIR}/_ext/1422153699/MemoryResponse.o \
	${OBJECTDIR}/_ext/997839248/FetchStage.o \
	${OBJECTDIR}/_ext/997839248/Processor.o \
	${OBJECTDIR}/architecture/Loader.o \
	${OBJECTDIR}/architecture/MIPS32ISA.o \
	${OBJECTDIR}/architecture/MIPS32Loader.o \
	${OBJECTDIR}/architecture/Operand.o \
	${OBJECTDIR}/architecture/StaticInstruction.o \
	${OBJECTDIR}/common/Queue.o \
	${OBJECTDIR}/common/SimpleFileParser.o \
	${OBJECTDIR}/debug/MemoryDebug.o \
	${OBJECTDIR}/interconnect/Bus.o \
	${OBJECTDIR}/interconnect/GlobalInterconnectionNetwork.o \
	${OBJECTDIR}/interconnect/InterconnectionNetwork.o \
	${OBJECTDIR}/interconnect/Message.o \
	${OBJECTDIR}/interconnect/P2PLink.o \
	${OBJECTDIR}/interconnect/PacketSwitch.o \
	${OBJECTDIR}/interconnect/RoutingAlgorithm.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/memory/Cache.o \
	${OBJECTDIR}/memory/IMessageDispatcher.o \
	${OBJECTDIR}/memory/MemoryDevice.o \
	${OBJECTDIR}/memory/MemoryTable.o \
	${OBJECTDIR}/memory/RAM.o \
	${OBJECTDIR}/processor/ExecuteStage.o \
	${OBJECTDIR}/processor/FunctionalUnit.o \
	${OBJECTDIR}/processor/Register.o \
	${OBJECTDIR}/processor/RegisterFile.o \
	${OBJECTDIR}/processor/SimpleUnpipedProcessor.o \
	${OBJECTDIR}/simulator/ConfigManager.o \
	${OBJECTDIR}/simulator/ExecutionManager.o \
	${OBJECTDIR}/simulator/ISimulable.o \
	${OBJECTDIR}/simulator/StatisticsManager.o \
	${OBJECTDIR}/simulator/TraceManager.o \
	${OBJECTDIR}/system/ComputationalSystem.o \
	${OBJECTDIR}/system/MemoryMapEntry.o \
	${OBJECTDIR}/system/MemorySystem.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f6 \
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

${OBJECTDIR}/_ext/1966265013/Instruction.o: ../ESimCO/architecture/Instruction.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1966265013
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1966265013/Instruction.o ../ESimCO/architecture/Instruction.cpp

${OBJECTDIR}/_ext/1422153699/MemoryRequest.o: ../ESimCO/memory/MemoryRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422153699
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1422153699/MemoryRequest.o ../ESimCO/memory/MemoryRequest.cpp

${OBJECTDIR}/_ext/1422153699/MemoryResponse.o: ../ESimCO/memory/MemoryResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422153699
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1422153699/MemoryResponse.o ../ESimCO/memory/MemoryResponse.cpp

${OBJECTDIR}/_ext/997839248/FetchStage.o: ../ESimCO/processor/FetchStage.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/997839248
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/997839248/FetchStage.o ../ESimCO/processor/FetchStage.cpp

${OBJECTDIR}/_ext/997839248/Processor.o: ../ESimCO/processor/Processor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/997839248
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/997839248/Processor.o ../ESimCO/processor/Processor.cpp

${OBJECTDIR}/architecture/Loader.o: architecture/Loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/Loader.o architecture/Loader.cpp

${OBJECTDIR}/architecture/MIPS32ISA.o: architecture/MIPS32ISA.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/MIPS32ISA.o architecture/MIPS32ISA.cpp

${OBJECTDIR}/architecture/MIPS32Loader.o: architecture/MIPS32Loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/MIPS32Loader.o architecture/MIPS32Loader.cpp

${OBJECTDIR}/architecture/Operand.o: architecture/Operand.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/Operand.o architecture/Operand.cpp

${OBJECTDIR}/architecture/StaticInstruction.o: architecture/StaticInstruction.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/StaticInstruction.o architecture/StaticInstruction.cpp

${OBJECTDIR}/common/Queue.o: common/Queue.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/Queue.o common/Queue.cpp

${OBJECTDIR}/common/SimpleFileParser.o: common/SimpleFileParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/SimpleFileParser.o common/SimpleFileParser.cpp

${OBJECTDIR}/debug/MemoryDebug.o: debug/MemoryDebug.cpp 
	${MKDIR} -p ${OBJECTDIR}/debug
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/debug/MemoryDebug.o debug/MemoryDebug.cpp

${OBJECTDIR}/interconnect/Bus.o: interconnect/Bus.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/Bus.o interconnect/Bus.cpp

${OBJECTDIR}/interconnect/GlobalInterconnectionNetwork.o: interconnect/GlobalInterconnectionNetwork.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/GlobalInterconnectionNetwork.o interconnect/GlobalInterconnectionNetwork.cpp

${OBJECTDIR}/interconnect/InterconnectionNetwork.o: interconnect/InterconnectionNetwork.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/InterconnectionNetwork.o interconnect/InterconnectionNetwork.cpp

${OBJECTDIR}/interconnect/Message.o: interconnect/Message.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/Message.o interconnect/Message.cpp

${OBJECTDIR}/interconnect/P2PLink.o: interconnect/P2PLink.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/P2PLink.o interconnect/P2PLink.cpp

${OBJECTDIR}/interconnect/PacketSwitch.o: interconnect/PacketSwitch.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/PacketSwitch.o interconnect/PacketSwitch.cpp

${OBJECTDIR}/interconnect/RoutingAlgorithm.o: interconnect/RoutingAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/RoutingAlgorithm.o interconnect/RoutingAlgorithm.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/memory/Cache.o: memory/Cache.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory/Cache.o memory/Cache.cpp

${OBJECTDIR}/memory/IMessageDispatcher.o: memory/IMessageDispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory/IMessageDispatcher.o memory/IMessageDispatcher.cpp

${OBJECTDIR}/memory/MemoryDevice.o: memory/MemoryDevice.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory/MemoryDevice.o memory/MemoryDevice.cpp

${OBJECTDIR}/memory/MemoryTable.o: memory/MemoryTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory/MemoryTable.o memory/MemoryTable.cpp

${OBJECTDIR}/memory/RAM.o: memory/RAM.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory/RAM.o memory/RAM.cpp

${OBJECTDIR}/processor/ExecuteStage.o: processor/ExecuteStage.cpp 
	${MKDIR} -p ${OBJECTDIR}/processor
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/processor/ExecuteStage.o processor/ExecuteStage.cpp

${OBJECTDIR}/processor/FunctionalUnit.o: processor/FunctionalUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/processor
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/processor/FunctionalUnit.o processor/FunctionalUnit.cpp

${OBJECTDIR}/processor/Register.o: processor/Register.cpp 
	${MKDIR} -p ${OBJECTDIR}/processor
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/processor/Register.o processor/Register.cpp

${OBJECTDIR}/processor/RegisterFile.o: processor/RegisterFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/processor
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/processor/RegisterFile.o processor/RegisterFile.cpp

${OBJECTDIR}/processor/SimpleUnpipedProcessor.o: processor/SimpleUnpipedProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/processor
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/processor/SimpleUnpipedProcessor.o processor/SimpleUnpipedProcessor.cpp

${OBJECTDIR}/simulator/ConfigManager.o: simulator/ConfigManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/simulator
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator/ConfigManager.o simulator/ConfigManager.cpp

${OBJECTDIR}/simulator/ExecutionManager.o: simulator/ExecutionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/simulator
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator/ExecutionManager.o simulator/ExecutionManager.cpp

${OBJECTDIR}/simulator/ISimulable.o: simulator/ISimulable.cpp 
	${MKDIR} -p ${OBJECTDIR}/simulator
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator/ISimulable.o simulator/ISimulable.cpp

${OBJECTDIR}/simulator/StatisticsManager.o: simulator/StatisticsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/simulator
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator/StatisticsManager.o simulator/StatisticsManager.cpp

${OBJECTDIR}/simulator/TraceManager.o: simulator/TraceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/simulator
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator/TraceManager.o simulator/TraceManager.cpp

${OBJECTDIR}/system/ComputationalSystem.o: system/ComputationalSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/ComputationalSystem.o system/ComputationalSystem.cpp

${OBJECTDIR}/system/MemoryMapEntry.o: system/MemoryMapEntry.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/MemoryMapEntry.o system/MemoryMapEntry.cpp

${OBJECTDIR}/system/MemorySystem.o: system/MemorySystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/MemorySystem.o system/MemorySystem.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/MemoryHierarchyTests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/MIPS32ISAUnitTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/MultipleProcessorTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/RoutingAlgorithmTests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/SimpleUnpipedProcessorTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/MainTests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/MemoryHierarchyTests.o: tests/MemoryHierarchyTests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/MemoryHierarchyTests.o tests/MemoryHierarchyTests.cpp


${TESTDIR}/tests/MIPS32ISAUnitTest.o: tests/MIPS32ISAUnitTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/MIPS32ISAUnitTest.o tests/MIPS32ISAUnitTest.cpp


${TESTDIR}/tests/MultipleProcessorTest.o: tests/MultipleProcessorTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/MultipleProcessorTest.o tests/MultipleProcessorTest.cpp


${TESTDIR}/tests/RoutingAlgorithmTests.o: tests/RoutingAlgorithmTests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/RoutingAlgorithmTests.o tests/RoutingAlgorithmTests.cpp


${TESTDIR}/tests/SimpleUnpipedProcessorTest.o: tests/SimpleUnpipedProcessorTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/SimpleUnpipedProcessorTest.o tests/SimpleUnpipedProcessorTest.cpp


${TESTDIR}/tests/MainTests.o: tests/MainTests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/MainTests.o tests/MainTests.cpp


${OBJECTDIR}/_ext/1966265013/Instruction_nomain.o: ${OBJECTDIR}/_ext/1966265013/Instruction.o ../ESimCO/architecture/Instruction.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1966265013
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1966265013/Instruction.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1966265013/Instruction_nomain.o ../ESimCO/architecture/Instruction.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1966265013/Instruction.o ${OBJECTDIR}/_ext/1966265013/Instruction_nomain.o;\
	fi

${OBJECTDIR}/_ext/1422153699/MemoryRequest_nomain.o: ${OBJECTDIR}/_ext/1422153699/MemoryRequest.o ../ESimCO/memory/MemoryRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1422153699
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1422153699/MemoryRequest.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1422153699/MemoryRequest_nomain.o ../ESimCO/memory/MemoryRequest.cpp;\
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
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1422153699/MemoryResponse_nomain.o ../ESimCO/memory/MemoryResponse.cpp;\
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
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/997839248/FetchStage_nomain.o ../ESimCO/processor/FetchStage.cpp;\
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
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/997839248/Processor_nomain.o ../ESimCO/processor/Processor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/997839248/Processor.o ${OBJECTDIR}/_ext/997839248/Processor_nomain.o;\
	fi

${OBJECTDIR}/architecture/Loader_nomain.o: ${OBJECTDIR}/architecture/Loader.o architecture/Loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	@NMOUTPUT=`${NM} ${OBJECTDIR}/architecture/Loader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/Loader_nomain.o architecture/Loader.cpp;\
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
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/MIPS32ISA_nomain.o architecture/MIPS32ISA.cpp;\
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
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/MIPS32Loader_nomain.o architecture/MIPS32Loader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/architecture/MIPS32Loader.o ${OBJECTDIR}/architecture/MIPS32Loader_nomain.o;\
	fi

${OBJECTDIR}/architecture/Operand_nomain.o: ${OBJECTDIR}/architecture/Operand.o architecture/Operand.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	@NMOUTPUT=`${NM} ${OBJECTDIR}/architecture/Operand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/Operand_nomain.o architecture/Operand.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/architecture/Operand.o ${OBJECTDIR}/architecture/Operand_nomain.o;\
	fi

${OBJECTDIR}/architecture/StaticInstruction_nomain.o: ${OBJECTDIR}/architecture/StaticInstruction.o architecture/StaticInstruction.cpp 
	${MKDIR} -p ${OBJECTDIR}/architecture
	@NMOUTPUT=`${NM} ${OBJECTDIR}/architecture/StaticInstruction.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/architecture/StaticInstruction_nomain.o architecture/StaticInstruction.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/architecture/StaticInstruction.o ${OBJECTDIR}/architecture/StaticInstruction_nomain.o;\
	fi

${OBJECTDIR}/common/Queue_nomain.o: ${OBJECTDIR}/common/Queue.o common/Queue.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	@NMOUTPUT=`${NM} ${OBJECTDIR}/common/Queue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/Queue_nomain.o common/Queue.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/common/Queue.o ${OBJECTDIR}/common/Queue_nomain.o;\
	fi

${OBJECTDIR}/common/SimpleFileParser_nomain.o: ${OBJECTDIR}/common/SimpleFileParser.o common/SimpleFileParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	@NMOUTPUT=`${NM} ${OBJECTDIR}/common/SimpleFileParser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/SimpleFileParser_nomain.o common/SimpleFileParser.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/common/SimpleFileParser.o ${OBJECTDIR}/common/SimpleFileParser_nomain.o;\
	fi

${OBJECTDIR}/debug/MemoryDebug_nomain.o: ${OBJECTDIR}/debug/MemoryDebug.o debug/MemoryDebug.cpp 
	${MKDIR} -p ${OBJECTDIR}/debug
	@NMOUTPUT=`${NM} ${OBJECTDIR}/debug/MemoryDebug.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/debug/MemoryDebug_nomain.o debug/MemoryDebug.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/debug/MemoryDebug.o ${OBJECTDIR}/debug/MemoryDebug_nomain.o;\
	fi

${OBJECTDIR}/interconnect/Bus_nomain.o: ${OBJECTDIR}/interconnect/Bus.o interconnect/Bus.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interconnect/Bus.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/Bus_nomain.o interconnect/Bus.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/interconnect/Bus.o ${OBJECTDIR}/interconnect/Bus_nomain.o;\
	fi

${OBJECTDIR}/interconnect/GlobalInterconnectionNetwork_nomain.o: ${OBJECTDIR}/interconnect/GlobalInterconnectionNetwork.o interconnect/GlobalInterconnectionNetwork.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interconnect/GlobalInterconnectionNetwork.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/GlobalInterconnectionNetwork_nomain.o interconnect/GlobalInterconnectionNetwork.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/interconnect/GlobalInterconnectionNetwork.o ${OBJECTDIR}/interconnect/GlobalInterconnectionNetwork_nomain.o;\
	fi

${OBJECTDIR}/interconnect/InterconnectionNetwork_nomain.o: ${OBJECTDIR}/interconnect/InterconnectionNetwork.o interconnect/InterconnectionNetwork.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interconnect/InterconnectionNetwork.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/InterconnectionNetwork_nomain.o interconnect/InterconnectionNetwork.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/interconnect/InterconnectionNetwork.o ${OBJECTDIR}/interconnect/InterconnectionNetwork_nomain.o;\
	fi

${OBJECTDIR}/interconnect/Message_nomain.o: ${OBJECTDIR}/interconnect/Message.o interconnect/Message.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interconnect/Message.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/Message_nomain.o interconnect/Message.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/interconnect/Message.o ${OBJECTDIR}/interconnect/Message_nomain.o;\
	fi

${OBJECTDIR}/interconnect/P2PLink_nomain.o: ${OBJECTDIR}/interconnect/P2PLink.o interconnect/P2PLink.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interconnect/P2PLink.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/P2PLink_nomain.o interconnect/P2PLink.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/interconnect/P2PLink.o ${OBJECTDIR}/interconnect/P2PLink_nomain.o;\
	fi

${OBJECTDIR}/interconnect/PacketSwitch_nomain.o: ${OBJECTDIR}/interconnect/PacketSwitch.o interconnect/PacketSwitch.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interconnect/PacketSwitch.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/PacketSwitch_nomain.o interconnect/PacketSwitch.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/interconnect/PacketSwitch.o ${OBJECTDIR}/interconnect/PacketSwitch_nomain.o;\
	fi

${OBJECTDIR}/interconnect/RoutingAlgorithm_nomain.o: ${OBJECTDIR}/interconnect/RoutingAlgorithm.o interconnect/RoutingAlgorithm.cpp 
	${MKDIR} -p ${OBJECTDIR}/interconnect
	@NMOUTPUT=`${NM} ${OBJECTDIR}/interconnect/RoutingAlgorithm.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/interconnect/RoutingAlgorithm_nomain.o interconnect/RoutingAlgorithm.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/interconnect/RoutingAlgorithm.o ${OBJECTDIR}/interconnect/RoutingAlgorithm_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/memory/Cache_nomain.o: ${OBJECTDIR}/memory/Cache.o memory/Cache.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	@NMOUTPUT=`${NM} ${OBJECTDIR}/memory/Cache.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory/Cache_nomain.o memory/Cache.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/memory/Cache.o ${OBJECTDIR}/memory/Cache_nomain.o;\
	fi

${OBJECTDIR}/memory/IMessageDispatcher_nomain.o: ${OBJECTDIR}/memory/IMessageDispatcher.o memory/IMessageDispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	@NMOUTPUT=`${NM} ${OBJECTDIR}/memory/IMessageDispatcher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory/IMessageDispatcher_nomain.o memory/IMessageDispatcher.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/memory/IMessageDispatcher.o ${OBJECTDIR}/memory/IMessageDispatcher_nomain.o;\
	fi

${OBJECTDIR}/memory/MemoryDevice_nomain.o: ${OBJECTDIR}/memory/MemoryDevice.o memory/MemoryDevice.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	@NMOUTPUT=`${NM} ${OBJECTDIR}/memory/MemoryDevice.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory/MemoryDevice_nomain.o memory/MemoryDevice.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/memory/MemoryDevice.o ${OBJECTDIR}/memory/MemoryDevice_nomain.o;\
	fi

${OBJECTDIR}/memory/MemoryTable_nomain.o: ${OBJECTDIR}/memory/MemoryTable.o memory/MemoryTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	@NMOUTPUT=`${NM} ${OBJECTDIR}/memory/MemoryTable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory/MemoryTable_nomain.o memory/MemoryTable.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/memory/MemoryTable.o ${OBJECTDIR}/memory/MemoryTable_nomain.o;\
	fi

${OBJECTDIR}/memory/RAM_nomain.o: ${OBJECTDIR}/memory/RAM.o memory/RAM.cpp 
	${MKDIR} -p ${OBJECTDIR}/memory
	@NMOUTPUT=`${NM} ${OBJECTDIR}/memory/RAM.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/memory/RAM_nomain.o memory/RAM.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/memory/RAM.o ${OBJECTDIR}/memory/RAM_nomain.o;\
	fi

${OBJECTDIR}/processor/ExecuteStage_nomain.o: ${OBJECTDIR}/processor/ExecuteStage.o processor/ExecuteStage.cpp 
	${MKDIR} -p ${OBJECTDIR}/processor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/processor/ExecuteStage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/processor/ExecuteStage_nomain.o processor/ExecuteStage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/processor/ExecuteStage.o ${OBJECTDIR}/processor/ExecuteStage_nomain.o;\
	fi

${OBJECTDIR}/processor/FunctionalUnit_nomain.o: ${OBJECTDIR}/processor/FunctionalUnit.o processor/FunctionalUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/processor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/processor/FunctionalUnit.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/processor/FunctionalUnit_nomain.o processor/FunctionalUnit.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/processor/FunctionalUnit.o ${OBJECTDIR}/processor/FunctionalUnit_nomain.o;\
	fi

${OBJECTDIR}/processor/Register_nomain.o: ${OBJECTDIR}/processor/Register.o processor/Register.cpp 
	${MKDIR} -p ${OBJECTDIR}/processor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/processor/Register.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/processor/Register_nomain.o processor/Register.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/processor/Register.o ${OBJECTDIR}/processor/Register_nomain.o;\
	fi

${OBJECTDIR}/processor/RegisterFile_nomain.o: ${OBJECTDIR}/processor/RegisterFile.o processor/RegisterFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/processor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/processor/RegisterFile.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/processor/RegisterFile_nomain.o processor/RegisterFile.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/processor/RegisterFile.o ${OBJECTDIR}/processor/RegisterFile_nomain.o;\
	fi

${OBJECTDIR}/processor/SimpleUnpipedProcessor_nomain.o: ${OBJECTDIR}/processor/SimpleUnpipedProcessor.o processor/SimpleUnpipedProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/processor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/processor/SimpleUnpipedProcessor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/processor/SimpleUnpipedProcessor_nomain.o processor/SimpleUnpipedProcessor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/processor/SimpleUnpipedProcessor.o ${OBJECTDIR}/processor/SimpleUnpipedProcessor_nomain.o;\
	fi

${OBJECTDIR}/simulator/ConfigManager_nomain.o: ${OBJECTDIR}/simulator/ConfigManager.o simulator/ConfigManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/simulator
	@NMOUTPUT=`${NM} ${OBJECTDIR}/simulator/ConfigManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator/ConfigManager_nomain.o simulator/ConfigManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/simulator/ConfigManager.o ${OBJECTDIR}/simulator/ConfigManager_nomain.o;\
	fi

${OBJECTDIR}/simulator/ExecutionManager_nomain.o: ${OBJECTDIR}/simulator/ExecutionManager.o simulator/ExecutionManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/simulator
	@NMOUTPUT=`${NM} ${OBJECTDIR}/simulator/ExecutionManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator/ExecutionManager_nomain.o simulator/ExecutionManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/simulator/ExecutionManager.o ${OBJECTDIR}/simulator/ExecutionManager_nomain.o;\
	fi

${OBJECTDIR}/simulator/ISimulable_nomain.o: ${OBJECTDIR}/simulator/ISimulable.o simulator/ISimulable.cpp 
	${MKDIR} -p ${OBJECTDIR}/simulator
	@NMOUTPUT=`${NM} ${OBJECTDIR}/simulator/ISimulable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator/ISimulable_nomain.o simulator/ISimulable.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/simulator/ISimulable.o ${OBJECTDIR}/simulator/ISimulable_nomain.o;\
	fi

${OBJECTDIR}/simulator/StatisticsManager_nomain.o: ${OBJECTDIR}/simulator/StatisticsManager.o simulator/StatisticsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/simulator
	@NMOUTPUT=`${NM} ${OBJECTDIR}/simulator/StatisticsManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator/StatisticsManager_nomain.o simulator/StatisticsManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/simulator/StatisticsManager.o ${OBJECTDIR}/simulator/StatisticsManager_nomain.o;\
	fi

${OBJECTDIR}/simulator/TraceManager_nomain.o: ${OBJECTDIR}/simulator/TraceManager.o simulator/TraceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/simulator
	@NMOUTPUT=`${NM} ${OBJECTDIR}/simulator/TraceManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator/TraceManager_nomain.o simulator/TraceManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/simulator/TraceManager.o ${OBJECTDIR}/simulator/TraceManager_nomain.o;\
	fi

${OBJECTDIR}/system/ComputationalSystem_nomain.o: ${OBJECTDIR}/system/ComputationalSystem.o system/ComputationalSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/system/ComputationalSystem.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/ComputationalSystem_nomain.o system/ComputationalSystem.cpp;\
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
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/MemoryMapEntry_nomain.o system/MemoryMapEntry.cpp;\
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
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/system/MemorySystem_nomain.o system/MemorySystem.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/system/MemorySystem.o ${OBJECTDIR}/system/MemorySystem_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
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
