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

#include "ExamplePlugin.h"

/**
 * Constructor and Deconstructor
 */
ExamplePlugin::ExamplePlugin(void)
    : m_HookCore(nullptr)
    , m_PluginId(0)
    , m_Direct3DDevice(nullptr)
{ }
ExamplePlugin::~ExamplePlugin(void)
{ }

/**
 * Returns the plugins information structure.
 *
 * @returns {plugininfo_t} The plugin information structure.
 *
 * @notes
 *
 *      This structure contains the information about your plugin that the rMod
 *      plugin manager will use to display your plugins info in things such as
 *      the loaded list of plugins.
 */
plugininfo_t ExamplePlugin::GetPluginInfo(void)
{
    return (*g_PluginInfo);
}

/**
 * Invoked when the plugin is loaded, allowing it to prepare for usage.
 *
 * @param {IHookCore*} hookCore - The core hook object instsance.
 * @param {uint32_t} pluginId - The id of the plugin.
 * @returns {bool} True on success, false otherwise.
 *
 * @notes
 *
 *      Plugins must return true here otherwise, the plugin will be considered invalid
 *      or errored and will not be loaded. You can use this to begin preparing your
 *      plugin for usage, checking if what is required is available, etc.
 */
bool ExamplePlugin::Initialize(IHookCore* hookCore, const uint32_t pluginId)
{
    this->m_HookCore = hookCore;
    this->m_PluginId = pluginId;

    this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin was loaded");

    return true;
}

/**
 * Invoked when the plugin is unloaded, allowing it to cleanup its resources.
 *
 * @notes
 *
 *      Plugins can use this call to cleanup any of their resources before it is fully
 *      unloaded from the plugin manager.
 */
void ExamplePlugin::Release(void)
{
    this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin was unloaded");
}

/**
 * Invoked when the plugin is given a chance to handle a console command.
 *
 * @param {const char*} command - The console command currently being handled.
 * @returns {bool} True on success, false otherwise.
 *
 * @notes
 *
 *      Plugins can handle and block console commands from being further processed here by
 *      returning true. If your plugin does react to a command seen here, it should return
 *      true to prevent other plugins from seeing the command or having it still be sent to
 *      the rMod console and seen as an invalid command.
 */
bool ExamplePlugin::HandleCommand(const char* command)
{
    // Obtain the command arguments..
    std::vector<std::string> args;
    const auto count = Atomic::Commands::GetCommandArgs(command, &args);

    // Handle the /test command..
    HANDLECOMMAND("/test")
    {
        this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin handled the /test command!");
        return true;
    }

    // Handle the /foo command with sub-arguments..
    HANDLECOMMAND("/foo")
    {
        if (count >= 2 && args[1] == "on")
        {
            this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin handled the /foo on command!");
            return true;
        }
        if (count >= 2 && args[1] == "off")
        {
            this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin handled the /foo off command!");
            return true;
        }

        return true;
    }

    return false;
}

/**
 * Invoked when a keyboard event occurs. (WH_KEYBOARD event callback.)
 *
 * @param {int32_t} nCode - The code of the event.
 * @param {WPARAM} wParam - The wParam of the event.
 * @param {LPARAM} lParam - The lParam of the event.
 * @param {bool} blocked - Flag set if the event has been blocked already by another plugin.
 * @returns {bool} True if handled, false otherwise.
 *
 * @notes
 *
 *      Plugins can handle and block keyboard events from being sent to the game here by
 *      returning true. This allows you to handle personal/custom actions with your plugin
 *      if you wish to.
 *
 *      If block is set to true, this means that an addon or another plugin has already processed
 *      the event and is blocking it from being returned. You can still react to it yourself if
 *      you wish but if block is already true, returning false will not unblock it.
 */
bool ExamplePlugin::HandleKeyboard(int32_t nCode, WPARAM wParam, LPARAM lParam, bool blocked)
{
    // Ignore the event if it was already blocked..
    if (blocked)
        return blocked;

    // Block the L key from being pressed/released..
    if (wParam == 0x4C)
    {
        this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin saw and blocked a key event for the L key!");
        return true;
    }

    return false;
}

