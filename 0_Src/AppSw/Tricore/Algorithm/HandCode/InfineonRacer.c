/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "InfineonRacer.h"
#include "Basic.h"
#include "AppTaskFu.h"
/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/




/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

typedef struct{
	uint16 state;

	uint16 Dashleft_cnt1;
	uint16 Dashleft_cnt2;
	float32 Dashleft_servo1;
	float32 Dashleft_servo2;

	uint16 Dashright_cnt1;
	uint16 Dashright_cnt2;
	float32 Dashright_servo1;
	float32 Dashright_servo2;
}DashLine_t;

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
/******7월 5일 ******/
//uint16 S_START = 10, S_FINISH = 113, S_CENTER = 61;
//uint16 L_0 = 18, R_0 = 104;

/******7월 7일 ******/
uint16 S_START = 7, S_FINISH = 113, S_CENTER = 60;
uint16 L_0 = 19, R_0 = 101;

sint16 OFFSET;
uint16 SCAN_STATE;
uint16 Left_line, Right_line;
uint16 left_cnt = 0,right_cnt = 0;
uint16 Left_pre_line = 19, Right_pre_line = 101;
sint16 BackDutyCnt;
uint16 lane_reset;
sint16 ERROR_steer, ERROR_steer_old;
float rotate;

uint16 skip_n = 1;
float Percent_n = 0.8; //Num = 13, PercentDen = 16;

uint16 skip_c = 5;
float Percent_c = 0.5;

float SteerDuty, SteerDutyMax = 0.17;
float MotorOn = 1.0;
float var1;
float check_motor; //임시 파일

static int alpha =0;

InfineonRacer_t IR_Ctrl  /**< \brief  global data */
		={64, 64, FALSE  };

SteerGain_t SteerGain ={
		.fltSteerPgain = 0.004,
		.fltSteerDgain = 0.00003
};

IrScan_t IrScan;
RoadState_t Road_State;
DashLine_t DashLine;
BLT_t BLT;
DLposition_t DLposition = D_NO;


/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

uint16 Find_BlackLine(uint16 Start, uint16 Final, uint16 LR);
float Steer_Control_PD(void);
float Cal_volatge(float distance);
float MotorDuty_Reference(float tMotorDutyMax);
float MotorDuty_Con_BackCnt(float MotorDutyRef);
void InfineonRacer_IrScan(void);
void InfineonRacer_detectCross(void);
void InfineonRacer_DashLine(void);

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
void InfineonRacer_init(void){
	OFFSET = 61;
	SCAN_STATE = 22;

	SteerDuty = 0.0;
	ERROR_steer_old = 0;
	Road_State = 1;
	BLT.Scanstate = 4;
	Left_pre_line = L_0;
	Right_pre_line = R_0;
	BLT.Dashstate = 6;
	BUTTON = FALSE;
	DLposition = 1;
}

uint16 Find_BlackLine(uint16 Start, uint16 Final, uint16 LR)
{
	uint16 k;
	uint16 Left = 0, Right = 1;
	uint32 var2, LineK = 0;

	if (LR == Left)			// Left scan
	{
		LineK = S_START;
		for (k = Start; k >= Final+skip_n+2; k--)
		{
			var2 = IR_LineScan.adcResult[1][k]*Percent_n;
			if (IR_LineScan.adcResult[1][k-skip_n-1] < var2
					|| IR_LineScan.adcResult[1][k-skip_n-2] < var2)
			{
				LineK = k;
				break;
			}
		}
	}
	else if (LR == Right)	// Right Scan
	{
		LineK = S_FINISH;
		for (k = Start; k <= Final-skip_n-2; k++)
		{
			{
				var2 = IR_LineScan.adcResult[1][k]*Percent_n;
				if (IR_LineScan.adcResult[1][k+skip_n+1] < var2
						|| IR_LineScan.adcResult[1][k+skip_n+2] < var2)
				{
					LineK = k;
					break;
				}
			}
		}
	}
	return LineK;
}

