#include "bridge.h"

// ============================================================================
// TV DEVICE IMPLEMENTATION (구체적인 TV 구현)
// ============================================================================

static bool tv_is_on(Device* self) {
    return self->is_enabled;
}

static void tv_enable(Device* self) {
    self->is_enabled = true;
    printf("[%s] TV is now ON\n", self->name);
}

static void tv_disable(Device* self) {
    self->is_enabled = false;
    printf("[%s] TV is now OFF\n", self->name);
}

static int tv_get_volume(Device* self) {
    return self->volume;
}

static void tv_set_volume(Device* self, int percent) {
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;
    self->volume = percent;
    printf("[%s] TV volume set to %d%%\n", self->name, percent);
}

static int tv_get_channel(Device* self) {
    return self->channel;
}

static void tv_set_channel(Device* self, int channel) {
    if (channel < 1) channel = 1;
    if (channel > 999) channel = 999;
    self->channel = channel;
    printf("[%s] TV channel changed to %d\n", self->name, channel);
}

static void tv_print_status(Device* self) {
    printf("---- [%s] TV Status ----\n", self->name);
    printf("Power: %s\n", self->is_enabled ? "ON" : "OFF");
    printf("Volume: %d%%\n", self->volume);
    printf("Channel: %d\n", self->channel);
    printf("------------------------\n");
}

static void tv_destroy(Device* self) {
    printf("[%s] TV destroyed\n", self->name);
    free(self);
}

Device* create_tv_device(const char* name) {
    TVDevice* tv = malloc(sizeof(TVDevice));
    if (!tv) return NULL;
    
    // 기본 값 초기화
    tv->base.is_enabled = false;
    tv->base.volume = 30;
    tv->base.channel = 1;
    strncpy(tv->base.name, name, sizeof(tv->base.name) - 1);
    tv->base.name[sizeof(tv->base.name) - 1] = '\0';
    
    // 함수 포인터 설정 (TV 특화 구현)
    tv->base.is_on = tv_is_on;
    tv->base.enable = tv_enable;
    tv->base.disable = tv_disable;
    tv->base.get_volume = tv_get_volume;
    tv->base.set_volume = tv_set_volume;
    tv->base.get_channel = tv_get_channel;
    tv->base.set_channel = tv_set_channel;
    tv->base.print_status = tv_print_status;
    tv->base.destroy = tv_destroy;
    
    return (Device*)tv;
}

// ============================================================================
// RADIO DEVICE IMPLEMENTATION (구체적인 Radio 구현)
// ============================================================================

static void radio_enable(Device* self) {
    self->is_enabled = true;
    printf("[%s] Radio is now ON - Playing music ♪\n", self->name);
}

static void radio_disable(Device* self) {
    self->is_enabled = false;
    printf("[%s] Radio is now OFF - Silence...\n", self->name);
}

static void radio_set_volume(Device* self, int percent) {
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;
    self->volume = percent;
    printf("[%s] Radio volume set to %d%% ♪\n", self->name, percent);
}

static void radio_set_channel(Device* self, int channel) {
    if (channel < 88) channel = 88;
    if (channel > 108) channel = 108;
    self->channel = channel;
    printf("[%s] Radio tuned to %.1f FM\n", self->name, channel / 10.0);
}

static void radio_print_status(Device* self) {
    printf("---- [%s] Radio Status ----\n", self->name);
    printf("Power: %s\n", self->is_enabled ? "ON ♪" : "OFF");
    printf("Volume: %d%%\n", self->volume);
    printf("Frequency: %.1f FM\n", self->channel / 10.0);
    printf("---------------------------\n");
}

static void radio_destroy(Device* self) {
    printf("[%s] Radio destroyed\n", self->name);
    free(self);
}

