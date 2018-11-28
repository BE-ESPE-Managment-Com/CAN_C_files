#ifndef CAN_appli_H
#define CAN_appli_H

// Includes
#include <stm32f1xx_hal.h>

// Fonctions publiques

// Construit le status byte (cf CAN BUS FRAME DESCRIPTOR, p.2, .SHARED FOLDER)
void vCAN_Build_Status_Msg(uint8_t * __Data, bool bSubsys_halted, bool bInitialising, bool bSubsysERR, bool bCAN_ERR, bool bArg4, bool bArg5, bool bArg6, bool bArg7);

// Configure un filtre matériel autorisant les messgaes CAN utiles.
void vCAN_SetFilter(uint16_t __u16_CAN_ID, uint8_t __u8_FilterNum);

// Configure les masques de réception CAN et arme la première réception de message CAN; 
void vCAN_StartListening(void);

// Envoie une donnée sur le CAN  TODO à modifier
void vCAN_Send<myData>(uint32_t <__myData>)

// Envoie en une seule trame les données batterie, courant et rapport cyclique
void vCAN_SendAllData(uint16_t __u16_BatterymV, uint16_t __u16_AlphaPercent, int16_t __s16CurrentmA);

#endif
