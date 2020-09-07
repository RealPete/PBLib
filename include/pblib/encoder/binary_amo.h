#ifndef BINARY_AMO_H
#define BINARY_AMO_H
#include <vector>
#include <sstream>

#include <pblib/SimplePBConstraint.h>
#include <pblib/IncSimplePBConstraint.h>
#include <pblib/PBConfig.h>
#include <pblib/clausedatabase.h>
#include <pblib/auxvarmanager.h>
#include <pblib/weightedlit.h>

#include <pblib/encoder/Encoder.h>

// Frisch, A. M. and Peugniez, T. J. (2001) Solving non-Boolean satisfiability problems with stochastic local search, in Proc. of the Seventeenth Int. Joint Conf. on Artificial Intelligence, Seattle, Washington, pp. 282-288. 
// enhanced binary encoding 
class Binary_AMO_Encoder : public Encoder
{
private:
    std::vector<Lit> _literals;
    std::vector<Lit> bits;
    int nBits;
    int two_pow_nbits;
    int k;

    void encode_intern( std::vector<Lit>& literals, ClauseDatabase & formula, AuxVarManager & auxvars);    
public:
    void encode(const SimplePBConstraint& pbconstraint, ClauseDatabase & formula, AuxVarManager & auxvars);
    int64_t encodingValue(const SimplePBConstraint& pbconstraint);

    Binary_AMO_Encoder(PBConfig & config);
    virtual ~Binary_AMO_Encoder();
};

#endif // BINARY_AMO_H
