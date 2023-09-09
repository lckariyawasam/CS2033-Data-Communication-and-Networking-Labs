// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here
#include <math.h> 
// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:
int decimal_to_binary(int dec);

int no_of_samples;

// implementation
float analog_signal_generator(asignal signal, int t)
{
	//TODO
	// printf("%f \n",signal.A * sin((signal.omega * t) + signal.sigma));
	return signal.A * sin((signal.omega * t) + signal.sigma);

}
void sampler(float *samples, int interval, asignal signal)
{
	//TODO

	// Get the number of samples required
	no_of_samples = floor((signal.duration / interval)) + 1;

	// Store the sampled value at each of the sample points
	for (int i = 0; i < no_of_samples; i++) {
		samples[i] = analog_signal_generator(signal, i*interval);
	}
}
void quantizer(float *samples, int *pcmpulses, int levels, float A)
{
	//TODO
	for (int i = 0; i < no_of_samples; i++) {
		pcmpulses[i] = floor(((samples[i] + A) / (2 * A)) * levels);
		// printf("%d \n", pcmpulses[i]);
	}

}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	//TODO

	for (int i = 0; i < no_of_samples; i++) {
		dsignal[i] = decimal_to_binary(pcmpulses[i]);
	}
}

int decimal_to_binary(int dec) {
	//Convert decimal to binary

	int bin = 0;
	int rem, i = 1;

	while (dec != 0) {
		rem = dec % 2;
		dec /= 2;
		bin += rem * i;
		i *= 10;
	}

	return bin;
}