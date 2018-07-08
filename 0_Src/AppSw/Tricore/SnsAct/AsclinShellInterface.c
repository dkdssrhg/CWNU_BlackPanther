/**
 * \file AsclinShellInterface.c
 * \brief ASCLIN Shell interface demo
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "AsclinShellInterface.h"
#include "SysSe/Time/Ifx_DateTime.h"
#include "IfxLldVersion.h"
#include "_Impl/IfxGlobal_cfg.h"
#include "Cpu0_Main.h"

#include "AppTaskFu.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

#define SHELL_HELP_DESCRIPTION_TEXT                                 \
    "     : Display command list."ENDL                              \
    "           A command followed by a question mark '?' will"ENDL \
    "           show the command syntax"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/
typedef struct{
	boolean enable;
	sint32	period_ms;
} linescan_t;

typedef struct{
	boolean enable;
	sint32	period_ms;
} irscan_t;
/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

App_AsclinShellInterface g_AsclinShellInterface; /**< \brief Demo information */
linescan_t	g_LineScan = {FALSE, 1000};
irscan_t	g_IrScan = {FALSE, 1000};
/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

boolean AppShell_status(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_scan(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_steerPgain(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_steerDgain(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_motor0vol(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_motor1vol(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_motor0en(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_motor1en(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_srv(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_beeperon(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_beeperfreq(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_beepervol(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_led108(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_led109(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_led110(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_linescan0(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_linescan1(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_monlinescan(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_monirscan(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_vadcbg1(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_enc(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_port00_0(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_port00_1(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_info(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_button(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_Scanstate(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_Dashstate(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_servo1(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_servo2(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_cnt1(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_cnt2(pchar args, void *data, IfxStdIf_DPipe *io);

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/** \brief Application shell command list */
const Ifx_Shell_Command AppShell_commands[] = {
    {"status", "   : Show the application status", &g_AsclinShellInterface,       &AppShell_status,    },
	{"scan", "     : Show the scan status", &g_AsclinShellInterface,       &AppShell_scan,    },
//	{"scs", "      : Show the scan state", &g_AsclinShellInterface,       &AppShell_Scanstate,    },
//	{"dsh", "      : Show the dash state", &g_AsclinShellInterface,       &AppShell_Dashstate,    },
//	{"btt", "      : Show the button state", &g_AsclinShellInterface,       &AppShell_button,    },
//	{"cnt1", "      : Show the cnt1", &g_AsclinShellInterface,       &AppShell_cnt1,    },
//	{"cnt2", "      : Show the cnt2", &g_AsclinShellInterface,       &AppShell_cnt2,    },
//	{"srv1", "      : Show the srv1", &g_AsclinShellInterface,       &AppShell_servo1,    },
//	{"srv2", "      : Show the srv2", &g_AsclinShellInterface,       &AppShell_servo2,    },

	{"spg", "      : Steer P Gain", &g_AsclinShellInterface,       &AppShell_steerPgain,    },
	{"sdg", "      : Steer D Gain", &g_AsclinShellInterface,       &AppShell_steerDgain,    },
    {"m0v", "      : Motor0Vol", &g_AsclinShellInterface,       &AppShell_motor0vol,    },
    {"m1v", "      : Motor1Vol", &g_AsclinShellInterface,       &AppShell_motor1vol,    },
    {"m0e", "      : Motor0Enable", &g_AsclinShellInterface,       &AppShell_motor0en,    },
    {"m1e", "      : Motor1Enable", &g_AsclinShellInterface,       &AppShell_motor1en,    },
    {"srv", "      : Servo Angle", &g_AsclinShellInterface,       &AppShell_srv,    },
    {"bpon", "     : Beeper On", &g_AsclinShellInterface,       &AppShell_beeperon,    },
    {"bpf", "      : Beeper Freq", &g_AsclinShellInterface,       &AppShell_beeperfreq,    },
    {"bpv", "      : Beeper Vol", &g_AsclinShellInterface,       &AppShell_beepervol,    },
    {"l108", "     : LED108", &g_AsclinShellInterface,       &AppShell_led108,    },
    {"l109", "     : LED109", &g_AsclinShellInterface,       &AppShell_led109,    },
    {"l110", "     : LED110", &g_AsclinShellInterface,       &AppShell_led110,    },
    {"ls0", "      : LineScan0", &g_AsclinShellInterface,       &AppShell_linescan0,    },
    {"ls1", "      : LineScan1", &g_AsclinShellInterface,       &AppShell_linescan1,    },
    {"mls", "      : Monitoring LineScan", &g_AsclinShellInterface,       &AppShell_monlinescan,    },
	{"mirs", "     : Monitoring IrScan", &g_AsclinShellInterface,       &AppShell_monirscan,    },
    {"vadc", "     : Vadc Backgound 1", &g_AsclinShellInterface,       &AppShell_vadcbg1,    },
//    {"enc", "      : Encoder", &g_AsclinShellInterface,       &AppShell_enc,    },
//    {"p00_0", "    : Port00_0", &g_AsclinShellInterface,       &AppShell_port00_0,    },
//    {"p00_1", "    : Port00_1", &g_AsclinShellInterface,       &AppShell_port00_1,    },
//    {"info",   "     : Show the welcome screen",   &g_AsclinShellInterface,       &AppShell_info,      },
    {"help",   SHELL_HELP_DESCRIPTION_TEXT,        &g_AsclinShellInterface.shell, &Ifx_Shell_showHelp, },
    IFX_SHELL_COMMAND_LIST_END
};

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
/** \addtogroup IfxLld_Demo_AsclinShellInterface_SrcDoc_Main_Interrupt
 * \{ */

/** \name Interrupts for Serial interface
 * \{ */

IFX_INTERRUPT(ISR_Asc_0_rx, 0, ISR_PRIORITY_ASC_0_RX);
IFX_INTERRUPT(ISR_Asc_0_tx, 0, ISR_PRIORITY_ASC_0_TX);
IFX_INTERRUPT(ISR_Asc_0_ex, 0, ISR_PRIORITY_ASC_0_EX);

/** \} */

/** \} */

/** \brief Handle Asc0 Rx interrupt
 *
 * \isrProvider \ref ISR_PROVIDER_ASC_0
 * \isrPriority \ref ISR_PRIORITY_ASC_0_RX
 *
 * - Configuration of this interrupt is done by Asc_If_init()
 * - This interrupt is raised each time a data have been received on the serial interface.
 *   and Asc_If_receiveIrq() will be called
 */

boolean AppShell_servo1(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : srv1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		BLT.servo1 = vol;
    	}
    	IfxStdIf_DPipe_print(io, "  servo1 : %4.2f "ENDL, BLT.servo1);
    }

    return TRUE;
}

boolean AppShell_servo2(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : srv2"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		BLT.servo2 = vol;
    	}
    	IfxStdIf_DPipe_print(io, "  servo2 : %4.2f "ENDL, BLT.servo2);
    }

    return TRUE;
}


boolean AppShell_cnt1(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : cnt1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		BLT.cnt1 = vol;
    	}
    	IfxStdIf_DPipe_print(io, "  cnt1 : %4d "ENDL, BLT.cnt1);
    }

    return TRUE;
}

boolean AppShell_cnt2(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : cnt2"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		BLT.cnt2 = vol;
    	}
    	IfxStdIf_DPipe_print(io, "  cnt2 : %4d "ENDL, BLT.cnt2);
    }

    return TRUE;
}

boolean AppShell_button(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : button 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		BLT.button = vol;
    	}
    	IfxStdIf_DPipe_print(io, "  button : %4d "ENDL, BLT.button);
    }

    return TRUE;
}

boolean AppShell_Scanstate(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : ScanState"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		BLT.Scanstate = vol;
    	}
    	IfxStdIf_DPipe_print(io, "  scan : %4d "ENDL, BLT.Scanstate);
    }

    return TRUE;
}

boolean AppShell_Dashstate(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : DashState"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		BLT.Dashstate = vol;
    	}
    	IfxStdIf_DPipe_print(io, "  dash : %4d "ENDL, BLT.Dashstate);
    }

    return TRUE;
}

void ISR_Asc_0_rx(void)
{
    IfxCpu_enableInterrupts();
    IfxStdIf_DPipe_onReceive(&g_AsclinShellInterface.stdIf.asc);
}


/** \brief Handle Asc0 Tx interrupt
 *
 * \isrProvider \ref ISR_PROVIDER_ASC_0
 * \isrPriority \ref ISR_PRIORITY_ASC_0_TX
 *
 * - Configuration of this interrupt is done by Asc_If_init()
 * - This interrupt is raised each time the serial interface transmit buffer get empty
 *   and Asc_If_transmitIrq() will be called
 */
void ISR_Asc_0_tx(void)
{
    IfxCpu_enableInterrupts();
    IfxStdIf_DPipe_onTransmit(&g_AsclinShellInterface.stdIf.asc);
}


/** \brief Handle Asc0 Ex interrupt.
 *
 * \isrProvider \ref ISR_PROVIDER_ASC_0
 * \isrPriority \ref ISR_PRIORITY_ASC_0_EX
 *
 * - Configuration of this interrupt is done by Asc_If_init()
 * - This interrupt is raised each time an error occurs on the serial interface and
 *   Asc_If_errorIrq() will be called.
 */
void ISR_Asc_0_ex(void)
{
    IfxCpu_enableInterrupts();
    IfxStdIf_DPipe_onError(&g_AsclinShellInterface.stdIf.asc);
}


/** \addtogroup IfxLld_Demo_AsclinShellInterface_SrcDoc_Main_Interrupt
 * \{ */

/** Send the welcome screen to the Terminal
 *
 */
void welcomeScreen(App_AsclinShellInterface *app, IfxStdIf_DPipe *io)
{
    IfxStdIf_DPipe_print(io, ENDL ""ENDL);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDL);
    IfxStdIf_DPipe_print(io, "*******  Welcome to Infineon Racer Shell                               *******"ENDL);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDL);
    IfxStdIf_DPipe_print(io, "*******  Software Version Date : %4X/%2X/%2X                            *******"ENDL, app->info.srcRevDate >> 16, (app->info.srcRevDate >> 8) & 0xFF, (app->info.srcRevDate & 0xFF));
    IfxStdIf_DPipe_print(io, "*******  Software Version      : %2d.%02d                                 *******"ENDL, (app->info.srcRev >> 8) & 0xFF, (app->info.srcRev >> 0) & 0xFF);
    IfxStdIf_DPipe_print(io, "*******  iLLD version          : %d.%d.%d.%d.%d                            *******"ENDL, IFX_LLD_VERSION_GENERATION, IFX_LLD_VERSION_MAJOR, IFX_LLD_VERSION_MAJOR_UPDATE, IFX_LLD_VERSION_MINOR, IFX_LLD_VERSION_REVISION);
    IfxStdIf_DPipe_print(io, "*******  "COMPILER_NAME " Compiler         : %ld.%1dr%1d                                 *******"ENDL, (app->info.compilerVer >> 16) & 0xFF, (app->info.compilerVer >> 8) & 0xFF, (app->info.compilerVer >> 0) & 0xFF);
    IfxStdIf_DPipe_print(io, "*******  Author                : Wootaik Lee (CI-ARCLab)               *******"ENDL);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDL);

    Ifx_DateTime rt;
    DateTime_get(&rt);
    IfxStdIf_DPipe_print(io, "Real-time: %02d:%02d:%02d"ENDL, rt.hours, rt.minutes, rt.seconds);
    IfxStdIf_DPipe_print(io, "CPU Frequency: %ld Hz"ENDL, (sint32)g_AppCpu0.info.cpuFreq);
    IfxStdIf_DPipe_print(io, "SYS Frequency: %ld Hz"ENDL, (sint32)g_AppCpu0.info.sysFreq);
    IfxStdIf_DPipe_print(io, "STM Frequency: %ld Hz"ENDL, (sint32)g_AppCpu0.info.stmFreq);
}


/** \brief Handle the 'info' command.
 *
 * \par Syntax
 * - info : Show application information */
boolean AppShell_info(pchar args, void *data, IfxStdIf_DPipe *io)
{
    App_AsclinShellInterface *app = (App_AsclinShellInterface *)data;

    welcomeScreen(app, io);
    return TRUE;
}


/** \brief Handle the 'status' command
 *
 * \par Syntax
 *  - status : Show the application internal state
 */
boolean AppShell_status(pchar args, void *data, IfxStdIf_DPipe *io)
{
	AppShell_motor0vol(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_motor1vol(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_motor0en(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_motor1en(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_srv(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_beeperon(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_beeperfreq(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_beepervol(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_led108(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_led109(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_led110(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_vadcbg1(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_enc(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_port00_0(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_port00_1(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
//	AppShell_linescan0(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
//	AppShell_linescan1(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
    return TRUE;
}

boolean AppShell_scan(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
	    {
	        IfxStdIf_DPipe_print(io, "  Syntax     : hand code vlaues"ENDL);
	    }
	    else
	    {
	    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
	    		;
	    	}
	    	IfxStdIf_DPipe_print(io, "  ScanState: %d fraction"ENDL, SCAN_STATE);
	    	IfxStdIf_DPipe_print(io, "  OFFSET: %d fraction"ENDL, OFFSET);
	    	IfxStdIf_DPipe_print(io, "  SteerDuty: %4.2f fraction"ENDL, SteerDuty);
	    	IfxStdIf_DPipe_print(io, "  Left Line: %d fraction"ENDL, Left_line);
	    	IfxStdIf_DPipe_print(io, "  Right Line: %d fraction"ENDL, Right_line);
	    	IfxStdIf_DPipe_print(io, "  var1: %4.6f fraction"ENDL, var1);
	    	IfxStdIf_DPipe_print(io, "  ERROR_steer: %d fraction"ENDL, ERROR_steer);
	    	IfxStdIf_DPipe_print(io, "  ERROR_steer_old: %d fraction"ENDL, ERROR_steer_old);
	    }

    return TRUE;
}

boolean AppShell_steerPgain(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : Steer P gain"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		SteerGain.fltSteerPgain = vol;
    	}
    	IfxStdIf_DPipe_print(io, "  SteerPgain: %4.5f fraction"ENDL, SteerGain.fltSteerPgain);
    }

    return TRUE;
}

boolean AppShell_steerDgain(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : Steer D gain"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		SteerGain.fltSteerDgain = vol;
    	}
    	IfxStdIf_DPipe_print(io, "  SteerPgain: %4.5f fraction"ENDL, SteerGain.fltSteerDgain);
    }

    return TRUE;
}

boolean AppShell_motor0vol(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : m0v frac-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		IR_setMotor0Vol(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  Motor0Vol: %4.2f fraction"ENDL, IR_getMotor0Vol());
    }

    return TRUE;
}

boolean AppShell_motor1vol(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : m1v frac-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		IR_setMotor1Vol(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  Motor1Vol: %4.2f fraction"ENDL, IR_getMotor1Vol());
    }

    return TRUE;
}

boolean AppShell_motor0en(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : m0e 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		IR_setMotor0En(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  Motor0En: %4d "ENDL, IR_getMotor0En());
    }

    return TRUE;
}

boolean AppShell_motor1en(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : m1e 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		IR_setMotor1En(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  Motor1En: %4d "ENDL, IR_getMotor1En());
    }

    return TRUE;
}

boolean AppShell_srv(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : srv frac-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		IR_setSrvAngle(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  SrvAngle: %4.2f fraction"ENDL, IR_getSrvAngle());
    }

    return TRUE;
}

boolean AppShell_beeperon(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 beeper;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : bpon 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &beeper) != FALSE){
    		IR_setBeeperOn((boolean)beeper);
    	}
    	IfxStdIf_DPipe_print(io, "  Beeper On: %4d "ENDL, IR_getBeeperOn());
    }

    return TRUE;
}

boolean AppShell_beeperfreq(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 freq;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : bpf float-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &freq) == TRUE){
    		IR_setBeeperFreq(freq);
    	}
    	IfxStdIf_DPipe_print(io, "  Beeper Freq: %7.1f "ENDL, IR_getBeeperFreq());
    }

    return TRUE;
}

boolean AppShell_beepervol(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : bpv frac-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		IR_setBeeperVol(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  Beeper Volume: %4.2f "ENDL, IR_getBeeperVol());
    }

    return TRUE;
}

boolean AppShell_led108(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 led;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : l108 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &led) != FALSE){
    		IR_setLed108((boolean)led);
    	}
    	IfxStdIf_DPipe_print(io, "  Led108: %4d "ENDL, IR_getLed108());
    }

    return TRUE;
}

boolean AppShell_led109(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 led;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : l109 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &led) != FALSE){
    		IR_setLed109((boolean)led);
    	}
    	IfxStdIf_DPipe_print(io, "  Led109: %4d "ENDL, IR_getLed109());
    }

    return TRUE;
}

boolean AppShell_led110(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 led;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : l110 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &led) != FALSE){
    		IR_setLed110((boolean)led);
    	}
    	IfxStdIf_DPipe_print(io, "  Led110: %4d "ENDL, IR_getLed110());
    }

    return TRUE;
}

boolean AppShell_monlinescan(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 period_ms;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : mls period_ms"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &period_ms) != FALSE){
    		g_LineScan.period_ms = period_ms;
    		g_LineScan.enable = TRUE;
    	}else
    	{
    		g_LineScan.enable = FALSE;
    	}
    	IfxStdIf_DPipe_print(io, "  mls: %4d "ENDL, g_LineScan.period_ms);
    }

    return TRUE;
}

boolean AppShell_monirscan(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 period_ms;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : mirs period_ms"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &period_ms) != FALSE){
    		g_IrScan.period_ms = period_ms;
    		g_IrScan.enable = TRUE;
    	}else
    	{
    		g_IrScan.enable = FALSE;
    	}
    	IfxStdIf_DPipe_print(io, "  mirs: %4d "ENDL, g_IrScan.period_ms);
    }

    return TRUE;
}

boolean AppShell_linescan0(pchar args, void *data, IfxStdIf_DPipe *io){
	sint32 i;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : ls0 "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  LineScan0 results "ENDL);
    	for(i = 0; i<127; i++){
    		IfxStdIf_DPipe_print(io, "%5d,",IR_LineScan.adcResult[0][i]);
    	}
		IfxStdIf_DPipe_print(io, "%5d"ENDL,IR_LineScan.adcResult[0][i]);
    }
    return TRUE;
}

boolean AppShell_linescan1(pchar args, void *data, IfxStdIf_DPipe *io){
	sint32 i;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : ls1 "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  LineScan1 results "ENDL);
    	for(i = 0; i<127; i++){
    		IfxStdIf_DPipe_print(io, "%5d,",IR_LineScan.adcResult[1][i]);
    	}
		IfxStdIf_DPipe_print(io, "%5d"ENDL,IR_LineScan.adcResult[1][i]);
    }
    return TRUE;
}

