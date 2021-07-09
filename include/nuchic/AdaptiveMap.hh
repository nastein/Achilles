#ifndef ADAPTIVE_MAP_HH
#define ADAPTIVE_MAP_HH

#include <array>
#include <limits>
#include <mutex>
#include <string>
#include <vector>
#include <iosfwd>

namespace nuchic {

using Vector2D = std::vector<std::vector<double>>;
using Vector = std::vector<double>;
using lim = std::numeric_limits<double>;

class AdaptiveMap {
    public:
        AdaptiveMap() = default;
        AdaptiveMap(const size_t&);
        AdaptiveMap(const Vector2D&, const size_t& nbins_=0);
        AdaptiveMap(const AdaptiveMap&) = default;
        AdaptiveMap(AdaptiveMap&&) = default;
        AdaptiveMap &operator=(const AdaptiveMap&) = default;
        AdaptiveMap &operator=(AdaptiveMap&&) = default;
        virtual ~AdaptiveMap() = default;

        void MakeUniform(const size_t& nbins_=0);
        std::vector<double> Jacobian(const std::vector<double>&);
        void AddTrainingData(const Vector2D&, const Vector&);
        void AddTrainingData(const Vector&, const double&);
        void Adapt(const double&, const size_t& nbins_=0);
        void Map(Vector2D&, Vector2D&, Vector&);

        std::string Settings(const size_t& ngrid_=5) const;
        std::vector<std::array<double,2>> AllRegion() const;
        std::array<double,2> Region(const size_t&) const;
        size_t GetBins() const {return bins[0].size();}
        size_t GetDims() const {return grid.size();}

        std::vector<double> Random();
        std::vector<double> operator ()(const std::vector<double>&);
        void MPISync();

    private:
        void InitGrid(const Vector2D&, const bool& init=false);

        size_t nbins{}, ndims{};
        double jacobian{};
        Vector2D bins, grid, sumF, nF;
};

enum class AdaptiveMapSplit {
    half,
    third,
    quarter
};

class AdaptiveMap2 {
    public:
        AdaptiveMap2() = default;
        AdaptiveMap2(size_t dims, size_t bins) 
            : m_hist(dims * (bins+1)), m_dims(std::move(dims)), m_bins(std::move(bins)) {
                for(size_t i = 0; i < m_bins + 1; ++i) {
                    m_hist[i] = static_cast<double>(i)/static_cast<double>(bins);
                }

                for(size_t i = 1; i < m_dims; ++i) {
                    std::copy(m_hist.begin(), m_hist.begin() + static_cast<int>(bins + 1),
                              m_hist.begin() + static_cast<int>(i * (bins + 1)));
                }
            }

        // Serialization
        void Deserialize(std::istream &in);
        void Serialize(std::ostream &out) const;

        // Bin locations
        double lower_edge(size_t dim, size_t bin) const { return m_hist[dim*(m_bins+1) + bin]; }
        double upper_edge(size_t dim, size_t bin) const { return m_hist[dim*(m_bins+1) + bin + 1]; }
        double width(size_t dim, size_t bin) const { return upper_edge(dim, bin) - lower_edge(dim, bin); }

        // Map information
        std::vector<double> Edges() const { return m_hist; }
        size_t Bins() const { return m_bins; }
        size_t Dims() const { return m_dims; }

        // Generate random numbers
        double operator()(std::vector<double>&) const;

        // Update histograms
        void Adapt(const double&, const std::vector<double>&);
        void Split(AdaptiveMapSplit split = AdaptiveMapSplit::half);
            

    private:
        std::vector<double> m_hist;
        size_t m_dims{}, m_bins{};
};

}

#endif
