#ifndef slic3r_Schematic_hpp_
#define slic3r_Schematic_hpp_

#include "libslic3r.h"
#include "ElectronicPart.hpp"
#include "ElectronicNet.hpp"
#include "RubberBand.hpp"
#include "NetPoint.hpp"
#include "Point.hpp"
#include "Polyline.hpp"
#include "../pugixml/pugixml.hpp"
#include <vector>
#include <list>


namespace Slic3r {

class Schematic
{
    public:
    Schematic(const Point objectCenter);
    ~Schematic();
	void setFilename(std::string filename);
	std::string getFilename() const {return this->filename;};
    void addElectronicPart(ElectronicPart* part);
    ElectronicPart* addElectronicPart(std::string name, std::string library, std::string deviceset, std::string device, std::string package);
    ElectronicPart* getElectronicPart(unsigned int partID);
    ElectronicPart* getElectronicPart(std::string partName);
    void addElectronicNet(ElectronicNet* net);
    ElectronicParts* getPartlist();
    RubberBandPtrs* getRubberBands();
    NetPointPtrs* getNetPoints();
    const NetPoint* findNearestSplittingPoint(const RubberBand* rubberband, const Pointf3& p) const;
    void splitWire(const RubberBand* rubberband, const Pointf3& p);
    bool removeWire(const unsigned int rubberBandID);
    bool removeNetPoint(const NetPoint* netPoint);

    void updatePartNetPoints();
    void updatePartNetPoints(ElectronicPart* part);

    Polylines getChannels(const double z_bottom, const double z_top, coord_t extrusion_overlap, coord_t layer_overlap);

    bool write3deFile(std::string filename, std::string filebase);
    bool load3deFile(std::string filename);


	private:
    bool _checkRubberBandVisibility(const RubberBand* rb, const double z);

    ElectronicNets netlist;
    ElectronicParts partlist;
    std::string filename;
    const Point objectCenter;
    RubberBandPtrs rubberBands;
    NetPointPtrs netPoints;

};

}

#endif