/**
 * Invoked when a mouse event occurs. (WH_MOUSE event callback.)
 *
 * @param {int32_t} nCode - The code of the event.
 * @param {WPARAM} wParam - The wParam of the event.
 * @param {LPARAM} lParam - The lParam of the event.
 * @param {bool} blocked - Flag set if the event has been blocked already by another plugin.
 * @returns {bool} True if handled, false otherwise.
 *
 * @notes
 *
 *      Plugins can handle and block mouse events from being sent to the game here by
 *      returning true. This allows you to handle personal/custom actions with your plugin
 *      if you wish to.
 *
 *      If block is set to true, this means that an addon or another plugin has already processed
 *      the event and is blocking it from being returned. You can still react to it yourself if
 *      you wish but if block is already true, returning false will not unblock it.
 */
bool ExamplePlugin::HandleMouse(int32_t nCode, WPARAM wParam, LPARAM lParam, bool blocked)
{
    // Ignore the event if it was already blocked..
    if (blocked)
        return blocked;

    // Block all mouse down and up events..
    if (wParam == 513 || wParam == 514)
    {
        this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin saw and blocked a mouse down or up event!");
        return true;
    }

    return false;
}

/**
 * Invoked when the plugin is initialized for Direct3D.
 *
 * @param {IDirect3DDevice9*} lpDevice - The Direct3D device.
 * @returns {bool} True if the plugin wants to receive D3D events, false otherwise.
 *
 * @notes
 *
 *      Plugins are informed when the Direct3D device is ready for use with this event. This
 *      event is also handled to optimize callbacks by allowing your plugin to opt-out of
 *      future Direct3D calls.
 *
 *      If you return true in this function, that means that you do wish to receive other
 *      Direct3D related calls in your plugin. If you return false, this means you are opting
 *      out of future calls and will not see any other Direct3D related calls.
 *
 *      If your plugin does not need to use any other Direct3D related calls, such as
 *      Direct3DBeginscene/Direct3DEndScene and so on, you should return false to help
 *      optimize the speed of callbacks in the rMod plugin manager.
 */
bool ExamplePlugin::Direct3DInitialize(IDirect3DDevice9* lpDevice)
{
    this->m_Direct3DDevice = lpDevice;

    this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin was told the Direct3D device initialized!");
    return true;
}

/**
 * Invoked when the plugin is being unloaded and is asked to cleanup its Direct3D related resources.
 *
 * @notes
 *
 *      Plugins can use this callback to cleanup any Direct3D related resources that they created.
 *      This is called both when your plugin is unload, but also if the Direct3D device is ever
 *      destroyed and recreated.
 */
void ExamplePlugin::Direct3DRelease(void)
{
    this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin was told the Direct3D device was released!");
}

/**
 * Invoked when the Direct3D device is being reset. (pre)
 *
 * @param {D3DPRESENT_PARAMS*} pparams - The present params of the device.
 *
 * @notes
 *
 *      Plugins are informed when the Direct3D device is being reset. This callback is invoked
 *      just before the real reset call happens. Allowing you to invalidate and cleanup your
 *      custom objects.
 *
 *      Plugins will only see this message if they returned true in Direct3DInitialize.
 */
void ExamplePlugin::Direct3DPreReset(D3DPRESENT_PARAMETERS* pparams)
{
    this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin was told the Direct3D device is about to reset!");
}

/**
 * Invoked when the Direct3D device is being reset. (post)
 *
 * @param {D3DPRESENT_PARAMS*} pparams - The present params of the device.
 *
 * @notes
 *
 *      Plugins are informed when the Direct3D device is being reset. This callback is invoked
 *      just after the real reset call happens. Allowing you to recreate your custom objects.
 *
 *      Plugins will only see this message if they returned true in Direct3DInitialize.
 */
void ExamplePlugin::Direct3DPostReset(D3DPRESENT_PARAMETERS* pparams)
{
    this->m_HookCore->GetConsole()->Write(D3DCOLOR_ARGB(255, 175, 255, 0), "ExamplePlugin was told the Direct3D device has reset!");
}

/**
 * Invoked when the Direct3D device begins a scene.
 *
 * @notes
 *
 *      Plugins are informed when the Direct3D device is starting a new scene.
 *
 *      Reckoning calls BeginScene/EndScene multiple times per scene due to how it renders various
 *      parts of the game world. If you need to handle custom drawing, it is recommended to do
 *      any custom drawing within the Present calls instead.
 *
 *      Plugins will only see this message if they returned true in Direct3DInitialize.
 */
