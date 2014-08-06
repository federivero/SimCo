/* 
 * File:   main.cpp
 * Author: fede
 *
 * Created on 12 de diciembre de 2013, 03:50 PM
 */

#include <cstdlib>

#include "simulator/ConfigManager.h"
#include "system/MemorySystem.h"
#include <iostream>
#include <string.h>
#include <string>
#include "common/SimpleFileParser.h"
#include "memory/MemoryDevice.h"
#include "memory/Cache.h"
#include "interconnect/Bus.h"
#include "exceptions/RuntimeException.h"
#include "processor/SimpleUnpipedProcessor.h"
#include "processor/Processor.h"
#include "architecture/MIPS32ISA.h"
#include "memory/RAM.h"
#include "architecture/MIPS32Loader.h"

#define END_COMMAND "end"
#define SIMPLE_UNPIPED_PROCESSOR_COMMAND "simpleunpipedprocessor"
#define CACHE_COMMAND "cache"
#define RAM_COMMAND "ram"
#define BUS_COMMAND "bus"
        
#define PROPERTY_NAME "name"
#define PROPERTY_ISA "isa"
#define PROPERTY_CYCLE_LIMIT "cyclelimit"

// SimpleUnpipedProcessor properties
#define PROPERTY_CPU_DATA_MEMORY_INTERFACE "datameminterface"
#define PROPERTY_CPU_INST_MEMORY_INTERFACE "instmeminterface"
#define PROPERTY_PC_VALUE "pcvalue"

// Memory Device properties
#define PROPERTY_LATENCY "latency"
#define PROPERTY_PORT_COUNT "ports"

//Cache properties
#define PROPERTY_SET_COUNT "setcount"
#define PROPERTY_ASSOCIATIVITY "associativity"
#define PROPERTY_LINE_SIZE "linesize"
#define PROPERTY_REPLACEMENT_POLICY "replpolicy"
#define PROPERTY_WRITE_POLICY "writepolicy"
#define PROPERTY_COHERENCE_PROTOCOL "coherence"
#define PROPERTY_UPPER_INTERFACE "upperinterface"
#define PROPERTY_LOWER_INTERFACE "lowerinterface"

// RAM specific properties
#define PROPERTY_CAPACITY "capacity"
#define PROPERTY_INTERFACE "interface"

// Property values
#define ISA_MIPS_32_STRING "mips32"
#define REPLACEMENT_POLICY_FIFO "fifo"
#define REPLACEMENT_POLICY_LRU "lru"
#define REPLACEMENT_POLICY_RANDOM "random"
#define WRITE_POLICY_WRITE_BACK "writeback"
#define WRITE_POLICY_WRITE_THROUGH "writethrough"
#define COHERENCE_PROTOCOL_MSI "msi"
#define COHERENCE_PROTOCOL_MESI "mesi"

// Default values
#define PC_DEFAULT_VALUE "0x1000"
#define ISA_DEFAULT_VALUE "mips32isa"

using namespace std;

// Enumerate to note what kind of device is currently being parsed
enum DefinitionType{
    DEF_TYPE_CACHE, DEF_TYPE_RAM, DEF_TYPE_BUS, DEF_TYPE_SIMPLE_UNPIPED_PROCESSOR,
    DEF_TYPE_UNDEFINED // Definition starts as undefined
};

