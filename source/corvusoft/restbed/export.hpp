/*
 * Copyright 2022, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
    #define RESTBED_SHARED_EXPORT __declspec(dllexport)
    #define RESTBED_SHARED_IMPORT __declspec(dllimport)
#else
    #define RESTBED_SHARED_EXPORT __attribute__((visibility("default")))
    #define RESTBED_SHARED_IMPORT
#endif

#if !defined(RESTBED_STATIC)
    #if defined(RESTBED_BUILDING_DLL)
        #define RESTBED_EXPORT RESTBED_SHARED_EXPORT
    #else
        #define RESTBED_EXPORT RESTBED_SHARED_IMPORT
    #endif
#else
    #define RESTBED_EXPORT
#endif
