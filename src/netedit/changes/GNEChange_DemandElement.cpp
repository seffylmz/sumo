/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2019 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    GNEChange_DemandElement.cpp
/// @author  Pablo Alvarez Lopez
/// @date    Jan 2019
///
// A network change in which a busStop is created or deleted
/****************************************************************************/

// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <netedit/GNENet.h>
#include <netedit/elements/network/GNEEdge.h>
#include <netedit/elements/demand/GNEDemandElement.h>
#include <netedit/frames/demand/GNEVehicleTypeFrame.h>
#include <netedit/GNEViewParent.h>
#include <netedit/GNEViewNet.h>

#include "GNEChange_DemandElement.h"

// ===========================================================================
// FOX-declarations
// ===========================================================================
FXIMPLEMENT_ABSTRACT(GNEChange_DemandElement, GNEChange, nullptr, 0)

// ===========================================================================
// member method definitions
// ===========================================================================

GNEChange_DemandElement::GNEChange_DemandElement(GNEDemandElement* demandElement, bool forward) :
    GNEChange(demandElement->getViewNet()->getNet(), demandElement, demandElement, forward),
    myDemandElement(demandElement),
    myEdgePath(demandElement->getPathEdges()) {
    myDemandElement->incRef("GNEChange_DemandElement");
}


GNEChange_DemandElement::~GNEChange_DemandElement() {
    assert(myDemandElement);
    myDemandElement->decRef("GNEChange_DemandElement");
    if (myDemandElement->unreferenced()) {
        // show extra information for tests
        WRITE_DEBUG("Deleting unreferenced " + myDemandElement->getTagStr() + " '" + myDemandElement->getID() + "'");
        // make sure that element isn't in net before removing
        if (myNet->demandElementExist(myDemandElement)) {
            // remove demand element of network
            myNet->deleteDemandElement(myDemandElement, false);
            // remove element from path
            for (const auto& i : myEdgePath) {
                i->removePathElement(myDemandElement);
            }
            // remove demand element from parents and children
            removeDemandElement(myDemandElement);
        }
        delete myDemandElement;
    }
}


void
GNEChange_DemandElement::undo() {
    if (myForward) {
        // show extra information for tests
        WRITE_DEBUG("Removing " + myDemandElement->getTagStr() + " '" + myDemandElement->getID() + "' in GNEChange_DemandElement");
        // delete demand element from net
        myNet->deleteDemandElement(myDemandElement, false);
        // remove element from path
        for (const auto& i : myEdgePath) {
            i->removePathElement(myDemandElement);
        }
        // remove demand element from parents and children
        removeDemandElement(myDemandElement);
    } else {
        // show extra information for tests
        WRITE_DEBUG("Adding " + myDemandElement->getTagStr() + " '" + myDemandElement->getID() + "' in GNEChange_DemandElement");
        // insert demand element into net
        myNet->insertDemandElement(myDemandElement);
        // add demand element in parents and children
        addDemandElement(myDemandElement);
    }
    // update vehicle type selector if demand element is a VType and vehicle type Frame is shown
    if ((myDemandElement->getTagProperty().getTag() == SUMO_TAG_VTYPE) && myNet->getViewNet()->getViewParent()->getVehicleTypeFrame()->shown()) {
        myNet->getViewNet()->getViewParent()->getVehicleTypeFrame()->getVehicleTypeSelector()->refreshVehicleTypeSelector();
    }
    // update stack labels
    if (myParentEdges.size() > 0) {
        myParentEdges.front()->updateVehicleStackLabels();
    }
    // Requiere always save elements
    myNet->requireSaveDemandElements(true);
}


void
GNEChange_DemandElement::redo() {
    if (myForward) {
        // show extra information for tests
        WRITE_DEBUG("Adding " + myDemandElement->getTagStr() + " '" + myDemandElement->getID() + "' in GNEChange_DemandElement");
        // insert demand element into net
        myNet->insertDemandElement(myDemandElement);
        // add demand element in parents and children
        addDemandElement(myDemandElement);
    } else {
        // show extra information for tests
        WRITE_DEBUG("Removing " + myDemandElement->getTagStr() + " '" + myDemandElement->getID() + "' in GNEChange_DemandElement");
        // delete demand element from net
        myNet->deleteDemandElement(myDemandElement, false);
        // remove element from path
        for (const auto& i : myEdgePath) {
            i->removePathElement(myDemandElement);
        }
        // remove demand element from parents and children
        removeDemandElement(myDemandElement);
    }
    // update vehicle type selector if demand element is a VType and vehicle type Frame is shown
    if ((myDemandElement->getTagProperty().getTag() == SUMO_TAG_VTYPE) && myNet->getViewNet()->getViewParent()->getVehicleTypeFrame()->shown()) {
        myNet->getViewNet()->getViewParent()->getVehicleTypeFrame()->getVehicleTypeSelector()->refreshVehicleTypeSelector();
    }
    // update stack labels
    if (myParentEdges.size() > 0) {
        myParentEdges.front()->updateVehicleStackLabels();
    }
    // Requiere always save elements
    myNet->requireSaveDemandElements(true);
}


FXString
GNEChange_DemandElement::undoName() const {
    if (myForward) {
        return ("Undo create " + myDemandElement->getTagStr()).c_str();
    } else {
        return ("Undo delete " + myDemandElement->getTagStr()).c_str();
    }
}


FXString
GNEChange_DemandElement::redoName() const {
    if (myForward) {
        return ("Redo create " + myDemandElement->getTagStr()).c_str();
    } else {
        return ("Redo delete " + myDemandElement->getTagStr()).c_str();
    }
}