/*detect cross*/
void InfineonRacer_detectCross(void)
{
	int i;
	int Black_cnt = 0;
	uint32 var;
	static uint16 Change_cnt = 0;

	Change_cnt++;
//	for(i = S_CENTER; i <= R_0 - skip_c - 1; i++)
	for(i = Left_pre_line; i <= Right_pre_line - skip_c - 1; i++)
	{
		var = IR_LineScan.adcResult[1][i]*Percent_c;
		if(IR_LineScan.adcResult[1][i+ skip_c + 1] < var)
		{
			Black_cnt++;
		}
	}

	if(Black_cnt >= 4 && Change_cnt >= 25)
	{
		switch (Road_State)
		{
			case 1:
				Road_State = CROSSIN;
				Change_cnt = 0;
				break;

			case 3:
			case 4:
				Road_State = CROSSOUT;
				Change_cnt = 0;
				break;

			default:
				break;
		}
	}
	if(Change_cnt >= 1000) Change_cnt = 1000;
}

void InfineonRacer_DashLine(void){
//	int i;
//
//	uint32 var;
//	static uint16 Change_cnt = 0;
//	uint16 left_on = 0,right_on = 0;
//	Change_cnt++;
//	if(lane_reset == 0 && OFFSET <64 && OFFSET  > 58 ){
//	for(i = S_CENTER; i <= R_0 - skip_n - 1; i++)
//		{
//			var = IR_LineScan.adcResult[1][i]*Percent_n;
//			if(IR_LineScan.adcResult[1][i+ skip_n + 1] < var )
//			{
//				left_on = 1;
//				break;
//			}
//		}
//
//	for(i = S_CENTER; i >= L_0 + skip_n + 1; i--)
//		{
//			var = IR_LineScan.adcResult[1][i]*Percent_n;
//			if(IR_LineScan.adcResult[1][i- skip_n - 1] < var)
//			{
//				right_on = 1;
//				break;
//			}
//		}
//	if(right_on > left_on){
//		right_cnt++;
//	}
//	else if(right_on < left_on){
//		left_cnt++;
//	}
//}
	int k;
	static int L_cnt=0, R_cnt=0;
	if(lane_reset == 1){
	if((Left_line <= Left_pre_line +2) && (Left_line >= Left_pre_line -2))
	{
		L_cnt++;
	}
	if((Right_line <= Right_pre_line +2) && (Right_line >= Right_pre_line -2))
	{
		R_cnt++;
	}

	if(L_cnt >= 7 || R_cnt >= 7)
	{
		if(R_cnt > L_cnt)
		{
			DLposition = D_LEFT;
			L_cnt = 0;
			R_cnt = 0;
		}
		else if(L_cnt > R_cnt)
		{
			DLposition = D_RIGHT;
			L_cnt = 0;
			R_cnt = 0;
		}
	}
	}
	else if(lane_reset == 0){
		if(DLposition == D_LEFT){
			DLposition = D_RIGHT;
		}
		else if(DLposition == D_RIGHT){
			DLposition = D_LEFT;
		}
	}
}



void InfineonRacer_IrScan(void){
	uint32 i;
	for(i = 0;i <= 19;){
		IrSum = IrSum + IR_Result[i++];
	}
	IrAvg = IrSum/20;
	IrSum = 0;

}



