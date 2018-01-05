//
// Created by pwu on 12/19/17.
//

#ifndef TICK_SIMULATION_SRC_HAWKES_CUSTOM_H_
#define  TICK_SIMULATION_SRC_HAWKES_CUSTOM_H_

#include "hawkes.h"

class Hawkes_custom : public Hawkes {
public:
    //! Peng Wu, An array, indicaitng the global status after the i_th event
    VArrayULong global_n;

    //! @brief the max value of n kept for all f_i(n)
    ulong MaxN_of_f;
    SArrayDoublePtrList1D f_i;
    //! array for accelerating the calculation
    ArrayDouble f_i_Max;

    ulong last_global_n;
//    using Hawkes::get_baseline_bound;
//    using Hawkes::baselines;
//    using Hawkes::kernels;

public :
    Hawkes_custom(unsigned int n_nodes, int seed, ulong _MaxN_of_f, const SArrayDoublePtrList1D &_f_i);

    // This forbids the unwanted copy of an Hawkes process
    Hawkes_custom(Hawkes_custom &hawkes_custom) = delete;

    /**
     * @brief Updates the current time so that it goes forward of delay seconds
     * The intensities must be updated and track recorded if needed
     * Returns false if negative intensities were encountered
     * \param delay : Time to update
     * \param intensity : The intensity vector to update
     * \param total_intensity_bound : If not NULL then used to set a bound of
     * total future intensity
     */
    bool update_time_shift_(double delay,
                            ArrayDouble &intensity,
                            double *total_intensity_bound);

    void update_jump(int index);

    VArrayULongPtr get_global_n() {
        VArrayULongPtr shared_process = VArrayULong::new_ptr(global_n);
        return shared_process;
    }

};

#endif // TICK_SIMULATION_SRC_HAWKES_CUSTOM_H_