boolean AppShell_vadcbg1(pchar args, void *data, IfxStdIf_DPipe *io){
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : vadc "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  Vadc ");
    	IfxStdIf_DPipe_print(io, "  Ch15: %4.2f,",IR_getChn15());
    	IfxStdIf_DPipe_print(io, "  Ch16: %4.2f,",IR_getChn16());
    	IfxStdIf_DPipe_print(io, "  Ch20: %4.2f,",IR_getChn20());
    	IfxStdIf_DPipe_print(io, "  Ch21: %4.2f,"ENDL,IR_getChn21());
    }
    return TRUE;
}


boolean AppShell_enc(pchar args, void *data, IfxStdIf_DPipe *io)
{
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : enc "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  Encoder speed: %5d, position: %4d, direction: %1d "ENDL,
    			IR_getEncSpeed(), IR_getEncPosition(), IR_getEncDirection());
    }

    return TRUE;
}

boolean AppShell_port00_0(pchar args, void *data, IfxStdIf_DPipe *io)
{
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : p00_0 "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  Port00_0: %4d "ENDL, IR_getPort00_0());
    }

    return TRUE;
}

boolean AppShell_port00_1(pchar args, void *data, IfxStdIf_DPipe *io)
{
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : p00_0 "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  Port00_0: %4d "ENDL, IR_getPort00_1());
    }

    return TRUE;
}

