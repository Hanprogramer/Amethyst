/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <mc/src/common/AppPlatformListener.hpp>

class IMinecraftApp;
class Minecraft;
class ServerNetworkSystem;
class GameCallbacks;
class LoopbackPacketSender;
class Timer;
class Scheduler;
class EducationOptions;
class LevelStorage;

namespace Core {
	class StorageAreaStateListener;
};

class ServerInstance : public Bedrock::EnableNonOwnerReferences, public AppPlatformListener, public GameCallbacks, Core::StorageAreaStateListener {
public:
	std::chrono::steady_clock::time_point mLastSyncTime;
	IMinecraftApp const& mApp;
	std::unique_ptr<Minecraft> mMinecraft;
	std::unique_ptr<ServerNetworkSystem> mNetwork;
	std::unique_ptr<LoopbackPacketSender> mPacketSender;
	std::unique_ptr<Timer> mSimTimer;
	std::unique_ptr<Timer> mRealTimer;
	std::unique_ptr<Scheduler> mScheduler;
	std::unique_ptr<EducationOptions> mEducationOptions;
	LevelStorage* mStorage;
	std::atomic<bool> mInUpdate;
	std::atomic<int> mWriteRefCounter;
	std::atomic<bool> mThreadShouldJoin;
private:
	char pad[0x1BF];
public:
	std::string mLevelId;
	std::string mServerName;

public:
	/// @sig {40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B DA 48 89 54 24 ? 8B 81 ? ? ? ? 90 83 F8 ? 74}
	MC void _threadSafeExecute(std::function<void()> func);

	/// @sig {48 89 5C 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 48 C7 44 24 ? ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 54 24 ? 48 8B CB E8 ? ? ? ? 90}
	MC void queueForServerThread(std::function<void()> func);
};