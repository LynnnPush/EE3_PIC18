/*
 * File:   nrf24_lib.c
 * Author: Noyel Seth (noyelseth@gamil.com)
 * Modified by: BUILD1 (EE3, GroupT, KUL)
 */

#include "nrf24_lib.h"


void nrf24_write_register(uint8_t mnemonic_addr, uint8_t value) {
//    NRF24L01_CSN_L();
    if (mnemonic_addr < W_REGISTER) {
		// This is a register access
        NRF24L01_CSN_L();
		SPI_WRITE_BYTE(W_REGISTER | (mnemonic_addr & NRF24_MEM_REGISTER_MASK));
		SPI_WRITE_BYTE(value);
	} else {
		// This is a single byte command or future command/register
		SPI_WRITE_BYTE(mnemonic_addr);
		if ((mnemonic_addr != FLUSH_TX) && (mnemonic_addr != FLUSH_RX) && \
				(mnemonic_addr != REUSE_TX_PL) && (mnemonic_addr != NRF24_MEM_CMD_NOP)) {
			// Send register value
            NRF24L01_CSN_L();
			SPI_WRITE_BYTE(value);
		}
	}
    NRF24L01_CSN_H();
    __delay_us(10);
}

uint8_t nrf24_read_register(uint8_t mnemonic_addr) {
    uint8_t byte0;
    NRF24L01_CSN_L();
    SPI_WRITE_BYTE(R_REGISTER | (mnemonic_addr & NRF24_MEM_REGISTER_MASK) );
    byte0 = SPI_READ_BYTE(0xFF);
    NRF24L01_CSN_H();
    return byte0;
}

void nrf24_write_buff(unsigned char mnemonic_addr, unsigned char *buffer, unsigned char bytes) {
    unsigned char i;
    NRF24L01_CSN_L();
    //printf("Buffer = %s\r\n", buffer);
    SPI_WRITE_BYTE(W_REGISTER | mnemonic_addr);
    for (i = 0; i < bytes; i++) {
        SPI_WRITE_BYTE(*buffer);
        buffer++;
        __delay_us(10);
    }
    NRF24L01_CSN_H();
//    __delay_us(10);
}

void nrf24_read_buff(unsigned char mnemonic_addr, unsigned char *buffer, unsigned char bytes) {
    unsigned char i;
    NRF24L01_CSN_L();
    SPI_WRITE_BYTE(R_REGISTER | mnemonic_addr);
    for (i = 0; i < bytes; i++) {
        *buffer = SPI_READ_BYTE(NRF24_MEM_CMD_NOP);
        buffer++;
    }
    *buffer = (unsigned char )NULL;
    NRF24L01_CSN_H();
}

NRF24_INIT_STATUS nrf24_rf_init(unsigned char mode, unsigned char rf_channel) {
    NRF24_INIT_STATUS stat = NRF24_INIT_FAILED;
    SPI_INIT();
    NRF24L01_CSN_SetOutput();
    NRF24L01_CE_SetOutput();
    NRF24L01_CSN_H();
    NRF24L01_CE_L();
    __delay_us(10);
    NRF24L01_CE_L();
    nrf24_write_register(NRF24_MEM_CONFIG, 0x0A);
    //__delay_us(10);
    nrf24_write_register(NRF24_MEM_EN_AA, 0x01);
    nrf24_write_register(NRF24_MEM_EN_RXADDR, 0x03);
    nrf24_write_register(NRF24_MEM_SETUP_AW, 0x03);
    nrf24_write_buff(NRF24_MEM_RX_ADDR_P0 , ADDRESS_DATA_RXPIPE0, 5);
    nrf24_write_buff(NRF24_MEM_TX_ADDR , ADDRESS_DATA_TXPIPE0, 5);
    
    nrf24_write_register(NRF24_MEM_SETUP_RETR, 0x03);
    nrf24_set_channel_frq(rf_channel);
    nrf24_write_register(NRF24_MEM_RF_SETUP, 0x06);
    //NRF24L01_WriteRegister(STATUSS, 0x70);
    
    nrf24_write_register(NRF24_MEM_RX_PW_P0, PAYLOAD_BYTES);
    
    __delay_us(10);
    nrf24_set_rf_mode(mode);
    __delay_us(10);
    
    // Clear TX&RX FIFO
    nrf24_flush_tx_rx();
    
    uint8_t i = nrf24_read_register(NRF24_MEM_CONFIG);
    if ((i & 0x08) != 0){
      //printf("rfCardPresent = TRUE\r\n");
      stat = NRF24_INIT_OK;
    }
    __delay_us(100);
    return stat;
}

