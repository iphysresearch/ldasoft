//
//  VerificationBinaryWrapper.h
//  ldasoft
//
//  Created by Tyson Littenberg on 8/11/21.
//

#ifndef VerificationBinaryWrapper_h
#define VerificationBinaryWrapper_h

struct VBMCMCData
{
    int mcmc_step;
    int status;
    
    int procID; //!<MPI process identifier
    int nProc;  //!<Number of processing segments
    int procID_min; //!<lowest rank MPI process for VBMCMC block
    int procID_max; //!<highest rank MPI process for VBMCMC block

    struct Flags *flags;
    struct Orbit *orbit;
    struct Chain **chain_vec;
    struct Data  **data_vec;
    struct Prior **prior_vec;
    struct Proposal ***proposal_vec;
    struct Model ***trial_vec;
    struct Model ***model_vec;
    
    double cpu_time; //!<CPU time for single update
};

void alloc_vbmcmc_data(struct VBMCMCData *vbmcmc_data, struct GBMCMCData *gbmcmc_data, int procID);

void setup_vbmcmc_data(struct VBMCMCData *vbmcmc_data, struct GBMCMCData *gbmcmc_data, struct TDI *tdi_full);

void initialize_vbmcmc_sampler(struct VBMCMCData *vbmcmc_data);

int update_vbmcmc_sampler(struct VBMCMCData *vbmcmc_data);

void select_vbmcmc_segments(struct VBMCMCData *vbmcmc_data, struct TDI *tdi);

void print_vbmcmc_state(struct VBMCMCData *vbmcmc_data, FILE *fptr, int counter);

#endif /* VerificationBinaryWrapper_h */
