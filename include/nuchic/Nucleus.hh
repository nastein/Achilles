#ifndef NUCLEUS_HH
#define NUCLEUS_HH

#include <functional>
#include <iosfwd>
#include <map>
#include <memory>
#include <vector>

#include "nuchic/Random.hh"

class Particle;
class ThreeVector;

using Particles = std::vector<Particle>;

/// The Nucleus class implements the physics needed to describe an arbitrary nucleus. It provides
/// the ability to generate configurations of nucleons for the cascade, as well as perform checks
/// on if nucleons are captured in the potential or escape.
class Nucleus {
    public:
        /// @name Constructors and Destructors
        /// @{

        /// Create a nucleus
        ///@param Z: The number of protons
        ///@param A: The number of nucleons
        ///@param binding: The binding energy of the nucleus
        ///@param fermiMomentum: The Fermi Momentum of the nucleus
        ///@param density: A function that generates nucleon configurations according 
        ///                to the density profile
        Nucleus(const int&, const int&, const double&, const double&,
                const std::function<Particles()>&);

        /// Default destructor
        ~Nucleus() {};
        ///@}

        /// @name Setters
        /// @{
        /// These functions provide access to setting the parameters of the Nucleus object

        /// Set the nucleons, protons, and neutrons of the nucleus
        ///@param nucleons: The nucleons to be used for the nucleus
        void SetNucleons(Particles& _nucleons) noexcept;

        /// Set the binding energy of the nucleus in MeV
        ///@param energy: The binding energy to be set in MeV
        void SetBindingEnergy(const double& energy) noexcept {binding = energy;}

        /// Set the Fermi Momentum of the nucleus in MeV
        ///@param mom: The Fermi Momentum to be set in MeV
        void SetFermiMomentum(const double& mom) noexcept {fermiMomentum = mom;}

        /// Set the potential energy of the nucleus. This value defaults to:
        /// @f[
        ///     \sqrt{m_{N}^2+k_{f}^2} - m_{N} + 8 \text{MeV}.
        /// @f]
        ///@param energy: The potential energy to be set in MeV
        void SetPotential(const double& energy) noexcept {potential = energy;}

        /// Set the density function to use for configuration generation
        ///@param density: The function to be use for generating nucleons
        void SetDensity(const std::function<Particles()>& _density) noexcept {density = _density;}
        ///@}

        /// @name Getters
        /// @{
        /// These functions provide get specific features from the Nucleus object

        /// Return a vector of the current nucleons
        ///@return Particles: The current nucleons generated for the nucleus
        Particles Nucleons() const noexcept {return nucleons;}

        /// Return a vector of the current protons
        ///@return Particles: The current protons generated for the nucleus
        Particles Protons() const noexcept {return protons;}

        /// Return a vector of the current neutrons
        ///@return Particles: The current neutrons generated for the nucleus
        Particles Neutrons() const noexcept {return neutrons;}

        /// Return the number of nucleons in the nucleus
        ///@return int: The number of nucleons in the nucleus
        const int NNucleons() const noexcept {return nucleons.size();}

        /// Return the number of protons in the nucleus
        ///@return int: The number of protons in the nucleus
        const int NProtons() const noexcept {return protons.size();}

        /// Return the number of neutrons in the nucleus
        ///@return int: The number of neutrons in the nucleus
        const int NNeutrons() const noexcept {return neutrons.size();}

        /// Return the current binding energy of the nucleus
        ///@return double: The binding energy in MeV
        const double& BindingEnergy() const noexcept {return binding;}

        /// Return the current Fermi Momentum of the nucleus
        ///@return double: The Fermi Momentum in MeV
        const double& FermiMomentum() const noexcept {return fermiMomentum;}

        /// Return the current potential energy of the nucleus
        ///@return double: The potential energy in MeV
        const double& PotentialEnergy() const noexcept {return potential;}

        /// Return the radius cutoff of the nucleus used for the cascade
        ///@return double: The radius in femtometers
        const double& Radius() const noexcept {return radius;}
        ///@}

        /// @name Functions
        /// @{

        /// Determine if a particle escapes from the nucleus or is recaptured
        ///@param particle: The particle that is attempting to escape
        ///@return bool: True if the particle escapes, False if recaptured
        bool Escape(Particle&) noexcept;

        /// Generate a configuration of the nucleus based on the density function
        ///@return Particles: A list of nucleons that represent a random configuration
        Particles GenerateConfig();

        /// Generate a random momentum for a nucleon in the nucleus
        ///@return std::array<double, 3>: Random momentum generated using the Fermi momentum
        const std::array<double, 3> GenerateMomentum() noexcept;

        /// Return a string representation of the nucleus
        ///@return std::string: a string representation of the nucleus
        const std::string ToString() const noexcept;
        /// @}

        // Nucleus maker
        /// Generate a nucleus based on an input string, a binding energy, a Fermi Momentum,
        /// and a density function. The format of the string has to be of the form, AX, where
        /// A represents the number of nucleons, and X represents the chemical symbol for the 
        /// element. Currently, the following elements are available in the code:
        ///
        /// @rst
        /// 
        /// +-----+-----+
        /// |  Z  |  X  |
        /// +=====+=====+
        /// |  1  |  H  |
        /// +-----+-----+
        /// |  2  | He  |
        /// +-----+-----+
        /// |  3  | Li  |
        /// +-----+-----+
        /// |  6  |  C  |
        /// +-----+-----+
        /// |  8  |  O  |
        /// +-----+-----+
        /// | 13  | Al  |
        /// +-----+-----+
        /// | 18  | Ar  |
        /// +-----+-----+
        /// | 20  | Ca  |
        /// +-----+-----+
        /// | 26  | Fe  |
        /// +-----+-----+
        ///
        /// @endrst
        ///@param name: Nucleus in format discussed above
        ///@param binding: The binding energy of the nucleus
        ///@param fermiMomentum: The Fermi Momentum of the nucleus
        ///@param density: The density function to use to generate configurations with
        static Nucleus MakeNucleus(const std::string&, const double&,
                                   const double&, const std::function<Particles()>&);

        /// @name Stream Operators
        /// @{
        /// These functions are currently **not implemented** for this class

        friend std::ostream& operator<<(std::ostream&, const Nucleus&);
        friend std::istream& operator>>(std::istream&, Nucleus&);
        /// @}

    private:
        Particles nucleons, protons, neutrons;
        double binding, fermiMomentum, radius, potential;
        std::function<Particles()> density;

        static const std::map<int, std::string> ZToName;
        static int NameToZ(const std::string&);

        randutils::mt19937_rng rng;
};



#endif // end of include guard: NUCLEUS_HH