void nrf24_set_rf_mode(NRF24_OPERATION_MODE mode) {
    switch (mode) {
        case RX_MODE:
//            printf("RX mode\r\n");
            nrf24_write_register(NRF24_MEM_CONFIG, 0x0F); // RX Control
            NRF24L01_CE_H();
            break;
        case TX_MODE:
            nrf24_write_register(NRF24_MEM_CONFIG, 0x0E); // TX Control 
            NRF24L01_CE_L();
            break;
    }
}

void nrf24_send_rf_data(unsigned char *buffer) {
    nrf24_set_rf_mode(TX_MODE);
    nrf24_write_buff(W_TX_PAYLOAD, buffer, PAYLOAD_BYTES);
    
    // STATUS and FIFO_STATUS before sending data
//    printf("Before Sending: \n");
//    nrf24_printf_rf_status();
    
    NRF24L01_CE_H();
    __delay_ms(1);
    NRF24L01_CE_L();
    
    //If the MAX_RT is set, clear it to enable communication
    if(nrf24_read_register(NRF24_MEM_STATUSS)&0x01)
        nrf24_flush_tx_rx();
    else if(nrf24_read_register(NRF24_MEM_STATUSS)&0x20)
        printf("TX side: ACK Received!\n");
    
    
    // STATUS and FIFO_STATUS after sending data
    printf("After Sending: \n");
    nrf24_printf_rf_status();
    printf("\n");
    
    nrf24_write_register(NRF24_MEM_STATUSS,0x70);
}

unsigned char nrf24_is_rf_data_available(void) {
    if ((nrf24_read_register(NRF24_MEM_STATUSS) & 0x40) == 0x40) {
        return 1;
    }
    return 0;
}

void nrf24_read_rf_data(unsigned char *buffer) {
    nrf24_read_buff(R_RX_PAYLOAD, buffer, PAYLOAD_BYTES);
    nrf24_write_register(NRF24_MEM_STATUSS, 0x70); // Clear STATUS.
    nrf24_flush_tx_rx();
}

void nrf24_set_channel_frq(unsigned char rf_channel) {
    nrf24_write_register(NRF24_MEM_RF_CH, rf_channel);
}

unsigned char nrf24_get_channel_frq(void) {
    return nrf24_read_register(NRF24_MEM_RF_CH);
}

void nrf24_standby_I(void) {
    nrf24_write_register(NRF24_MEM_CONFIG, 0x0A);
    __delay_ms(10);
}

void nrf24_flush_tx_rx(void) {
    NRF24L01_CSN_L();
    nrf24_write_register(NRF24_MEM_STATUSS, 0x70);
    __delay_ms(10);
    NRF24L01_CSN_H();
    
    NRF24L01_CSN_L();
    SPI_WRITE_BYTE(FLUSH_TX);
    __delay_ms(10);
    NRF24L01_CSN_H();
    
    NRF24L01_CSN_L();
    SPI_WRITE_BYTE(FLUSH_RX);
    __delay_ms(10);    
    NRF24L01_CSN_H();
}

