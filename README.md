# CSE3030 - Introduction to Computer System Labs

서강대학교 컴퓨터공학과 CSE3030 컴퓨터시스템개론 실습 과제 모음입니다.

## 📚 Labs Overview

### Lab #1: Bit Lab
- **목적**: 비트 레벨 연산을 이용한 퍼즐 해결
- **주요 내용**: 
  - `bitMask(x)`: 32-x개의 0과 x개의 1로 구성된 마스크 생성
  - `absVal(x)`: 절댓값 계산 (조건문 없이)
  - `conditional(x, y, z)`: 삼항 연산자 구현 (조건문 없이)
- **제약사항**: `! ~ & ^ | + << >>` 연산자만 사용, 제어문 금지

### Lab #2: Reversing Lab
- **목적**: 어셈블리 코드 분석을 통한 역공학
- **주요 내용**: 
  - x86-64 어셈블리 코드 분석
  - GDB 디버거 사용법 학습
  - 프로그램의 입력 조건 역추적
- **도구**: GDB, Python 스크립트

### Lab #3: Cache Lab
- **목적**: 캐시 메모리 시뮬레이터 구현
- **주요 내용**:
  - **3-1**: 단일 레벨 캐시 시뮬레이터
  - **3-2**: 다중 레벨 캐시 시뮬레이터
- **핵심 개념**: LRU 교체 정책, 캐시 히트/미스 판정

## 🏗️ Project Structure

```
├── Lab01/
│   ├── 1-1/
│   │   └── bitMask.c          
│   ├── 1-2/
│   │   └── absVal.c           
│   └── 1-3/
│       └── conditional.c      
├── Lab02/
|   ├── report.pdf
│   ├── 2-1/
│   │   ├── problem1.c         
│   │   ├── problem1.bin       
│   │   └── solve1.py          
│   ├── 2-2/
│   │   ├── problem2.c
│   │   ├── problem2.bin       
│   │   └── solve2.py          
│   ├── 2-3/
│   │   ├── problem3.c
│   │   ├── problem3.bin       
│   │   └── solve3.py          
│   └── 2-4/
│       ├── problem4.c
│       ├── problem4.bin       
│       └── solve4.py          
└── Lab03/
    ├── 3-1/                   # Single-level Cache
    │   ├── single_cache.c
    │   ├── single_cache.h     
    │   └── types.h
    └── 3-2/                   # Multi-level Cache
        ├── multi_cache.c
        ├── multi_cache.h      
        ├── single_cache.c     
        ├── single_cache.h
        └── types.h
```

## 🛠️ Development Environment

- **언어**: C
- **컴파일러**: GCC
- **플랫폼**: Linux (cspro.sogang.ac.kr)
- **빌드 도구**: Make

## 🎯 학습 목표

1. **시스템 레벨 프로그래밍** 이해
2. **비트 연산과 어셈블리** 숙련도 향상  
3. **디버깅 도구 활용** 능력 배양
4. **캐시 메모리 시스템** 동작 원리 이해
5. **역공학 기법** 습득

---

**Course**: CSE3030 Introduction to Computer System  
**Instructor**: Prof. Jaeseung Choi  
**Institution**: Sogang University, Dept. of Computer Science and Engineering
