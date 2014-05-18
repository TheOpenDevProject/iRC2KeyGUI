#include "windowskeyboardsim.h"
#include <windows.h>

WindowsKeyboardSim::WindowsKeyboardSim()
{

}
void WindowsKeyboardSim::SendKey(int KeyCode){
      keybd_event(KeyCode, 0, 0, 0);
      ::Sleep(200);
      keybd_event(KeyCode, 0,KEYEVENTF_KEYUP, 0);
}
