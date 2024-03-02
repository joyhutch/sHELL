
#include "../include/sHELL.h"
#include "errhandlingapi.h"
#include <windows.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

const char Name[] = "download";
const char Help[] =
    "Download a file from a specified URL to the local filesystem.\n"
    "Usage:\n"
    "    download <URL> <local file path>";

InternalAPI *core = NULL;

LPVOID lpOut = NULL;
__declspec(dllexport) VOID CommandCleanup() {
  if (lpOut) {
    core->free(lpOut);
    lpOut = NULL;
  }
}
// initialization code
__declspec(dllexport) BOOL CommandInit(InternalAPI *lpCore) { 
  core = lpCore; 
  return TRUE;
}

// Exported function - Name
__declspec(dllexport) const char *CommandNameA() { return Name; }

// Exported function - Help
__declspec(dllexport) const char *CommandHelpA() { return Help; }

// Exported function - Run
__declspec(dllexport) LPVOID CommandRunA(int argc, char **argv) {
  if (argc != 3) {
    core->wprintf(L"Invalid arguments.\n%S", CommandHelpA());
    return (LPVOID)1; // Error code for invalid arguments
  }
  
  const char *url = argv[1];
  const char *localFilePath = argv[2];

  HRESULT hResult = URLDownloadToFileA(NULL, url, localFilePath, 0, NULL);
  if (FAILED(hResult)) {
    debug_wprintf(L"[!] Failed to download URL. Error code: %08X\n", hResult);
    return NULL;
  }

  debug_wprintf(L"[!] success!\n");
  return (LPVOID)1; // Sucess 
}

// Entrypoint for the DLL
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  switch (fdwReason) {
  case DLL_PROCESS_ATTACH:
    // Code to run when the DLL is loaded
    break;
  case DLL_PROCESS_DETACH:
    // Code to run when the DLL is unloaded
    break;
  case DLL_THREAD_ATTACH:
    // Code to run when a thread is created during DLL's existence
    break;
  case DLL_THREAD_DETACH:
    // Code to run when a thread ends normally
    break;
  }
  return TRUE; // Successful
}
