#pragma once

class fft0 {
	public:
		
	fft0();
	~fft0();
	
	/* Calculate the power spectrum */
	void powerSpectrum0(int start, int half, float *data, int windowSize,float *magnitude,float *phase, float *power, float *avg_power);
	/* ... the inverse */
	void inversePowerSpectrum0(int start, int half, int windowSize, float *finalOut,float *magnitude,float *phase);
	

};
