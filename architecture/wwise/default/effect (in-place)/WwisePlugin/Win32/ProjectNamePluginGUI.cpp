/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2025 Audiokinetic Inc.
*******************************************************************************/

#include "${name}PluginGUI.h"
#include "../resource.h"
#include <string>
//https://www.audiokinetic.com/en/public-library/2024.1.6_8842/?source=SDK&id=_g_u_i_windows_8h_ace7e697c1d8a310c9794cf05ce8ce1d8.html#ace7e697c1d8a310c9794cf05ce8ce1d8
AK_WWISE_PLUGIN_GUI_WINDOWS_BEGIN_POPULATE_TABLE(PropertyTable)
// AK_WWISE_PLUGIN_GUI_WINDOWS_POP_ITEM(IDC_STATIC_BARGRAPH, "chan_0")
AK_WWISE_PLUGIN_GUI_WINDOWS_END_POPULATE_TABLE()


${name}PluginGUI::${name}PluginGUI()
{
}

HINSTANCE ${name}PluginGUI::GetResourceHandle() const
{
  // https://www.audiokinetic.com/en/public-library/2024.1.6_8842/?source=SDK&id=plugin_frontend_windows.html#wwiseplugin_dialogcode
    AFX_MANAGE_STATE( AfxGetStaticModuleState() );
    return AfxGetStaticModuleState()->m_hCurrentResourceHandle;
}

bool ${name}PluginGUI::GetDialog( AK::Wwise::Plugin::eDialog in_eDialog, UINT & out_uiDialogID, AK::Wwise::Plugin::PopulateTableItem *& out_pTable ) const
{
  // https://www.audiokinetic.com/en/public-library/2024.1.6_8842/?source=SDK&id=plugin_frontend_windows.html#wwiseplugin_dialogcode
    AKASSERT( in_eDialog == AK::Wwise::Plugin::SettingsDialog );
    out_uiDialogID = IDD_WINDOW_BIG; //IDC_STATIC_BARGRAPH;
    out_pTable = PropertyTable;
    return true;
} 


bool ${name}PluginGUI::WindowProc(
    AK::Wwise::Plugin::eDialog in_eDialog,
    HWND in_hWnd,
    uint32_t in_message,
    WPARAM in_wParam,
    LPARAM in_lParam,
    LRESULT& out_lResult)
{
    switch (in_message)
    {

    case WM_INITDIALOG:
        <<FOREACHPARAM:IF io_type==output:${hwndVarName} = GetDlgItem(in_hWnd,${hwnd_IDCNAME});>>
        // m_hwndBargraphText = GetDlgItem(in_hWnd, IDC_STATIC_BARGRAPH);
        break;

    case WM_DESTROY:
        <<FOREACHPARAM:IF io_type==output:${hwndVarName} = nullptr;>>
        // m_hwndBargraphText = nullptr;
        break;
    }

    out_lResult = 0;
    return false;
}


void ${name}PluginGUI::NotifyMonitorData(
    AkTimeMs in_iTimeStamp,
    const AK::Wwise::Plugin::MonitorData* in_pMonitorDataArray,
    unsigned int in_uMonitorDataArraySize,
    bool in_bIsRealtime)
{
    if (in_uMonitorDataArraySize > 0 && in_pMonitorDataArray[0].pData && in_pMonitorDataArray[0].uDataSize == sizeof(float))
    {
        // show only the first one...
        float value;
        memcpy(&value, in_pMonitorDataArray[0].pData, sizeof(float));
        m_monitorValue = value;

        <<FOREACHPARAM:IF io_type==output:if (${hwndVarName}){wchar_t buffer[64];swprintf(buffer, 64, L"%.1f", m_monitorValue);SetWindowText(${hwndVarName}, buffer);}>>
        
        // if (m_hwndBargraphText)
        // {
        //     wchar_t buffer[64];
        //     swprintf(buffer, 64, L"%.1f", m_monitorValue);
        //     SetWindowText(m_hwndBargraphText, buffer);
        // }
    }
}



AK_ADD_PLUGIN_CLASS_TO_CONTAINER(
    ${name},            // Name of the plug-in container for this shared library
    ${name}PluginGUI,   // Authoring plug-in class to add to the plug-in container
    ${name}FX           // Corresponding Sound Engine plug-in class
);
