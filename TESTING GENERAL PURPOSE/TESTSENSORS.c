#pragma config(Sensor, dgtl1,  cBar,           sensorQuadEncoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int cbar = 0;
task main()
{
	while(1){

		cbar = SensorValue[cBar];
	}

}
