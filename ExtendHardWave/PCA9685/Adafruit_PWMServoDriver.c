/*************************************************** 
  This is a library for our Adafruit 16-channel PWM & Servo driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_PWMServoDriver.h>
#include <math.h>


// Set to true to print some debug messages, or false to disable them.
#define ENABLE_DEBUG_OUTPUT 1

//void Adafruit_PWMServoDriver(u8 addr) {
//	addr= 0x40;
//  _i2caddr = addr;
//}

//u8 _i2caddr=0x80;
u8 _i2caddr=0xAA;

void begin(void) {
	IIC_Init();
	reset(); 
//	printf("PWM servo Init Over!\n");
}


void reset(void) {
 write8(PCA9685_MODE1, 0x0);
}

void SetPWMFreq(float freq) {
	
	
	u8 oldmode = read8(PCA9685_MODE1);
	u8 newmode = (oldmode&0x7F) | 0x10; // sleep
	u8 prescale;
	float prescaleval;
	//Serial.print("Attempting to set freq ");
	//Serial.println(freq);
	freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
	prescaleval = 25000000;
	printf("EVA :%f\t",prescaleval);
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	if (ENABLE_DEBUG_OUTPUT) {
	printf("Estimated pre-scale: "); printf("%f\t",prescaleval);
	}
	prescale = floor(prescaleval + 0.5);
	if (ENABLE_DEBUG_OUTPUT) {
	printf("Final pre-scale: "); printf("%d\n",prescale);
	}


	write8(PCA9685_MODE1, newmode); // go to sleep
	write8(PCA9685_PRESCALE, prescale); // set the prescaler
	write8(PCA9685_MODE1, oldmode);
	delay_us(50);
	write8(PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
							// This is why the beginTransmission below was not working.
	//  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);
}

void SetPWM(u8 num, u16 on, u16 off) {
	//Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);
//	printf("setPWM");
      IIC_Start();
	IIC_Sentdate(_i2caddr);
	IIC_Sentdate(LED0_ON_L+4*num);
	IIC_Sentdate(on);
	IIC_Sentdate(on>>8);
	IIC_Sentdate(off);
	IIC_Sentdate(off>>8);
	IIC_Stop();
}

// Sets pin without having to deal with on/off tick placement and properly handles
// a zero value as completely off.  Optional invert parameter supports inverting
// the pulse for sinking to ground.  Val should be a value from 0 to 4095 inclusive.
void SetPin(u8 num, u16 val, u8 invert)
{
	// Clamp value between 0 and 4095 inclusive.
	val = fmin(val, 4095);
	if (invert) {
		if (val == 0) {
		// Special value for signal fully on.
			SetPWM(num, 4096, 0);
		}
		else if (val == 4095) {
		// Special value for signal fully off.
			SetPWM(num, 0, 4096);
		}
		else {
			SetPWM(num, 0, 4095-val);
		}
	}
	else {
		if (val == 4095) {
		// Special value for signal fully on.
			SetPWM(num, 4096, 0);
		}
		else if (val == 0) {
		// Special value for signal fully off.
			SetPWM(num, 0, 4096);
		}
		else {
			SetPWM(num, 0, val);
		}
	}
}

u8 read8(u8 addr) {
	u8 data;
	IIC_Start();
	IIC_Sentdate(_i2caddr);
	IIC_Sentdate(addr);

	IIC_Start();
	IIC_Sentdate(_i2caddr+1);
	data=IIC_Readdate(0);
	IIC_Stop();
	return data;	
	
}

void write8(u8 addr, u8 d) {
	IIC_Start();
	IIC_Sentdate(_i2caddr);
	IIC_Sentdate(addr);
	IIC_Sentdate(d);
	IIC_Stop();
}