void ExamplePlugin::Direct3DBeginScene(void)
{
}

/**
 * Invoked when the Direct3D device ends a scene.
 *
 * @notes
 *
 *      Plugins are informed when the Direct3D device is ending a scene.
 *
 *      Reckoning calls BeginScene/EndScene multiple times per scene due to how it renders various
 *      parts of the game world. If you need to handle custom drawing, it is recommended to do
 *      any custom drawing within the Present calls instead.
 *
 *      Plugins will only see this message if they returned true in Direct3DInitialize.
 */
void ExamplePlugin::Direct3DEndScene(void)
{
}

/**
 * Invoked when the Direct3D device presents a scene. (pre)
 *
 * @param {RECT*} pSourceRect - The source rect to present from.
 * @param {RECT*} pDestRect - The dest rect to present to.
 * @param {HWND} hDestWindowOverride - The window handle to present into.
 * @param {RGNDATA*} pDirtyRegion - The dirty region.
 *
 * @notes
 *
 *      Plugins are informed when the Direct3D device is presenting a scene. This callback is
 *      invoked just before a Present call happens. Custom rendering from your plugin should
 *      happen here if you wish to draw over the entire scene.
 *
 *      Plugins will only see this message if they returned true in Direct3DInitialize.
 */
void ExamplePlugin::Direct3DPrePresent(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
}

/**
 * Invoked when the Direct3D device presents a scene. (post)
 *
 * @param {RECT*} pSourceRect - The source rect to present from.
 * @param {RECT*} pDestRect - The dest rect to present to.
 * @param {HWND} hDestWindowOverride - The window handle to present into.
 * @param {RGNDATA*} pDirtyRegion - The dirty region.
 *
 * @notes
 *
 *      Plugins are informed when the Direct3D device is presenting a scene. This callback is
 *      invoked just after a Present call happens.
 *
 *      Plugins will only see this message if they returned true in Direct3DInitialize.
 */
void ExamplePlugin::Direct3DPostPresent(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
}

/**
 * Returns the interface version this plugin was compiled against.
 *
 * @returns {double} The plugin interface version.
 *
 * @notes
 *
 *      The HOOK_INTERFACE_VERSION macro is defined in the Plugin.h header file of the rMod
 *      plugin SDK. You should not alter this at all and just return the predefined macro.
 *
 *      When an update happens that may cause the interface to increment this value, it will
 *      help show what plugins are out of date and need to be recompiled against the new SDK.
 */
__declspec(dllexport) double __stdcall GetInterfaceVersion(void)
{
    return HOOK_INTERFACE_VERSION;
}

/**
 * Creates and populates the plugin information structure.
 *
 * @param {plugininfo_t*} info - The information pointer to hold this plugins info.
 *
 * @notes
 *
 *      The rMod plugin manager calls this exported function to obtain information about your plugin.
 *      The 'info' parameter is created by the plugin manager within rMod and should not be
 *      deleted by your plugin. rMod will cleanup the object itself when your plugin is unloaded!
 *
 */
__declspec(dllexport) void __stdcall CreatePluginInfo(plugininfo_t* info)
{
    // Store the plugin information pointer..
    g_PluginInfo = info;

    // Populate the structure with the plugins information..
    strcpy_s(info->Author, sizeof(info->Author), "atom0s");
    strcpy_s(info->Name, sizeof(info->Name), "ExamplePlugin");
    info->InterfaceVersion = HOOK_INTERFACE_VERSION;
    info->PluginVersion = 1.0f;
    info->Priority = 0;
}

/**
 * Returns an instance of the plugins main class.
 *
 * @returns {IPlugin*} Instance of this plugins main class.
 *
 * @notes
 *
 *      The rMod plugin manager calls this exported function to obtain the class instance of your
 *      plugin to be used for all the above callback functions. Your plugin must return a valid
 *      plugin class here that inherits from IPlugin.
 */
__declspec(dllexport) IPlugin* __stdcall CreatePlugin(void)
{
    return (IPlugin*)new ExamplePlugin();
}