#pragma once

#define SINGLE(type) static const type* GetInstance() {static type mgr;return &mgr;}