void printUsage(){
    cout << "SimCo usage: " << endl << endl;
    cout << "SimCo uses two files as input, a configuration File and a Program File. ";
    cout << "The configuration file describes the target architecture to be used in the simulation ";
    cout << "and the program file sets the initial memory content in the simulation. " << endl << endl;

    cout << "SimCo provides two output files at best, one with statistical information about the simulation ";
    cout << "(stats file) and a second one with a trace of the simulation (which basically describes what happened ";
    cout << "every clock cycle." << endl << endl;

    cout << "SimCo parameters are: " << endl << endl;
    cout << " -config             : path to the configuration file (required). " << endl;
    cout << " -program            : path to the program file (required). " << endl;
    cout << " -stats              : name of the output stats file (optional). " << endl;
    cout << " -trace              : name of the output trace file (optional). " << endl << endl;

    cout << "Configuration File Format: " << endl << endl;
    cout << "SimpleUnpipedProcessor Definition: " << endl << endl;
    cout << "simpleunpipedprocessor" << endl;
    cout << "name                          : name of the processor " << endl;
    cout << "datameminterface              : name of the bus or network to access data memory " << endl;
    cout << "instmeminterface              : name of the bus or network to access instruction memory " << endl;
    cout << "pcvalue                       : startup PC value " << endl;
    cout << "end " << endl << endl;
   
    cout << "RAM Definition: " << endl << endl;
    cout << "RAM " << endl;
    cout << "name                          : name of the RAM chip " << endl;
    cout << "capacity                      : memory capacity in bytes " << endl;
    cout << "ports                         : number of R/W ports on memory" << endl;
    cout << "latency                       : latency of the memory in cycles" << endl;
    cout << "interface                     : name of the bus or networks which access this memory device " << endl << endl;

    cout << "Cache Definition: " << endl << endl;
    cout << "cache " << endl;
    cout << "name                          : name of the cache " << endl;
    cout << "setcount                      : number of sets in the cache (1 for fully associative caches, must be a power of two)" << endl;
    cout << "associativity                 : number of ways in each set (1 for direct mapped)" << endl;
    cout << "linesize                      : line size in bytes (must be a power of two) " << endl;
    cout << "replpolicy                    : replacement policy being used (lru, fifo, random) " << endl;
    cout << "writepolicy                   : write policy used by this cache (writethrough, writeback)" << endl;
    cout << "coherence                     : coherence protocol being used (msi, mesi, nocoherence)" << endl;
    cout << "ports                         : number of R/W ports on memory " << endl;
    cout << "latency                       : hit latency of the memory in cycles " << endl;
    cout << "upperinterface                : name of the bus or network to access upper memory hierarchy " << endl;
    cout << "lowerinterface                : name of the bus or network to access lower memory hierarchy " << endl;
    cout << "end" << endl << endl;

    cout << "Bus definition " << endl << endl;
    cout << "bus" << endl;
    cout << "name                          : name of the bus " << endl;
    cout << "width                         : bus width in bytes " << endl;
    cout << "end" << endl << endl;

}

void printUsageAndClose(int exitCode){
    printUsage();
    exit(exitCode);
}


