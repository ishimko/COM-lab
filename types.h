#ifndef TYPES_H
#define TYPES_H


typedef enum{
	ST_NORMAL,
	ST_BLOCK_MSGS
} ChatState;

typedef enum{
	CONTROL_MSG,
	CONTROL_BLOCK,
	CONTROL_ENABLE
} ControlValues;

#endif // TYPES_H