/** Initialise the serial interafce
 *
 */
void initSerialInterface(void)
{
    {   /** - Serial interface */
        IfxAsclin_Asc_Config config;
        IfxAsclin_Asc_initModuleConfig(&config, &MODULE_ASCLIN0);
        config.baudrate.baudrate             = CFG_ASC_BAUDRATE;
        config.baudrate.oversampling         = IfxAsclin_OversamplingFactor_16;
        config.bitTiming.medianFilter        = IfxAsclin_SamplesPerBit_three;
        config.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_8;
        config.interrupt.rxPriority          = ISR_PRIORITY(INTERRUPT_ASC_0_RX);
        config.interrupt.txPriority          = ISR_PRIORITY(INTERRUPT_ASC_0_TX);
        config.interrupt.erPriority          = ISR_PRIORITY(INTERRUPT_ASC_0_EX);
        config.interrupt.typeOfService       = ISR_PROVIDER_ASC_0;
        IfxAsclin_Asc_Pins ascPins = {
            .cts       = NULL_PTR,
            .ctsMode   = IfxPort_InputMode_noPullDevice,
            .rx        = &IfxAsclin0_RXB_P15_3_IN,
            .rxMode    = IfxPort_InputMode_noPullDevice,
            .rts       = NULL_PTR,
            .rtsMode   = IfxPort_OutputMode_pushPull,
            .tx        = &IfxAsclin0_TX_P15_2_OUT,
            .txMode    = IfxPort_OutputMode_pushPull,
            .pinDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1
        };
        config.pins         = &ascPins;
        config.rxBuffer     = g_AsclinShellInterface.ascBuffer.rx;
        config.txBuffer     = g_AsclinShellInterface.ascBuffer.tx;
        config.txBufferSize = CFG_ASC_TX_BUFFER_SIZE;
        config.rxBufferSize = CFG_ASC_RX_BUFFER_SIZE;
        IfxAsclin_Asc_initModule(&g_AsclinShellInterface.drivers.asc, &config);

        /* Connect the standard asc interface to the device driver*/
        IfxAsclin_Asc_stdIfDPipeInit(&g_AsclinShellInterface.stdIf.asc, &g_AsclinShellInterface.drivers.asc);
    }

    /* Ifx_Console initialisation */
    Ifx_Console_init(&g_AsclinShellInterface.stdIf.asc);

    /* Assert initialisation */
    Ifx_Assert_setStandardIo(&g_AsclinShellInterface.stdIf.asc);
}


