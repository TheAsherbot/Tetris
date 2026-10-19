struct Peice
{
    enum PeiceType : int
    {
        L,
        J,
        I,
        O,
        T,
        Z,
        S
    };
	PeiceType type;
	bool pattern[16]; // 4x4
};

namespace Peices
{
    const Peice LPeiceData = 
    { 
        Peice::L, 
        {
            true,   false,  false,  false,
            true,   false,  false,  false,
            true,   true,   false,  false,
            false,  false,  false,  false
        } 
    };

    const Peice JPeiceData = 
    { 
        Peice::J, 
        {
            false,  true,   false,  false,
            false,  true,   false,  false,
            true,   true,   false,  false,
            false,  false,  false,  false
        } 
    };

    const Peice IPeiceData = 
    { 
        Peice::I, 
        {
            false,  false,  true,   false,
            false,  false,  true,   false,
            false,  false,  true,   false,
            false,  false,  true,   false
        } 
    };

    const Peice OPeiceData = 
    { 
        Peice::O, 
        {
            false,  false,  false,  false,
            false,  true,   true,   false,
            false,  true,   true,   false,
            false,  false,  false,  false
        } 
    };

    const Peice TPeiceData = 
    { 
        Peice::T, 
        {
            false,  true,   false,  false,
            true,   true,   true,   false,
            false,  false,  false,  false,
            false,  false,  false,  false
        } 
    };

    const Peice ZPeiceData = 
    { 
        Peice::Z, 
        {
            true,   true,   false,  false,
            false,  true,   true,   false,
            false,  false,   false,  false,
            false,  false,  false,  false
        } 
    };

    const Peice SPeiceData =
    { 
        Peice::S, 
        {
            false,  true,   true,   false,
            true,   true,   false,  false,
            false,  false,  false,  false,
            false,  false,  false,  false
        } 
    };

    Peice GetRandomPeice();
	Peice RotateClockwise(const Peice& peice);
    Peice RotateCounterClockwise(const Peice& peice);
    short LowestPointFromTop(const Peice& peice);
}