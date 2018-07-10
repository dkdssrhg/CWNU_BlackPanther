#ifndef INFINEONRACER_H_
#define INFINEONRACER_H_


/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include <Ifx_Types.h>
#include "Configuration.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/
#define IR_getLs0Margin()		IR_Ctrl.Ls0Margin
#define IR_getLs1Margin()		IR_Ctrl.Ls1Margin
#define SteerPgain				SteerGain.fltSteerPgain
#define SteerDgain				SteerGain.fltSteerDgain
#define IrSum					IrScan.fltIrSum
#define IrAvg					IrScan.fltIrAvg
#define BUTTON					BLT.button

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

typedef enum{
	NORMAL = 1,
	CROSSIN,
	DASHLINE,
	LANECHANGE,
	CROSSOUT,
	AEB
}RoadState_t;

typedef enum{
	D_LEFT = -1,
	D_NO = 0,
	D_RIGHT = 1
}DLposition_t;

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/
typedef struct{
	sint32 Ls0Margin;
	sint32 Ls1Margin;
	boolean basicTest;
}InfineonRacer_t;

typedef struct{
	float fltSteerPgain;
	float fltSteerDgain;

}SteerGain_t;

typedef struct{
	float fltIrSum;
	float fltIrAvg;

}IrScan_t;



typedef struct{
	boolean button;

	uint16 cnt1;
	uint16 cnt2;
	uint16 Scanstate;
	uint16 Dashstate;

	float32 servo1;
	float32 servo2;
}BLT_t;


/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
IFX_EXTERN InfineonRacer_t IR_Ctrl;

IFX_EXTERN uint16 left_cnt,right_cnt;

IFX_EXTERN uint16		SCAN_STATE;
IFX_EXTERN uint16 		Left_line, Right_line;
IFX_EXTERN sint16		OFFSET;
IFX_EXTERN sint16 		ERROR_steer, ERROR_steer_old;
IFX_EXTERN float 		SteerDuty;
IFX_EXTERN float		var1;
IFX_EXTERN SteerGain_t  SteerGain;
IFX_EXTERN RoadState_t  Road_State;
IFX_EXTERN DLposition_t DLposition;

IFX_EXTERN BLT_t		BLT;
IFX_EXTERN IrScan_t  	IrScan;
/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/
IFX_EXTERN void InfineonRacer_init(void);
IFX_EXTERN void InfineonRacer_detectLane(void);
IFX_EXTERN void InfineonRacer_control(void);
IFX_EXTERN void InfineonRacer_Avoid(sint32 task_cnt);

#endif
