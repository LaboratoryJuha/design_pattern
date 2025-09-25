/* 새 구조에 맞춘 구현 */
#include "strategy.h"

/* 공통 로그 유틸 */
static void log_action(const char *who, const char *msg) {
    printf("[%s] %s\n", who, msg);
}

/* ================= TMap 구현 ================= */
static bool tmap_start(MapStrategy *self) {
    log_action(self->name, "Starting navigation.");
    return true;
}
static bool tmap_stop(MapStrategy *self) {
    log_action(self->name, "Stopping navigation.");
    return true;
}
static bool tmap_find(MapStrategy *self, const char *start, const char *end) {
    (void)self; 
    printf("[TMap] Finding route (AI augmented) from %s to %s...\n", start, end);
    return true;
}
static bool tmap_start_ai(TMapStrategy *self) {
    if (!self->ai_enabled) {
        self->ai_enabled = true;
        printf("[TMap] AI features enabled.\n");
    } else {
        printf("[TMap] AI already enabled.\n");
    }
    return true;
}
static bool tmap_stop_ai(TMapStrategy *self) {
    if (self->ai_enabled) {
        self->ai_enabled = false;
        printf("[TMap] AI features disabled.\n");
    } else {
        printf("[TMap] AI already disabled.\n");
    }
    return true;
}

MapStrategy *tmap_create(void) {
    TMapStrategy *impl = (TMapStrategy *)malloc(sizeof(*impl));
    if (!impl) return NULL;
    impl->base.name       = "TMap";
    impl->base.start      = tmap_start;
    impl->base.stop       = tmap_stop;
    impl->base.find_place = tmap_find;
    impl->ai_enabled      = false;
    impl->start_ai        = tmap_start_ai;
    impl->stop_ai         = tmap_stop_ai;
    return &impl->base;
}

/* ================= KakaoMap 구현 ================= */
static bool kakao_start(MapStrategy *self) {
    log_action(self->name, "Engine + messenger warm-up.");
    return true;
}
static bool kakao_stop(MapStrategy *self) {
    log_action(self->name, "Shutdown navigation + messenger sync.");
    return true;
}
static bool kakao_find(MapStrategy *self, const char *start, const char *end) {
    (void)self;
    printf("[KakaoMap] Calculating route from %s to %s...\n", start, end);
    return true;
}
static bool kakao_start_messenger(KakaoMapStrategy *self) {
    if (!self->messenger_enabled) {
        self->messenger_enabled = true;
        printf("[KakaoMap] Messenger service started.\n");
    } else {
        printf("[KakaoMap] Messenger already running.\n");
    }
    return true;
}
static bool kakao_stop_messenger(KakaoMapStrategy *self) {
    if (self->messenger_enabled) {
        self->messenger_enabled = false;
        printf("[KakaoMap] Messenger service stopped.\n");
    } else {
        printf("[KakaoMap] Messenger already stopped.\n");
    }
    return true;
}

MapStrategy *kakao_create(void) {
    KakaoMapStrategy *impl = (KakaoMapStrategy *)malloc(sizeof(*impl));
    if (!impl) return NULL;
    impl->base.name        = "KakaoMap";
    impl->base.start       = kakao_start;
    impl->base.stop        = kakao_stop;
    impl->base.find_place  = kakao_find;
    impl->messenger_enabled = false;
    impl->start_messenger   = kakao_start_messenger;
    impl->stop_messenger    = kakao_stop_messenger;
    return &impl->base;
}

int main(void) {
    MapApp *strategy = NULL;
    TMapStrategy *tmap = NULL;
    KakaoMapStrategy *kakao = NULL;

    strategy = tmap_create();
    if (!strategy) return 1;
    strategy->start(strategy);
    strategy->find_place(strategy, "A", "B");
    strategy->stop(strategy);

    tmap = as_tmap(strategy);
    if (tmap) {
        tmap->start_ai(tmap);
        tmap->stop_ai(tmap);
    }
    free(strategy); 

    strategy = kakao_create();
    if (!strategy) return 1;
    strategy->start(strategy);
    strategy->find_place(strategy, "C", "D");
    strategy->stop(strategy);

    kakao = as_kakao(strategy);
    if (kakao) {
        kakao->start_messenger(kakao);
        kakao->stop_messenger(kakao);
    }
    free(strategy);

    return 0;
}