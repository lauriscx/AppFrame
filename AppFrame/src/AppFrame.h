#pragma once

/* Module system */
#include "Core/ModuleSystem/Module.h"
#include "Core/ModuleSystem/ModuleRegistry.h"

#include "Application/Modules/Window/ModuleWindow.h"
#include "Application/Modules/Console/ModuleConsole.h"
#include "Application/Modules/GUI/ModuleIMGUI.h"
#include "Application/Modules/Sound/SoundModule.h"
#include "Application/Modules/Sound/ResourceSound.h"
#include "Application/Modules/Sound/SoundSource.h"

/* Virtual file system */
#include "Core/FileSystem/File.h"
#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/VFS/MountPoints/ARFMountPoint.h"
#include "Core/FileSystem/VFS/MountPoints/CloudMountPoint.h"
#include "Core/FileSystem/VFS/MountPoints/MountPoint.h"
#include "Core/FileSystem/VFS/MountPoints/PhysicalMountPoint.h"
#include "Core/FileSystem/VFS/MountPoints/RAMMountPoint.h"

/* Event system */
#include "Core/EventSystem/Event.h"
#include "Core/EventSystem/EventHandler.h"
#include "Core/EventSystem/EventManager.h"

#include "Application/Events/AppEvents.h"
#include "Application/Events/EventTypes.h"

/* Input system */
#include "Core/InputSystem/InputData.h"
#include "Core/InputSystem/InputHandler.h"
#include "Core/InputSystem/InputManager.h"

/* Multithreading */
#include "Core/MultiThreading/TaskManager.h"
#include "Core/MultiThreading/Thread.h"

/* Resource manager */
#include "Core/ResourceManager/Resource.h"
#include "Core/ResourceManager/ResourceManager.h"

/* Application stuff */
#include "Core/Asserts.h"
#include "Core/Memory/Memory.h"
#include "Core/Memory/DataTypes.h"
#include "Core/Utils/Timer.h"
#include "Core/UUID/UUID.h"
#include "Core/XML/XML.h"
#include "Application/Application.h"