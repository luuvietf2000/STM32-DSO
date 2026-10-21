#include "AcquisittionTask.h"
#include "Acquisittion.h"
#include "AcquisittionQueue.h"
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
void AcquisittionTaskHandle(AcquisittionMsg *msg){
	switch(msg->type){
		case ACQUISITTION_START:
			AcquisittionStart();
			break;
		case ACQUISITTION_STOP:
			AcquisittionStop();
			break;
	}
}
