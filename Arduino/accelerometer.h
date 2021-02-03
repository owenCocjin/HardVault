//Author:  Owen Cocjin
//Version: 1.0
//Date:    02/02/2021
//Description:  Handles MPU stuff
//Notes:
long gRawX, gRawY, gRawZ;
long aRawX, aRawY, aRawZ;

void setupMPU(){
	//Wakeup MPU, which boots asleep by default
	Wire.beginTransmission(0x68);
	Wire.write(0x6b);  //Power Management  register
	Wire.write(0x00);  //Mostly wanna set sleep to 0 (wake up!)
	Wire.endTransmission();
	//Reset config Gyro
	Wire.beginTransmission(0x68);
	Wire.write(0x1b);
	Wire.write(0x00);
	Wire.endTransmission();
	//Reset config Accel
	Wire.beginTransmission(0x68);
	Wire.write(0x1c);
	Wire.write(0x00);
	Wire.endTransmission();
}//setupMPU

void getAccel(){
	//Get accelerometer data
	Wire.beginTransmission(0x68);
	Wire.write(0x3b);  //Start of accel data -> 0x40
	Wire.endTransmission();
	Wire.requestFrom(0x68, 6);  //Request 6 bytes, starting from 0x3b to 0x40
	//Read bytes into accel
	while(Wire.available()>0){
		//Read bytes into accel
		aRawX=Wire.read()<<8|Wire.read();
		aRawY=Wire.read()<<8|Wire.read();
		aRawZ=Wire.read()<<8|Wire.read();
	}//while()
}//getAccel()

void getGyro(){
	//Get gryoscope data
	Wire.beginTransmission(0x68);
	Wire.write(0x43);
	Wire.requestFrom(0x68, 6);
	while(Wire.available()>0){
		gRawX=Wire.read()<<8|Wire.read();
		gRawY=Wire.read()<<8|Wire.read();
		gRawZ=Wire.read()<<8|Wire.read();
	}//while()
}//getGyro
