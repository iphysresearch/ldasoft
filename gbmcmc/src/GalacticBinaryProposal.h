//
//  GalacticBinaryProposal.h
//  
//
//  Created by Littenberg, Tyson B. (MSFC-ZP12) on 2/6/17.
//
//

#ifndef GalacticBinaryProposal_h
#define GalacticBinaryProposal_h

#ifdef __GNUC__
#define UNUSED __attribute__ ((unused))
#else
#define UNUSED
#endif

#include <stdio.h>

/*
 proposal prototype
 (func*)(struct, struct, struct, double, gsl_rng)
 */
struct Proposal
{
  double (*function)(struct Data*,struct Model*,struct Source*,struct Proposal*,double*,gsl_rng*);
  double (*density)(struct Data*, struct Model*, struct Source*,struct Proposal*,double*);
  int *trial;
  int *accept;
  char name[128];
  double norm;
  double maxp;     /* maximum p for rejection sampling */
  double weight;   /* between 0 and 1 */
  double rjweight; /* weight for RJ moves */

  int size;
  double *vector;
  double **matrix;
  double ***tensor;
};

void setup_frequency_proposal(struct Data *data);
void print_acceptance_rates(struct Proposal **proposal, int NP, int ic, FILE *fptr);

double t0_shift                 (UNUSED struct Data *data, struct Model *model, UNUSED struct Source *source, UNUSED struct Proposal *proposal, UNUSED double *params, gsl_rng *seed);
double draw_from_prior          (UNUSED struct Data *data, struct Model *model, UNUSED struct Source *source, struct Proposal *proposal, double *params, gsl_rng *seed);
double draw_from_extrinsic_prior(UNUSED struct Data *data, struct Model *model, UNUSED struct Source *source, struct Proposal *proposal, double *params, gsl_rng *seed);
double draw_from_fisher         (UNUSED struct Data *data, struct Model *model, struct Source *source, struct Proposal *proposal, double *params, gsl_rng *seed);
double draw_from_cdf            (UNUSED struct Data *data, struct Model *model, struct Source *source, struct Proposal *proposal, double *params, gsl_rng *seed);
double draw_from_cov            (UNUSED struct Data *data, struct Model *model, struct Source *source, struct Proposal *proposal, double *params, gsl_rng *seed);
double draw_from_fstatistic     (struct Data *data, UNUSED struct Model *model, UNUSED struct Source *source, struct Proposal *proposal, double *params, gsl_rng *seed);
double draw_signal_amplitude    (struct Data *data, struct Model *model, UNUSED struct Source *source, UNUSED struct Proposal *proposal, double *params, gsl_rng *seed);
double draw_from_spectrum       (struct Data *data, struct Model *model, struct Source *source, UNUSED struct Proposal *proposal, double *params, gsl_rng *seed);
double fm_shift                 (struct Data *data, struct Model *model, struct Source *source, struct Proposal *proposal, double *params, gsl_rng *seed);
double psi_phi_jump             (UNUSED struct Data *data, UNUSED struct Model *model, struct Source *source, UNUSED struct Proposal *proposal, double *params, gsl_rng *seed);
double jump_from_fstatistic     (struct Data *data, struct Model *model, struct Source *source, struct Proposal *proposal, double *params, gsl_rng *seed);
double draw_from_galaxy_prior   (struct Model *model, struct Prior *prior, double *params, gsl_rng *seed);

double draw_calibration_parameters(struct Data *data, struct Model *model, gsl_rng *seed);

//double cdf_density(struct Model *model, struct Source *source, struct Proposal *proposal);
double cdf_density(UNUSED struct Data *data, struct Model *model, struct Source * source, struct Proposal *proposal, UNUSED double *params);

//double cov_density(struct Model *model, struct Source *source, struct Proposal *proposal);
double cov_density(UNUSED struct Data *data, struct Model *model, struct Source *source, struct Proposal *proposal, double *params);


void initialize_proposal(struct Orbit *orbit, struct Data *data, struct Prior *prior, struct Chain *chain, struct Flags *flags, struct Proposal **proposal, int NMAX);

void setup_fstatistic_proposal(struct Orbit *orbit, struct Data *data, struct Flags *flags, struct Proposal *proposal);

void setup_prior_proposal(struct Flags *flags, struct Prior *prior, struct Proposal *proposal);

void setup_cdf_proposal(struct Data *data, struct Flags *flags, struct Proposal *proposal, int NMAX);

void setup_covariance_proposal(struct Data *data, struct Flags *flags, struct Proposal *proposal);

//double evaluate_fstatistic_proposal(struct Data *data, struct Proposal *proposal, double *params);
double evaluate_fstatistic_proposal(struct Data *data, UNUSED struct Model *model, UNUSED struct Source * source, struct Proposal *proposal, double *params);

double prior_density(struct Data *data, struct Model *model, UNUSED struct Source *source, struct Proposal *proposal, double *params);

//dummy function for proposal that don't have density functions defined
double symmetric_density(UNUSED struct Data *data, UNUSED struct Model *model, UNUSED struct Source *source, UNUSED struct Proposal *proposal, UNUSED double *params);

#endif /* GalacticBinaryProposal_h */