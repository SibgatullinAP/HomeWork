#include "filter.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void band_pass_example()
{
    CHEBandStop* filter = create_che_band_stop_filter(48, 0.5, 100, 45, 1000);
    
    for(int i = 0; i < 100; i++){
        printf("Output[%d]:%f\n", i, che_band_stop(filter, i* 100));
    }

    free_che_band_stop(filter);

}

int main() {   
    printf("========= Band pass filter example =========\n\n");
    band_pass_example();
    printf("========= Done. =========\n\n");
    return 0;
}