Device* create_radio_device(const char* name) {
    RadioDevice* radio = malloc(sizeof(RadioDevice));
    if (!radio) return NULL;
    
    // 기본 값 초기화 (라디오 특화)
    radio->base.is_enabled = false;
    radio->base.volume = 50;
    radio->base.channel = 1000;  // 100.0 FM
    strncpy(radio->base.name, name, sizeof(radio->base.name) - 1);
    radio->base.name[sizeof(radio->base.name) - 1] = '\0';
    
    // 함수 포인터 설정 (일부는 TV와 동일, 일부는 Radio 특화)
    radio->base.is_on = tv_is_on;  // 동일한 로직 재사용
    radio->base.enable = radio_enable;  // Radio 특화
    radio->base.disable = radio_disable;  // Radio 특화
    radio->base.get_volume = tv_get_volume;  // 동일한 로직 재사용
    radio->base.set_volume = radio_set_volume;  // Radio 특화
    radio->base.get_channel = tv_get_channel;  // 동일한 로직 재사용
    radio->base.set_channel = radio_set_channel;  // Radio 특화
    radio->base.print_status = radio_print_status;  // Radio 특화
    radio->base.destroy = radio_destroy;
    
    return (Device*)radio;
}

// ============================================================================
// BASIC REMOTE CONTROL IMPLEMENTATION (기본 리모컨)
// ============================================================================

static void remote_toggle_power(RemoteControl* self) {
    if (self->device->is_on(self->device)) {
        self->device->disable(self->device);
    } else {
        self->device->enable(self->device);
    }
}

static void remote_volume_down(RemoteControl* self) {
    int current = self->device->get_volume(self->device);
    self->device->set_volume(self->device, current - 10);
}

static void remote_volume_up(RemoteControl* self) {
    int current = self->device->get_volume(self->device);
    self->device->set_volume(self->device, current + 10);
}

static void remote_channel_down(RemoteControl* self) {
    int current = self->device->get_channel(self->device);
    self->device->set_channel(self->device, current - 1);
}

static void remote_channel_up(RemoteControl* self) {
    int current = self->device->get_channel(self->device);
    self->device->set_channel(self->device, current + 1);
}

static void remote_destroy(RemoteControl* self) {
    free(self);
}

RemoteControl* create_remote_control(Device* device) {
    RemoteControl* remote = malloc(sizeof(RemoteControl));
    if (!remote) return NULL;
    
    remote->device = device;  // 브릿지 연결!
    
    remote->toggle_power = remote_toggle_power;
    remote->volume_down = remote_volume_down;
    remote->volume_up = remote_volume_up;
    remote->channel_down = remote_channel_down;
    remote->channel_up = remote_channel_up;
    remote->destroy = remote_destroy;
    
    return remote;
}

// ============================================================================
// ADVANCED REMOTE CONTROL IMPLEMENTATION (고급 리모컨)
// ============================================================================

static void advanced_mute(AdvancedRemoteControl* self) {
    printf("Advanced Remote: MUTE activated\n");
    self->base.device->set_volume(self->base.device, 0);
}

static void advanced_set_favorite(AdvancedRemoteControl* self, int channel) {
    if (self->favorite_count < 5) {  // 최대 5개
        self->favorite_channels[self->favorite_count] = channel;
        self->favorite_count++;
        printf("Advanced Remote: Channel %d added to favorites\n", channel);
    } else {
        printf("Advanced Remote: Favorite list is full!\n");
    }
}

static void advanced_switch_to_favorite(AdvancedRemoteControl* self, int index) {
    if (index < 0 || index >= self->favorite_count) {
        printf("Advanced Remote: Invalid favorite index\n");
        return;
    }
    
    int channel = self->favorite_channels[index];
    printf("Advanced Remote: Switching to favorite #%d\n", index + 1);
    self->base.device->set_channel(self->base.device, channel);
}

static void advanced_destroy(RemoteControl* self) {
    AdvancedRemoteControl* advanced = (AdvancedRemoteControl*)self;
    free(advanced->favorite_channels);
    free(advanced);
}

