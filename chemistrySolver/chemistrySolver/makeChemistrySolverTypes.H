/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2017 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#ifndef makeChemistrySolverTypes_H
#define makeChemistrySolverTypes_H

#include "chemistrySolver.H"

#include "StandardChemistryModel.H"
#include "pyJacChemistryModel.H"

#include "noChemistrySolver.H"
#include "EulerImplicit.H"
#include "ode.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeChemistrySolverType(SS, Comp, Thermo)                                 \
                                                                                  \
    typedef SS<pyJacChemistryModel<Comp, Thermo>> pyJac##SS##Comp##Thermo;            \
                                                                                  \
    defineTemplateTypeNameAndDebugWithName                                        \
    (                                                                             \
        pyJac##SS##Comp##Thermo,                                                    \
        (#SS"<" + word(pyJacChemistryModel<Comp, Thermo>::typeName_()) + "<"        \
        + word(Comp::typeName_()) + "," + Thermo::typeName() + ">>").c_str(),     \
        0                                                                         \
    );                                                                            \
                                                                                  \
    BasicChemistryModel<Comp>::                                                   \
        add##thermo##ConstructorToTable<pyJac##SS##Comp##Thermo>                    \
        add##pyJac##SS##Comp##Thermo##thermo##ConstructorTo##BasicChemistryModel    \
##Comp##Table_;                                                                   \

#define makeChemistrySolverTypes(Comp, Thermo)                                 \
                                                                               \
    makeChemistrySolverType                                                    \
    (                                                                          \
        noChemistrySolver,                                                     \
        Comp,                                                                  \
        Thermo                                                                 \
    );                                                                         \
                                                                               \
    makeChemistrySolverType                                                    \
    (                                                                          \
        EulerImplicit,                                                         \
        Comp,                                                                  \
        Thermo                                                                 \
    );                                                                         \
                                                                               \
    makeChemistrySolverType                                                    \
    (                                                                          \
        ode,                                                                   \
        Comp,                                                                  \
        Thermo                                                                 \
    );                                                                         \


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
