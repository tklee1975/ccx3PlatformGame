//
//  TDDDefine.h
//  TDDLib
//
//  Created by Ken Lee on 13/12/13.
//
//

#ifdef ENABLE_TDD
#ifndef TDDLib_TDDDefine_h
#define TDDLib_TDDDefine_h

#include "TDDTypes.h"
#include "TDDTest.h"		// contain the data structure
#include "ExampleTest.h"

// Add the Header here!
#include "SampleTest.h"

// MACRO
#define ADD_CASE(__ClassName__)		 			{#__ClassName__, []() { return new __ClassName__(); } }

// Define
TDDTestCase gTestArray[] =
{
	ADD_CASE(TDDTest),
	ADD_CASE(TDDSample1),
	ADD_CASE(ExampleTest),
};

#endif
#endif