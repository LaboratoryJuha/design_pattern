#ifndef STRATEGY_H
#define STRATEGY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct MapStrategy {
	const char *name;
	bool (*start)(struct MapStrategy *self);
	bool (*stop)(struct MapStrategy *self);
	bool (*find_place)(struct MapStrategy *self, const char *start, const char *end);
} MapStrategy;

/* TMap 구체 전략 */
typedef struct TMapStrategy {
	MapStrategy base; /* 첫 멤버: 업캐스트 안전 */
	bool ai_enabled;
	bool (*start_ai)(struct TMapStrategy *self);
	bool (*stop_ai)(struct TMapStrategy *self);
} TMapStrategy;

/* KakaoMap 구체 전략 */
typedef struct KakaoMapStrategy {
	MapStrategy base;
	bool messenger_enabled;
	bool (*start_messenger)(struct KakaoMapStrategy *self);
	bool (*stop_messenger)(struct KakaoMapStrategy *self);
} KakaoMapStrategy;

/* 공용 타입 별칭 */
typedef MapStrategy MapApp;

/* 생성자 */
MapStrategy *tmap_create(void);
MapStrategy *kakao_create(void);

/* 안전 다운캐스트 헬퍼 */
static inline TMapStrategy *as_tmap(MapStrategy *m) {
	return (m && m->name && strcmp(m->name, "TMap") == 0) ? (TMapStrategy *)m : NULL;
}
static inline KakaoMapStrategy *as_kakao(MapStrategy *m) {
	return (m && m->name && strcmp(m->name, "KakaoMap") == 0) ? (KakaoMapStrategy *)m : NULL;
}

#endif 