LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/lighting/Effect.cpp \
                   ../../../Classes/lighting/EffectSprite.cpp \
                   ../../../Classes/lighting/LightEffect.cpp \
                   ../../../Classes/SpriteSystem.cpp \
                   ../../../Classes/AnimationSystem.cpp \
                   ../../../Classes/GameStateManager.cpp \
                   ../../../Classes/KeyboardManager.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/SpriteLoader.cpp \
                   ../../../Classes/AnimationLoader.cpp \
                   ../../../Classes/ParticleLoader.cpp \
                   ../../../Classes/CollisionManager.cpp \
                   ../../../Classes/AIBase.cpp \
                   ../../../Classes/AIEnemy.cpp \
                   ../../../Classes/GameObject.cpp \
                   ../../../Classes/InteractableGameObject.cpp \
                   ../../../Classes/PhysicsGameObject.cpp \
                   ../../../Classes/Enemy.cpp \
                   ../../../Classes/Player.cpp \
                   ../../../Classes/GameObjectManager.cpp \
                   ../../../Classes/CameraController.cpp \
                   ../../../Classes/EffectTileMap.cpp \
                   ../../../Classes/FileOperation.cpp \
                   ../../../Classes/FollowWithLerp.cpp \
                   ../../../Classes/GUILayer.cpp \
                   ../../../Classes/PauseLayer.cpp \
                   ../../../Classes/EffectTileLayer.cpp \
                   ../../../Classes/WonOrGameoverLayer.cpp \
                   ../../../Classes/HelloWorldScene.cpp \
                   ../../../Classes/InGameScene.cpp \
                   ../../../Classes/MainMenuScene.cpp \
                   ../../../Classes/StoreScene.cpp \
                   ../../../Classes/TilemapManager.cpp \
                   ../../../Classes/SoundLoader.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
