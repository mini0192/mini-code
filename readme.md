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

## 조건문 (if)
"if" 명령어는 조건에 따라 특정 명령어는 실행하거나 실행하지 않게 하는 제어문 입니다. 조건이 참(true)일 때만 명령어가 실행됩니다. 조건이 거짓(false)일 경우 명령어는 실행되지 않습니다.

### 기본 예제
```
next out "Hello if!" if false
```
위의 예제에서는 if false가 붙어 있으므로 "Hello if!" 라는 문자열은 출력되지 않습니다.

```
next out "Hello if!" if true
```
위의 예제에서는 if true가 붙어 있으므로 "test" 라는 문자열은 출력됩니다.

## 실행 조건의 세부 사항
"if" 문의 조건은 특히 이 언어에서는 조건이 0보다 클 때만 명령어가 실행된다는 점을 이해하는 것이 중요합니다. 조건이 0(false)이거나 0보다 작을 경우, 명령어는 실행되지 않습니다. 반대로 1(true)이거나 1보다 클 경우 명령어는 실행됩니다. 이를 통해 if 문이 어떤 상황에서 명령어를 실행하는지 명확하게 알 수 있습니다.

## 심화 예제
### 예제 1: 조건이 양수일 때
```
num data1 10
num data2 5
next out "data1 is greater than data2" if data1 - data2
```
위의 예제에서는 data1이 data2 보다 크므로 "data1 is greater than data2"가 출력됩니다.
이는 data1 - data2가 양수(0보다 큼)이기 때문입니다.

### 예제 2: 조건이 음수일 때
```
num data1 3
num data2 7
next out "data1 is less than data2" if data1 - data2
```
위의 예제에서는 data1이 data2 보다 작으므로, 조건이 거짓이 되어 "data1 is less than data2"가 출력되지 않습니다.

### 예제 3: 같은 값을 비교할 때
```
num data1 10
num data2 10
next out "data1 is equal to data2" if data1 == data2
```
위의 예제에서는 data1과 data2가 같으므로 "data1 is equal to data2"가 출력됩니다.
이는 value1 == value2는 1(true)이기 때문입니다.

## 실습 예제
```
out "Enter a number: "
num input in

next out "The number is greater than 10." if input - 10
next out "The number is 10." if input == 10
next out "The number is less than 10." if 10 - input
```
이 프로그램은 사용자가 입력한 숫자에 따라 적절한 메시지를 출력합니다.

### 예시 출력 결과
사용자가 15를 입력했을 때
```
Enter a number: 15
The number is greater than 10.
```

사용자가 10을 입력했을 때
```
Enter a number: 10
The number is 10.
```

사용자가 5를 입력했을 때
```
Enter a number: 5
The number is less than 10.
```