AdvancedRemoteControl* create_advanced_remote_control(Device* device) {
    AdvancedRemoteControl* remote = malloc(sizeof(AdvancedRemoteControl));
    if (!remote) return NULL;
    
    // 기본 리모컨 기능 초기화
    remote->base.device = device;  // 브릿지 연결!
    remote->base.toggle_power = remote_toggle_power;
    remote->base.volume_down = remote_volume_down;
    remote->base.volume_up = remote_volume_up;
    remote->base.channel_down = remote_channel_down;
    remote->base.channel_up = remote_channel_up;
    remote->base.destroy = advanced_destroy;  // 고급 리모컨 전용 소멸자
    
    // 고급 기능 초기화
    remote->favorite_channels = malloc(5 * sizeof(int));
    remote->favorite_count = 0;
    remote->mute = advanced_mute;
    remote->set_favorite = advanced_set_favorite;
    remote->switch_to_favorite = advanced_switch_to_favorite;
    
    return remote;
}

// ============================================================================
// DEMONSTRATION MAIN (브릿지 패턴 시연)
// ============================================================================

int main() {
    printf("=====================================\n");
    printf("   BRIDGE PATTERN DEMONSTRATION\n");
    printf("=====================================\n\n");
    
    // 1. 다양한 디바이스 생성
    printf("1. Creating devices...\n");
    Device* tv = create_tv_device("Samsung-TV");
    Device* radio = create_radio_device("Sony-Radio");
    printf("\n");
    

    // 2. 기본 리모컨으로 TV 제어
    printf("2. Basic Remote + TV:\n");
    RemoteControl* basic_tv_remote = create_remote_control(tv);
    basic_tv_remote->toggle_power(basic_tv_remote);
    basic_tv_remote->volume_up(basic_tv_remote);
    basic_tv_remote->volume_up(basic_tv_remote);
    basic_tv_remote->channel_up(basic_tv_remote);
    tv->print_status(tv);
    printf("\n");
    
    // 3. 고급 리모컨으로 TV 제어
    printf("3. Advanced Remote + TV:\n");
    AdvancedRemoteControl* advanced_tv_remote = create_advanced_remote_control(tv);
    advanced_tv_remote->set_favorite(advanced_tv_remote, 7);
    advanced_tv_remote->set_favorite(advanced_tv_remote, 11);
    advanced_tv_remote->switch_to_favorite(advanced_tv_remote, 0);
    advanced_tv_remote->mute(advanced_tv_remote);
    tv->print_status(tv);
    printf("\n");
    
    // 4. 같은 리모컨으로 다른 디바이스(라디오) 제어
    printf("4. Same Advanced Remote + Radio (Bridge Pattern Magic!):\n");
    AdvancedRemoteControl* advanced_radio_remote = create_advanced_remote_control(radio);
    advanced_radio_remote->base.toggle_power((RemoteControl*)advanced_radio_remote);
    advanced_radio_remote->base.volume_up((RemoteControl*)advanced_radio_remote);
    advanced_radio_remote->set_favorite(advanced_radio_remote, 955);  // 95.5 FM
    advanced_radio_remote->set_favorite(advanced_radio_remote, 1071); // 107.1 FM
    advanced_radio_remote->switch_to_favorite(advanced_radio_remote, 1);
    radio->print_status(radio);
    printf("\n");
    
    printf("=====================================\n");
    printf("브릿지 패턴의 핵심:\n");
    printf("1. 추상화(리모컨)와 구현(디바이스)이 분리됨\n");
    printf("2. 리모컨과 디바이스를 독립적으로 확장 가능\n");
    printf("3. 런타임에 구현을 바꿀 수 있음\n");
    printf("4. 하나의 추상화가 여러 구현을 지원\n");
    printf("=====================================\n");
    
    // 메모리 정리
    basic_tv_remote->destroy(basic_tv_remote);
    advanced_tv_remote->base.destroy((RemoteControl*)advanced_tv_remote);
    advanced_radio_remote->base.destroy((RemoteControl*)advanced_radio_remote);
    tv->destroy(tv);
    radio->destroy(radio);
    
    return 0;
}
