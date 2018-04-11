/**
 * rMod - Copyright (c) 2018 atom0s [atom0s@live.com]
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/ or send a letter to
 * Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
 *
 * By using rMod, you agree to the above license and its terms.
 *
 *      Attribution - You must give appropriate credit, provide a link to the license and indicate if changes were
 *                    made. You must do so in any reasonable manner, but not in any way that suggests the licensor
 *                    endorses you or your use.
 *
 *   Non-Commercial - You may not use the material (rMod) for commercial purposes.
 *
 *   No-Derivatives - If you remix, transform, or build upon the material (rMod), you may not distribute the
 *                    modified material. You are, however, allowed to submit the modified works back to the original
 *                    rMod project in attempt to have it added to the original project.
 *
 * You may not apply legal terms or technological measures that legally restrict others
 * from doing anything the license permits.
 *
 * No warranties are given.
 */

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppUnusedIncludeDirective

#ifndef __EXAMPLEPLUGIN_H_INCLUDED__
#define __EXAMPLEPLUGIN_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Windows.h>
#include "Z:/Gitlab/KoA-rMod/rMod/plugins/sdk/Plugin.h"

/**
 * Plugin Information Object
 */
plugininfo_t* g_PluginInfo = nullptr;

/**
 * Example Plugin Implementation
 *
 * This is the main class object that your plugin will expose back to rMod. rMod uses this class
 * to forward calls to your plugin allowing it to react and handle the various events.
 */
class ExamplePlugin : public IPlugin
{
    IHookCore*                  m_HookCore;
    uint32_t                    m_PluginId;
    IDirect3DDevice9*           m_Direct3DDevice;

public:
    ExamplePlugin(void);
    ~ExamplePlugin(void);

public:
    plugininfo_t GetPluginInfo(void) override;

public:
    bool Initialize(IHookCore* hookCore, const uint32_t pluginId) override;
    void Release(void) override;

public:
    bool HandleCommand(const char* command) override;
    bool HandleKeyboard(int32_t nCode, WPARAM wParam, LPARAM lParam, bool blocked) override;
    bool HandleMouse(int32_t nCode, WPARAM wParam, LPARAM lParam, bool blocked) override;

public:
    bool Direct3DInitialize(IDirect3DDevice9* lpDevice) override;
    void Direct3DRelease(void) override;
    void Direct3DPreReset(D3DPRESENT_PARAMETERS* pparams) override;
    void Direct3DPostReset(D3DPRESENT_PARAMETERS* pparams) override;
    void Direct3DBeginScene(void) override;
    void Direct3DEndScene(void) override;
    void Direct3DPrePresent(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion) override;
    void Direct3DPostPresent(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion) override;
};

#endif // __EXAMPLEPLUGIN_H_INCLUDED__