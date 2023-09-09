// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "mypcm.h"
#include "math.h"


// function prototypes
void run(asignal * inputsignal);


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
    int no_of_samples = floor((duration / interval)) + 1;
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


