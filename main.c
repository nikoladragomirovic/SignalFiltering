//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *                                                                          
// * Description:  Main function.
// *                                                                          
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *                                                                          
// *                                                                          
// *                                                                          
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "WAVheader.h"
#include "fir.h"
#include "iir.h"
#include "low_pass.h"
#include "notch.h"

static WAV_HEADER outputWAVhdr;
static WAV_HEADER inputWAVhdr;

#define SAMPLE_RATE 48000L
#define GAIN 0

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

/* TO DO: Define history buffers and Rd/Wr pointers*/
/* Your code here */

/*
 *
 *  main( )
 *
 */

Int16 HistoryL[LP_LENGTH1];
Int16 HistoryR[LP_LENGTH1];

Uint16 StateL;
Uint16 StateR;

Int16 HistoryIIRL[2] = {0};
Int16 HistoryIIRR[2] = {0};

Int16 HistoryL_2x[2][2];
Int16 HistoryR_2x[2][2];
Int16 HistoryL_2y[2][2];
Int16 HistoryR_2y[2][2];

Int16 HistoryL_3x[3][2];
Int16 HistoryR_3x[3][2];
Int16 HistoryL_3y[3][2];
Int16 HistoryR_3y[3][2];

void main( void )
{
	int i, j;
	Int32 number_of_blocks;
	/* Initialize BSL */
	EZDSP5535_init( );

	/* Initialise hardware interface and I2C for code */
	aic3204_hardware_init();

	aic3204_set_input_filename("../OUTPUT4.wav");
	aic3204_set_output_filename("../OUTPUT7.wav");

	/* Initialise the AIC3204 codec */
	aic3204_init();

	aic3204_dma_init();

	aic3204_read_wav_header(&inputWAVhdr);

	// Set up output WAV header
	outputWAVhdr = inputWAVhdr;

	number_of_blocks = inputWAVhdr.data.SubChunk2Size/
				(inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample*AUDIO_IO_SIZE/8);

	aic3204_write_wav_header(&outputWAVhdr);

    /* TO DO: Initialize history buffers to 0 */
    /* Your code here */

	for (i = 0; i < 2; i++) {
		HistoryL[i] = 0;
		HistoryR[i] = 0;
	    	for (j = 0; j < 2; j++) {
	    		HistoryL_2x[i][j] = 0;
	    		HistoryL_2y[i][j] = 0;
	    		HistoryR_2x[i][j] = 0;
	    		HistoryR_2y[i][j] = 0;
	    	}
	}

	for(i = 0; i < 3; i++){
		for(j = 0; j < 2; j++){
    		HistoryL_3x[i][j] = 0;
    		HistoryL_3y[i][j] = 0;
    		HistoryR_3x[i][j] = 0;
    		HistoryR_3y[i][j] = 0;
		}
	}

	for(i = 0; i < number_of_blocks; ++i)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		/* TO DO: Invoke filtering routine */
		/* Your code here */

		for(j = 0; j < AUDIO_IO_SIZE; j++)
		{

			//OutputBufferL[j] = fir_circular(InputBufferL[j], low_pass_35, HistoryL, LP_LENGTH1, &StateL);
			//OutputBufferR[j] = fir_circular(InputBufferR[j], low_pass_35, HistoryR, LP_LENGTH1, &StateR);

			//OutputBufferL[j] = second_order_IIR(InputBufferL[j], IIR_low_pass_2000_2, HistoryL, HistoryIIRL);
			//OutputBufferR[j] = second_order_IIR(InputBufferR[j], IIR_low_pass_2000_2, HistoryR, HistoryIIRR);

			//OutputBufferL[j] = fir_circular(InputBufferL[j], low_pass_77, HistoryL, LP_LENGTH2, &StateL);
			//OutputBufferR[j] = fir_circular(InputBufferR[j], low_pass_77, HistoryR, LP_LENGTH2, &StateR);

			//OutputBufferL[j] = fir_circular(InputBufferL[j], low_pass_129, HistoryL, LP_LENGTH3, &StateL);
			//OutputBufferR[j] = fir_circular(InputBufferR[j], low_pass_129, HistoryR, LP_LENGTH3, &StateR);

			//OutputBufferL[j] = second_order_IIR(InputBufferL[j], IIR_low_pass_300_2, HistoryL, HistoryIIRL);
			//OutputBufferR[j] = second_order_IIR(InputBufferR[j], IIR_low_pass_300_2, HistoryR, HistoryIIRR);

			//OutputBufferL[j] = fourth_order_IIR(InputBufferL[j], IIR_low_pass_300_4, HistoryL_2x, HistoryL_2y);
			//OutputBufferR[j] = fourth_order_IIR(InputBufferR[j], IIR_low_pass_300_4, HistoryR_2x, HistoryR_2y);

			//OutputBufferL[j] = sixth_order_IIR(InputBufferL[j], IIR_low_pass_300_6, HistoryL_3x, HistoryL_3y);
			//OutputBufferR[j] = sixth_order_IIR(InputBufferR[j], IIR_low_pass_300_6, HistoryR_3x, HistoryR_3y);
		}
		aic3204_write_block(OutputBufferL, OutputBufferR);
	}
	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}
