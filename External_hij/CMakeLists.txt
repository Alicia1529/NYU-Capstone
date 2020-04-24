cmake_minimum_required(VERSION 3.12)
project(source_V3_0_0)

set(CMAKE_CXX_STANDARD 14)

include_directories(source_MATH1)

add_executable(source_V3_0_0
        source_MATH1/AssociatedLegendreFunction.cpp
        source_MATH1/AssociatedLegendreFunction.h
        source_MATH1/BesselSpherical.cpp
        source_MATH1/BesselSpherical.h
        source_MATH1/Liste.cpp
        source_MATH1/Liste.h
        source_MATH1/Math1.cpp
        source_MATH1/Math1.h
        source_MATH1/Matrice.cpp
        source_MATH1/Matrice.h
        source_MATH1/ScalarTranslationalMatrix.cpp
        source_MATH1/ScalarTranslationalMatrix.h
        source_MATH1/Tableau.h
        source_MATH1/TableauX.cpp
        source_MATH1/TableauX.h
        source_MATH1/VectorialTranslationalMatrix.cpp
        source_MATH1/VectorialTranslationalMatrix.h
        main.cpp)
