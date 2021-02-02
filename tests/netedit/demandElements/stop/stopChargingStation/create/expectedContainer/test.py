#!/usr/bin/env python
# Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
# Copyright (C) 2009-2021 German Aerospace Center (DLR) and others.
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# https://www.eclipse.org/legal/epl-2.0/
# This Source Code may also be made available under the following Secondary
# Licenses when the conditions for such availability set forth in the Eclipse
# Public License 2.0 are satisfied: GNU General Public License, version 2
# or later which is available at
# https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later

# @file    test.py
# @author  Pablo Alvarez Lopez
# @date    2019-07-16

# import common functions for netedit tests
import os
import sys

testRoot = os.path.join(os.environ.get('SUMO_HOME', '.'), 'tests')
neteditTestRoot = os.path.join(
    os.environ.get('TEXTTEST_HOME', testRoot), 'netedit')
sys.path.append(neteditTestRoot)
import neteditTestFunctions as netedit  # noqa

# Open netedit
neteditProcess, referencePosition = netedit.setupAndStart(neteditTestRoot, ['--gui-testing-debug-gl'])

# go to demand mode
netedit.supermodeDemand()

# force save additionals
netedit.forceSaveAdditionals()

# go to stop mode
netedit.stopMode()

# change stop type with a valid value
netedit.changeStopType("stopChargingStation")

# change triggered
netedit.changeDefaultBoolValue(10)

# set invalid value
netedit.changeDefaultValue(11, ";;;;;;;;;;")

# try to create stop
netedit.leftClick(referencePosition, 290, 215)

# set invalid value
netedit.changeDefaultValue(11, "")

# try to create stop
netedit.leftClick(referencePosition, 290, 215)

# set valid value
netedit.changeDefaultValue(11, "ID1")

# create stop
netedit.leftClick(referencePosition, 290, 215)

# set valid value
netedit.changeDefaultValue(11, "ID1 ID2 ID3")

# create stop
netedit.leftClick(referencePosition, 290, 215)

# Check undo redo
netedit.undo(referencePosition, 6)
netedit.redo(referencePosition, 6)

# save additionals
netedit.saveAdditionals(referencePosition)

# save routes
netedit.saveRoutes(referencePosition)

# save network
netedit.saveNetwork(referencePosition)

# quit netedit
netedit.quit(neteditProcess)