void InfineonRacer_detectLane(void){
	uint16 Left = 0, Right = 1;

	Left_pre_line = Left_line;
	Right_pre_line = Right_line;
	if(Road_State == NORMAL || Road_State == DASHLINE)
	{
		InfineonRacer_detectCross();
	}

	if(Road_State == NORMAL || Road_State == DASHLINE){
	switch (SCAN_STATE)
	{
		case 11:
		case 12:
		case 21:
		case 22:
			Left_line = Find_BlackLine(OFFSET,S_START,Left);
			Right_line = Find_BlackLine(OFFSET,S_FINISH,Right);
			if (Left_line == S_START)
			{
				if (Right_line == S_FINISH)
				{
					OFFSET = S_CENTER;
					SCAN_STATE = 11;
				}
				else if (Right_line > S_CENTER)
				{
					OFFSET = S_CENTER + Right_line - R_0;
					SCAN_STATE = 12;
				}
				else
				{
					OFFSET = S_CENTER + Right_line - R_0;
					SCAN_STATE = 13;
				}
			}
			else if (Left_line < S_CENTER)
			{
				if (Right_line == S_FINISH)
				{
					OFFSET = S_CENTER + Left_line - L_0;
					SCAN_STATE = 21;
				}
				else
				{
					OFFSET = (Left_line + Right_line) >> 1;
					SCAN_STATE = 22;
				}
			}
			else
			{
				OFFSET = S_CENTER + Left_line - L_0;
				SCAN_STATE = 31;
			}
			break;

		case 13:
			Left_line = Find_BlackLine(OFFSET,S_START,Left);
			Right_line = Find_BlackLine(OFFSET,S_FINISH,Right);
			if (Right_line == S_FINISH)
			{
				OFFSET = S_START;
				SCAN_STATE = 14;
			}
			else if (Right_line > S_CENTER)
			{
				OFFSET = S_CENTER + Right_line - R_0;
				SCAN_STATE = 12;
			}
			else
			{
				OFFSET = S_CENTER + Right_line - R_0;
				SCAN_STATE = 13;
			}
			break;

		case 14:
			Right_line = Find_BlackLine(OFFSET,S_FINISH,Right);
			if (Right_line == S_FINISH)
			{
				OFFSET = S_START;
				SCAN_STATE = 14;
			}
			else if (Right_line < S_CENTER)
			{
				OFFSET = S_CENTER + Right_line - R_0;
				SCAN_STATE = 13;
			}
			break;

		case 31:
			Left_line = Find_BlackLine(OFFSET,S_START,Left);
			Right_line = Find_BlackLine(OFFSET,S_FINISH,Right);
			if (Left_line == S_START)
			{
				OFFSET = S_FINISH;
				SCAN_STATE = 41;
			}
			else if (Left_line > S_CENTER)
			{
				OFFSET = S_CENTER + Left_line - L_0;
				SCAN_STATE = 31;
			}
			else
			{
				OFFSET = S_CENTER + Left_line - L_0;
				SCAN_STATE = 21;
			}
			break;

		case 41:
			Left_line = Find_BlackLine(OFFSET,S_START,Left);
			if (Left_line == S_START)
			{
				OFFSET = S_FINISH;
				SCAN_STATE = 41;
			}
			else
			{
				OFFSET = S_CENTER + Left_line - L_0;
				SCAN_STATE = 31;
			}
			break;

		default: break;
	}
		if (OFFSET < S_START)		OFFSET = S_START;
		else if (OFFSET > S_FINISH)	OFFSET = S_FINISH;
	}

		if(Road_State == DASHLINE )
			{
			  InfineonRacer_DashLine();
			}
//
//			if(Road_State == LANECHANGE && lane_reset == 0){
//				if(left_cnt < right_cnt){
//					DLposition = D_LEFT;
//					left_cnt = 0;
//					right_cnt = 0;
//				}
//				else if(left_cnt > right_cnt){
//					DLposition = D_RIGHT;
//					left_cnt = 0;
//					right_cnt = 0;
//				}
//			}
//
//			if(lane_reset == 1 && DLposition == D_LEFT){
//				DLposition = D_RIGHT;
//			}
//			else if(lane_reset == 1 && DLposition == D_RIGHT){
//				DLposition = D_LEFT;
//			}
//
//
//	if(Road_State == CROSSIN || Road_State == CROSSOUT || Road_State == LANECHANGE)
//	{
//		OFFSET = S_CENTER;
//	}
//
//
}

/*******************************************PD control*******************************************/

