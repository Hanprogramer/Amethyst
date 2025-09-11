#include "hooks/Hooks.hpp"
#include <amethyst/runtime/events/RenderingEvents.hpp>
#include <minecraft/src/common/world/level/block/definition/BlockDefinitionGroup.hpp>
#include <amethyst/runtime/events/RegisterEvents.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>
#include <minecraft/src-client/common/client/renderer/screen/MinecraftUIRenderContext.hpp>

SafetyHookInline _ScreenView_setupAndRender;
SafetyHookInline _ClientInstance_onStartJoinGame;
SafetyHookInline _ClientInstance_requestLeaveGame;
SafetyHookInline _Minecraft_update;
SafetyHookInline _VanillaItems_registerItems;
SafetyHookInline _BlockDefinitionGroup_registerBlocks;
SafetyHookInline _LevelRenderer_renderLevel;
SafetyHookInline _ClientInstance__ClientInstance;
SafetyHookInline _BlockGraphics_initBlocks;

void ScreenView_setupAndRender(ScreenView* self, MinecraftUIRenderContext* ctx)
{
    Amethyst::EventBus* eventBus = AmethystRuntime::getEventBus();
    BeforeRenderUIEvent ev(*self, *ctx);
    eventBus->Invoke(ev);

    _ScreenView_setupAndRender.call(self, ctx);

    AfterRenderUIEvent afterEv(*self, *ctx);
    eventBus->Invoke(afterEv);
}


int64_t ClientInstance_onStartJoinGame(ClientInstance* self, int64_t a2, int64_t a3, uint64_t a4)
{
    OnStartJoinGameEvent event(*self);
    AmethystRuntime::getEventBus()->Invoke(event);
    AmethystRuntime::getContext()->mIsInWorldOrLoading = true;
    return _ClientInstance_onStartJoinGame.call<int64_t, ClientInstance*, int64_t, int64_t, uint64_t>(self, a2, a3, a4);
}

void ClientInstance_requestLeaveGame(ClientInstance* self, char switchScreen, char sync)
{
    OnRequestLeaveGameEvent event(*self);
    AmethystRuntime::getEventBus()->Invoke(event);
    AmethystRuntime::getContext()->mIsInWorldOrLoading = false;
    _ClientInstance_requestLeaveGame.thiscall(self, switchScreen, sync);
}

BOOL Minecraft_update(Minecraft* self)
{
    BOOL value = _Minecraft_update.call<BOOL, Minecraft*>(self);

    UpdateEvent event(*self);
    AmethystRuntime::getEventBus()->Invoke(event);

    return value;
}

void VanillaItems_registerItems(
    void* a1,
    const ItemRegistryRef* itemRegistry,
    const BaseGameVersion* baseGameVersion,
    const Experiments* experiments) 
{
    // Allow Vanilla to register its own items first
    _VanillaItems_registerItems.fastcall(a1, itemRegistry, baseGameVersion, experiments);

    //std::shared_ptr<ItemRegistry> registry = itemRegistry.mItemRegistry.lock();
    ItemRegistry* registry = itemRegistry->mItemRegistry.lock().get();
    RegisterItemsEvent event(*registry);
    AmethystRuntime::getEventBus()->Invoke(event);
}

void BlockDefinitionGroup_registerBlocks(BlockDefinitionGroup* self) {
    RegisterBlocksEvent event(*self);
    AmethystRuntime::getEventBus()->Invoke(event);
    _BlockDefinitionGroup_registerBlocks.thiscall<void>(self);
}

void LevelEvent(Level* level) {
    if (level == nullptr) {
        OnLevelDestroyedEvent event;
        AmethystRuntime::getEventBus()->Invoke(event);
        return;
    }

    OnLevelConstructedEvent event(*level);
    AmethystRuntime::getEventBus()->Invoke(event);
}

void* ClientInstance__ClientInstance(ClientInstance* self, uint64_t a2, uint64_t a3, uint64_t a4, char a5, void* a6, void* a7, uint64_t a8, void* a9) {
    void* ret = _ClientInstance__ClientInstance.call<void*>(self, a2, a3, a4, a5, a6, a7, a8, a9);

    AmethystRuntime::getContext()->mClientInstance = self;

    return ret;
}

SafetyHookInline _Minecraft__Minecraft;

Minecraft* Minecraft__Minecraft(Minecraft* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10, char a11, void* a12, void* a13, void* a14, void* a15) {
    _Minecraft__Minecraft.call<Minecraft*>(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    AmethystContext* ctx = AmethystRuntime::getContext();
    
    if (ctx->mClientMinecraft == nullptr) {
        ctx->mClientMinecraft = a1;
    }
    else {
        ctx->mServerMinecraft = a1;
    }

    auto context = Bedrock::PubSub::SubscriptionContext::makeDefaultContext("Amethyst LevelEvent Subscriber");
    a1->mLevelSubscribers->_connectInternal(LevelEvent, Bedrock::PubSub::ConnectPosition::AtFront, std::move(context), std::nullopt);

    return a1;
}

void BlockGraphics_initBlocks(ResourcePackManager& resources, const Experiments& experiments) {
    _BlockGraphics_initBlocks.call<void, ResourcePackManager&, const Experiments&>(resources, experiments);

    InitBlockGraphicsEvent event(resources, experiments);
    AmethystRuntime::getEventBus()->Invoke(event);
}

void CreateModFunctionHooks() {
    Amethyst::HookManager* hooks = AmethystRuntime::getHookManager();

    // HOOK(ScreenView, setupAndRender);
    // HOOK(Minecraft, update);
    // HOOK(ClientInstance, onStartJoinGame);
    // HOOK(ClientInstance, requestLeaveGame);
    // HOOK(ClientInstance, _ClientInstance);
    // HOOK(VanillaItems, registerItems);
    // HOOK(BlockDefinitionGroup, registerBlocks);
    // HOOK(BlockGraphics, initBlocks);
    // HOOK(Minecraft, _Minecraft);
}