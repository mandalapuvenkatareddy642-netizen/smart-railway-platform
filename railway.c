#include "railway.h"

// Train details stored in the main database.
TrainInfo_t TrainDB[TOTAL_TRAINS] =
{
    {12627, 0, "Karnataka Express", "New Delhi", 6, 30, 6, 35, 6, 30, 6, 35, 1, 0},

    {12028, 1, "Shatabdi Express", "Chennai", 7, 15, 7, 20, 7, 15, 7, 20, 2, 0},

    // This train is configured with a delay.
    {12785, 1, "Kacheguda Express", "Hyderabad", 8, 00, 8, 05, 8, 20, 8, 25, 3, 20}
};
