#ifndef BRIDGE_H
#define BRIDGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
브릿지 패턴: 범용 리모컨 시스템

ABSTRACTION (리모컨 기능 계층):
  RemoteControl -> AdvancedRemoteControl -> VoiceRemoteControl
         |
         | (브릿지: 어떤 디바이스든 제어 가능!)
         ↓  
IMPLEMENTATION (디바이스 플랫폼 계층):
  Device -> TVDevice, RadioDevice, SmartSpeakerDevice

목표: 하나의 리모컨으로 모든 디바이스를 제어!
*/

// ============================================================================
// IMPLEMENTATION SIDE (구현부 - 다양한 디바이스들)
// ============================================================================

// 디바이스 인터페이스 (구현부의 기본 인터페이스)
typedef struct Device {
    bool is_enabled;
    int volume;
    int channel;
    char name[32];
    
    // 가상 함수들 (함수 포인터로 구현)
    bool (*is_on)(struct Device* self);
    void (*enable)(struct Device* self);
    void (*disable)(struct Device* self);
    int (*get_volume)(struct Device* self);
    void (*set_volume)(struct Device* self, int percent);
    int (*get_channel)(struct Device* self);
    void (*set_channel)(struct Device* self, int channel);
    void (*print_status)(struct Device* self);
    void (*destroy)(struct Device* self);
} Device;

// 구체적인 디바이스들
typedef struct {
    Device base;
    // 모니터 색상 설정 특화 필드
    int color_temperature;
    // TV 특화 필드들 추가 가능
} TVDevice;

typedef struct {
    Device base;
    // 라디오 주파수 설정 특화 필드
    float frequency;
    // Radio 특화 필드들 추가 가능
} RadioDevice;

// ============================================================================
// ABSTRACTION SIDE (추상화부 - 다양한 리모컨들)
// ============================================================================

// 기본 리모컨 (추상화의 기본 클래스)
typedef struct RemoteControl {
    Device* device;  // 브릿지! 구현부와 연결하는 다리
    
    void (*toggle_power)(struct RemoteControl* self);
    void (*volume_down)(struct RemoteControl* self);
    void (*volume_up)(struct RemoteControl* self);
    void (*channel_down)(struct RemoteControl* self);
    void (*channel_up)(struct RemoteControl* self);
    void (*destroy)(struct RemoteControl* self);
} RemoteControl;

// 고급 리모컨 전방 선언
typedef struct AdvancedRemoteControl AdvancedRemoteControl;

// 고급 리모컨 (추상화 확장)
struct AdvancedRemoteControl {
    RemoteControl base;
    int* favorite_channels;
    int favorite_count;
    
    void (*mute)(AdvancedRemoteControl* self);
    void (*set_favorite)(AdvancedRemoteControl* self, int channel);
    void (*switch_to_favorite)(AdvancedRemoteControl* self, int index);
};

// ============================================================================
// 팩토리 함수들
// ============================================================================

// 디바이스 생성
Device* create_tv_device(const char* name);
Device* create_radio_device(const char* name);

// 리모컨 생성
RemoteControl* create_remote_control(Device* device);
AdvancedRemoteControl* create_advanced_remote_control(Device* device);

#endif // BRIDGE_H