int main(int argc, char** argv) {
    try{
    bool argumentError = false;
    int endCycle = -1;
    char* traceFile = NULL;
    char* traceMode = NULL;
    char* configFile = NULL;
    char* statsFile = NULL;
    char* programFile = NULL;
    
    // Check for line parameters
    for (int i = 1; i < argc; i++){
        if (argv[i][0] != '-'){
            argumentError = true;
            break;
        }
        if (strcmp(argv[i],"-trace") == 0){
            traceFile = argv[i+1];
            i++;
        }else if (strcmp(argv[i],"-program") == 0){
            programFile = argv[i+1];    
            i++;
        }else if (strcmp(argv[i],"-config") == 0){
            configFile = argv[i+1];
            i++;
        }else if (strcmp(argv[i],"-stats") == 0){
            statsFile = argv[i+1];
            i++;
        }else if (strcmp(argv[i],"-help") == 0){
            printUsageAndClose(0);
        }
    }
    
    if (argumentError){
        printUsageAndClose(1);
    }
    
    // Initialize config variables
    GenMap<string,Processor*>* processorMap = new ListMap<string,Processor*>(100);
    GenMap<string,MemoryDevice*>* memDevicesMap = new ListMap<string,MemoryDevice*>(100);
    GenMap<string,InterconnectionNetwork*>* interconnectMap = new ListMap<string,InterconnectionNetwork*>(100);
    List<ISimulable*>* simulatedDevices = new List<ISimulable*>();
    List<Processor*>* processors = new List<Processor*>();
    List<MemoryDevice*>* memoryDevices = new List<MemoryDevice*>();
    List<InterconnectionNetwork*>* interfaces = new List<InterconnectionNetwork*>();
    
    GenMap<InterconnectionNetwork*,List<IMessageDispatcher*>* >* interconnectDevices = 
                        new ListMap<InterconnectionNetwork*,List<IMessageDispatcher*>* >(100);
    
    // Get reference to TraceManager
    TraceManager* tracer = TraceManager::getInstance();
    
    // Create basic systems
    ComputationalSystem* compSys = new ComputationalSystem();
    
    // Initialize execution manager
    ExecutionManager* simulator = ExecutionManager::getInstance();
    simulator->initialize();
    simulator->setComputationalSystem(compSys);
    
    
    // Initialize tracer
    if (traceFile != NULL){
        tracer->setFileName(traceFile);
        tracer->startTrace();
        // TODO: implement range tracing
        tracer->setEnabled(true);
    }
    
    SimpleFileParser* sfp = new SimpleFileParser();
    if (!sfp->open(configFile)){
        printUsageAndClose(1);
    } 
    sfp->set_single_char_tokens("=");
    
    // Variable declaration
    bool deviceDefOn = false;
    DefinitionType defType = DEF_TYPE_UNDEFINED;
    Processor* processor;
    Cache* cache;
    MemoryDevice* memDevice;
    Bus* bus;
    RAM* ram;
    ISA* isa;
    ISAType isaType = ISA_TYPE_UNDEFINED;
    
    /* Definition loop. Parse the file, determine each device being declared 
       and store it apropiately */
    while(sfp->get_next_line()){
        if (sfp->get_num_tokens() > 0){
            string firstToken = sfp->get_token(0);
            // Check if line is not a comment
            if (firstToken[0] != '#'){
                // If just one token, then its a command line
                if (sfp->get_num_tokens() == 1){
                    string command = sfp->get_token(0);
                    if (deviceDefOn){
                        if (command.compare(END_COMMAND) == 0){
                            deviceDefOn = false;                       
                        }
                    }else{
                        if (command.compare(SIMPLE_UNPIPED_PROCESSOR_COMMAND) == 0){
                            deviceDefOn = true;
                            processor = new SimpleUnpipedProcessor();
                            defType = DEF_TYPE_SIMPLE_UNPIPED_PROCESSOR;
                        }else if (command.compare(CACHE_COMMAND) == 0){
                            deviceDefOn = true;
                            memDevice = new Cache();
                            defType = DEF_TYPE_CACHE;
                        }else if (command.compare(BUS_COMMAND) == 0){
                            deviceDefOn = true;
                            bus = new Bus();
                            defType = DEF_TYPE_BUS;
                        }else if (command.compare(RAM_COMMAND) == 0){
                            deviceDefOn = true;
                            memDevice = new RAM();
                            defType = DEF_TYPE_RAM;
                        }
                    }
                }else{
                    // Look for name property to insert into map structures
                    if (deviceDefOn){
                        string propertyName = sfp->get_token(0);
                        if (propertyName.compare(PROPERTY_NAME) == 0){
                            string name = sfp->get_token(2);
                            switch(defType){
                                case DEF_TYPE_CACHE:
                                case DEF_TYPE_RAM:
                                    memDevice->setName((char*) name.c_str());
                                    memDevicesMap->put(name,memDevice);
                                    simulatedDevices->add((ISimulable*)memDevice);
                                    memoryDevices->add(memDevice);
                                    break;
                                case DEF_TYPE_BUS:
                                    bus->setName((char*) name.c_str());
                                    interconnectMap->put(name,bus);
                                    simulatedDevices->add((ISimulable*)bus);
                                    interconnectDevices->put(bus,new List<IMessageDispatcher*>());
                                    interfaces->add(bus);
                                    break;
                                case DEF_TYPE_SIMPLE_UNPIPED_PROCESSOR:
                                    processor->setName((char*)name.c_str());
                                    processorMap->put(name,processor);
                                    simulatedDevices->add((ISimulable*)processor);
                                    processors->add(processor); 
                                    break;
                                case DEF_TYPE_UNDEFINED:
                                    throw new RuntimeException("wtf?");
                                    break;
                            }
                        }
                    }else{
                        // Device def OFF, so its a global property
                        string paramName = sfp->get_token(0);
                        string paramValue = sfp->get_token(2);
                        if (paramName.compare(PROPERTY_ISA) == 0){
                            // ISA parameter
                            if (paramValue.compare(ISA_MIPS_32_STRING) == 0){
                                isa = MIPS32ISA::getInstance();
                                isaType = ISA_MIPS_32;
                            }
                            
                            
                        }else if (paramName.compare(PROPERTY_CYCLE_LIMIT) == 0){
                            endCycle = atoi(paramValue.c_str());
                        }
                        
                    }
                }
            }
        }
    }
    // Processor load variables
    string dataMemInterface = string();
    string instructionMemInterface = string();
    string pcvalue = string();
    string iSimulableName = string();
    SimpleUnpipedProcessor* simpleCPU = NULL;
    InterconnectionNetwork* interface = NULL;
    // Memory device load variables
    string latency = string();
    string portCount = string();
    string associativity = string();
    string setCount = string();
    string lineSize = string();
    string replacementPolicy = string();
    string writePolicy = string();
    string coherenceProtocol = string();
    string upperInterface = string();
    string lowerInterface = string();
    // Bus load variables
    
    // Ram load variables
    string capacity = string();
    
    // default base for ascii string numbers
    int base = 10;
    defType = DEF_TYPE_UNDEFINED;
    
    sfp->close();
    sfp->open(configFile);
    
    /* Main configuration loop, parse each line:
     * if starts with # its a comment, if its a single word
     * its the start of the definition of a device
     * if its a property = value line, it defines a property value
     */
    while(sfp->get_next_line()){
        if (sfp->get_num_tokens() > 0){ 
            string firstToken = sfp->get_token(0);
            // Check if line is not a comment
            if (firstToken[0] != '#'){
                // Not a comment, continue to parse. 
                if (sfp->get_num_tokens() == 1){
                    // Single word on line, its a command!
                    if (deviceDefOn){
                        string endComand = sfp->get_token(0);
                        if (endComand.compare(END_COMMAND) == 0){
                            deviceDefOn = false;
                            // Now that the device has ended, add all its properties
                            switch(defType){
                                case DEF_TYPE_SIMPLE_UNPIPED_PROCESSOR:
                                    if (iSimulableName.empty()){
                                        throw new RuntimeException("Undefined name for processor");
                                    }
                                    simpleCPU = (SimpleUnpipedProcessor*) processorMap->getData(iSimulableName);
                                    // Set ISA
                                    simpleCPU->setISA(isa);
                                    // Set PC value
                                    base = 10;
                                    if (pcvalue.rfind("0x") == 0){
                                        base = 16;
                                    }
                                    simpleCPU->setPCValue(strtol(pcvalue.c_str(),NULL,base));
                                    // Set data memory interface
                                    if (dataMemInterface.empty()){
                                        throw new RuntimeException(((string)("Undefined memory interface for processor " + iSimulableName)).c_str());
                                    }else{
                                        interface = interconnectMap->getData(dataMemInterface.c_str());
                                        if (interface == NULL){
                                            throw new RuntimeException(((string)("Undefined memory interface (datameminterface property) for simple unpiped processor " + iSimulableName)).c_str());
                                        }
                                        simpleCPU->setDataMemoryInterface(interface,interconnectDevices->getData(interface));
                                    }
                                    // Set intruction memory interface
                                    if (instructionMemInterface.empty()){
                                        throw new RuntimeException(((string)("Undefined instruction memory interface for processor " + iSimulableName)).c_str());
                                    }else{
                                        interface = interconnectMap->getData(instructionMemInterface.c_str());
                                        if (interface == NULL){
                                            throw new RuntimeException(((string)("Undefined instructin memory interface (instructionmeminterface property) for simple unpiped processor " + iSimulableName)).c_str());
                                        }
                                        IMessageDispatcher* attachedInterface = simpleCPU->setInstructionMemoryInterface(interface);
                                        interconnectDevices->getData(interface)->add(attachedInterface);
                                    }
                                    break;
                                case DEF_TYPE_CACHE:
                                    if (iSimulableName.empty()){
                                        throw new RuntimeException("Undefined name for cache");
                                    }
                                    cache = (Cache*) memDevicesMap->getData(iSimulableName);
                                    // Set set count
                                    if (setCount.empty()){
                                        throw new RuntimeException(((string)("Undefined set count for cache" + iSimulableName)).c_str());
                                    }
                                    cache->setSetCount(atoi(setCount.c_str()));
                                    // Set line size
                                    if (lineSize.empty()){
                                        throw new RuntimeException(((string)("Undefined line size for cache " + iSimulableName)).c_str());
                                    }
                                    cache->setLineSize(atoi(lineSize.c_str()));
                                    // Set associativity
                                    if (associativity.empty()){
                                        throw new RuntimeException(((string)("Undefined associativy  for cache " + iSimulableName)).c_str());
                                    }
                                    cache->setAssociativity(atoi(associativity.c_str()));
                                    // Set latency (default value 1))
                                    cache->setLatency(atoi(latency.c_str()));
                                    // Set port count (default value 1)
                                    cache->setPortCount(atoi(portCount.c_str()));
                                    // Set replacement policy
                                    if (replacementPolicy.compare(REPLACEMENT_POLICY_FIFO) == 0){
                                        cache->setReplacementPolicy(CACHE_REPLACEMENT_FIFO);
                                    }else if (replacementPolicy.compare(REPLACEMENT_POLICY_RANDOM) == 0){
                                        cache->setReplacementPolicy(CACHE_REPLACEMENT_RANDOM);
                                    }else if (replacementPolicy.compare(REPLACEMENT_POLICY_LRU) == 0){
                                        cache->setReplacementPolicy(CACHE_REPLACEMENT_LRU);
                                    }else{
                                        throw new RuntimeException(((string)("Unrecognized replacement policy " + replacementPolicy)).c_str());
                                    }
                                    // Set write policy
                                    if (writePolicy.compare(WRITE_POLICY_WRITE_BACK) == 0){
                                        cache->setWritePolicy(CACHE_WRITE_WRITEBACK);
                                    }else if (writePolicy.compare(WRITE_POLICY_WRITE_THROUGH) == 0){
                                        cache->setWritePolicy(CACHE_WRITE_WRITETHROUGH);
                                    }else{
                                        throw new RuntimeException(((string)("Unrecognized write policy " + writePolicy)).c_str());
                                    }
                                    // Set coherence protocol
                                    if (coherenceProtocol.compare(COHERENCE_PROTOCOL_MSI) == 0){
                                        cache->setCoherenceProtocol(CACHE_COHERENCE_MSI);
                                    }else if (coherenceProtocol.compare(COHERENCE_PROTOCOL_MESI) == 0){
                                        cache->setCoherenceProtocol(CACHE_COHERENCE_MESI);
                                    }else{
                                        throw new RuntimeException(((string)("Unrecognized coherence protocol " + writePolicy)).c_str());
                                    }
                                    cache->initialize();
                                    // Set upper and lower interfaces
                                    if (upperInterface.empty()){
                                        throw new RuntimeException(((string)("Undefined upper hierarchy interface for cache " + iSimulableName)).c_str());
                                    }else{
                                        interface = interconnectMap->getData(upperInterface.c_str());
                                        if (interface == NULL){
                                            throw new RuntimeException(((string)("Unrecognized upper hierarchy interface (upperinterface property) for cache " + iSimulableName)).c_str());
                                        }
                                        cache->setUpperMemoryHierarchyPort(interface);
                                        interconnectDevices->getData(interface)->add(cache);
                                    }
                                    if (lowerInterface.empty()){
                                        throw new RuntimeException(((string)("Undefined lower hierarchy interface for cache " + iSimulableName)).c_str());
                                    }else{
                                        interface = interconnectMap->getData(lowerInterface.c_str());
                                        if (interface == NULL){
                                            throw new RuntimeException(((string)("Unrecognized lower hierarchy interface (upperinterface property) for cache " + iSimulableName)).c_str());
                                        }
                                        cache->setLowerMemoryHierarchyPort(interface);
                                        interconnectDevices->getData(interface)->add(cache);
                                    }
                                    break;
                                case DEF_TYPE_BUS:
                                    if (iSimulableName.empty()){
                                        throw new RuntimeException("Undefined name for bus");
                                    }
                                    bus = (Bus*) interconnectMap->getData(iSimulableName);
                                    // Set port count (default value 1)
                                    bus->setTransfersPerCycle(atoi(portCount.c_str()));
                                    break;
                                case DEF_TYPE_RAM:
                                    if (iSimulableName.empty()){
                                        throw new RuntimeException("Undefined name for RAM");
                                    }
                                    ram = (RAM*) memDevicesMap->getData(iSimulableName);
                                    if (capacity.empty()){
                                        throw new RuntimeException(((string)"Undefined capacity for RAM " + iSimulableName).c_str());
                                    }
                                    base = 10;
                                    if (capacity.rfind((string)"0x") == 0){
                                        base = 16;
                                    }
                                    ram->setCapacity(strtol(capacity.c_str(),NULL,base));
                                    ram->setLatency(atoi(latency.c_str()));
                                    ram->setPorts(atoi(portCount.c_str()));
                                    if (upperInterface.empty()){
                                        throw new RuntimeException(((string)("Undefined upper hierarchy interface for RAM " + iSimulableName)).c_str());
                                    }else{
                                        interface = interconnectMap->getData(upperInterface.c_str());
                                        if (interface == NULL){
                                            throw new RuntimeException(((string)("Unrecognized upper hierarchy interface (interface property) for RAM " + iSimulableName)).c_str());
                                        }
                                        ram->setInterface(interface);
                                        interconnectDevices->getData(interface)->add(ram);
                                    }
                                    ram->initialize();
                                    break;
                                default:
                                    break;
                            }
                        }else{
                            throw new RuntimeException(((string)("Expected end command but found " + endComand)).c_str());
                        }
                    }else{
                        // Device definition start, set status as parsing a device
                        // and initialize all its properties with default values
                        deviceDefOn = true;
                        iSimulableName.clear();
                        string defTypeString = sfp->get_token(0);
                        if (defTypeString.compare(SIMPLE_UNPIPED_PROCESSOR_COMMAND) == 0){
                            defType = DEF_TYPE_SIMPLE_UNPIPED_PROCESSOR;
                            pcvalue = PC_DEFAULT_VALUE;
                            dataMemInterface.clear();
                            instructionMemInterface.clear();
                            processor = NULL;
                        }else if (defTypeString.compare(CACHE_COMMAND) == 0){
                            defType = DEF_TYPE_CACHE;
                            latency = "1";
                            portCount = "1";
                            associativity.clear();
                            setCount.clear();
                            lineSize.clear();
                            replacementPolicy = "lru";
                            writePolicy = "writeback";
                            coherenceProtocol = "msi";
                            upperInterface.clear();
                            lowerInterface.clear();
                        }else if (defTypeString.compare(BUS_COMMAND) == 0){
                            portCount = "1"; 
                            defType = DEF_TYPE_BUS;
                        }else if (defTypeString.compare(RAM_COMMAND) == 0){
                            portCount = "1";                            
                            latency = "1";
                            capacity.clear();
                            upperInterface.clear();
                            defType = DEF_TYPE_RAM;
                        }else{
                            defType = DEF_TYPE_UNDEFINED;
                        }
                    }
                }else{
                    // More than one token, parameter value line
                    string paramName = sfp->get_token(0);
                    string paramValue = sfp->get_token(2);
                    if (paramName.compare(PROPERTY_NAME)==0){
                        iSimulableName = paramValue;
                    }
                    switch(defType){
                        case DEF_TYPE_SIMPLE_UNPIPED_PROCESSOR:
                            if (paramName.compare(PROPERTY_PC_VALUE)==0){
                                pcvalue = paramValue;
                            }else if (paramName.compare(PROPERTY_CPU_DATA_MEMORY_INTERFACE) == 0){
                                dataMemInterface = paramValue;
                            }else if (paramName.compare(PROPERTY_CPU_INST_MEMORY_INTERFACE) == 0){
                                instructionMemInterface = paramValue;
                            }
                            break;
                        case DEF_TYPE_CACHE:
                            if (paramName.compare(PROPERTY_ASSOCIATIVITY) == 0){
                                associativity = paramValue;
                            }else if (paramName.compare(PROPERTY_COHERENCE_PROTOCOL) == 0){
                                coherenceProtocol = paramValue;
                            }else if (paramName.compare(PROPERTY_SET_COUNT) == 0){
                                setCount = paramValue;
                            }else if (paramName.compare(PROPERTY_LATENCY) == 0){
                                latency = paramValue;
                            }else if (paramName.compare(PROPERTY_PORT_COUNT) == 0){
                                portCount = paramValue;
                            }else if (paramName.compare(PROPERTY_LINE_SIZE) == 0){
                                lineSize = paramValue;
                            }else if (paramName.compare(PROPERTY_REPLACEMENT_POLICY) == 0){
                                replacementPolicy = paramValue;
                            }else if (paramName.compare(PROPERTY_REPLACEMENT_POLICY) == 0){
                                replacementPolicy = paramValue;
                            }else if (paramName.compare(PROPERTY_WRITE_POLICY) == 0){
                                writePolicy = paramValue;
                            }else if (paramName.compare(PROPERTY_LOWER_INTERFACE) == 0){
                                lowerInterface = paramValue;
                            }else if (paramName.compare(PROPERTY_UPPER_INTERFACE) == 0){
                                upperInterface = paramValue;
                            }
                            break;
                        case DEF_TYPE_BUS:
                            if (paramName.compare(PROPERTY_PORT_COUNT) == 0){
                                portCount = paramValue;
                            }
                            break;
                        case DEF_TYPE_RAM:
                            if (paramName.compare(PROPERTY_PORT_COUNT) == 0){
                                portCount = paramValue;
                            }else if (paramName.compare(PROPERTY_LATENCY) == 0){
                                latency = paramValue;
                            }else if (paramName.compare(PROPERTY_CAPACITY) == 0){
                                capacity = paramValue;
                            }else if (paramName.compare(PROPERTY_INTERFACE) == 0){
                                upperInterface = paramValue;
                            }
                            break;
                        case DEF_TYPE_UNDEFINED:
                            break;
                        default:
                            break;
                    }
                }
               
            }
        }
    }
    
    // Initialize computationa system and events of those processors
    compSys->setProcessorCount(processors->getSize());
    int i = 0;
    Iterator<Processor*>* iterProcessors = processors->iterator();
    while(iterProcessors->hasNext()){
        processor = iterProcessors->next();
        compSys->addProcessor(processor,i);
        processor->setComputationalSystem(compSys);
        i++;
        /* Two events must be created for processors, the fixed event at the start of cycle, and 
           the initial execution event */
        processor->scheduleInitCycleFixedEvent();
        processor->scheduleInitExecutionEvent();
        processor->traceSimulable();
    }
    
    // Initialize memory system
    MemorySystem* memSystem = new MemorySystem(compSys,memoryDevices->getSize(),1);
    i = 0;
    Iterator<MemoryDevice*>* iterMemDevices = memoryDevices->iterator();
    while(iterMemDevices->hasNext()){
        memDevice = iterMemDevices->next();
        memSystem->addMemoryDevice(memDevice,i);
        i++;
        memDevice->scheduleInitCycleFixedEvent();
        memDevice->traceSimulable();
    }
    
    // Initialize interconnection network
    Iterator<InterconnectionNetwork*>* iterInterfaces = interfaces->iterator();
    while(iterInterfaces->hasNext()){
        InterconnectionNetwork* interface = iterInterfaces->next();
        interface->traceSimulable();
        interface->scheduleInitCycleFixedEvent();
        List<IMessageDispatcher*>* attachedDevices = interconnectDevices->getData(interface);
        interface->setDeviceCount(attachedDevices->getSize());
        interface->initialize();
        Iterator<IMessageDispatcher*>* iterAttachedDevices = attachedDevices->iterator();
        i = 0;
        while(iterAttachedDevices->hasNext()){
            interface->addDevice(iterAttachedDevices->next(),i);
            i++;
        }
    }
   
    // Load program into memory!
    Loader* loader = NULL;
    switch(isaType){
        case ISA_MIPS_32:
            loader = new MIPS32Loader(memSystem);
            MIPS32ISA::getInstance()->setLoader(loader);
            break;
        case ISA_TYPE_UNDEFINED:
            break;
    }
    loader->loadProgram(programFile);
    
    // Initializ statistics manager
    StatisticManager* statsManager = StatisticManager::getInstance();
    if (statsFile != NULL){
        statsManager->setComputationalSystem(compSys);
        statsManager->setMemorySystem(memSystem);
    }
    
    // Set end cycle
    // Configure max cycles simulated
    if (endCycle != -1){
        simulator->setUnlimitedCycles(false);
        simulator->setCycleLimit((unsigned long) endCycle);
    }else{
        simulator->setUnlimitedCycles(true);
    }
    
    /* Execute */
    simulator->simulate();
    /* Print statistics */
    if (statsFile != NULL){
        statsManager->printStatistics(statsFile);
    }
    
    }catch(exception* e){
        cout << "Exception caught: " << endl;
        cout << "Message: " << e->what() << endl;
    }
    
    
    return 0;
}

