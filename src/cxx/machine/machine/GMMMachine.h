/// @file GMMMachine.h
/// @author <a href="mailto:Roy.Wallace@idiap.ch">Roy Wallace</a> 
/// @brief This class implements a multivariate diagonal Gaussian distribution.
/// @details See Section 2.3.9 of Bishop, "Pattern recognition and machine learning", 2006

#ifndef _GMMMACHINE_H
#define _GMMMACHINE_H

#include "machine/Machine.h"
#include "machine/FrameSample.h"
#include "trainer/Sampler.h"
#include "machine/GMMStats.h"
#include "machine/Gaussian.h"

namespace Torch {
namespace machine {
  
/// @brief This class implements a multivariate diagonal Gaussian distribution.
/// @details See Section 2.3.9 of Bishop, "Pattern recognition and machine learning", 2006
class GMMMachine : public Machine<FrameSample, double> {
  public:

    /// Default constructor
    GMMMachine();

    /// Constructor
    /// @param[in] n_gaussians  The number of Gaussian components
    /// @param[in] n_inputs     The feature dimensionality
    GMMMachine(int n_gaussians, int n_inputs);

    /// Copy constructor
    /// (Needed because the GMM points to its constituent Gaussian members)
    GMMMachine(const GMMMachine& other);

    /// Assigment
    GMMMachine & operator= (const GMMMachine &other);

    /// Destructor
    virtual ~GMMMachine(); 

    /// Set the feature dimensionality
    /// Overrides Machine::setNInputs
    void setNInputs(int n_inputs);

    /// Get number of inputs
    int getNInputs() const;

    /// Reset the input dimensionality, and the number of Gaussian components.
    /// Initialises the weights to uniform distribution.
    /// @param n_gaussians The number of Gaussian components
    /// @param n_inputs    The feature dimensionality
    void resize(int n_gaussians, int n_inputs);

    /// Set the weights
    void setWeights(const blitz::Array<double,1> &weights);

    /// Set the means
    void setMeans(const blitz::Array<double,2> &means);

    /// Get the means
    void getMeans(blitz::Array<double,2> &means) const;
    
    blitz::Array<double,2> getMeans() const;

    /// Set the variances
    void setVariances(const blitz::Array<double,2> &variances);

    /// Get the variances
    void getVariances(blitz::Array<double,2> &variances) const;
    
    blitz::Array<double,2> getVariances() const;

    /// Set the variance flooring thresholds in each dimension 
    /// to a proportion of the current variance, for each Gaussian
    void setVarianceThresholds(double factor);

    /// Set the variance flooring thresholds in each dimension
    /// (equal for all Gaussian components)
    void setVarianceThresholds(blitz::Array<double,1> variance_thresholds);

    /// Set the variance flooring thresholds for each Gaussian in each dimension
    void setVarianceThresholds(const blitz::Array<double,2> &variance_thresholds);

    /// Get the variance flooring thresholds for each Gaussian in each dimension
    void getVarianceThresholds(blitz::Array<double,2> &variance_thresholds) const;
    
    /// Get the variance flooring thresholds
    blitz::Array<double,2> getVarianceThresholds() const;

    /// Output the log likelihood of the sample, x, i.e. log(p(x|GMMMachine))
    /// @param[in]  x                                 The sample
    /// @param[out] log_weighted_gaussian_likelihoods For each Gaussian, i: log(weight_i*p(x|Gaussian_i))
    /// @return     The GMMMachine log likelihood, i.e. log(p(x|GMMMachine))
    double logLikelihood(const blitz::Array<double, 1> &x, blitz::Array<double,1> &log_weighted_gaussian_likelihoods) const;

    /// Output the log likelihood of the sample, x, i.e. log(p(x|GMM))
    /// @param[in]  x The sample
    double logLikelihood(const blitz::Array<double, 1> &x) const;

    /// Output the log likelihood of the sample, x 
    /// (overrides Machine::forward)
    void forward (const FrameSample& input, double& output) const;
    
    /// Accumulates the GMM statistics over a dataset.
    /// @see bool accStatistics(const blitz::Array<float,1> &x, GMMStats stats)
    void accStatistics(const Torch::trainer::Sampler<FrameSample> &sampler, GMMStats &stats) const;

    /// Accumulate the GMM statistics for this sample.
    ///
    /// @param[in]  x     The current sample
    /// @param[out] stats The accumulated statistics
    void accStatistics(const blitz::Array<double,1> &x, GMMStats &stats) const;
    
    /// Get the weights
    /// @param[out] weights The weights ("mixing coefficients") of the Gaussian components
    void getWeights(blitz::Array<double,1> &weights) const;

    ///Get the weights
    blitz::Array<double, 1> getWeights() const;

    /// Get a pointer to a particular Gaussian component
    /// @param[i] i The index of the Gaussian component
    /// @return A pointer to the i'th Gaussian component
    ///         if it exists, otherwise NULL
    Gaussian* getGaussian(int i) const;

    /// Return the number of Gaussian components
    int getNGaussians() const;

    /// Print the parameters of the GMM
    void print() const;

  protected:

    /// Copy another GMMMachine
    void copy(const GMMMachine&);
    
    /// The number of Gaussian components
    int m_n_gaussians;
    int m_n_inputs;

    /// The Gaussian components
    Gaussian *m_gaussians;

    /// The weights (also known as "mixing coefficients")
    blitz::Array<double,1> m_weights;
};

}
}

#endif