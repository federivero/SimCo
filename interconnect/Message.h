/* 
 * File:   Message.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 03:52 PM
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

enum MessageType{
    MEMORY_REQUEST_MEMORY_READ,
    MEMORY_REQUEST_MEMORY_WRITE,
    MEMORY_RESPONSE,
    INVALIDATING_MEMORY_RESPONSE,
    CACHE_COHERENCE_INVALIDATE
};

class Message{
    private:
        MessageType messageType;
        // for tracing
        unsigned long messageId;
        // origin and destination address
        unsigned long originDeviceId;
        unsigned long destinationDeviceId;
    public: 
        Message(MessageType type, unsigned long originDeviceId);
        MessageType getMessageType();
        unsigned long getMessageId();
        unsigned long getOriginDeviceId();
        unsigned long getDestinationDeviceId();
        void setOriginDeviceId(unsigned long id);
        void setDestinationDeviceId(unsigned long id);
        virtual ~Message();
};


class InvalidateMessage : public Message{
    private:
        unsigned int invalidateAddress;
    public:
        InvalidateMessage(unsigned int address, MessageType type, unsigned long originDeviceId);
        unsigned int getInvalidateAddress();
        void setInvalidateAddress(unsigned int address);
};

#endif	/* MESSAGE_H */


