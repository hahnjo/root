# Copyright (C) 1995-2019, Rene Brun and Fons Rademakers.
# All rights reserved.
#
# For the licensing terms see $ROOTSYS/LICENSE.
# For the list of contributors see $ROOTSYS/README/CREDITS.

project(mathcore-tests)

set(Libraries Core RIO Net Hist Graf Graf3d Gpad Tree Minuit2
              Rint Postscript Matrix Physics MathCore Thread)

set(TestSource
    testMathRandom.cxx
    testTMath.cxx
    testBinarySearch.cxx
    testSortOrder.cxx
    stressGoFTest.cxx
    stressTMath.cxx
    stressTF1.cxx
    testIntegration.cxx
    testSampleQuantiles.cxx
    kDTreeTest.cxx
    testkdTreeBinning.cxx
    newKDTreeTest.cxx
    binarySearchTime.cxx
    stdsort.cxx
    testSpecFuncErf.cxx
    testSpecFuncGamma.cxx
    testSpecFuncBeta.cxx
    testSpecFuncBetaI.cxx
    testSpecFuncSiCi.cxx
    testIntegrationMultiDim.cxx
    testAnalyticalIntegrals.cxx
    testTStatistic.cxx
    fit/SparseDataComparer.cxx
    fit/SparseFit3.cxx
    fit/SparseFit4.cxx
    fit/testBinnedFitExecPolicy.cxx
    fit/testFit.cxx
    fit/testGraphFit.cxx
    fit/testLogLExecPolicy.cxx
    fit/testMinim.cxx)

if(mathmore)
  list(APPEND Libraries MathMore)
endif()

if(r)
 add_definitions(-DROOT_HAS_R)
 list(APPEND Libraries RInterface)
endif()

#---Build and add all the defined test in the list---------------
foreach(file ${TestSource})
  get_filename_component(testname ${file} NAME_WE)
  ROOT_EXECUTABLE(${testname} ${file} LIBRARIES ${Libraries})
  ROOT_ADD_TEST(mathcore-${testname} COMMAND ${testname} LABELS ${${testname}_LABELS})
endforeach()

ROOT_STANDARD_LIBRARY_PACKAGE(TrackMathCoreUnitDict
                              NO_INSTALL_HEADERS
                              NO_SOURCES
                              HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/stress/TrackMathCore.h
                              LINKDEF stress/TrackMathCoreLinkDef.h
                              DEPENDENCIES Core MathCore RIO GenVector Smatrix)

if(MSVC AND NOT CMAKE_GENERATOR MATCHES Ninja)
  add_custom_command(TARGET TrackMathCoreUnitDict POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/libTrackMathCoreUnitDict.dll
                                     ${CMAKE_CURRENT_BINARY_DIR}/libTrackMathCoreUnitDict.dll)
endif()

ROOT_ADD_GTEST(stressMathCoreUnit stress/testSMatrix.cxx stress/testGenVector.cxx
        stress/testStat.cxx stress/testSVector.cxx stress/testVector.cxx stress/testVector34.cxx
        stress/TestHelper.cxx
        LIBRARIES Core MathCore Hist RIO Tree GenVector)

ROOT_ADD_GTEST(GradientUnit testGradient.cxx LIBRARIES Core MathCore Hist )

ROOT_ADD_GTEST(GradientFittingUnit testGradientFitting.cxx LIBRARIES Core MathCore Hist)

ROOT_ADD_GTEST(MulmodUnitOpt mulmod_opt.cxx)
ROOT_ADD_GTEST(MulmodUnitNoInt128 mulmod_noint128.cxx)
ROOT_ADD_GTEST(RanluxLCGUnit ranlux_lcg.cxx)

ROOT_ADD_GTEST(RanluxppEngineTests RanluxppEngine.cxx
        LIBRARIES Core MathCore)

if(veccore AND vc)
  ROOT_ADD_GTEST(VectorizedTMathUnit testVectorizedTMath.cxx
        LIBRARIES Core MathCore)
endif()

ROOT_ADD_GTEST(testRootFinder testRootFinder.cxx  LIBRARIES ${Libraries})

ROOT_ADD_GTEST(testKahan testKahan.cxx LIBRARIES Core MathCore)
ROOT_ADD_GTEST(testDelaunay2D testDelaunay2D.cxx LIBRARIES Core MathCore)

if(clad)
  ROOT_ADD_GTEST(CladDerivatorTests CladDerivatorTests.cxx LIBRARIES Core MathCore)
endif()
