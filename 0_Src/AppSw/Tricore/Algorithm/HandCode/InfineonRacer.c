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

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/
/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
void InfineonRacer_init(void){
	IR_setMotor0En(0.0);
	IR_Motor.Motor0Vol = 0.25;
	IR_getSrvAngle() = 0.0;
}

void InfineonRacer_detectLane(void){

	float error_left=0;
	float error_right=0;

	error_left = 63.5 - index_left;		// 가운데에서 왼쪽의 검은선 까지의 픽셀거리
	error_right = index_right - 63.5;	// 가운데에서 오른쪽의 검은선 까지의 픽셀거리

	if( error_left - error_right > 5 )	// 왼쪽의 픽셀거리가 더 크면 좌회전
	{
		IR_getSrvAngle() = -0.1;
	}

	if (error_left - error_right < -5)	// 오른쪽의 픽셀거리가 더 크면 우회전
	{
		IR_getSrvAngle() = 0.1;
	}

	if ( (error_left - error_right > -5) && (error_left - error_right < 5) )	// 큰 차이가 없으면 직진
	{
		IR_getSrvAngle() = 0.0;
	}
}

void InfineonRacer_control(void){

}

void FindIndex( void )
{
	float pixel_left_sum = 0.0; // pixel 총합
	float pixel_right_sum = 0.0;

	int pixel_left;		// 반복문 pixel
	int pixel_right;

	float pixel_LeftCount = 0.0;	// 흑색 픽셀 카운트
	float pixel_RightCount = 0.0;

	index_left = 0;
	index_right = 0;
	pixel_count_cross = 0;		// 횡단보도 인식을 위한 count variable

	for(pixel_left = 0; pixel_left <= 63; pixel_left++)		// 좌측의 흑색 픽셀 카운트
	{
		if(IR_LineScan.adcResult[1][pixel_left] < 2000)
		{
			pixel_left_sum = pixel_left + pixel_left_sum;	// 픽셀 넘버 총합
			pixel_LeftCount++;									// 카운트 된 픽셀 수
			pixel_count_cross++;
		}
	}
	index_left = pixel_left_sum / pixel_LeftCount;				// 픽셀들의 평균(가운데값)



	for(pixel_right = 64; pixel_right < 128; pixel_right++)	// 우측의 흑색 픽셀 카운트
	{
		if(IR_LineScan.adcResult[1][pixel_right] < 2000)
		{
			pixel_right_sum = pixel_right + pixel_right_sum;
			pixel_RightCount++;
			pixel_count_cross++;
		}
	}
	index_right = pixel_right_sum / pixel_RightCount;
	pixel_RightCount = 0.0;
}

void Find_Cross(void)
{
	if(pixel_count_cross >= 50)	// 0~128픽셀 중 흑색 픽셀이 50이상인 경우
	{
		if(status == normal)		// normal 상태이면
		{
			status = v_limit;		// 속도제한 구간에 들어온 상태로 변경
			IR_setBeeperOn(TRUE);	// Beep ON해서 알 수 있게 함.
			status_count = 0;
		}

		if(status == v_limit)		// v_limit 상태이면
		{
			status = normal;		// 속도제한 구간에서 나가는 상태
			IR_setBeeperOn(FALSE);	// Beep OFF로 알 수 있게 함.
			status_count = 0;
		}
	pixel_count_cross = 0;			// count variable 초기화
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
