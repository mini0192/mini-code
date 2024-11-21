# MINI CODE

Mini는 간단하고 직관적인 프로그래밍 언어입니다.

이 언어는 인터프리터 형식으로 동작하며,

.mini 확장자를 가진 파일을 읽어 해석하고 실행합니다.

Mini는 배우기 쉬운 문법과 구문을 제공하여, 프로그래밍을 처음 접하는 사람들에게 적합한 선택이 될 수 있습니다.

## 실행 방법(윈도우 기준)
1. minicode를 gcc로 컴파일 해줍니다
```
gcc minicode.c
```
2. ./minicode.exe 파일명으로 프로그램을 실행합니다
```
./a.exe test.mini
```

## 문법

### 변수
#### 변수 선언
```
num data1 30
str data2 "it is str"
bool data3 true
```
변수의 자료형은 num, str, bool이 있습니다.

> num: 숫자 저장,

> str: 문자열 저장,

> bool: true, false를 저장 
#### 변수 수정
```
num data 30
data 20
```
#### 변수에 입력
```
var data in
```

### 출력
#### 문자열 출력
```
out "it is print"
```
> 출력 값: it is print

#### 변수 출력
```
str data "it is just test"
out data
```
> 출력 값: it is just test

### 연산
```
out 20 + 30
```
> 출력 값: 50

연산은 기본적으로 한번에 하나를 연산하는 것을 권장합니다.