float Steer_Control_PD(void)
{
	float Ts = 0.02;
	float SteerDuty0 = -0.052;
	float SteerDuty_in;
	float value1;

	ERROR_steer = OFFSET - S_CENTER;
	value1 = ((float)(ERROR_steer - ERROR_steer_old))/Ts;
	SteerDuty = SteerPgain*(float)ERROR_steer + SteerDgain*value1;

	if(SteerDuty > SteerDutyMax)		SteerDuty = SteerDutyMax;
	else if(SteerDuty < -SteerDutyMax)	SteerDuty = -SteerDutyMax;

	SteerDuty_in = SteerDuty + SteerDuty0;
	ERROR_steer_old = ERROR_steer;

	return SteerDuty_in;
}

/***********************MotorDuty_Reference*********************************/

float MotorDuty_Reference(float MotorDutyMax)
{
	float SpeedSlope = 2;
	float MotorDutyRef, MotorDutyMin = 0.2;
	//MotorDutyMax = 0.35 or MotorDutyMax = 0.15

	/****** Speed Control ********/
	if (SteerDuty > 0)	MotorDutyRef = MotorDutyMin - SpeedSlope*(SteerDuty - SteerDutyMax);
	else				MotorDutyRef = MotorDutyMin + SpeedSlope*(SteerDuty + SteerDutyMax);

	if (MotorDutyRef > MotorDutyMax)		MotorDutyRef = MotorDutyMax;
	else if (MotorDutyRef < MotorDutyMin)	MotorDutyRef = MotorDutyMin;

	return MotorDutyRef;
}

/*******************************************Con_BackCnt*******************************************/

float MotorDuty_Con_BackCnt(float MotorDutyRef)
{
	static uint16 Decel_State = 0;
	static sint16 BackCnt = 0;
	static float MotorDutyRef_old = 0.0;
	float MotorDuty;
	float BackDuty = -0.2, DiffDecel = -0.06, BackCntGain = 10.0;

	switch (Decel_State)
	{
		case 1:
			BackCnt--;
			if (BackCnt < 0)	BackCnt = 0;

			if (BackCnt > 0)	MotorDuty = BackDuty;
			else
			{
				Decel_State = 0;
				MotorDuty = MotorDutyRef;
			}
			break;
		case 0:
			if (MotorDutyRef_old > 3.0
					&& MotorDutyRef - MotorDutyRef_old < DiffDecel)
			{
				Decel_State = 1;
				MotorDuty = BackDuty;
				BackCnt = (sint16)(BackCntGain*(MotorDutyRef - MotorDutyRef_old));
			}
			else	MotorDuty = MotorDutyRef;
			break;
		default:
			MotorDuty = MotorDutyRef;
			break;
	}
	MotorDutyRef_old = MotorDutyRef;
	return MotorDuty;
}


float Cal_volatge(float distance){
	float IRvalue;
	float IRslope = 70,vol_0 = -0.3,d_0 = -10;

	IRvalue = IRslope*(distance - d_0) +vol_0;
	return IRvalue;
}
/*-------------------------InfineonRacer_control---------------------------*/

