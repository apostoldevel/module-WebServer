/*++

Program name:

  Apostol Web Service

Module Name:

  WebServer.cpp

Notices:

  Module: Web Server

Author:

  Copyright (c) Prepodobny Alen

  mailto: alienufo@inbox.ru
  mailto: ufocomp@gmail.com

--*/

//----------------------------------------------------------------------------------------------------------------------

#include "Core.hpp"
#include "WebServer.hpp"
//----------------------------------------------------------------------------------------------------------------------

extern "C++" {

namespace Apostol {

    namespace Module {

        //--------------------------------------------------------------------------------------------------------------

        //-- CWebServer ------------------------------------------------------------------------------------------------

        //--------------------------------------------------------------------------------------------------------------

        CWebServer::CWebServer(CModuleProcess *AProcess) : CApostolModule(AProcess, "web server", "module/WebServer") {
            m_Headers.Add("Authorization");

            CWebServer::InitMethods();
        }
        //--------------------------------------------------------------------------------------------------------------

        void CWebServer::InitMethods() {
#if defined(_GLIBCXX_RELEASE) && (_GLIBCXX_RELEASE >= 9)
            m_Methods.AddObject(_T("GET")    , (CObject *) new CMethodHandler(true , [this](auto && Connection) { DoGet(Connection); }));
            m_Methods.AddObject(_T("OPTIONS"), (CObject *) new CMethodHandler(true , [this](auto && Connection) { DoOptions(Connection); }));
            m_Methods.AddObject(_T("HEAD")   , (CObject *) new CMethodHandler(true , [this](auto && Connection) { DoHead(Connection); }));
            m_Methods.AddObject(_T("POST")   , (CObject *) new CMethodHandler(false, [this](auto && Connection) { MethodNotAllowed(Connection); }));
            m_Methods.AddObject(_T("PUT")    , (CObject *) new CMethodHandler(false, [this](auto && Connection) { MethodNotAllowed(Connection); }));
            m_Methods.AddObject(_T("DELETE") , (CObject *) new CMethodHandler(false, [this](auto && Connection) { MethodNotAllowed(Connection); }));
            m_Methods.AddObject(_T("TRACE")  , (CObject *) new CMethodHandler(false, [this](auto && Connection) { MethodNotAllowed(Connection); }));
            m_Methods.AddObject(_T("PATCH")  , (CObject *) new CMethodHandler(false, [this](auto && Connection) { MethodNotAllowed(Connection); }));
            m_Methods.AddObject(_T("CONNECT"), (CObject *) new CMethodHandler(false, [this](auto && Connection) { MethodNotAllowed(Connection); }));
#else
            m_Methods.AddObject(_T("GET")    , (CObject *) new CMethodHandler(true, std::bind(&CWebServer::DoGet, this, _1)));
            m_Methods.AddObject(_T("OPTIONS"), (CObject *) new CMethodHandler(true, std::bind(&CWebServer::DoOptions, this, _1)));
            m_Methods.AddObject(_T("HEAD")   , (CObject *) new CMethodHandler(true, std::bind(&CWebServer::DoHead, this, _1)));
            m_Methods.AddObject(_T("POST")   , (CObject *) new CMethodHandler(false, std::bind(&CWebServer::MethodNotAllowed, this, _1)));
            m_Methods.AddObject(_T("PUT")    , (CObject *) new CMethodHandler(false, std::bind(&CWebServer::MethodNotAllowed, this, _1)));
            m_Methods.AddObject(_T("DELETE") , (CObject *) new CMethodHandler(false, std::bind(&CWebServer::MethodNotAllowed, this, _1)));
            m_Methods.AddObject(_T("TRACE")  , (CObject *) new CMethodHandler(false, std::bind(&CWebServer::MethodNotAllowed, this, _1)));
            m_Methods.AddObject(_T("PATCH")  , (CObject *) new CMethodHandler(false, std::bind(&CWebServer::MethodNotAllowed, this, _1)));
            m_Methods.AddObject(_T("CONNECT"), (CObject *) new CMethodHandler(false, std::bind(&CWebServer::MethodNotAllowed, this, _1)));
#endif
        }
        //--------------------------------------------------------------------------------------------------------------

        void CWebServer::DoGet(CHTTPServerConnection *AConnection) {

            const auto &caRequest = AConnection->Request();

            CString sPath(caRequest.Location.pathname);

            // Request path must be absolute and not contain "..".
            if (sPath.empty() || sPath.front() != '/' || sPath.find(_T("..")) != CString::npos) {
                AConnection->SendStockReply(CHTTPReply::bad_request);
                return;
            }

            CStringList TryFiles;
            if (sPath.SubString(0, 7) == _T("/oauth/")) {
                TryFiles.Add("/oauth/index.html");
            }

            TryFiles.Add("/index.html");

            SendResource(AConnection, sPath, nullptr, false, TryFiles);
        }
        //--------------------------------------------------------------------------------------------------------------

        bool CWebServer::Enabled() {
            if (m_ModuleStatus == msUnknown)
                m_ModuleStatus = Config()->IniFile().ReadBool(SectionName().c_str(), "enable", true) ? msEnabled : msDisabled;
            return m_ModuleStatus == msEnabled;
        }
        //--------------------------------------------------------------------------------------------------------------
    }
}
}