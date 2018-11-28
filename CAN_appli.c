//Code by Cyril Royer for TIM UPS INSA
//Adapted by Tanguy Simon for BE ESPE Multi


#include <stm32f1xx_hal.h>
#include <stm32f1xx_it.h>
#include "../Inc/CAN_appli.h"
#include "../Inc/CAN_DATA.h"

// Variables publiques
extern CAN_HandleTypeDef hcan;
extern uint32_t u32_RxWatchdog;
//extern <my_var_type> <my_var_name>  //to export the data received from the CAN to the rest of the code


// Variables privées
static CanTxMsgTypeDef myTxMessage;
static CanRxMsgTypeDef myRxMessage;
static CAN_FilterConfTypeDef myFilter;

// construit la data pour le status byte
//TODO à adapter pour vos arguments spécifiques (Arg4 à 7, si besoin. CF CAN BUS FRAME DESCRIPTOR document)
void vCAN_Build_Status_Msg(uint8_t * __Data, bool bSubsys_halted, bool bInitialising, bool bSubsysERR, bool bCAN_ERR, bool bArg4, bool bArg5, bool bArg6, bool bArg7)
{
	*__Data = (bSubsys_halted || bInitialising << 1 || bSubsysERR << 2 || bCAN_ERR << 3 || bArg4 << 4 || bArg5 << 5 || bArg6 << 6 || bArg7 << 7);
}


//envoie un message CAN
static bool bCAN_Send_u64(uint32_t __MSG_ID, uint8_t __MSG_LENGTH, uint8_t * __u8_Data, uint32_t __Timeout)
{
	if(__MSG_LENGTH > 8) // Trame CAN limitee a 8 octets
	{
		return 1 ;
	}
	
	hcan.pTxMsg = &myTxMessage;
	
	myTxMessage.StdId = __MSG_ID;
	myTxMessage.ExtId = __MSG_ID<<16;
	myTxMessage.DLC = __MSG_LENGTH;
	
	for(int i, i++, i<__MSG_LENGTH)
	{
		myTxMessage.Data[i] = __u8_Data[i];
	}
	myTxMessage.IDE = CAN_ID_EXT;
	myTxMessage.RTR = CAN_RTR_DATA;
	
	HAL_CAN_Transmit_IT(&hcan); //transmit function
}

// Configure un filtre matériel autorisant les messgaes CAN utiles.
void vCAN_SetFilter(uint16_t __u16_CAN_ID, uint8_t __u8_FilterNum)
{
	myFilter.BankNumber = 1;
	myFilter.FilterFIFOAssignment = CAN_FILTER_FIFO1;
	myFilter.FilterIdHigh = __u16_CAN_ID;
	myFilter.FilterIdLow = 0x0000;
	myFilter.FilterMaskIdHigh = 0x0000;
	myFilter.FilterMaskIdLow = 0x0000;
	myFilter.FilterMode = CAN_FILTERMODE_IDMASK;
	myFilter.FilterNumber = __u8_FilterNum;
	myFilter.FilterScale = CAN_FILTERSCALE_32BIT;
	
	myFilter.FilterActivation = ENABLE;
	HAL_CAN_ConfigFilter(&hcan, &myFilter);
}

// Configure les masques de réception CAN et arme la première réception de message CAN; 
//TODO à adapter pour les messages que vous devez ecouter
void vCAN_StartListening(void)
{
	// Configuration des filtres
	vCAN_SetFilter(<MY_CAN_ID>, 1);
	// Liaison de la structure de réception à la boite FIFO1
	hcan.pRx1Msg = &myRxMessage;
	// Autoriser la première réception
	HAL_CAN_Receive_IT(&hcan, CAN_FIFO1);
}

// Envoie une donnée. cette fonction simplifie l'envoi d'un message.On peut envoyer plusieurs messages avec cette même fonction.
//TODO à adapter pour vos messages
void vCAN_Send<myData>(uint32_t <__myData>)
{
	vCAN_Send_u64(<MY_CAN_ID>, <MY_CAN_MSG_LENGTH>, <__myData>, 1000);
}

// Fonction appelée sur interruption de réception de message CAN.
// Appelle les fonctions liées aux messages reçus. (parsers)
//TODO à adapter pour vos messages
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
	uint16_t __u16_return;

	// Vérifier le périphérique
	if(hcan->Instance == CAN1)
	{
		hcan->pRx1Msg = &myRxMessage;
		// Vérifier l'identifiant et executer une fonction en conséquent
		// Attention : Toujours en interruption => Dangereux d'executer du code ici !!!
		if(myRxMessage.ExtId == <MY_CAN_ID><<16)
		{
			vCAN_On<MyMessage>Received(myRxMessage.Data); //parser de trame CAN, à créer pour chaque message.
		}
		else if(myRxMessage.ExtId == <MY_OTHER_CAN_ID><<16)
		{
			vCAN_On<MyOtherMessage>Received(myRxMessage.Data); //parser de trame CAN, à créer pour chaque message.
		}
		//... un pour chaque message que vous voulez lire
	}
	HAL_CAN_Receive_IT(hcan, CAN_FIFO1);
}