void InfineonRacer_control(void)
{
//	float Ts = 0.02;  // Ts = 20ms
//	float var2;
//	float SteerDuty0 = -0.052;
//	float SteerDuty_in;
//	float SpeedSlope = 2;
//	float MotorDuty, MotorDutyMax = 0.35, MotorDutyMin = 0.2;
	uint16 Left, Right;
	uint16 Left_dashline, Right_dashline;
	static uint16 Road_cnt = 0;
	static uint16 LaneChange_state = 0;
	static boolean IRon = 0;
	float  ActDistance;
	float MotorDutyRef;

//	Road_State = BLT.Scanstate;
		//	float SteerPgain = 0.004;
		//	float SteerDgain = 0.00003;

/**********************************************case 1 normal_state********************************************/
	switch(Road_State){
	case 1:

		IR_getSrvAngle() = Steer_Control_PD();

		MotorDutyRef = MotorDuty_Reference(0.3);
		IR_Motor.Motor0Vol = MotorDutyRef;
//		IR_Motor.Motor0Vol = MotorDuty_Con_BackCnt(MotorDutyRef);

		/****** Recognize CrossLine ********/
//		Road_State = BLT.Dashstate;// 임시
		if(IRon == 1){
//			ActDistance = Cal_volatge(IrAvg);
//			if(ActDistance < 100) Road_State = AEB;
			if(IrAvg > 0.2) Road_State = AEB;
		}
		break;

/*******************************************case 2 CrossIn_state********************************************/
	case 2:
//		IR_Motor.Motor0Vol = 0.15;
		Road_State = DASHLINE;
		lane_reset = 1;
		break;

/*******************************************case 3 DashLine_state********************************************/
	case 3:
		IR_getSrvAngle() = Steer_Control_PD();

		MotorDutyRef = MotorDuty_Reference(0.15);
		IR_Motor.Motor0Vol = MotorDutyRef;
//		IR_Motor.Motor0Vol = MotorDuty_Con_BackCnt(MotorDutyRef);
//		ActDistance = Cal_volatge(IrAvg);
		alpha = 1;
		if( 0.3 < IrAvg ){
			Road_State = LANECHANGE;
			lane_reset = 0;
			LaneChange_state = 4;
			alpha = 0;
		}
		break;



/*******************************************case 4 LaneChange_state********************************************/
/***************case 4 기본 ***************/
	case 4:						//LaneChange_state
//		if( DLposition == DASH_LEFT )
//		{
//			switch(DashLine.state)
//			{
//			case 1:
//				IR_getSrvAngle() = 0.2;
//				--DashLine.Dashleft_cnt1;
//				if(DashLine.Dashleft_cnt1 == 0){
//					DashLine.state = 2;
//					DashLine.Dashleft_cnt1 = 500;
//				}
//				break;
//			case 2:
//				IR_getSrvAngle() = DashLine.Dashleft_servo2;
//				--DashLine.Dashleft_cnt2;
//			if(DashLine.Dashleft_cnt2 == 0){
//				Road_State = DASHLINE;
//				DashLine.Dashleft_cnt2 = 500;
//			}
//			break;
//			}
//		}
//		else if( DLposition == DASH_RIGHT)
//		{
//			switch(DashLine.state)
//			{
//			case 1:
//				IR_getSrvAngle() = DashLine.Dashright_servo1;
//				--DashLine.Dashright_cnt1;
//				if(DashLine.Dashright_cnt1 == 0){
//					DashLine.state = 2;
//					DashLine.Dashright_cnt1 = 500;
//				}
//				break;
//			case 2:
//				IR_getSrvAngle() = DashLine.Dashleft_servo2;
//				--DashLine.Dashright_cnt2;
//				if(DashLine.Dashright_cnt2 == 0){
//					Road_State = DASHLINE;
//					-DashLine.Dashright_cnt2 = 500;
//				}
//				break;
//			}
//		}
//		ActDistance = Cal_volatge(IrAvg);
//		if((ActDistance >= 140) && (LaneChange_state == 0))


		if( (DLposition == D_LEFT || DLposition == D_RIGHT) && LaneChange_state == 4 && alpha != 1)
		{
			IR_getSrvAngle() = (float)DLposition*0.16 - 0.052;
			IR_Motor.Motor0Vol = 0.13;
			LaneChange_state = 1;
			alpha = 0;
		}
		if((IrAvg <= 0.05) && (LaneChange_state == 1))
		{
			Road_cnt = 40;
			IR_getSrvAngle() = -0.052;
			LaneChange_state = 2;
		}


		if(Road_cnt == 0){
			switch(LaneChange_state){
				case 2 :
					Road_cnt = 25;
					IR_getSrvAngle() = (float)DLposition*(-0.16) - 0.052;
					LaneChange_state = 3;
					alpha = 1;
					break;
				case 3 :
					Road_State = DASHLINE;
					LaneChange_state = 4;
					alpha = 1;
//					lane_reset = 1;
//					left_cnt = 0;
//					right_cnt = 0;
//					LaneChange_state = 0;
					break;
				default: break;
			}
		}
		Road_cnt--;
		break;

/***************case 4 bluetooth 용 ***************/
//	case 4:						//LaneChange_state
//		DLposition = BLT.Dashstate;
//
//		//////////////////////////////////////////////DASH_LEFT////////////////////////////////////////
//		if( DLposition == DASH_LEFT )
//		{
//			switch(DashLine.state)
//			{
//			case 1:
//
//				if(BUTTON == TRUE){
//					IR_getSrvAngle() = BLT.servo1;
//					IR_Motor.Motor0Vol = 0.15;
//					IR_MotorEn.Motor0Enable = 1;
//					DashLine.Dashleft_cnt1 = BLT.cnt1;
//					BUTTON = FALSE;
//				}
//				--DashLine.Dashleft_cnt1;
//
//				if(DashLine.Dashleft_cnt1 == 0){
//					DashLine.state = 2;
//					BUTTON = TRUE;
//				}
//				break;
//			case 2:
//
//				if(BUTTON == TRUE){
//					IR_getSrvAngle() = BLT.servo2;
//					DashLine.Dashleft_cnt2 = BLT.cnt2;
//					BUTTON = FALSE;
//				}
//				--DashLine.Dashleft_cnt2;
//			if(DashLine.Dashleft_cnt2 == 0){
//				IR_MotorEn.Motor0Enable = 0;
//				IR_Motor.Motor0Vol = 0;
//			}
//			break;
//			}
//		}
//		//////////////////////////////////////////////DASH_RIGHT////////////////////////////////////////////
//		else if( DLposition == DASH_RIGHT)
//		{
//			switch(DashLine.state)
//			{
//			case 1:
//				IR_getSrvAngle() = BLT.servo1;
//				if(BUTTON == TRUE){
//					DashLine.Dashright_cnt1 = BLT.cnt1;
//					IR_Motor.Motor0Vol = 0.15;
//					IR_MotorEn.Motor0Enable = 1;
//					BUTTON = FALSE;
//				}
//				--DashLine.Dashright_cnt1;
//
//				if(DashLine.Dashright_cnt1 == 0){
//					DashLine.state = 2;
//					BUTTON = TRUE;
//				}
//				break;
//			case 2:
//				IR_getSrvAngle() = BLT.servo2;
//				if(BUTTON == TRUE){
//					DashLine.Dashright_cnt2 = BLT.cnt2;
//					BUTTON = FALSE;
//				}
//				--DashLine.Dashright_cnt2;
//
//				if(DashLine.Dashright_cnt2 == 0){
//					IR_MotorEn.Motor0Enable = 0;
//					IR_Motor.Motor0Vol = 0;
//				}
//				break;
//			}
//		}
//		break;

/******************************************* case 5 CrossOut_state********************************************/
	case 5:
		if(alpha == 1){
			Road_cnt = 30;
			IR_getSrvAngle() = -0.052;
			LaneChange_state = 4;
			alpha = 0;
		}
		--Road_cnt;
		if(Road_cnt == 0){
		Road_State = NORMAL;
//		LaneChange_state = 4;
		IRon = 1;
		}
		break;

/*******************************************AEB_state********************************************/
	case 6:
		IR_Motor.Motor0Vol = -0.05;
		break;
	}
}



/********** AVOID OBJECTS FUNCTION **********/
//void InfineonRacer_Avoid(sint32 task_cnt)
//{
//	IR_getSrvAngle() = -0.1;
//	task_cnt=0;
//	while(task_cnt <= 150)
//	{}
//
//	IR_getSrvAngle() = 0.1;
//	task_cnt=0;
//	while(task_cnt <= 100)
//	{}
//
//	if(task_cnt>=100)
//	{
//		IR_getSrvAngle() = 0.0;
//	}
//}

