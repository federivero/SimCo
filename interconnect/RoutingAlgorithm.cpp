
#include "RoutingAlgorithm.h"
#include <cmath>

using namespace std;

/* Dimesional order routing */
DimensionOrderRouting::DimensionOrderRouting(NetworkTopologyType topologyType, DimensionOrderRoutingType order, int dimensionBits){
    this->orderType = order;
    this->topology = topologyType;
    this->bitsPerDimension = dimensionBits;
    this->dimensionMask = log2(bitsPerDimension) - 1;
}

/* DimensionOrderRouting: Routing that works for square meshes and grids. First we route in one direction 
 * (horizontal or vertical) and then in the second one. One easy way to implement this is to numerate horizonal and 
 * vertical lines independently, and then assign id = horizontal * 2^M + vertical. 
 * Returns: 0 if output link is UP
 *          1 if output link is DOWN
 *          2 if output link is RIGHT
 *          3 if output link is LEFT
 *         -1 if output link is device link
 */
unsigned int DimensionOrderRouting::getNextOutputLink(unsigned long originId, unsigned long destinationId){
    unsigned int originX = originId & dimensionMask;
    originId >>= bitsPerDimension;
    unsigned int originY = originId & dimensionMask;
    originId >>= bitsPerDimension;
    unsigned int originZ = originId & dimensionMask;
    unsigned int destinationX = destinationId & dimensionMask;
    destinationId >>= bitsPerDimension;
    unsigned int destinationY = destinationId & dimensionMask;
    destinationId >>= bitsPerDimension;
    unsigned int destinationZ = destinationId & dimensionMask;
    unsigned int xDistance = originX - destinationX;
    unsigned int yDistance = originY - destinationY;
    unsigned int zDistance = originZ - destinationZ;
    unsigned int returnValue = -1;
    switch(topology){
        case NETWORK_TOPOLOGY_2D_GRID:
            switch(orderType){
                case DIMENSION_ORDER_HORIZONTAL_FIRST:
                    if (originX < destinationX){
                        returnValue = DIMENSION_ORDER_RIGHT;
                    }else if (originX > destinationX){
                        returnValue = DIMENSION_ORDER_LEFT;
                    }else if (originY < destinationY){
                        returnValue = DIMENSION_ORDER_UP;
                    }else if (originY > destinationY){
                        returnValue = DIMENSION_ORDER_DOWN;
                    }
                    break;
                case DIMENSION_ORDER_VERTICAL_FIRST:
                    if (originY < originY){
                        returnValue = DIMENSION_ORDER_UP;
                    }else if (originY > originY){
                        returnValue = DIMENSION_ORDER_DOWN;
                    }else if (originX < destinationY){
                        returnValue = DIMENSION_ORDER_RIGHT;
                    }else if (originX > destinationY){
                        returnValue = DIMENSION_ORDER_LEFT;
                    }
                    break;
                case DIMENSION_ORDER_CLOSEST_FIRST:
                    if (abs(xDistance) > abs(yDistance)){
                        if (xDistance < 0){ 
                            returnValue = DIMENSION_ORDER_LEFT;
                        }else{
                            returnValue = DIMENSION_ORDER_RIGHT;
                        }
                    }else{
                        if (yDistance < 0){
                            returnValue = DIMENSION_ORDER_DOWN;
                        }else if (yDistance > 0){
                            returnValue = DIMENSION_ORDER_UP;
                        }
                    }
                    break;
                case DIMENSION_ORDER_FARTHEST_FIRST:
                    // TODO
                    break;
                default:
                    break;
            }
            break;
        case NETWORK_TOPOLOGY_3D_GRID:
            switch(orderType){
                case DIMENSION_ORDER_HORIZONTAL_FIRST:
                    // TODO
                    break;
                case DIMENSION_ORDER_VERTICAL_FIRST:
                    // TODO
                    break;
                case DIMENSION_ORDER_CLOSEST_FIRST:
                    // TODO
                    break;
                case DIMENSION_ORDER_FARTHEST_FIRST:
                    // TODO
                    break;
                default:
                    break;
            }
            break;
        case NETWORK_TOPOLOGY_2D_TORUS:
            switch(orderType){
                case DIMENSION_ORDER_HORIZONTAL_FIRST:
                    // TODO
                    break;
                case DIMENSION_ORDER_VERTICAL_FIRST:
                    // TODO
                    break;
                case DIMENSION_ORDER_CLOSEST_FIRST:
                    // TODO
                    break;
                case DIMENSION_ORDER_FARTHEST_FIRST:
                    // TODO
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
            
    }
}






