/* 
 * File:   SimpleProcessorStage.h
 * Author: fede
 *
 * Created on 31 de julio de 2014, 08:15 PM
 */

#ifndef SIMPLEPROCESSORSTAGE_H
#define	SIMPLEPROCESSORSTAGE_H

enum SimpleProcessorStage{
    SP_STAGE_FETCH,
    SP_STAGE_DECODE,
    SP_STAGE_EXECUTE,
    SP_STAGE_WRITEBACK,
    SP_STAGE_IDLE // Used to stop de processor
};

#endif	/* SIMPLEPROCESSORSTAGE_H */

