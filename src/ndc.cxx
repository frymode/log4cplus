// Module:  Log4CPLUS
// File:    ndc.cxx
// Created: 6/2001
// Author:  Tad E. Smith
//
//
// Copyright (C) Tad E. Smith  All rights reserved.
//
// This software is published under the terms of the Apache Software
// License version 1.1, a copy of which has been included with this
// distribution in the LICENSE.APL file.
//

#include <log4cplus/ndc.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/pointer.h>
#include <log4cplus/internal/internal.h>
#include <exception>

using namespace log4cplus;
using namespace log4cplus::helpers;



///////////////////////////////////////////////////////////////////////////////
// public methods
///////////////////////////////////////////////////////////////////////////////

NDC& 
log4cplus::getNDC()
{
    static NDC singleton;
    return singleton;
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::DiagnosticContext ctors
///////////////////////////////////////////////////////////////////////////////

DiagnosticContext::DiagnosticContext(const log4cplus::tstring& message, DiagnosticContext* parent)
 : message(message),
   fullMessage( (  (parent == NULL) 
                 ? message 
                 : parent->fullMessage + LOG4CPLUS_TEXT(" ") + message) )
{
}


DiagnosticContext::DiagnosticContext(const log4cplus::tstring& message)
 : message(message),
   fullMessage(message)
{
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::NDC ctor and dtor
///////////////////////////////////////////////////////////////////////////////

NDC::NDC() 
{ }


NDC::~NDC() 
{ }



///////////////////////////////////////////////////////////////////////////////
// log4cplus::NDC public methods
///////////////////////////////////////////////////////////////////////////////

void
NDC::clear()
{
    try {
        DiagnosticContextStack* ptr = getPtr();
        DiagnosticContextStack ().swap (*ptr);
    }
    catch(std::exception& e) {
        getLogLog().error(  LOG4CPLUS_TEXT("NDC::clear()- exception occured: ") 
                          + LOG4CPLUS_C_STR_TO_TSTRING(e.what()));
    }
    catch(...) {
        getLogLog().error(LOG4CPLUS_TEXT("NDC::clear()- exception occured"));
    }
}


DiagnosticContextStack
NDC::cloneStack() const
{
    try {
        DiagnosticContextStack* ptr = getPtr();
        return DiagnosticContextStack(*ptr);
    }
    catch(std::exception& e) {
        getLogLog().error(  LOG4CPLUS_TEXT("NDC::cloneStack()- exception occured: ") 
                          + LOG4CPLUS_C_STR_TO_TSTRING(e.what()));
    }
    catch(...) {
        getLogLog().error(LOG4CPLUS_TEXT("NDC::cloneStack()- exception occured"));
    }

    return DiagnosticContextStack();
}


void 
NDC::inherit(const DiagnosticContextStack& stack)
{
    try {
        DiagnosticContextStack* ptr = getPtr();
        DiagnosticContextStack (stack).swap (*ptr);
    }
    catch(std::exception& e) {
        getLogLog().error(  LOG4CPLUS_TEXT("NDC::inherit()- exception occured: ") 
                          + LOG4CPLUS_C_STR_TO_TSTRING(e.what()));
    }
    catch(...) {
        getLogLog().error(LOG4CPLUS_TEXT("NDC::inherit()- exception occured"));
    }
}


log4cplus::tstring const &
NDC::get() const
{
    try {
        DiagnosticContextStack* ptr = getPtr();
        if(!ptr->empty())
            return ptr->back().fullMessage;
    }
    catch(std::exception& e) {
        getLogLog().error(  LOG4CPLUS_TEXT("NDC::get()- exception occured: ") 
                          + LOG4CPLUS_C_STR_TO_TSTRING(e.what()));
    }
    catch(...) {
        getLogLog().error(LOG4CPLUS_TEXT("NDC::get()- exception occured"));
    }

    return log4cplus::internal::empty_str;
}


size_t 
NDC::getDepth() const
{
    try {
        DiagnosticContextStack* ptr = getPtr();
        return ptr->size();
    }
    catch(std::exception& e) {
        getLogLog().error(  LOG4CPLUS_TEXT("NDC::getDepth()- exception occured: ") 
                          + LOG4CPLUS_C_STR_TO_TSTRING(e.what()));
    }
    catch(...) {
        getLogLog().error(LOG4CPLUS_TEXT("NDC::getDepth()- exception occured"));
    }

    return 0;
}


log4cplus::tstring 
NDC::pop()
{
    try {
        DiagnosticContextStack* ptr = getPtr();
        if(!ptr->empty())
        {
            DiagnosticContext dc = ptr->back();
            ptr->pop_back();
            return dc.message;
        }
    }
    catch(std::exception& e) {
        getLogLog().error(  LOG4CPLUS_TEXT("NDC::pop()- exception occured: ") 
                          + LOG4CPLUS_C_STR_TO_TSTRING(e.what()));
    }
    catch(...) {
        getLogLog().error(LOG4CPLUS_TEXT("NDC::pop()- exception occured"));
    }

    return LOG4CPLUS_TEXT("");
}


log4cplus::tstring const &
NDC::peek() const
{
    try {
        DiagnosticContextStack* ptr = getPtr();
        if(!ptr->empty())
            return ptr->back().message;
    }
    catch(std::exception& e) {
        getLogLog().error(  LOG4CPLUS_TEXT("NDC::peek()- exception occured: ") 
                          + LOG4CPLUS_C_STR_TO_TSTRING(e.what()));
    }
    catch(...) {
        getLogLog().error(LOG4CPLUS_TEXT("NDC::peek()- exception occured"));
    }

    return log4cplus::internal::empty_str;
}


void 
NDC::push(const log4cplus::tstring& message)
{
    try {
        DiagnosticContextStack* ptr = getPtr();
        if(ptr->empty())
            ptr->push_back( DiagnosticContext(message, NULL) );
        else {
            DiagnosticContext dc = ptr->back();
            ptr->push_back( DiagnosticContext(message, &dc) );
        }
    }
    catch(std::exception& e) {
        getLogLog().error(  LOG4CPLUS_TEXT("NDC::push()- exception occured: ") 
                          + LOG4CPLUS_C_STR_TO_TSTRING(e.what()));
    }
    catch(...) {
        getLogLog().error(LOG4CPLUS_TEXT("NDC::push()- exception occured"));
    }
}


void 
NDC::remove()
{
    try {
        DiagnosticContextStack* ptr = getPtr();
        DiagnosticContextStack ().swap (*ptr);
    }
    catch(std::exception& e) {
        getLogLog().error(  LOG4CPLUS_TEXT("NDC::remove()- exception occured: ") 
                          + LOG4CPLUS_C_STR_TO_TSTRING(e.what()));
    }
    catch(...) {
        getLogLog().error(LOG4CPLUS_TEXT("NDC::remove()- exception occured"));
    }
}


void 
NDC::setMaxDepth(size_t maxDepth)
{
    try {
        DiagnosticContextStack* ptr = getPtr();
        while(maxDepth < ptr->size())
            ptr->pop_back();
    }
    catch(std::exception& e) {
        getLogLog().error(  LOG4CPLUS_TEXT("NDC::setMaxDepth()- exception occured: ") 
                          + LOG4CPLUS_C_STR_TO_TSTRING(e.what()));
    }
    catch(...) {
        getLogLog().error(LOG4CPLUS_TEXT("NDC::setMaxDepth()- exception occured"));
    }
}


DiagnosticContextStack* NDC::getPtr() const
{
    internal::per_thread_data * ptd = internal::get_ptd ();
    return &ptd->ndc_dcs;
}


//
//
//

NDCContextCreator::NDCContextCreator(const log4cplus::tstring& msg) 
{ 
    getNDC().push(msg); 
}


NDCContextCreator::~NDCContextCreator() 
{ 
    getNDC().pop(); 
}