// Print nRF24L01+ current configuration (for debug purposes)
void nrf24_printf_rf_config(void) {
	uint8_t i,j;
	uint8_t aw;
	uint8_t buf[5];

	// Dump nRF24L01+ configuration
	// CONFIG
	i = nrf24_read_register(NRF24_MEM_CONFIG);
	printf("[0x%02X] 0x%02X MASK:%03X CRC:%02X PWR:%s MODE:P%s\r\n",
			NRF24_MEM_CONFIG,
			i,
			i >> 4,
			(i & 0x0c) >> 2,
			(i & 0x02) ? "ON" : "OFF",
			(i & 0x01) ? "RX" : "TX"
		);
    
    
	// EN_AA
	i = nrf24_read_register(NRF24_MEM_EN_AA);
	printf("[0x%02X] 0x%02X ENAA: ",NRF24_MEM_EN_AA,i);
	for (j = 0; j < 6; j++) {
		printf("[P%1u%s]%s",j,
				(i & (1 << j)) ? "+" : "-",
				(j == 5) ? "\r\n" : " "
			);
	}
	// EN_RXADDR
	i = nrf24_read_register(NRF24_MEM_EN_RXADDR);
	printf("[0x%02X] 0x%02X EN_RXADDR: ",NRF24_MEM_EN_RXADDR,i);
	for (j = 0; j < 6; j++) {
		printf("[P%1u%s]%s",j,
				(i & (1 << j)) ? "+" : "-",
				(j == 5) ? "\r\n" : " "
			);
	}
	// SETUP_AW
	i = nrf24_read_register(NRF24_MEM_SETUP_AW);
	aw = (i & 0x03) + 2;
    //printf("%d..\r\n",(i & 0x03) + 2);
	printf("[0x%02X] 0x%02X Address Width: %u bytes\r\n",NRF24_MEM_SETUP_AW,i,aw);
	// SETUP_RETR
	i = nrf24_read_register(NRF24_MEM_SETUP_RETR);
	printf("[0x%02X] 0x%02X ARD=%X ARC=%X (retr.delay=%uus, count=%u)\r\n",
			NRF24_MEM_SETUP_RETR,
			i,
			i >> 4,
			i & 0x0F,
			((i >> 4) * 250) + 250,
			i & 0x0F
		);
	// RF_CH
	i = nrf24_read_register(NRF24_MEM_RF_CH);
	printf("[0x%02X] 0x%02X (%.3uGHz)\r\n",NRF24_MEM_RF_CH,i,2400 + i);
	// RF_SETUP
	i = nrf24_read_register(NRF24_MEM_RF_SETUP);
	printf("[0x%02X] 0x%02X CONT_WAVE:%s PLL_LOCK:%s DataRate=",
			NRF24_MEM_RF_SETUP,
			i,
			(i & 0x80) ? "ON" : "OFF",
			(i & 0x80) ? "ON" : "OFF"
		);
	switch ((i & 0x28) >> 3) {
		case 0x00:
			printf("1Mbps ");
			break;
		case 0x01:
			printf("2Mbps ");
			break;
		case 0x04:
			printf("250kbps ");
			break;
		default:
			printf("??? ");
			break;
	}
	printf("RF_PWR=");
	switch ((i & 0x06) >> 1) {
		case 0x00:
			printf("-18");
			break;
		case 0x01:
			printf("-12");
			break;
		case 0x02:
			printf("-6");
			break;
		case 0x03:
			printf("0");
			break;
		default:
			printf("???");
			break;
	}
	printf("dBm\r\n");
    
    
	// STATUS
	i = nrf24_read_register(NRF24_MEM_STATUSS);
	printf("[0x%02X] 0x%02X IRQ:%03X RX_PIPE:%u TX_FULL:%s\r\n",
			NRF24_MEM_STATUSS,
			i,
			(i & 0x70) >> 4,
			(i & 0x0E) >> 1,
			(i & 0x01) ? "YES" : "NO"
		);
	// OBSERVE_TX
	i = nrf24_read_register(NRF24_MEM_OBSERVE_TX);
	printf("[0x%02X] 0x%02X PLOS_CNT=%u ARC_CNT=%u\r\n",NRF24_MEM_OBSERVE_TX,i,i >> 4,i & 0x0F);
    
	// RPD
	i = nrf24_read_register(NRF24_MEM_CD);
	printf("[0x%02X] 0x%02X RPD=%s\r\n",NRF24_MEM_CD,i,(i & 0x01) ? "YES" : "NO");
	
    // RX_ADDR_P0
	nrf24_read_buff(NRF24_MEM_RX_ADDR_P0,buf,aw);
	printf("[0x%02X] RX_ADDR_P0 \"",NRF24_MEM_RX_ADDR_P0);
	for (i = 0; i < aw; i++) printf("[0x%02X] ",buf[i]);
	printf("\"\r\n");
	
    // RX_ADDR_P1
	nrf24_read_buff(NRF24_MEM_RX_ADDR_P1,buf,aw);
	printf("[0x%02X] RX_ADDR_P1 \"",NRF24_MEM_RX_ADDR_P1);
	for (i = 0; i < aw; i++) printf("[0x%02X] ",buf[i]);
	printf("\"\r\n");
	
    // RX_ADDR_P2
	printf("[0x%02X] RX_ADDR_P2 \"",NRF24_MEM_RX_ADDR_P2);
	for (i = 0; i < aw - 1; i++) printf("[0x%02X] ",buf[i]);
	i = nrf24_read_register(NRF24_MEM_RX_ADDR_P2);
	printf("%c\"\r\n",i);
	
    // RX_ADDR_P3
	printf("[0x%02X] RX_ADDR_P3 \"",NRF24_MEM_RX_ADDR_P3);
	for (i = 0; i < aw - 1; i++) printf("[0x%02X] ",buf[i]);
	i = nrf24_read_register(NRF24_MEM_RX_ADDR_P3);
	printf("%c\"\r\n",i);
	
    // RX_ADDR_P4
	printf("[0x%02X] RX_ADDR_P4 \"",NRF24_MEM_RX_ADDR_P4);
	for (i = 0; i < aw - 1; i++) printf("[0x%02X] ",buf[i]);
	i = nrf24_read_register(NRF24_MEM_RX_ADDR_P4);
	printf("%c\"\r\n",i);
	
    // RX_ADDR_P5
	printf("[0x%02X] RX_ADDR_P5 \"",NRF24_MEM_RX_ADDR_P5);
	for (i = 0; i < aw - 1; i++) printf("[0x%02X] ",buf[i]);
	i = nrf24_read_register(NRF24_MEM_RX_ADDR_P5);
	printf("%c\"\r\n",i);
	
    // TX_ADDR
	nrf24_read_buff(NRF24_MEM_TX_ADDR,buf,aw);
	printf("[0x%02X] TX_ADDR \"",NRF24_MEM_TX_ADDR);
	for (i = 0; i < aw; i++) {printf("[0x%02X] ",buf[i]);/*printf("%c %d..",buf[i], buf[i]);*/}
	printf("\"\r\n");
	
    // RX_PW_P0
	i = nrf24_read_register(NRF24_MEM_RX_PW_P0);
	printf("[0x%02X] RX_PW_P0=%u\r\n",NRF24_MEM_RX_PW_P0,i);
	
    // RX_PW_P1
	i = nrf24_read_register(NRF24_MEM_RX_PW_P1);
	printf("[0x%02X] RX_PW_P1=%u\r\n",NRF24_MEM_RX_PW_P1,i);
	
    // RX_PW_P2
	i = nrf24_read_register(NRF24_MEM_RX_PW_P2);
	printf("[0x%02X] RX_PW_P2=%u\r\n",NRF24_MEM_RX_PW_P2,i);
	
    // RX_PW_P3
	i = nrf24_read_register(NRF24_MEM_RX_PW_P3);
	printf("[0x%02X] RX_PW_P3=%u\r\n",NRF24_MEM_RX_PW_P3,i);
	
    // RX_PW_P4
	i = nrf24_read_register(NRF24_MEM_RX_PW_P4);
	printf("[0x%02X] RX_PW_P4=%u\r\n",NRF24_MEM_RX_PW_P4,i);
	
    // RX_PW_P5
	i = nrf24_read_register(NRF24_MEM_RX_PW_P5);
	printf("[0x%02X] RX_PW_P5=%u\r\n",NRF24_MEM_RX_PW_P5,i);
    
    // FIFO_STATUS
    i = nrf24_read_register(NRF24_MEM_FIFO_STATUS);
    printf("[0x%02X] 0x%02X TX_FULL:%s TX_EMPTY:%s RX_FULL:%s RX_EMPTY:%s\r\n",
            NRF24_MEM_FIFO_STATUS,
            i,
            (i & 0x20) ? "YES" : "NO",
            (i & 0x10) ? "YES" : "NO",
            (i & 0x02) ? "YES" : "NO",
            (i & 0x01) ? "YES" : "NO"
        );
}

// Print values of STATUS and FIFO_STATUS register  (for debug purposes)
void nrf24_printf_rf_status(void) {
	uint8_t i;

    // STATUS
	i = nrf24_read_register(NRF24_MEM_STATUSS);
	printf("[0x%02X] 0x%02X IRQ:%03X RX_PIPE:%u TX_FULL:%s\r\n",
			NRF24_MEM_STATUSS,
			i,
			(i & 0x70) >> 4,
			(i & 0x0E) >> 1,
			(i & 0x01) ? "YES" : "NO"
		);
    
    // FIFO_STATUS
    i = nrf24_read_register(NRF24_MEM_FIFO_STATUS);
    printf("[0x%02X] 0x%02X TX_FULL:%s TX_EMPTY:%s RX_FULL:%s RX_EMPTY:%s\r\n",
            NRF24_MEM_FIFO_STATUS,
            i,
            (i & 0x20) ? "YES" : "NO",
            (i & 0x10) ? "YES" : "NO",
            (i & 0x02) ? "YES" : "NO",
            (i & 0x01) ? "YES" : "NO"
        );
}
    
    