void AsclinShellInterface_init(void)
{
    /** - Initialise the time constants */
    initTime();

    /** - Initialise the serial interface and the console */
    initSerialInterface();

    g_AsclinShellInterface.info.srcRev      = SW_REVISION;
    g_AsclinShellInterface.info.srcRevDate  = SW_REVISION_DATE;
    g_AsclinShellInterface.info.compilerVer = SW_COMPILER_VERSION;

    /** - Enable the global interrupts of this CPU */
    restoreInterrupts(TRUE);

    Ifx_Console_print(ENDL);

    /** - Show the welcome screen using the standard DPipe interface */
    welcomeScreen(&g_AsclinShellInterface, &g_AsclinShellInterface.stdIf.asc);

    /** - Initialise the shell interface  */
    {
        Ifx_Shell_Config config;
        Ifx_Shell_initConfig(&config);
        config.standardIo     = &g_AsclinShellInterface.stdIf.asc;
        config.commandList[0] = &AppShell_commands[0];

        Ifx_Shell_init(&g_AsclinShellInterface.shell, &config);
    }

//    Ifx_Console_print(ENDL "Enter 'help' to see the available commands"ENDL);
}


void AsclinShellInterface_run(void)
{
    /** Handle the shell interface */
    Ifx_Shell_process(&g_AsclinShellInterface.shell);
}

