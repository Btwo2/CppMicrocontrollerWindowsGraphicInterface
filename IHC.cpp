#include "IHC.h"

#include <windows.h>

#define ESPERA 500

bool IHC::escFoiPressionado() {
  // https://msdn.microsoft.com/pt-br/library/windows/desktop/ms646293(v=vs.85).aspx
  // http://www.gnu.org/software/libc/manual/html_node/Character-Input.html

  // Codigo especifico para o windows
  return GetAsyncKeyState(VK_ESCAPE);
}

void IHC::sleep() {
  // Codigo especifico para o windows
  Sleep (ESPERA);
}

IHC::IHC() {
}
