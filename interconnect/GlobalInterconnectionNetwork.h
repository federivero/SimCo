/* 
 * File:   GlobalInterconnectionNetwork.h
 * Author: fede
 *
 * Created on 20 de abril de 2014, 06:41 PM
 */

#ifndef GLOBALINTERCONNECTIONNETWORK_H
#define	GLOBALINTERCONNECTIONNETWORK_H

enum NetworkTopologyType{
    NETWORK_TOPOLOGY_2D_GRID,
    NETWORK_TOPOLOGY_3D_GRID,
    NETWORK_TOPOLOGY_2D_TORUS
};

#include "../common/List.h"
#include "PacketSwitch.h"

#define DIMENSION_ORDER_UP    0
#define DIMENSION_ORDER_DOWN  1
#define DIMENSION_ORDER_RIGHT 2
#define DIMENSION_ORDER_LEFT  3

/* A global interconnection network has the 'global view' of the network. A link
 * is a interconnection network, as well as a bus, as well as a 2D Mesh, but of 
 * course they cant inherite from the same class because you cant request access
 * to a '2D Mesh', as well as it would not make sense for a bus to run a 
 * routing algorithm
 */


class GlobalInterconnectionNetwork{
    private:
        /* Topology of the network */
        NetworkTopologyType topology;
        
        List<PacketSwitch*> *packetSwitches;
    public:
        
        GlobalInterconnectionNetwork(NetworkTopologyType type);
        
        NetworkTopologyType getTopology();
        List<PacketSwitch*> *getSwitches();
    
        /* Given a specification of the network, initialize its switches */
        void createNetwork();
};

#endif	/* GLOBALINTERCONNECTIONNETWORK_H */

