/* 
 * File:   RoutingAlgorithm.h
 * Author: fede
 *
 * Created on 19 de abril de 2014, 09:23 PM
 */

#ifndef ROUTINGALGORITHM_H
#define	ROUTINGALGORITHM_H

#include "../common/List.h"

class PacketSwitch;

#include "GlobalInterconnectionNetwork.h"

class GlobalInterconnectionNetwork;

class RoutingAlgorithm{
    private:
    
    protected:
        /* Pointer to general network type */
        GlobalInterconnectionNetwork* globalNetwork;
    public:
        /*  Main routing algorithm function. Given an switch and a device destination
         *  id, returns the ourgoing link of the router
         */ 
        virtual unsigned int getNextOutputLink(PacketSwitch* origin, unsigned long destinationId) = 0;
};

enum DimensionOrderRoutingType{
    DIMENSION_ORDER_HORIZONTAL_FIRST,
    DIMENSION_ORDER_VERTICAL_FIRST,
    DIMENSION_ORDER_CLOSEST_FIRST,
    DIMENSION_ORDER_FARTHEST_FIRST
};


class DimensionOrderRouting : public RoutingAlgorithm{
    private:
        int bitsPerDimension;
        unsigned int dimensionMask;
        DimensionOrderRoutingType orderType;
        NetworkTopologyType topology;
    public:
        DimensionOrderRouting(NetworkTopologyType topologyType, DimensionOrderRoutingType order, int dimensionBits);
        unsigned int getNextOutputLink(unsigned long    origin, unsigned long destinationId);
        
};

#endif	/* ROUTINGALGORITHM_H */

