/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "InfineonRacer.h"
#include "Basic.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

typedef enum now_status{
	normal = 0,
	v_limit
}status_t;
/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

InfineonRacer_t IR_Ctrl  /**< \brief  global data */
		={64, 64, FALSE  };

status_t status = normal;

int status_count;

float index_left;
float index_right;

int pixel_count_cross;
uint32 Find_Timecnt;

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/
void adj_value(float pixel_RightCount,float pixel_LeftCount);
void InfineonRacer_ControlSrv(float error_value);

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
void InfineonRacer_init(void)
{
	IR_setMotor0En(0.0);
	IR_Motor.Motor0Vol = 0.25;
	IR_getSrvAngle() = 0.0;
	Find_Timecnt = 0;
}

void InfineonRacer_detectLane(void)
{
	float error_left=0;
	float error_right=0;
	float error;

	error_left = 63.5 - index_left;		// ������� ������ ������ ������ �ȼ��Ÿ�
	error_right = index_right - 63.5;	// ������� �������� ������ ������ �ȼ��Ÿ�
	error = error_left - error_right;

	if (error_right <= 0)
	{
		error_right = 63.5;
	}

	InfineonRacer_ControlSrv(error);
}


void InfineonRacer_control(void)
{

}


void FindIndex( void )
{
	float pixel_left_sum = 0.0; // pixel ����
	float pixel_right_sum = 0.0;

	int pixel_left;		// �ݺ��� pixel
	int pixel_right;

	float pixel_LeftCount = 0.0;	// ��� �ȼ� ī��Ʈ
	float pixel_RightCount = 0.0;

	index_left = 0;
	index_right = 0;
	pixel_count_cross = 0;		// Ⱦ�ܺ��� �ν��� ���� count variable

	for(pixel_left = 0; pixel_left <= 63; pixel_left++)		// ������ ��� �ȼ� ī��Ʈ
	{
		if(IR_LineScan.adcResult[1][pixel_left] < 1500)
		{
			pixel_left_sum = pixel_left + pixel_left_sum;	// �ȼ� �ѹ� ����
			pixel_LeftCount++;									// ī��Ʈ �� �ȼ� ��
			pixel_count_cross++;
		}
	}
	index_left = pixel_left_sum / pixel_LeftCount;				// �ȼ����� ���(�����)



	for(pixel_right = 64; pixel_right < 128; pixel_right++)	// ������ ��� �ȼ� ī��Ʈ
	{
		if(IR_LineScan.adcResult[1][pixel_right] < 1500)
		{
			pixel_right_sum = pixel_right + pixel_right_sum;
			pixel_RightCount++;
			pixel_count_cross++;
		}
	}
	index_right = pixel_right_sum / pixel_RightCount;

	adj_value(pixel_RightCount,pixel_LeftCount);		//Ŀ���߿� LSC��  20 ~ 100�ȼ��� �߰��Ǵ� ������ �����Ѵ�.
}



void Find_Cross(void)
{

	Find_Timecnt++;

	if((pixel_count_cross >= 50) && (Find_Timecnt >= 50))	// 0~128�ȼ� �� ��� �ȼ��� 50�̻��� ���, status�� 1�� �ֱ�� ����ȴ�.
	{
		if(status == normal)		// normal �����̸�
		{
			status = v_limit;		// �ӵ����� ������ ���� ���·� ����
			IR_setBeeperOn(TRUE);	// Beep ON�ؼ� �� �� �ְ� ��.
			Find_Timecnt = 0;
		}

		else if(status == v_limit)		// v_limit �����̸�
		{
			status = normal;		// �ӵ����� �������� ������ ����
			IR_setBeeperOn(FALSE);	// Beep OFF�� �� �� �ְ� ��.
			Find_Timecnt = 0;
		}

		if(Find_Timecnt >= 1000)
		{
			Find_Timecnt = 1000;
		}

	}
}



void Control_Velocity (void)
{
	if(status == normal)
	{
		IR_Motor.Motor0Vol = 0.25;
	}

	if(status == v_limit)
	{
		IR_Motor.Motor0Vol = 0.15;
	}
}



void adj_value(float RightCount,float LeftCount)		// Ŀ�� ���� �߰��� ������ ������ �����ϱ� ���ؼ� ���
{
	if((RightCount > 0) && (LeftCount > 0))
	{
		if((index_left >20) && (index_left <63.5))
		{
			index_left = 0;
		}
		if((index_right > 63.5) && (index_right <100))
		{
			index_right = 0;
		}

	}
}

void InfineonRacer_ControlSrv(float error_value)   //error_value�� ���� ��������� angle �� ������Ų��.
{
	if( error_value < -10 )
		{
			IR_getSrvAngle() = 0.2;
		}

	if ((error_value >= -10) && (error_value <= -5))
		{
			IR_getSrvAngle() = 0.1;
		}

	if ( (error_value > -5) && (error_value < 5) )
		{
			IR_getSrvAngle() = 0.0;
		}

	if( (error_value >= 5) && (error_value <= 10) )
		{
			IR_getSrvAngle() = -0.1;
		}

	if( error_value > 10 )
		{
			IR_getSrvAngle() = -0.2;
		}
}
