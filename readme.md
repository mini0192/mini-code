# MINI CODE

Mini는 간단하고 직관적인 프로그래밍 언어입니다.

이 언어는 인터프리터 형식으로 동작하며,

.mini 확장자를 가진 파일을 읽어 해석하고 실행합니다.

Mini는 배우기 쉬운 문법과 구문을 제공하여, 프로그래밍을 처음 접하는 사람들에게 적합한 선택이 될 수 있습니다.

# 실행 방법(윈도우 기준)
1. minicode를 gcc로 컴파일 해줍니다
```
gcc minicode.c
```
2. ./minicode.exe 파일명으로 프로그램을 실행합니다
```
./a.exe test.mini
```

# 문법

## 변수 선언 및 자료형
- **num:** 숫자 데이터를 저장합니다.
- **str:** 문자열 데이터를 저장합니다.
- **bool:** 논리값을 저장합니다(true 혹은 false).

## 기본 예제
```
num data1 30
str data2 "it is str"
bool data3 true
```
## 동작 설명
### 변수 선언과 임시 저장
- **num data1 30:** data1 이라는 이름의 숫자 변수에 숫자 30을 할당하고, 이를 변수 영역에 저장합니다. 
- **str data2 "it is str":** data2 라는 이름의 문자열 변수에 문자열 "it is str"을 할당하고, 이를 변수 영역에 저장합니다.
- **bool data3 true:** data3 이라는 논리 변수에 true를 할당하고, 이를 변수 영역에 저장합니다.



## 출력(out)
"out" 명령어는 화면에 출력하는 역할을 합니다. 이 명령어는 정보를 사용자에게 전달하거나, 사용자와 상호작용하는 데 사용되는 기본적인 도구입니다.

### 기본 예제
```
out "Hello, World!"
```
위의 예제에서는 문자열 "Hello World!"를 화면에 출력합니다.

### 고급 예제
```
str greeting "Hello "
str name "Mini"
str punctuation "!"

out greeting
out name
out punctuation
```
위의 예제에서는 여러개의 문자열 변수를 출력합니다. 각 변수는 따로 출력되며 출력된 결과는 "Hello Mini!"가 됩니다.

## 개행(next)
"next" 명령어는 출력을 할 때 줄을 바꾸는, 즉 개행을 수행하는 역할을 합니다. 이를 통해 새로운 줄에서 출력을 시작할 수 있습니다.

### 기본 예제
```
out "Hello, World!"
next
out "This is a new line."
```
위의 예제에서는 "Hello, World!"를 출력한 후 줄을 바꿔 "This is a new line."을 출력합니다.

출력 결과는 다음과 같습니다
```
Hello, World!
This is a new line.
```

### 고급 예제
```
next out "Hello, World!"
next out "This is a new line."
```
위의 예제에서는 각 문장이 출력된 후 줄을 바꿉니다.

출력 결과는 다음과 같습니다.
```
Hello, World!
This is a new line.
```

## 입력(in)
"in" 명령어는 사용자로부터 데이터를 입력받아 변수에 저장하는 기능을 합니다. 이를 통해 프로그램이 사용자와 상호작용할 수 있습니다.

### 기본 예제
```
num age in
```
위의 예제에서는 사용자로부터 숫자를 입력 받아 age 변수에 저장합니다.
```
str name in
```
위의 예제에서는 사용자로부터 문자열을 입력 받아 name 변수에 저장합니다.

### 고급 예제
```
out "Enter your name: "
str name in

out "Enter your age: "
num age in


out "Hello "
out name
out "!"
next 

out "You are "
out age
out ", years old."
```
위의 예제에서는 사용자로 부터 이름과 나이를 입력 받고, 입력 받은 이름과 나이로 인사 메시지를 출력합니다.
```
Enter your name: mini
Enter your age: 20
Hello mini!
You are 20, years old.
```
