# MINI CODE

MINI CODE는 수학적인 표현을 최소화 하고 직관적인 예약어를 사용하여 처음 개발을 시작하는 사용자들이 프로그래밍의 깊은 이해를 할 수 있도록 설계된 프로그래밍 언어입니다.
이 언어는 사용자와 상호작용하고, 데이터를 처리하며, 조건부로 명령을 실행할 수 있도록 도와줍니다.
MINI CODE는 사용자들이 프로그래밍의 기본 개념을 명확히 이해할 수 있도록 설계되었습니다.

## 주요 특징
- **직관적인 예약어:** 이해하기 쉬운 예약어를 사용하여 프로그래밍의 기본 개념을 쉽게 배울 수 있습니다.
- **명확한 조건문(if):**  조건문을 통해 명령어의 실행 여부를 제어하며, 조건이 0보다 큰 경우에만 명령이 실행되는 명확한 규칙을 가지고 있습니다.
- **유연한 함수 정의:** 특정 작업을 반복적으로 수행할 수 있게 하는 함수 기능을 제공하며, 매개변수를 활용해 다양한 연산을 수행할 수 있습니다.
- **개발의 깊은 이해:** 프로그래밍의 기본 원리를 이해하고, 복잡한 문제를 해결하는 능력을 기를 수 있습니다.



# 실행 방법(윈도우 기준)
1. minicode.c 파일을 c++로 컴파일 합니다.
```
c++ minicode.cpp
```
2. 컴파일된 minicode.cpp 파일을 실행합니다.
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



## 조건(if)
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

### 실행 조건의 세부 사항
"if" 문의 조건은 특히 이 언어에서는 조건이 0보다 클 때만 명령어가 실행된다는 점을 이해하는 것이 중요합니다. 조건이 0(false)이거나 0보다 작을 경우, 명령어는 실행되지 않습니다. 반대로 1(true)이거나 1보다 클 경우 명령어는 실행됩니다. 이를 통해 if 문이 어떤 상황에서 명령어를 실행하는지 명확하게 알 수 있습니다.

### 심화 예제
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

### 실습 예제
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


## 함수(function)
함수는 특정 작업을 수행하는 명령어 블록입니다. 이 언어에서 함수는 function 키워드로 시작하며 parameter 키워드로 매개변수 구역의 끝을 나타냅니다. 함수는 done 키워드를 통해 종료됩니다. stop 명령어는 중간에 함수 실행을 멈추고 값을 반환할 때 사용되지만, 필수는 아닙니다.

### 함수 정의
```
function add
    num data1
    num data2
    parameter

    stop data1 + data2
done
```
함수는 두개의 숫자 data1과 data2를 매개변수로 받아, 이들의 합을 반환합니다.

### 함수 호출 및 출력
```
next out call add 3 5
```
이 명령어는 add 함수를 호출하고, 3과 5를 매개변수로 전달하여 결과를 출력합니다. 최종적으로 8이 출력됩니다.

### 함수의 구조 설명
1. 함수 시작(function add)
- function 키워드로 함수 정의가 시작됩니다.
- add 는 함수의 이름입니다.

2. 매개변수 정의
- **num data1:** 첫 번째 매개변수로 숫자형 data1을 선언합니다.
- **num data2:** 두 번째 매개변수로 숫자형 data2를 선언합니다.
- **parameter:** 매개변수 구역의 끝을 나타냅니다 매개변수가 없어도 반드시 사용해야 합니다.

3. 함수 본문
- **stop daata1 + data2:** 함수의 실행을 중지하고, data1과 data2의 합을 반환합니다.

4. 함수 끝(done)
- 함수 정의가 끝났음을 나타냅니다. stop 명령어 없이도 done을 만나면 함수가 종료 됩니다.

### 매개변수가 없는 함수
```
function greet
    parameter
    next out "Hello, World!"
done

call greet
```
이 예제는 greet 라는 이름의 함수를 정의하며, 매개변수가 없고 "Hello, World!"를 출력합니다.

### 실습 예제
```
function print
    num data
    parameter
    stop 0 if data == 10
    next out "Good"
done

call print in
```
이 프로그램은 사용자가 입력한 숫자에 따라 조건에 맞춰 "Good"을 출력합니다. 함수는 10이 아닌 숫자가 입력되었을 때만 "Good"을 출력합니다.

### 예시 출력 결과
사용자가 10을 입력했을 때
```
10
```
이 경우 아무것도 출력되지 않습니다.

사용자가 5를 입력했을 때
```
5
Good
```
이처럼 함수를 통해 다양한 조건을 확인하고, 그에 맞게 출력 결과를 다르게 할 수 있습니다.