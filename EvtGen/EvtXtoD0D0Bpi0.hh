#ifndef EvtXtoD0D0Bpi0_HH
#define EvtXtoD0D0Bpi0_HH

#include <string>

#include "EvtGenBase/EvtDecayAmp.hh"
#include "EvtGenBase/EvtVector4C.hh"
#include "EvtGenBase/EvtTensor4C.hh"

class EvtParticle;

class EvtXtoD0D0Bpi0 : public EvtDecayAmp
{
  public:

    virtual std::string getName()
    { return "X_D0D0BPI0"; }

    virtual EvtDecayBase* clone()
    { return new EvtXtoD0D0Bpi0; }

    virtual void init();

    // You only need to initProbMax for production MC
    // Otherwise it is determined automatically (but to limited, non-repeatable accuracy)
//    virtual void initProbMax()
//    { setProbMax(4*237.283*237.283); }  // current max based on BWamp^2 at pole (here 237.283) //

    virtual void decay( EvtParticle *X );

    double Breakup( const double& m12, const double& m1, const double& m2 );
    double Barrier( const int Spin, const double& d , const double& q_ab, const double& q_r );
    double Barrier( const int Spin, const double& d , const double& q_ab );
    double BarrierHQ( const int Spin, const double& d , const double& q_ab );
    double BarrierHQ( const int Spin, const double& d , const double& q_ab, const double& q_r );
    double Gamma( const double& GammaR, const double& mab , const double& mr, const double& p_mab, const double& p_mr, const double& BWbf, const double& J );
    EvtTensor4C P1( const EvtVector4R& p4 );
    EvtVector4C L1( const EvtVector4R& p4, const EvtVector4R& q4);
    EvtTensor4C L2( const EvtVector4R& p4, const EvtVector4R& q4);
    double calcXBasisAmp(const int eps, EvtParticle& X, EvtVector4R& p4_D0, EvtVector4R& p4_pi0, EvtVector4R& p4_antiD0);

    unsigned long int nEvt;
    unsigned int nPrintEvt = 5;
};

#endif //EvtXtoD0D0Bpi0_HH
