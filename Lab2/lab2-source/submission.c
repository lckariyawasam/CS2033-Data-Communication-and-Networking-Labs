#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mypcm.h"

// function prototypes
void run(asignal * inputsignal);
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

	// // Get the number of samples required
	// no_of_samples = floor((signal.duration / interval)) + 1;

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


//-------------------------------------------------------------

int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here

    free(inputsignal);
	return 0;
}

void run(asignal * inputsignal) 
{
	//todo
	// Declare variables to store in the inputs
    int A;
    int omega;
    int sigma;
    int duration;
    int interval;
    int encoderbits;

    // Get user input
    scanf("%d %d %d %d %d %d", &A, &omega, &sigma, &duration, &interval, &encoderbits);
	
    // Assign the properties of the signal
    inputsignal->A = A;
    inputsignal->omega = omega;
    inputsignal->sigma = sigma;
    inputsignal->duration = duration;

    // Compute number of samples and quantization levels
    no_of_samples = floor((duration / interval)) + 1;
    int levels = pow(2, encoderbits);

    // Allocate memory for samples, pcmpulses and digital signal
    float* samples = (float *) malloc(sizeof(float) * no_of_samples);
    int* pcmpulses = (int *) malloc(sizeof(int) * no_of_samples);
    int* dsignal = (int *) malloc(sizeof(int) * no_of_samples);

    // Sample the signal at intervals
    sampler(samples, interval, *inputsignal);

    // Quantize the sampled inputs into levels
    quantizer(samples, pcmpulses, levels, inputsignal->A);

    // Encode the quantization levels into binary
    encoder(pcmpulses, dsignal, 10);
    
    // Print each of the encodedbits into stdout
    for (int i = 0; i < no_of_samples; i++) {
        printf("%0*d", encoderbits, dsignal[i]);
    }
    printf("\n");

    // Free the memory allocated for arrays
    free(dsignal);
    free(pcmpulses);
    free(samples);
}
