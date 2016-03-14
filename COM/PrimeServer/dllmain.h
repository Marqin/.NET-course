// dllmain.h : Declaration of module class.

class CPrimeServerModule : public ATL::CAtlDllModuleT< CPrimeServerModule >
{
public :
	DECLARE_LIBID(LIBID_PrimeServerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PRIMESERVER, "{92AB9BE1-48EC-4223-A8C7-843FE6D4E883}")
};

extern class CPrimeServerModule _AtlModule;
