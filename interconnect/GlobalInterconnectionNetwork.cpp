#include "GlobalInterconnectionNetwork.h"
#include "PacketSwitch.h"


NetworkTopologyType GlobalInterconnectionNetwork::getTopology(){
    return topology;
}

List<PacketSwitch*> *GlobalInterconnectionNetwork::getSwitches(){
    return packetSwitches;
}

void GlobalInterconnectionNetwork::createNetwork(){
    switch(topology){
        case NETWORK_TOPOLOGY_2D_GRID:
            /*
            for (int i = 0; i < horizontalSwitches; i++){
                for (int j = 0; j < verticalSwitches; j++){
                    PacketSwitch* packetSwitch = new PacketSwitch()
                }
            }
             */
            break;
        case NETWORK_TOPOLOGY_2D_TORUS:
            // TODO
            break;
        case NETWORK_TOPOLOGY_3D_GRID:
            // TODO
            break;
        default:
            break;
        
    }
}







