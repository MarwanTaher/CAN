/*
 * SPI.h
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-063
 */

#ifndef SPI_H_
#define SPI_H_

extern void SPI_INIT ();
extern uint32_t SPI_RECIEVE();
void SPI_RECIEVE_INIT (void);
void SPI_TRANSMIT(uint32_t Data);

#endif /* SPI_H_ */
