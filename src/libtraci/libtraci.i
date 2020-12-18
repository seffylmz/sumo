%module libtraci
#define LIBTRACI 1
%{
#define LIBTRACI 1
%}

%include "../libsumo/libsumo_typemap.i"

// Add necessary symbols to generated header
%{
#include <libsumo/Edge.h>
#include <libsumo/InductionLoop.h>
#include <libsumo/Junction.h>
#include <libsumo/LaneArea.h>
#include <libsumo/Lane.h>
#include <libsumo/MultiEntryExit.h>
#include <libsumo/POI.h>
#include <libsumo/Polygon.h>
#include <libsumo/Route.h>
#include <libsumo/Simulation.h>
#include <libsumo/TrafficLight.h>
#include <libsumo/VehicleType.h>
#include <libsumo/Vehicle.h>
#include <libsumo/Person.h>
#include <libsumo/Calibrator.h>
#include <libsumo/BusStop.h>
#include <libsumo/ParkingArea.h>
#include <libsumo/ChargingStation.h>
#include <libsumo/OverheadWire.h>
#include <libsumo/Rerouter.h>
#include <libsumo/MeanData.h>
#include <libsumo/VariableSpeedSign.h>
#include <libsumo/RouteProbe.h>
%}

// Process symbols in header
%include "../libsumo/TraCIDefs.h"
%template(TraCILogicVector) std::vector<libsumo::TraCILogic>;
%template(TraCIStageVector) std::vector<libsumo::TraCIStage>;
%template(TraCINextStopDataVector2) std::vector<libsumo::TraCINextStopData>;
%template(TraCIReservationVector) std::vector<libsumo::TraCIReservation>;
%include "../libsumo/Edge.h"
%include "../libsumo/InductionLoop.h"
%include "../libsumo/Junction.h"
%include "../libsumo/LaneArea.h"
%include "../libsumo/Lane.h"
%include "../libsumo/MultiEntryExit.h"
%include "../libsumo/POI.h"
%include "../libsumo/Polygon.h"
%include "../libsumo/Route.h"
%include "../libsumo/Simulation.h"
%include "../libsumo/TraCIConstants.h"
%include "../libsumo/TrafficLight.h"
%include "../libsumo/VehicleType.h"
%include "../libsumo/Vehicle.h"
%include "../libsumo/Person.h"
%include "../libsumo/Calibrator.h"
%include "../libsumo/BusStop.h"
%include "../libsumo/ParkingArea.h"
%include "../libsumo/ChargingStation.h"
%include "../libsumo/OverheadWire.h"
%include "../libsumo/Rerouter.h"
%include "../libsumo/MeanData.h"
%include "../libsumo/VariableSpeedSign.h"
%include "../libsumo/RouteProbe.h"
