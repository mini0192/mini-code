# MINI CODE

Mini는 간단하고 직관적인 프로그래밍 언어입니다.

이 언어는 인터프리터 형식으로 동작하며,

.mini 확장자를 가진 파일을 읽어 해석하고 실행합니다.

Mini는 배우기 쉬운 문법과 구문을 제공하여, 프로그래밍을 처음 접하는 사람들에게 적합한 선택이 될 수 있습니다.

## 실행 방법(윈도우 기준)
1. minicode를 gcc로 컴파일 해줍니다
```
gcc minicode.c -o minicode
```
2. ./minicode.exe 파일명으로 프로그램을 실행합니다
```
./minicode.exe test.mini
```

## 문법

### 변수 선언
```
var data 30
```
변수명은 영어로만 구성되어야 하며, 자료형은 따로 지정해 주지 않습니다.

### 출력
#### 문자열 출력
```
out "print"
```
> 출력 값: print

#### 변수 출력
```
var data 30
out data
```
> 출력 값: 3

### 연산
```
var data 30
out data + 30
```
> 출력 값: 60