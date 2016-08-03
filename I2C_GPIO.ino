
#define SCL_HIGH digitalWrite(SCL,1)
#define SCL_LOW  digitalWrite(SCL,0)

#define SDA_HIGH digitalWrite(SDA,1)
#define SDA_LOW digitalWrite(SDA,0)
#define SCL_IN  digitalRead(SCL)
#define SDA_IN  digitalRead(SDA)

void i2c_dly(void)
{
  delayMicroseconds(100);
}
void i2c_start(void)
{
  SDA_HIGH;             // i2c start bit sequence
  i2c_dly();
  SCL_HIGH;
  i2c_dly();
  SDA_LOW;
  i2c_dly();
  SCL_LOW;
  i2c_dly();
}
void i2c_stop(void)
{
  SDA_LOW;             // i2c stop bit sequence
  i2c_dly();
  SCL_HIGH;
  i2c_dly();
  SDA_HIGH;
  i2c_dly();
}

unsigned char i2c_rx(char ack)
{
char x, d=0;
  SDA_HIGH; 
  for(x=0; x<8; x++) {
    d <<= 1;
    do {
      SCL_HIGH;
    }
    while(SCL_IN==0);    // wait for any SCL clock stretching
    i2c_dly();
    if(SDA_IN) d |= 1;
    SCL_LOW;
  } 
  if(ack) SDA_LOW;
  else SDA_HIGH;
  SCL_HIGH;
  i2c_dly();             // send (N)ACK bit
  SCL_LOW;
  SDA_HIGH;
  return d;
}
unsigned char i2c_tx(unsigned char d)
{
char x;
static unsigned char b;
  for(x=8; x; x--) {
    if(d&0x80) SDA_HIGH;
    else SDA_LOW;
    SCL_HIGH;
    d <<= 1;
    SCL_LOW;
  }
  SDA_HIGH;
  SCL_HIGH;
  i2c_dly();
  b = SDA_IN;          // possible ACK bit
  SCL_LOW;
  return b;
}
void I2C_ReadMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
	uint8_t i;
        i2c_start();
        i2c_tx(address);
       
        i2c_tx(reg);
	//TM_I2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_ENABLE);
	//TM_I2C_WriteData(I2Cx, reg);
        
	//TM_I2C_Stop(I2Cx);
        i2c_stop();
        i2c_start();
        i2c_tx(address);
        i2c_dly();
	//TM_I2C_Start(I2Cx, address, I2C_RECEIVER_MODE, I2C_ACK_ENABLE);
	for (i = 0; i < count; i++) {
		if (i == (count - 1)) {
			/* Last byte */
                       data[i] = i2c_rx(0);
			//data[i] = TM_I2C_ReadNack(I2Cx);
		} else {
                       data[i] = i2c_rx(1);
			// = TM_I2C_ReadAck(I2Cx);
		}
	}
       
}