void AsclinShellInterface_runLineScan(void)
{
	sint32 i;
	static sint32 cnt;

	if(g_LineScan.enable == TRUE)
	{
		cnt--;
		if(cnt < 0){
			cnt = (sint32) g_LineScan.period_ms/10;

			for(i = 0; i<128; i++){
			IfxStdIf_DPipe_print(&g_AsclinShellInterface.stdIf.asc, "%5d,%5d"ENDL,IR_LineScan.adcResult[0][i], IR_LineScan.adcResult[1][i]);
			}
		}
	}
}

//void AsclinShellInterface_runIrScan(void)
//{
//	sint32 i;
//	static sint32 cnt;
//
//	if(g_LineScan.enable == TRUE)
//	{
//		cnt--;
//		if(cnt < 0){
//			cnt = (sint32) g_LineScan.period_ms/10;
//
//
//			IfxStdIf_DPipe_print(&g_AsclinShellInterface.stdIf.asc, "  Ir Sensor Value: %4.2f,"ENDL,IR_getChn15());
//
//		}
//	}
//}

void AsclinShellInterface_ShowIrAvg(void)
 {
 	sint32 i;
 	static sint32 cnt;
 	if(g_IrScan.enable == TRUE)
 	{
		cnt--;
 		if(cnt < 0){
 			cnt = (sint32) g_IrScan.period_ms/20;
			IfxStdIf_DPipe_print(&g_AsclinShellInterface.stdIf.asc, "Sensor Value : ");
// 			for(i = 0;i <= 19;){
//				IfxStdIf_DPipe_print(&g_AsclinShellInterface.stdIf.asc, "[%4.2f],",IR_Result[i]);
// 			}
			IfxStdIf_DPipe_print(&g_AsclinShellInterface.stdIf.asc, ENDL"  Ir Avg Value: %4.2f"ENDL,IrScan.fltIrAvg);

			}

		}
 }
